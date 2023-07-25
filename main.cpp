#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>
using namespace std;

// ----- Function Declarations ----- //

int searchStudents(string program, int semester, int rollNo);
int searchTeachers(int id);
bool userExists(string username);

// ----- Aesthetic & Utility Functions ----- //

string toupperstr(string text) {
  for (int i = 0; i < text.length(); i++)
    text[i] = toupper(text[i]);
  return text;
}

void setColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

void printHeader(string text) {
  system("cls");

  setColor(9);
  cout << "# ----- ";
  setColor(7);

  for (int i = 0; i < text.length(); i++) {
    if (text[i] == '>') {
      setColor(9);
      cout << text[i];
      setColor(7);
    } else if (text[i] == '[') {
      setColor(10);
      cout << text[i];
    } else if (text[i] == ']') {
      cout << text[i];
      setColor(7);
    } else {
      cout << text[i];
    }
  }

  setColor(9);
  cout << " ----- #\n\n";
  setColor(7);
}

void printSuccess(string text) {
  setColor(10);
  cout << text;
  setColor(7);
}

void printWarning(string text) {
  setColor(14);
  cout << text;
  setColor(7);
}

void printError(string text) {
  setColor(12);
  cout << text;
  setColor(7);
}

// ----- Classes & Structs ----- //

class User {
protected:
  static int userCount;
  static char activeUserType;
  static int activeUserIndex;
  static string activeUserUsername;

  string username;
  string password;
  string firstName;
  string lastName;
  string contactNo;
  string city;

  bool lengthCheck(string text, int lenMin, int lenMax) {
    if (text.length() < lenMin || text.length() > lenMax)
      return false;
    else
      return true;
  }

public:
  User(bool incrementCount) {
    if (incrementCount)
      ++userCount;
  }

  User(string un,
       string pw,
       string fN,
       string lN,
       string cN,
       string ct) {
    ++userCount;
    username = un;
    password = pw;
    firstName = fN;
    lastName = lN;
    contactNo = cN;
    city = ct;
  }

  // ----- Change Password Function ----- //
  void changePassword() {
    string pwVerify, pwNew, pwConfirm;

    do {
      cout << "Enter current password: ";
      cin >> pwVerify;

      if (pwVerify == password)
        break;
      else
        printError("Incorrect password!\n\n");
    } while (true);

    do {
      cout << "Enter new password: ";
      cin >> pwNew;
      cout << "Confirm password: ";
      cin >> pwConfirm;

      if (pwNew == pwConfirm)
        break;
      else
        printError("Passwords do no match\n\n");
    } while (true);

    password = pwNew;
  }

  // ----- Setters ----- //
  static void setUserCount(int uC) { userCount = uC; }
  static void setActiveUserType(char aUT) { activeUserType = aUT; }
  static void setActiveUserIndex(int aUI) { activeUserIndex = aUI; }
  static void setActiveUserUsername(string aUUn) { activeUserUsername = aUUn; }

  // ----- Getters ----- //
  static int getUserCount() { return userCount; }
  static char getActiveUserType() { return activeUserType; }
  static int getActiveUserIndex() { return activeUserIndex; }
  static string getActiveUserUsername() { return activeUserUsername; }

  string getUsername() { return username; }
  string getPassword() { return password; }
  string getFirstName() { return firstName; }
  string getLastName() { return lastName; }
  string getContactNumber() { return contactNo; }
  string getCity() { return city; }

  // ----- Input Setters ----- //
  void inputUsername() {
    string newUsername;
    bool goodLength, validUsername;

    do {
      do {
        cout << "Enter username: ";
        cin >> newUsername;

        goodLength = lengthCheck(newUsername, 4, 20);

        validUsername = true;
        for (int i = 0; i < newUsername.length(); i++)
          if ((newUsername[i] < 'A' || newUsername[i] > 'Z') && (newUsername[i] < 'a' || newUsername[i] > 'z') && (newUsername[i] < '0' || newUsername[i] > '9'))
            validUsername = false;

        if (!goodLength)
          printError("Username should be between 4 & 20 characters\n");
        if (!validUsername)
          printError("Only letters and numbers are allowed in the username\n");
        if (!goodLength || !validUsername)
          cout << endl;
      } while (!goodLength || !validUsername);

      if (newUsername == username)
        break;
      else if (userExists(newUsername))
        printError("A record with this username already exits!\n\n");
      else
        break;
    } while (true);

    username = newUsername;
  }

