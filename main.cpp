#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>
using namespace std;

// ----- Function Declarations ----- //

int searchStudents(string program, int semester, int rollNo);
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
  cout << text;
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
  setColor(6);
  cout << text;
  setColor(7);
}

void printError(string text) {
  setColor(12);
  cout << text;
  setColor(7);
}

// ----- Classes ----- //

class User {
protected:
  static int userCount;
  string username;
  string password;
  string firstName;
  string lastName;
  long int contactNo;
  string address;

  bool lengthCheck(string text, int lenMin, int lenMax) {
    if (text.length() < lenMin || text.length() > lenMax)
      return false;
    else
      return true;
  }

public:
  User(string un = "",
       string pw = "",
       string fN = "",
       string lN = "",
       long int cN = 0,
       string add = "") {
    ++userCount;
    username = un;
    password = pw;
    firstName = fN;
    lastName = lN;
    contactNo = cN;
    address = add;
  }

  // ----- Setters ----- //
  static void setUserCount(int uC) { userCount = uC; }
  // void setUsername(string un) { username = un; }
  // void setPassword(string pw) { password = pw; }
  // void setFirstName(string fN) { firstName = fN; }
  // void setLastName(string lN) { lastName = lN; }
  // void setContactNumber(string cN) { contactNo = cN; }
  // void setAddress(string add) { address = add; }

  // ----- Getters ----- //
  static int getUserCount() { return userCount; }
  string getUsername() { return username; }
  string getPassword() { return password; }
  string getFirstName() { return firstName; }
  string getLastName() { return lastName; }
  long int getContactNumber() { return contactNo; }
  string getAddress() { return address; }

  // ----- Input Setters ----- //

  void inputUsername() {
    string newUsername;

    do {
      do {
        cout << "Enter username: ";
        cin >> newUsername;

        if (lengthCheck(newUsername, 4, 20))
          break;
        else
          printWarning("Username should be between 4 & 20 characters\n\n");
      } while (true);

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
public:
};

// ----- Student Class & Related Structs ----- //

struct Subject {
  string name;
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

  string offeredPrograms[5] = {"BSSE", "BSCS", "BSDS", "BSAI", "BSGM"};

  void createStudentID() {
    studentID = program + "-" + to_string(semester) + "-" + to_string(rollNo);
  }

public:
  Student(string un = "",
          string pw = "",
          string fN = "",
          string lN = "",
          long int cN = 0,
          string add = "",
          string p = "",
          int s = 0,
          int rN = 0,
          string sID = "",
          float sGPA = 0.0) : User(un, pw, fN, lN, cN, add) {
    ++studentCount;
    program = p;
    semester = s;
    rollNo = rN;
    studentID = sID;
    semesterGPA = sGPA;
  }

  // ----- Setters ----- //
  static void setStudentCount(int sC) { studentCount = sC; }
  // void setProgram(string p) { program = p; }
  // void setSemester(int s) { semester = s; }
  // void setRollNo(int rN) { rollNo = rN; }

  // ----- Getters ----- //
  static int getStudentCount() { return studentCount; }
  string getProgram() { return program; }
  int getSemester() { return semester; }
  int getRollNo() { return rollNo; }
  string getStudentID() { return studentID; }

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
        printError("Duplicate record found!\n\n");
      else
        break;
    } while (true);

    program = offeredPrograms[option - 1];
    void createStudentID();
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
        printError("Duplicate record found!\n\n");
      else
        break;
    } while (true);

    void createStudentID();
  }

  void inputRollNo() {
    do {
      cout << "Input roll number: ";
      cin >> rollNo;
      if (searchStudents(program, semester, rollNo) != -1)
        printError("Duplicate record found!\n\n");
      else
        break;
    } while (true);

    void createStudentID();
  }

  void inputData() {
    User::inputData();
    inputProgram();
    inputSemester();
    inputRollNo();
  }
};

// ----- Initializing Static Variables ----- //

int User::userCount = 0;
int Student::studentCount = 0;

// ----- Data Vectors ----- //

vector<Student> studentRecords;

// ----- Data Handling ----- //

vector<string> splitLine(string &line) {
  vector<string> result;
  stringstream lineStream(line);
  string item;

  while (getline(lineStream, item, ',')) {
    result.push_back(item);
  }

  return result;
}

bool loadData() {
  fstream reader("data.csv", ios::in);

  if (reader.is_open()) {
    int userCount, studentCount;
    reader >> userCount;
    reader >> studentCount;

    string line;
    vector<string> items;

    // Load Admins

    for (int i = 0; i < studentCount; i++) {
      reader >> line;
      items = splitLine(line);

      Student tempStudent(items[0],
                          items[1],
                          items[2],
                          items[3],
                          stol(items[4]),
                          items[5],
                          items[6],
                          stoi(items[7]),
                          stoi(items[8]),
                          items[9],
                          stof(items[10]));

      studentRecords.push_back(tempStudent);
    }
  } else {
    return false;
  }
}

// ----- Search Functions ----- //

int searchStudents(string program, int semester, int rollNo) {
  for (int i = 0; i < studentRecords.size(); i++) {
    if (studentRecords[i].getProgram() == program && studentRecords[i].getSemester() == semester && studentRecords[i].getRollNo() == rollNo)
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

bool userExists(string username) {
  int index;
  index = searchStudents(username);

  if (index = -1)
    return false;
  else
    return true;
}

// ----- Main Function ----- //

int main() {
  system("cls");

  cout << endl;
  system("pause");
}