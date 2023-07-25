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

void printColoredLine(int color, string text) {
  setColor(color);
  cout << text;
  setColor(7);
}

void printHeader(string text) {
  system("cls");

  printColoredLine(11, "# ----- ");

  for (int i = 0; i < text.length(); i++) {
    if (text[i] == '>') {
      setColor(11);
      cout << text[i];
      setColor(7);
    } else if (text[i] == '[') {
      setColor(3);
      cout << text[i];
    } else if (text[i] == ']') {
      cout << text[i];
      setColor(7);
    } else {
      cout << text[i];
    }
  }

  printColoredLine(11, " ----- #\n\n");
}

void printSuccess(string text) {
  printColoredLine(10, text);
}

void printWarning(string text) {
  printColoredLine(6, text);
}

void printError(string text) {
  printColoredLine(4, text);
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

  // Print Info Function
  void printInfo() {
    cout << "Username: ";
    printColoredLine(13, username + "\n");
    cout << "Full Name: ";
    printColoredLine(13, firstName + " " + lastName + "\n");
    cout << "Contact Number: ";
    printColoredLine(13, contactNo + "\n");
    cout << "City: ";
    printColoredLine(13, city + "\n");
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

  // Print Info Function
  void printInfo() {
    User::printInfo();
    cout << "Super Admin: ";
    if (superAdmin)
      printColoredLine(13, "Yes\n");
    else
      printColoredLine(13, "No\n");
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

  // Print Info Function
  void printInfo() {
    User::printInfo();
    cout << "Student ID: ";
    printColoredLine(13, studentID + "\n");
    for (int i = 0; i < subjects.size(); i++) {
      cout << "Subject " << i + 1 << ": ";
      printColoredLine(13, subjects[i].code + "\n");
    }
  }

  // ----- Setters ----- //
  static void setStudentCount(int sC) { studentCount = sC; }
  void setSubjects(vector<Subject> &updatedSubjects) {
    subjects = updatedSubjects;
  }

  // ----- Getters ----- //
  static int getStudentCount() { return studentCount; }
  string getProgram() { return program; }
  int getSemester() { return semester; }
  int getRollNo() { return rollNo; }
  string getStudentID() {
    createStudentID();
    return studentID;
  }

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

      if (searchStudents(offeredPrograms[option - 1], semester, rollNo) != -1 && offeredPrograms[option - 1] != program)
        printError("A student record with similar data already exists\n\n");
      else
        break;
    } while (true);

    program = offeredPrograms[option - 1];
  }

  void inputSemester() {
    int newSemester;

    do {
      do {
        cout << "Input semester: ";
        cin >> newSemester;
        if (newSemester < 1 || newSemester > 8)
          printError("Value should be between 1 & 8\n\n");
        else
          break;
      } while (true);

      if (searchStudents(program, newSemester, rollNo) != -1 && newSemester != semester)
        printError("A student record with similar data already exists\n\n");
      else
        break;
    } while (true);

    semester = newSemester;
  }

  void inputRollNo() {
    int newRollNo;

    do {
      cout << "Input roll number: ";
      cin >> newRollNo;

      if (searchStudents(program, semester, newRollNo) != -1 && newRollNo != rollNo)
        printError("A student record with similar data already exists\n\n");
      else
        break;
    } while (true);

    rollNo = newRollNo;
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

    subjects.clear();
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

  // ----- Attendance & GPA Marking Functions  ----- //
  static int markAttendance() {
    int attendance;

    do {
      cout << "Enter attendance percentage (0 to 100): ";
      cin >> attendance;

      if (attendance < 0 || attendance > 100)
        printError("Invalid input\n\n");
      else
        break;
    } while (true);

    return attendance;
  }

  static float markGPA() {
    float gpa;

    do {
      cout << "Enter gpa (0 to 4.00): ";
      cin >> gpa;

      if (gpa < 0 || gpa > 4.00)
        printError("Invalid input\n\n");
      else
        break;
    } while (true);

    return gpa;
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

  // Print Info Function
  void printInfo() {
    User::printInfo();
    cout << "Teacher ID: ";
    printColoredLine(13, teacherID + "\n");
  }

  // ----- Setters ----- //
  static void setTeacherCount(int aC) { teacherCount = aC; }

  // ----- Getters ----- //
  static int getTeacherCount() { return teacherCount; }
  string getDepartment() { return department; }
  int getYearJoined() { return yearJoined; }
  int getIDNo() { return idNo; }
  string getTeacherID() {
    createTeacherID();
    return teacherID;
  }

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
  }

  void inputIDNo() {
    int newID;

    do {
      cout << "Enter ID number: ";
      cin >> newID;

      if (searchTeachers(newID) != -1 && newID != idNo)
        printError("A teacher record with this ID number already exists\n\n");
      else
        break;
    } while (true);

    idNo = newID;
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

  printColoredLine(14, "\nTotal Admins: ");
  cout << Admin::getAdminCount() << endl;

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

  printColoredLine(14, "\nTotal Students: ");
  cout << Student::getStudentCount() << endl;

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
    cout << left << setw(23) << teacherRecords[i].getFirstName() + " " + teacherRecords[i].getLastName();
    cout << left << setw(14) << teacherRecords[i].getTeacherID();
    cout << left << setw(18) << teacherRecords[i].getContactNumber();
    cout << teacherRecords[i].getCity() << endl;
  }

  printColoredLine(14, "\nTotal Teachers: ");
  cout << Teacher::getTeacherCount() << endl;

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
    cout << "0: Go back\n\n";

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
  string userToEdit;
  int index;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Edit Admin Record");
    cout << "Enter username: ";
    cin >> userToEdit;
    index = searchAdmins(userToEdit);

    if (index != -1)
      break;
    else {
      printError("Record not found . . . ");
      Sleep(1000);
    }
  } while (true);

  int option;

  do {
    index = searchAdmins(userToEdit);
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Edit Admin [" + adminRecords[index].getUsername() + "]");

    cout << "1: Change Username\n";
    cout << "2: Change Password\n";
    cout << "3: Change First Name\n";
    cout << "4: Change Last Name\n";
    cout << "5: Change Contact Number\n";
    cout << "6: Change City\n";
    cout << "7: Change Super Admin Status\n\n";
    cout << "8: View current account info\n";
    cout << "0: Go back\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Admin [" + adminRecords[index].getUsername() + "]'s Username");
      adminRecords[index].inputUsername();

      if (User::getActiveUserUsername() == userToEdit)
        User::setActiveUserUsername(adminRecords[index].getUsername());

      userToEdit = adminRecords[index].getUsername();
      saveData();
      printSuccess("Username changed successfully\n\n");
      system("pause");
      break;

    case 2:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Admin [" + adminRecords[index].getUsername() + "]'s Password");
      adminRecords[index].inputPassword();
      saveData();
      printSuccess("Password changed successfully\n\n");
      system("pause");
      break;

    case 3:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Admin [" + adminRecords[index].getUsername() + "]'s First Name");
      adminRecords[index].inputFirstName();
      saveData();
      printSuccess("First Name changed successfully\n\n");
      system("pause");
      break;

    case 4:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Admin [" + adminRecords[index].getUsername() + "]'s Last Name");
      adminRecords[index].inputLastName();
      saveData();
      printSuccess("Last Name changed successfully\n\n");
      system("pause");
      break;

    case 5:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Admin [" + adminRecords[index].getUsername() + "]'s Contact Number");
      adminRecords[index].inputContactNumber();
      saveData();
      printSuccess("Contact Number changed successfully\n\n");
      system("pause");
      break;

    case 6:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Admin [" + adminRecords[index].getUsername() + "]'s City");
      adminRecords[index].inputCity();
      saveData();
      printSuccess("City changed successfully\n\n");
      system("pause");
      break;

    case 7:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Admin [" + adminRecords[index].getUsername() + "]'s Super Admin Status");
      adminRecords[index].inputSuperAdminStatus();
      saveData();
      printSuccess("Super Admin Status changed successfully\n\n");
      system("pause");
      break;

    case 8:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > View Admin [" + adminRecords[index].getUsername() + "]'s Account Info");
      adminRecords[index].printInfo();
      cout << endl;
      system("pause");
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

void admin_editStudent() {
  string userToEdit;
  int index;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Edit Student Record");
    cout << "Enter username: ";
    cin >> userToEdit;
    index = searchStudents(userToEdit);

    if (index != -1)
      break;
    else {
      printError("Record not found . . . ");
      Sleep(1000);
    }
  } while (true);

  int option;

  do {
    index = searchStudents(userToEdit);
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Edit Student [" + studentRecords[index].getUsername() + "]");

    cout << "1: Change Username\n";
    cout << "2: Change Password\n";
    cout << "3: Change First Name\n";
    cout << "4: Change Last Name\n";
    cout << "5: Change Contact Number\n";
    cout << "6: Change City\n";
    cout << "7: Change Program\n";
    cout << "8: Change Semester\n";
    cout << "9: Change Roll Number\n";
    cout << "10: Change Subjects\n\n";
    cout << "11: View current account info\n";
    cout << "0: Go back\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Student [" + studentRecords[index].getUsername() + "]'s Username");
      studentRecords[index].inputUsername();
      userToEdit = studentRecords[index].getUsername();
      saveData();
      printSuccess("Username changed successfully\n\n");
      system("pause");
      break;

    case 2:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Student [" + studentRecords[index].getUsername() + "]'s Password");
      studentRecords[index].inputPassword();
      saveData();
      printSuccess("Password changed successfully\n\n");
      system("pause");
      break;

    case 3:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Student [" + studentRecords[index].getUsername() + "]'s First Name");
      studentRecords[index].inputFirstName();
      saveData();
      printSuccess("First Name changed successfully\n\n");
      system("pause");
      break;

    case 4:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Student [" + studentRecords[index].getUsername() + "]'s Last Name");
      studentRecords[index].inputLastName();
      saveData();
      printSuccess("Last Name changed successfully\n\n");
      system("pause");
      break;

    case 5:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Student [" + studentRecords[index].getUsername() + "]'s Contact Number");
      studentRecords[index].inputContactNumber();
      saveData();
      printSuccess("Contact Number changed successfully\n\n");
      system("pause");
      break;

    case 6:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Student [" + studentRecords[index].getUsername() + "]'s City");
      studentRecords[index].inputCity();
      saveData();
      printSuccess("City changed successfully\n\n");
      system("pause");
      break;

    case 7:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Student [" + studentRecords[index].getUsername() + "]'s Program");
      studentRecords[index].inputProgram();
      saveData();
      printSuccess("Program changed successfully\n\n");
      system("pause");
      break;

    case 8:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Student [" + studentRecords[index].getUsername() + "]'s Semester");
      studentRecords[index].inputSemester();
      saveData();
      printSuccess("Semester changed successfully\n\n");
      system("pause");
      break;

    case 9:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Student [" + studentRecords[index].getUsername() + "]'s Roll Number");
      studentRecords[index].inputRollNo();
      saveData();
      printSuccess("Roll Number changed successfully\n\n");
      system("pause");
      break;

    case 10:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Student [" + studentRecords[index].getUsername() + "]'s Subjects");
      studentRecords[index].inputSubjects();
      saveData();
      printSuccess("\nSubjects changed successfully\n\n");
      system("pause");
      break;

    case 11:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > View Student [" + studentRecords[index].getUsername() + "]'s Account Info");
      studentRecords[index].printInfo();
      cout << endl;
      system("pause");
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

void admin_editTeacher() {
  string userToEdit;
  int index;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Edit Teacher Record");
    cout << "Enter username: ";
    cin >> userToEdit;
    index = searchTeachers(userToEdit);

    if (index != -1)
      break;
    else {
      printError("Record not found . . . ");
      Sleep(1000);
    }
  } while (true);

  int option;

  do {
    index = searchTeachers(userToEdit);
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Edit Teacher [" + teacherRecords[index].getUsername() + "]");

    cout << "1: Change Username\n";
    cout << "2: Change Password\n";
    cout << "3: Change First Name\n";
    cout << "4: Change Last Name\n";
    cout << "5: Change Contact Number\n";
    cout << "6: Change City\n";
    cout << "7: Change Department\n";
    cout << "8: Change Joining Year\n";
    cout << "9: Change ID Number\n\n";
    cout << "10: View current account info\n";
    cout << "0: Go back\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Teacher [" + teacherRecords[index].getUsername() + "]'s Username");
      teacherRecords[index].inputUsername();
      userToEdit = teacherRecords[index].getUsername();
      saveData();
      printSuccess("Username changed successfully\n\n");
      system("pause");
      break;

    case 2:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Teacher [" + teacherRecords[index].getUsername() + "]'s Password");
      teacherRecords[index].inputPassword();
      saveData();
      printSuccess("Password changed successfully\n\n");
      system("pause");
      break;

    case 3:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Teacher [" + teacherRecords[index].getUsername() + "]'s First Name");
      teacherRecords[index].inputFirstName();
      saveData();
      printSuccess("First Name changed successfully\n\n");
      system("pause");
      break;

    case 4:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Teacher [" + teacherRecords[index].getUsername() + "]'s Last Name");
      teacherRecords[index].inputLastName();
      saveData();
      printSuccess("Last Name changed successfully\n\n");
      system("pause");
      break;

    case 5:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Teacher [" + teacherRecords[index].getUsername() + "]'s Contact Number");
      teacherRecords[index].inputContactNumber();
      saveData();
      printSuccess("Contact Number changed successfully\n\n");
      system("pause");
      break;

    case 6:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Teacher [" + teacherRecords[index].getUsername() + "]'s City");
      teacherRecords[index].inputCity();
      saveData();
      printSuccess("City changed successfully\n\n");
      system("pause");
      break;

    case 7:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Teacher [" + teacherRecords[index].getUsername() + "]'s Department");
      teacherRecords[index].inputDepartment();
      saveData();
      printSuccess("Department changed successfully\n\n");
      system("pause");
      break;

    case 8:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Teacher [" + teacherRecords[index].getUsername() + "]'s Joining Year");
      teacherRecords[index].inputYearJoined();
      saveData();
      printSuccess("Joining Year changed successfully\n\n");
      system("pause");
      break;

    case 9:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Teacher [" + teacherRecords[index].getUsername() + "]'s ID Number");
      teacherRecords[index].inputIDNo();
      saveData();
      printSuccess("ID Number changed successfully\n\n");
      system("pause");
      break;

    case 10:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > View Teacher [" + teacherRecords[index].getUsername() + "]'s Account Info");
      teacherRecords[index].printInfo();
      cout << endl;
      system("pause");
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
bool confirmDelete() {
  char input;
  printWarning("\nThis action cannot be undone, are you sure you want to continue? (y/n): ");
  cin >> input;
  input = tolower(input);
  if (input == 'y')
    return true;
  else
    return false;
}

void admin_deleteAdmin() {
  string userToDelete;
  int index;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Delete Admin Record");
    cout << "Enter username: ";
    cin >> userToDelete;
    index = searchAdmins(userToDelete);

    if (index != -1) {
      if (adminRecords[index].getUsername() == User::getActiveUserUsername()) {
        printWarning("You are not allowed to delete your own record . . . ");
        Sleep(1500);
      } else {
        break;
      }
    } else {
      printError("Record not found . . . ");
      Sleep(1000);
    }
  } while (true);

  if (confirmDelete()) {
    adminRecords.erase(adminRecords.begin() + index);
    User::setUserCount(User::getUserCount() - 1);
    Admin::setAdminCount(Admin::getAdminCount() - 1);
    saveData();

    printSuccess("\nAdmin record deleted successfully!\n\n");
    system("pause");
  }
}