  void inputPassword() {
    do {
      cout << "Enter password: ";
      cin >> password;
      if (lengthCheck(password, 8, 32))
        break;
      else
        printError("Password should be between 8 & 32 characters\n\n");
    } while (true);
  }

  void inputFirstName() {
    cout << "Enter first name: ";
    cin >> firstName;
  }

  void inputLastName() {
    cout << "Enter last name: ";
    cin >> lastName;
  }

  void inputContactNumber() {
    bool goodLength, validNumber;

    do {
      cout << "Enter contact number: ";
      cin >> contactNo;

      goodLength = lengthCheck(contactNo, 7, 15);

      validNumber = true;
      for (int i = 0; i < contactNo.length(); i++)
        if (contactNo[i] < '0' || contactNo[i] > '9')
          validNumber = false;

      if (!goodLength)
        printError("Length should be between 7 & 15\n");
      if (!validNumber)
        printError("Only numbers are allowed\n");
      if (!goodLength || !validNumber)
        cout << endl;
    } while (!goodLength || !validNumber);
  }

  void inputCity() {
    cout << "Enter city: ";
    cin >> city;
  }

  void inputData() {
    inputUsername();
    inputPassword();
    inputFirstName();
    inputLastName();
    inputContactNumber();
    inputCity();
  }
};

class Admin : public User {
private:
  static int adminCount;
  bool superAdmin;

public:
  Admin(bool incrementCount) : User(incrementCount) {
    if (incrementCount)
      ++adminCount;
  }

  Admin(string un,
        string pw,
        string fN,
        string lN,
        string cN,
        string ct,
        bool sA = false) : User(un, pw, fN, lN, cN, ct) {
    ++adminCount;
    superAdmin = sA;
  }

  // ----- Operator Overload  ----- //
  bool operator<(Admin &next) {
    if (superAdmin > next.superAdmin)
      return true;
    if (superAdmin == next.superAdmin && username < next.username)
      return true;
  }

  // ----- Setters  ----- //
  static void setAdminCount(int aC) { adminCount = aC; }

  // ----- Getters ----- //
  static int getAdminCount() { return adminCount; }
  bool getSuperAdminStatus() { return superAdmin; }

  // ----- Input Setters ----- //
  void inputSuperAdminStatus() {
    char input;

    do {
      cout << "Set status to super admin? (y/n): ";
      cin >> input;
      input = tolower(input);

      if (input == 'y') {
        superAdmin = true;
        break;
      } else if (input == 'n') {
        superAdmin = false;
        break;
      } else {
        printError("Invalid input!\n\n");
      }
    } while (true);
  }

  void inputData() {
    User::inputData();
    inputSuperAdminStatus();
  }
};

struct Subject {
  Subject() : code("-"), attendance(-1), gpa(-1) {}
  string code;
  int attendance;
  float gpa;
};

class Student : public User {
private:
  static int studentCount;
  string program;
  int semester;
  int rollNo;
  string studentID;
  float semesterGPA;
  int noOfSubjects;
  vector<Subject> subjects;

  string offeredPrograms[5] = {"BSAI", "BSCS", "BSDS", "BSGM", "BSSE"};

  void createStudentID() {
    studentID = program + "-SM" + to_string(semester) + "-" + to_string(rollNo);
  }

public:
  Student(bool incrementCount) : User(incrementCount) {
    if (incrementCount)
      ++studentCount;
  }

  Student(string un,
          string pw,
          string fN,
          string lN,
          string cN,
          string ct,
          string p,
          int s,
          int rN,
          string sID,
          float sGPA,
          int nOS,
          vector<Subject> sbj) : User(un, pw, fN, lN, cN, ct) {
    ++studentCount;
    program = p;
    semester = s;
    rollNo = rN;
    studentID = sID;
    semesterGPA = sGPA;
    noOfSubjects = nOS;
    subjects = sbj;
  }

