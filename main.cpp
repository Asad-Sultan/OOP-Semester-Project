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

void setColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

void printHeader(string text) {
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
  static char currentUserType;
  static int currentUserIndex;
  static string currentUserUsername;

  string username;
  string password;
  string firstName;
  string lastName;
  string contactNo;
  string address;

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
       string add) {
    ++userCount;
    username = un;
    password = pw;
    firstName = fN;
    lastName = lN;
    contactNo = cN;
    address = add;
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
  static void setCurrentUserType(char cUT) { currentUserType = cUT; }
  static void setCurrentUserIndex(int cUI) { currentUserIndex = cUI; }
  static void setCurrentUserUsername(string cUUN) { currentUserUsername = cUUN; }

  // ----- Getters ----- //
  static int getUserCount() { return userCount; }
  static char getCurrentUserType() { return currentUserType; }
  static int getCurrentUserIndex() { return currentUserIndex; }
  static string getCurrentUserUsername() { return currentUserUsername; }

  string getUsername() { return username; }
  string getPassword() { return password; }
  string getFirstName() { return firstName; }
  string getLastName() { return lastName; }
  string getContactNumber() { return contactNo; }
  string getAddress() { return address; }

  // ----- Input Setters ----- //
  void inputUsername() {
    string newUsername;
    bool goodUsernameLength, validUsername;

    do {
      do {
        cout << "Enter username: ";
        cin >> newUsername;

        goodUsernameLength = lengthCheck(newUsername, 4, 20);

        validUsername = true;
        for (int i = 0; i < newUsername.length(); i++)
          if ((newUsername[i] < 'A' || newUsername[i] > 'Z') && (newUsername[i] < 'a' || newUsername[i] > 'z') && (newUsername[i] < '0' || newUsername[i] > '9'))
            validUsername = false;

        if (!goodUsernameLength)
          printError("Username should be between 4 & 20 characters\n");
        if (!validUsername)
          printError("Only letters and numbers are allowed in the username\n");
        if (!goodUsernameLength || !validUsername)
          cout << endl;
      } while (!goodUsernameLength || !validUsername);

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
    cout << "Enter contact number: ";
    cin >> contactNo;
  }

  void inputAddress() {
    cout << "Enter address: ";
    cin.ignore(1, '\n');
    getline(cin, address);
  }

  void inputData() {
    inputUsername();
    inputPassword();
    inputFirstName();
    inputLastName();
    inputContactNumber();
    inputAddress();
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
        string add,
        bool sA = false) : User(un, pw, fN, lN, cN, add) {
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
          string add,
          string p,
          int s,
          int rN,
          string sID,
          float sGPA,
          int nOS,
          vector<Subject> sbj) : User(un, pw, fN, lN, cN, add) {
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
    cout << endl;
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
    cout << endl;

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
      tempSubject.attendance = -1;
      tempSubject.gpa = -1;

      subjects.push_back(tempSubject);
    }
  }

  void inputData() {
    User::inputData();
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
          string add,
          string d,
          int yJ,
          int idN,
          string tID) : User(un, pw, fN, lN, cN, add) {
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
    cout << endl;
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
        printError("Year should be between " + to_string(minYear) + " & " + to_string(maxYear));
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
};

// ----- Initializing Static Variables ----- //

int User::userCount = 0;
char User::currentUserType = ' ';
int User::currentUserIndex = -1;
string User::currentUserUsername = "";

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
  int index;
  index = searchAdmins(username);
  index = searchStudents(username);
  index = searchTeachers(username);

  if (index == -1)
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
  switch (User::getCurrentUserType()) {
  case 'A':
    User::setCurrentUserIndex(searchAdmins(User::getCurrentUserUsername()));
    break;
  case 'S':
    User::setCurrentUserIndex(searchStudents(User::getCurrentUserUsername()));
    break;
  case 'T':
    User::setCurrentUserIndex(searchTeachers(User::getCurrentUserUsername()));
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
    writer << adminRecords[i].getAddress() << ",";
    writer << adminRecords[i].getSuperAdminStatus() << endl;
  }

  for (int i = 0; i < students; i++) {
    writer << studentRecords[i].getUsername() << ",";
    writer << studentRecords[i].getPassword() << ",";
    writer << studentRecords[i].getFirstName() << ",";
    writer << studentRecords[i].getLastName() << ",";
    writer << studentRecords[i].getContactNumber() << ",";
    writer << studentRecords[i].getAddress() << ",";
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
    writer << teacherRecords[i].getAddress() << ",";
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

        tempSubject.code = items[12 + j];
        tempSubject.attendance = stoi(items[13 + j]);
        tempSubject.gpa = stof(items[14 + j]);

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
    system("cls");
    printHeader("University Management System");
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    cout << endl;

    for (int i = 0; i < adminRecords.size(); i++) {
      if (adminRecords[i].getUsername() == username && adminRecords[i].getPassword() == password) {
        loggedIn = true;
        User::setCurrentUserType('A');
        User::setCurrentUserIndex(i);
        User::setCurrentUserUsername(username);
        printSuccess("Login Successful . . . ");
        Sleep(1000);
        break;
      }
    }

    for (int i = 0; i < studentRecords.size(); i++) {
      if (studentRecords[i].getUsername() == username && studentRecords[i].getPassword() == password) {
        loggedIn = true;
        User::setCurrentUserType('S');
        User::setCurrentUserIndex(i);
        User::setCurrentUserUsername(username);
        printSuccess("Login Successful . . . ");
        Sleep(1000);
        break;
      }
    }

    for (int i = 0; i < teacherRecords.size(); i++) {
      if (teacherRecords[i].getUsername() == username && teacherRecords[i].getPassword() == password) {
        loggedIn = true;
        User::setCurrentUserType('T');
        User::setCurrentUserIndex(i);
        User::setCurrentUserUsername(username);
        printSuccess("Login Successful . . . ");
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
  system("cls");
  printHeader("UMS > Admin Panel [" + User::getCurrentUserUsername() + "] > View Admins");

  setColor(14);
  cout << left << setw(21) << "Username";
  cout << left << setw(21) << "Full Name";
  cout << left << setw(15) << "Super Admin";
  cout << left << setw(21) << "Contact No";
  cout << "Address\n";
  setColor(7);

  for (int i = 0; i < adminRecords.size(); i++) {
    cout << left << setw(21) << adminRecords[i].getUsername();
    cout << left << setw(21) << adminRecords[i].getFirstName() + " " + adminRecords[i].getLastName();

    if (adminRecords[i].getSuperAdminStatus())
      cout << left << setw(15) << "Yes";
    else
      cout << left << setw(15) << "No";

    cout << left << setw(21) << adminRecords[i].getContactNumber();
    cout << adminRecords[i].getAddress() << endl;
  }

  cout << endl;
  system("pause");
}

void admin_viewStudents() {
  system("cls");
  printHeader("UMS > Admin Panel [" + User::getCurrentUserUsername() + "] > View Students");

  setColor(14);
  cout << left << setw(21) << "Username";
  cout << left << setw(21) << "Full Name";
  cout << left << setw(17) << "Student ID";
  cout << left << setw(11) << "SGPA";
  cout << left << setw(11) << "Subjects";
  cout << left << setw(21) << "Contact No";
  cout << "Address\n";
  setColor(7);

  for (int i = 0; i < studentRecords.size(); i++) {
    cout << left << setw(21) << studentRecords[i].getUsername();
    cout << left << setw(21) << studentRecords[i].getFirstName() + " " + studentRecords[i].getLastName();
    cout << left << setw(17) << studentRecords[i].getStudentID();

    if (studentRecords[i].getSemesterGPA() == -1)
      cout << left << setw(11) << "NA";
    else
      cout << left << setw(11) << studentRecords[i].getSemesterGPA();

    cout << left << setw(11) << studentRecords[i].getNoOfSubjects();
    cout << left << setw(21) << studentRecords[i].getContactNumber();
    cout << studentRecords[i].getAddress() << endl;
  }

  cout << endl;
  system("pause");
}

void admin_viewTeachers() {
  system("cls");
  printHeader("UMS > Admin Panel [" + User::getCurrentUserUsername() + "] > View Teachers");

  setColor(14);
  cout << left << setw(21) << "Username";
  cout << left << setw(21) << "Full Name";
  cout << left << setw(17) << "Teacher ID";
  cout << left << setw(21) << "Contact No";
  cout << "Address\n";
  setColor(7);

  for (int i = 0; i < teacherRecords.size(); i++) {
    cout << left << setw(21) << teacherRecords[i].getUsername();
    cout << left << setw(21) << teacherRecords[i].getFirstName() + " " + studentRecords[i].getLastName();
    cout << left << setw(17) << teacherRecords[i].getTeacherID();
    cout << left << setw(21) << teacherRecords[i].getContactNumber();
    cout << teacherRecords[i].getAddress() << endl;
  }

  cout << endl;
  system("pause");
}

void admin_view() {
  int option;

  do {
    system("cls");
    printHeader("UMS > Admin Panel [" + User::getCurrentUserUsername() + "] > View");

    cout << "1: Admins\n";
    cout << "2: Students\n";
    cout << "3: Teacher\n\n";
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

// Admin Panel
void admin_panel() {
  int option;

  do {
    system("cls");
    printHeader("UMS > Admin Panel [" + User::getCurrentUserUsername() + "]");

    cout << "1: View\n";
    cout << "2: Create\n";
    cout << "3: Edit\n";
    cout << "4: Delete\n\n";
    cout << "5: Change Account Info\n";
    cout << "0: Exit UMS\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      admin_view();
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

    case 5:
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

void student_panel() {}

// ----- Teacher Functions ----- //

void teacher_panel() {}

// ----- Main Function ----- //

int main() {
  loadData();
  login();

  switch (User::getCurrentUserType()) {
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