void admin_deleteStudent() {
  string userToDelete;
  int index;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Delete Student Record");
    cout << "Enter username: ";
    cin >> userToDelete;
    index = searchStudents(userToDelete);

    if (index != -1) {
      break;
    } else {
      printError("Record not found . . . ");
      Sleep(1000);
    }
  } while (true);

  if (confirmDelete()) {
    studentRecords.erase(studentRecords.begin() + index);
    User::setUserCount(User::getUserCount() - 1);
    Student::setStudentCount(Student::getStudentCount() - 1);
    saveData();

    printSuccess("\nStudent record deleted successfully!\n\n");
    system("pause");
  }
}

void admin_deleteTeacher() {
  string userToDelete;
  int index;

  do {
    printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Delete Teacher Record");
    cout << "Enter username: ";
    cin >> userToDelete;
    index = searchTeachers(userToDelete);

    if (index != -1) {
      break;
    } else {
      printError("Record not found . . . ");
      Sleep(1000);
    }
  } while (true);

  if (confirmDelete()) {
    teacherRecords.erase(teacherRecords.begin() + index);
    User::setUserCount(User::getUserCount() - 1);
    Teacher::setTeacherCount(Teacher::getTeacherCount() - 1);
    saveData();

    printSuccess("\nTeacher record deleted successfully!\n\n");
    system("pause");
  }
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
    cout << "6: Change Account Password\n\n";
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
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > View Account Info");
      adminRecords[User::getActiveUserIndex()].printInfo();
      cout << endl;
      system("pause");
      break;

    case 6:
      printHeader("UMS > Admin Panel [" + User::getActiveUserUsername() + "] > Change Account Password");
      adminRecords[User::getActiveUserIndex()].changePassword();
      saveData();
      printSuccess("\nAccount password changed successfully!\n\n");
      system("pause");
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
    cout << "3: Change Account Password\n\n";
    cout << "0: Exit UMS\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      /* code */
      break;

    case 2:
      printHeader("UMS > Student Panel [" + User::getActiveUserUsername() + "] > View Account Info");
      studentRecords[User::getActiveUserIndex()].printInfo();
      cout << endl;
      system("pause");
      break;

    case 3:
      printHeader("UMS > Student Panel [" + User::getActiveUserUsername() + "] > Change Account Password");
      studentRecords[User::getActiveUserIndex()].changePassword();
      saveData();
      printSuccess("\nAccount password changed successfully!\n\n");
      system("pause");
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

void teacher_mark() {
  string studentID;
  int index;

  do {
    printHeader("UMS > Teacher Panel [" + User::getActiveUserUsername() + "] > Marking");

    cout << "Enter Student ID: ";
    cin >> studentID;
    studentID = toupperstr(studentID);

    index = -1;
    for (int i = 0; i < studentRecords.size(); i++)
      if (studentRecords[i].getStudentID() == studentID)
        index = i;

    if (index == -1) {
      printError("Student record not found . . . ");
      Sleep(1000);
    } else {
      if (studentRecords[index].getProgram().substr(2, 3) != teacherRecords[User::getActiveUserIndex()].getDepartment()) {
        printWarning("Student does not belong to your department . . . ");
        Sleep(1500);
      } else {
        break;
      }
    }
  } while (true);

  int option;
  vector<Subject> sbjcts = studentRecords[index].getSubjects();

  do {
    printHeader("UMS > Teacher Panel [" + User::getActiveUserUsername() + "] > [" + studentRecords[index].getStudentID() + "]");

    for (int i = 0; i < sbjcts.size(); i++) {
      cout << i + 1 << ": " << sbjcts[i].code << endl;
    }
    cout << "\n0: Cancel\n\n";

    cout << "Choose a subject to mark: ";
    cin >> option;

    if (option == 0) {
      break;
    } else if (option <= sbjcts.size()) {
      int choice;
      do {
        printHeader("UMS > Teacher Panel [" + User::getActiveUserUsername() + "] > [" + studentRecords[index].getStudentID() + "] > Marking " + sbjcts[option - 1].code);

        cout << "1: Mark Attendance\n";
        cout << "2: Mark GPA\n\n";
        cout << "0: Cancel\n\n";

        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
          printHeader("UMS > Teacher Panel [" + User::getActiveUserUsername() + "] > [" + studentRecords[index].getStudentID() + "] > Marking " + sbjcts[option - 1].code + " Attendance");
          sbjcts[option - 1].attendance = Teacher::markAttendance();
          studentRecords[index].setSubjects(sbjcts);
          saveData();
          printSuccess("\nAttendance marked successfully!\n\n");
          system("pause");
          break;

        case 2:
          printHeader("UMS > Teacher Panel [" + User::getActiveUserUsername() + "] > [" + studentRecords[index].getStudentID() + "] > Marking " + sbjcts[option - 1].code + " GPA");
          sbjcts[option - 1].gpa = Teacher::markGPA();
          studentRecords[index].setSubjects(sbjcts);
          saveData();
          printSuccess("\nGPA marked successfully!\n\n");
          system("pause");
          break;

        case 0:
          break;

        default:
          printError("Invalid option . . . ");
          Sleep(1000);
          break;
        }
      } while (choice != 0 && choice != 1 && choice != 2);
    } else {
      printError("Invalid option . . . ");
      Sleep(1000);
    }
  } while (true);
}

void teacher_panel() {
  int option;

  do {
    printHeader("UMS > Teacher Panel [" + User::getActiveUserUsername() + "]");

    cout << "1: Mark Attendance/GPA\n\n";
    cout << "2: View Account Info\n";
    cout << "3: Change Account Password\n\n";
    cout << "0: Exit UMS\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
    case 1:
      teacher_mark();
      break;

    case 2:
      printHeader("UMS > Teacher Panel [" + User::getActiveUserUsername() + "] > View Account Info");
      teacherRecords[User::getActiveUserIndex()].printInfo();
      cout << endl;
      system("pause");
      break;

    case 3:
      printHeader("UMS > Teacher Panel [" + User::getActiveUserUsername() + "] > Change Account Password");
      teacherRecords[User::getActiveUserIndex()].changePassword();
      saveData();
      printSuccess("\nAccount password changed successfully!\n\n");
      system("pause");
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