  // ----- Operator Overload  ----- //
  bool operator<(Student &next) {
    if (program < next.program)
      return true;
    if (program == next.program && semester < next.semester)
      return true;
    if (program == next.program && semester == next.semester && rollNo < next.rollNo)
      return true;
  }

  // ----- Setters ----- //
  static void setStudentCount(int sC) { studentCount = sC; }

  // ----- Getters ----- //
  static int getStudentCount() { return studentCount; }
  string getProgram() { return program; }
  int getSemester() { return semester; }
  int getRollNo() { return rollNo; }
  string getStudentID() { return studentID; }

  float getSemesterGPA() {
    float sum = 0;
    for (int i = 0; i < noOfSubjects; i++) {
      if (subjects[i].gpa == -1) {
        semesterGPA = -1;
        return semesterGPA;
      } else {
        sum += subjects[i].gpa;
      }
    }
    semesterGPA = sum / noOfSubjects;
    semesterGPA = ceil(semesterGPA * 100.0) / 100.0;
    return semesterGPA;
  }

  int getNoOfSubjects() { return noOfSubjects; }
  vector<Subject> getSubjects() { return subjects; }

  // ----- Input Setters ----- //
  void inputProgram() {
    for (int i = 0; i < 5; i++) {
      cout << i + 1 << ": " << offeredPrograms[i] << endl;
    }
    cout << endl;

    int option;
    do {
      do {
        cout << "Choose a program: ";
        cin >> option;

        if (option < 1 || option > 5)
          printError("Invalid option!\n\n");
        else
          break;
      } while (true);

      if (searchStudents(offeredPrograms[option - 1], semester, rollNo) != -1)
        printError("A student record with similar data already exists\n\n");
      else
        break;
    } while (true);

    program = offeredPrograms[option - 1];
    createStudentID();
  }

  void inputSemester() {
    do {
      do {
        cout << "Input semester: ";
        cin >> semester;
        if (semester < 1 || semester > 8)
          printError("Value should be between 1 & 8\n\n");
        else
          break;
      } while (true);

      if (searchStudents(program, semester, rollNo) != -1)
        printError("A student record with similar data already exists\n\n");
      else
        break;
    } while (true);

    createStudentID();
  }

  void inputRollNo() {
    int newRollNo;

    do {
      cout << "Input roll number: ";
      cin >> newRollNo;

      if (searchStudents(program, semester, newRollNo) != -1)
        printError("A student record with similar data already exists\n\n");
      else
        break;
    } while (true);

    rollNo = newRollNo;
    createStudentID();
  }

  void inputSubjects() {
    do {
      cout << "Input number of subjects (5-8): ";
      cin >> noOfSubjects;

      if (noOfSubjects < 5 || noOfSubjects > 8)
        printError("A student can have minimum 5 and maximum 8 subjects\n\n");
      else
        break;
    } while (true);

    cout << endl;
    for (int i = 0; i < noOfSubjects; i++) {
      Subject tempSubject;

      cout << "Enter subject " << i + 1 << " code: ";
      cin >> tempSubject.code;
      tempSubject.code = toupperstr(tempSubject.code);
      tempSubject.attendance = -1;
      tempSubject.gpa = -1;

      subjects.push_back(tempSubject);
    }
  }

  void inputData() {
    User::inputData();
    cout << endl;
    inputProgram();
    inputSemester();
    inputRollNo();
    inputSubjects();
  }
};

class Teacher : public User {
private:
  static int teacherCount;
  string department;
  int yearJoined;
  int idNo;
  string teacherID;

  string departments[5] = {"AI", "CS", "DS", "GM", "SE"};

  void createTeacherID() {
    teacherID = department + "-" + to_string(yearJoined) + "-" + to_string(idNo);
  }

public:
  Teacher(bool incrementCount) : User(incrementCount) {
    if (incrementCount)
      ++teacherCount;
  }

  Teacher(string un,
          string pw,
          string fN,
          string lN,
          string cN,
          string ct,
          string d,
          int yJ,
          int idN,
          string tID) : User(un, pw, fN, lN, cN, ct) {
    ++teacherCount;
    department = d;
    yearJoined = yJ;
    idNo = idN;
    teacherID = tID;
  }

  // ----- Operator Overload  ----- //
  bool operator<(Teacher &next) {
    if (department < next.department)
      return true;
    if (department == next.department && yearJoined < next.yearJoined)
      return true;
    if (department == next.department && yearJoined == next.yearJoined && idNo < next.idNo)
      return true;
  }

  // ----- Setters ----- //
  static void setTeacherCount(int aC) { teacherCount = aC; }

  // ----- Getters ----- //
  static int getTeacherCount() { return teacherCount; }
  string getDepartment() { return department; }
  int getYearJoined() { return yearJoined; }
  int getIDNo() { return idNo; }
  string getTeacherID() { return teacherID; }

  // ----- Input Setters ----- //
  void inputDepartment() {
    for (int i = 0; i < 5; i++) {
      cout << i + 1 << ": " << departments[i] << endl;
    }
    cout << endl;

    int option;
    do {
      cout << "Choose a department: ";
      cin >> option;

      if (option < 1 || option > 5)
        printError("Invalid option!\n\n");
      else
        break;
    } while (true);

    department = departments[option - 1];
    createTeacherID();
  }

  void inputYearJoined() {
    int minYear = 1998, maxYear = 2023;

    do {
      cout << "Enter joining year: ";
      cin >> yearJoined;

      if (yearJoined < minYear || yearJoined > maxYear)
        printError("Year should be between " + to_string(minYear) + " & " + to_string(maxYear) + "\n\n");
      else
        break;
    } while (true);

    createTeacherID();
  }

  void inputIDNo() {
    int newID;

    do {
      cout << "Enter ID number: ";
      cin >> newID;

      if (searchTeachers(newID) != -1)
        printError("A teacher record with this ID number already exists\n\n");
      else
        break;
    } while (true);

    idNo = newID;
    createTeacherID();
  }

  void inputData() {
    User::inputData();
    cout << endl;
    inputDepartment();
    inputYearJoined();
    inputIDNo();
  }
};

// ----- Initializing Static Variables ----- //

int User::userCount = 0;
char User::activeUserType = ' ';
int User::activeUserIndex = -1;
string User::activeUserUsername = "";

int Admin::adminCount = 0;
int Student::studentCount = 0;
int Teacher::teacherCount = 0;

// ----- Data Vectors ----- //

vector<Admin> adminRecords;
vector<Student> studentRecords;
vector<Teacher> teacherRecords;

// ----- Search Functions ----- //

int searchAdmins(string username) {
  for (int i = 0; i < adminRecords.size(); i++) {
    if (adminRecords[i].getUsername() == username)
      return i;
  }
  return -1;
}

int searchStudents(string username) {
  for (int i = 0; i < studentRecords.size(); i++) {
    if (studentRecords[i].getUsername() == username)
      return i;
  }
  return -1;
}

int searchStudents(string program, int semester, int rollNo) {
  for (int i = 0; i < studentRecords.size(); i++) {
    if (studentRecords[i].getProgram() == program && studentRecords[i].getSemester() == semester && studentRecords[i].getRollNo() == rollNo)
      return i;
  }
  return -1;
}

int searchTeachers(string username) {
  for (int i = 0; i < teacherRecords.size(); i++) {
    if (teacherRecords[i].getUsername() == username)
      return i;
  }
  return -1;
}

int searchTeachers(int id) {
  for (int i = 0; i < teacherRecords.size(); i++) {
    if (teacherRecords[i].getIDNo() == id)
      return i;
  }
  return -1;
}

bool userExists(string username) {
  if (searchAdmins(username) == -1 && searchStudents(username) == -1 && searchTeachers(username) == -1)
    return false;
  else
    return true;
}

// ----- Data Sorting ----- //

void sortData() {
  sort(adminRecords.begin(), adminRecords.end());
  sort(studentRecords.begin(), studentRecords.end());
  sort(teacherRecords.begin(), teacherRecords.end());

  // Update current user index in case data sort changes the object's place in the vector
  switch (User::getActiveUserType()) {
  case 'A':
    User::setActiveUserIndex(searchAdmins(User::getActiveUserUsername()));
    break;
  case 'S':
    User::setActiveUserIndex(searchStudents(User::getActiveUserUsername()));
    break;
  case 'T':
    User::setActiveUserIndex(searchTeachers(User::getActiveUserUsername()));
    break;
  }
}

// ----- Data Handling ----- //

void saveData() {
  sortData();

  fstream writer("data.csv", ios::out);
  int users = User::getUserCount();
  int admins = Admin::getAdminCount();
  int students = Student::getStudentCount();
  int teachers = Teacher::getTeacherCount();

  writer << users << endl;
  writer << admins << endl;
  writer << students << endl;
  writer << teachers << endl;

  for (int i = 0; i < admins; i++) {
    writer << adminRecords[i].getUsername() << ",";
    writer << adminRecords[i].getPassword() << ",";
    writer << adminRecords[i].getFirstName() << ",";
    writer << adminRecords[i].getLastName() << ",";
    writer << adminRecords[i].getContactNumber() << ",";
    writer << adminRecords[i].getCity() << ",";
    writer << adminRecords[i].getSuperAdminStatus() << endl;
  }

  for (int i = 0; i < students; i++) {
    writer << studentRecords[i].getUsername() << ",";
    writer << studentRecords[i].getPassword() << ",";
    writer << studentRecords[i].getFirstName() << ",";
    writer << studentRecords[i].getLastName() << ",";
    writer << studentRecords[i].getContactNumber() << ",";
    writer << studentRecords[i].getCity() << ",";
    writer << studentRecords[i].getProgram() << ",";
    writer << studentRecords[i].getSemester() << ",";
    writer << studentRecords[i].getRollNo() << ",";
    writer << studentRecords[i].getStudentID() << ",";
    writer << studentRecords[i].getSemesterGPA() << ",";

    int noOfSubjects = studentRecords[i].getNoOfSubjects();
    vector<Subject> subjects = studentRecords[i].getSubjects();

    writer << noOfSubjects << ",";
    for (int j = 0; j < noOfSubjects; j++) {
      writer << subjects[j].code << ",";
      writer << subjects[j].attendance << ",";
      if (j == noOfSubjects - 1)
        writer << subjects[j].gpa << endl;
      else
        writer << subjects[j].gpa << ",";
    }
  }

  for (int i = 0; i < teachers; i++) {
    writer << teacherRecords[i].getUsername() << ",";
    writer << teacherRecords[i].getPassword() << ",";
    writer << teacherRecords[i].getFirstName() << ",";
    writer << teacherRecords[i].getLastName() << ",";
    writer << teacherRecords[i].getContactNumber() << ",";
    writer << teacherRecords[i].getCity() << ",";
    writer << teacherRecords[i].getDepartment() << ",";
    writer << teacherRecords[i].getYearJoined() << ",";
    writer << teacherRecords[i].getIDNo() << ",";
    writer << teacherRecords[i].getTeacherID() << endl;
  }

  writer.close();
}

// Function to split csv lines into values using vector & sstream
vector<string> splitLine(string &line) {
  vector<string> result;
  stringstream lineStream(line);
  string item;

  while (getline(lineStream, item, ',')) {
    result.push_back(item);
  }

  return result;
}

void loadData() {
  fstream reader("data.csv", ios::in);

  if (reader.is_open()) {
    int users, admins, students, teachers;
    reader >> users;
    reader >> admins;
    reader >> students;
    reader >> teachers;

    string line;
    vector<string> items;

    // Load admin data
    for (int i = 0; i < admins; i++) {
      reader >> line;
      items = splitLine(line);

      adminRecords.push_back(Admin(items[0],
                                   items[1],
                                   items[2],
                                   items[3],
                                   items[4],
                                   items[5],
                                   bool(stoi(items[6]))));
    }

    // Load student data
    for (int i = 0; i < students; i++) {
      reader >> line;
      items = splitLine(line);

      int noOfSubjects = stoi(items[11]);
      vector<Subject> subjects;

      for (int j = 0; j < noOfSubjects; j++) {
        Subject tempSubject;

        tempSubject.code = items[12 + (j * 3)];
        tempSubject.attendance = stoi(items[13 + (j * 3)]);
        tempSubject.gpa = stof(items[14 + (j * 3)]);

        subjects.push_back(tempSubject);
      }

      studentRecords.push_back(Student(items[0],
                                       items[1],
                                       items[2],
                                       items[3],
                                       items[4],
                                       items[5],
                                       items[6],
                                       stoi(items[7]),
                                       stoi(items[8]),
                                       items[9],
                                       stof(items[10]),
                                       noOfSubjects,
                                       subjects));
    }

    // Load teacher data
    for (int i = 0; i < teachers; i++) {
      reader >> line;
      items = splitLine(line);

      teacherRecords.push_back(Teacher(items[0],
                                       items[1],
                                       items[2],
                                       items[3],
                                       items[4],
                                       items[5],
                                       items[6],
                                       stoi(items[7]),
                                       stoi(items[8]),
                                       items[9]));
    }

    reader.close();
  } else {
    adminRecords.push_back(Admin("Admin", "12345678", "-", "-", "-", "-", true));

    vector<Subject> emptySubject;
    emptySubject.push_back(Subject());
    studentRecords.push_back(Student("Student", "12345678", "-", "-", "-", "-", "-", 0, 0, "-", -1, 1, emptySubject));

    teacherRecords.push_back(Teacher("Teacher", "12345678", "-", "-", "-", "-", "-", 0, 0, "-"));

    saveData();
    system("cls");
    printWarning("Warning! data.csv was not found. A new file has been created with the following logins:\n\n");

    setColor(11);
    cout << left << setw(21) << "Username";
    cout << "Password\n";
    setColor(7);

    cout << left << setw(21) << "Admin";
    cout << "12345678\n";
    cout << left << setw(21) << "Student";
    cout << "12345678\n";
    cout << left << setw(21) << "Teacher";
    cout << "12345678\n";

    cout << endl;
    system("pause");
  }
}

// ----- Login Function ----- //

void login() {
  string username, password;
  bool loggedIn = false;

  do {
    printHeader("University Management System");
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    cout << endl;

    for (int i = 0; i < adminRecords.size(); i++) {
      if (adminRecords[i].getUsername() == username && adminRecords[i].getPassword() == password) {
        loggedIn = true;
        User::setActiveUserType('A');
        User::setActiveUserIndex(i);
        User::setActiveUserUsername(username);
        printSuccess("Login successful . . . ");
        Sleep(1000);
        break;
      }
    }

    for (int i = 0; i < studentRecords.size(); i++) {
      if (studentRecords[i].getUsername() == username && studentRecords[i].getPassword() == password) {
        loggedIn = true;
        User::setActiveUserType('S');
        User::setActiveUserIndex(i);
        User::setActiveUserUsername(username);
        printSuccess("Login successful . . . ");
        Sleep(1000);
        break;
      }
    }

    for (int i = 0; i < teacherRecords.size(); i++) {
      if (teacherRecords[i].getUsername() == username && teacherRecords[i].getPassword() == password) {
        loggedIn = true;
        User::setActiveUserType('T');
        User::setActiveUserIndex(i);
        User::setActiveUserUsername(username);
        printSuccess("Login successful . . . ");
        Sleep(1000);
        break;
      }
    }

    if (loggedIn)
      break;
    else {
      printError("Incorrect username/password . . . ");
      Sleep(1000);
    }
  } while (true);
}

// ----- Admin Functions ----- //

// Admin View Functions
void admin_viewAdmins() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > View Admins");

  setColor(14);
  cout << left << setw(23) << "Username";
  cout << left << setw(23) << "Full Name";
  cout << left << setw(14) << "Super Admin";
  cout << left << setw(18) << "Contact No";
  cout << "City\n";
  setColor(7);

  for (int i = 0; i < adminRecords.size(); i++) {
    cout << left << setw(23) << adminRecords[i].getUsername();
    cout << left << setw(23) << adminRecords[i].getFirstName() + " " + adminRecords[i].getLastName();

    if (adminRecords[i].getSuperAdminStatus())
      cout << left << setw(14) << "Yes";
    else
      cout << left << setw(14) << "No";

    cout << left << setw(18) << adminRecords[i].getContactNumber();
    cout << adminRecords[i].getCity() << endl;
  }

  cout << endl;
  system("pause");
}

void admin_viewStudents() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > View Students");

  setColor(14);
  cout << left << setw(23) << "Username";
  cout << left << setw(23) << "Full Name";
  cout << left << setw(15) << "Student ID";
  cout << left << setw(7) << "SGPA";
  cout << left << setw(11) << "Subjects";
  cout << left << setw(18) << "Contact No";
  cout << "City\n";
  setColor(7);

  for (int i = 0; i < studentRecords.size(); i++) {
    cout << left << setw(23) << studentRecords[i].getUsername();
    cout << left << setw(23) << studentRecords[i].getFirstName() + " " + studentRecords[i].getLastName();
    cout << left << setw(15) << studentRecords[i].getStudentID();

    if (studentRecords[i].getSemesterGPA() == -1) {
      setColor(8);
      cout << left << setw(7) << "NA";
      setColor(7);
    } else
      cout << left << setw(7) << studentRecords[i].getSemesterGPA();

    cout << left << setw(11) << studentRecords[i].getNoOfSubjects();
    cout << left << setw(18) << studentRecords[i].getContactNumber();
    cout << studentRecords[i].getCity() << endl;
  }

  cout << endl;
  system("pause");
}

void admin_viewTeachers() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > View Teachers");

  setColor(14);
  cout << left << setw(23) << "Username";
  cout << left << setw(23) << "Full Name";
  cout << left << setw(14) << "Teacher ID";
  cout << left << setw(18) << "Contact No";
  cout << "City\n";
  setColor(7);

  for (int i = 0; i < teacherRecords.size(); i++) {
    cout << left << setw(23) << teacherRecords[i].getUsername();
    cout << left << setw(23) << teacherRecords[i].getFirstName() + " " + studentRecords[i].getLastName();
    cout << left << setw(14) << teacherRecords[i].getTeacherID();
    cout << left << setw(18) << teacherRecords[i].getContactNumber();
    cout << teacherRecords[i].getCity() << endl;
  }

  cout << endl;
  system("pause");
}

void admin_view() {
  int option;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > View");

    cout << "1: Admins\n";
    cout << "2: Students\n";
    cout << "3: Teachers\n\n";
    cout << "0: Go Back\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      admin_viewAdmins();
      break;

    case 2:
      admin_viewStudents();
      break;

    case 3:
      admin_viewTeachers();
      break;

    case 0:
      break;

    default:
      printError("Invalid option . . . ");
      Sleep(1000);
      break;
    }
  } while (option != 0);
}

// Admin Create Functions
void admin_createAdmin() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Create Admin Record");

  Admin newAdmin(true);
  newAdmin.inputData();
  adminRecords.push_back(newAdmin);
  saveData();
  printSuccess("\nAdmin record created successfully!\n\n");
  system("pause");
}

void admin_createStudent() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Create Student Record");

  Student newStudent(true);
  newStudent.inputData();
  studentRecords.push_back(newStudent);
  saveData();
  printSuccess("\nStudent record created successfully!\n\n");
  system("pause");
}

void admin_createTeacher() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Create Teacher Record");

  Teacher newTeacher(true);
  newTeacher.inputData();
  teacherRecords.push_back(newTeacher);
  saveData();
  printSuccess("\nTeacher record created successfully!\n\n");
  system("pause");
}

void admin_create() {
  int option;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Create");

    cout << "1: Admin\n";
    cout << "2: Student\n";
    cout << "3: Teacher\n\n";
    cout << "0: Go Back\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      if (!adminRecords[User::getActiveUserIndex()].getSuperAdminStatus()) {
        printError("Permission denied . . . ");
        Sleep(1000);
      } else {
        admin_createAdmin();
      }
      break;

    case 2:
      admin_createStudent();
      break;

    case 3:
      admin_createTeacher();
      break;

    case 0:
      break;

    default:
      printError("Invalid option . . . ");
      Sleep(1000);
      break;
    }
  } while (option != 0);
}

// Admin Edit Functions
void admin_editAdmin() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Edit Admin Record");

  cout << endl;
  system("pause");
}

void admin_editStudent() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Edit Student Record");

  cout << endl;
  system("pause");
}

void admin_editTeacher() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Edit Teacher Record");

  cout << endl;
  system("pause");
}

void admin_edit() {
  int option;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Edit");

    cout << "1: Admin\n";
    cout << "2: Student\n";
    cout << "3: Teacher\n\n";
    cout << "0: Go Back\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      if (!adminRecords[User::getActiveUserIndex()].getSuperAdminStatus()) {
        printError("Permission denied . . . ");
        Sleep(1000);
      } else {
        admin_editAdmin();
      }
      break;

    case 2:
      admin_editStudent();
      break;

    case 3:
      admin_editTeacher();
      break;

    case 0:
      break;

    default:
      printError("Invalid option . . . ");
      Sleep(1000);
      break;
    }
  } while (option != 0);
}

// Admin Delete Functions
void admin_deleteAdmin() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Delete Admin Record");

  cout << endl;
  system("pause");
}

void admin_deleteStudent() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Delete Student Record");

  cout << endl;
  system("pause");
}

void admin_deleteTeacher() {
  printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Delete Teacher Record");

  cout << endl;
  system("pause");
}

void admin_delete() {
  int option;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Delete");

    cout << "1: Admin\n";
    cout << "2: Student\n";
    cout << "3: Teacher\n\n";
    cout << "0: Go Back\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      if (!adminRecords[User::getActiveUserIndex()].getSuperAdminStatus()) {
        printError("Permission denied . . . ");
        Sleep(1000);
      } else {
        admin_deleteAdmin();
      }
      break;

    case 2:
      admin_deleteStudent();
      break;

    case 3:
      admin_deleteTeacher();
      break;

    case 0:
      break;

    default:
      printError("Invalid option . . . ");
      Sleep(1000);
      break;
    }
  } while (option != 0);
}

// Admin Panel
void admin_panel() {
  int option;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "]");

    cout << "1: View\n";
    cout << "2: Create\n";
    cout << "3: Edit\n";
    cout << "4: Delete\n\n";
    cout << "5: View Account Info\n";
    cout << "6: Change Account Password\n";
    cout << "0: Exit UMS\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      admin_view();
      break;

    case 2:
      admin_create();
      break;

    case 3:
      admin_edit();
      break;

    case 4:
      admin_delete();
      break;

    case 5:
      /* code */
      break;

    case 6:
      /* code */
      break;

    case 0:
      break;

    default:
      printError("Invalid option . . . ");
      Sleep(1000);
      break;
    }
  } while (option != 0);
}

// ----- Student Functions ----- //

void student_panel() {
  int option;

  do {
    printHeader("UMS > Student Panel [" + User::getActiveUserUsername() + "]");

    cout << "1: Academic Dashboard\n\n";
    cout << "2: View Account Info\n";
    cout << "3: Change Account Password\n";
    cout << "0: Exit UMS\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      /* code */
      break;

    case 2:
      /* code */
      break;

    case 3:
      /* code */
      break;

    case 0:
      break;

    default:
      printError("Invalid option . . . ");
      Sleep(1000);
      break;
    }
  } while (option != 0);
}

// ----- Teacher Functions ----- //

void teacher_panel() {
  int option;

  do {
    printHeader("UMS > Teacher Panel [" + User::getActiveUserUsername() + "]");

    cout << "1: Mark Attendance\n";
    cout << "2: Mark GPA\n\n";
    cout << "3: View Account Info\n";
    cout << "4: Change Account Password\n";
    cout << "0: Exit UMS\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      /* code */
      break;

    case 2:
      /* code */
      break;

    case 3:
      /* code */
      break;

    case 4:
      /* code */
      break;

    case 0:
      break;

    default:
      printError("Invalid option . . . ");
      Sleep(1000);
      break;
    }
  } while (option != 0);
}

// ----- Main Function ----- //

int main() {
  loadData();
  login();

  switch (User::getActiveUserType()) {
  case 'A':
    admin_panel();
    break;
  case 'S':
    student_panel();
    break;
  case 'T':
    teacher_panel();
    break;
  }
}