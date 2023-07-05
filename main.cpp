#include <iostream>
using namespace std;

class User {
private:
  string username;
  string password;
  string firstName;
  string lastName;

public:
  static int totalUsers;
  User(string un = "", string pw = "", string fN = "", string lN = "") : username(un), password(pw), firstName(fN), lastName(lN) {}

  // ----- Setters ----- //
  void setUsername(string un) { username = un; }
  void setPassword(string pw) { password = pw; }
  void setFirstName(string fN) { firstName = fN; }
  void setLastName(string lN) { lastName = lN; }

  // ----- Getters ----- //
  string getUsername() { return username; }
  string getPassword() { return password; }
  string getFirstName() { return firstName; }
  string getLastName() { return lastName; }

  // ----- Input Setters ----- //
};

class Admin : public User {
private:
public:
};

class Student : public User {
private:
  string program;
  string semester;
  int rollNo;

public:
  static int totalStudents;
  Student(string un = "", string pw = "", string fN = "", string lN = "", string p, string s, int rN) : User(un, pw, fN, lN), program(p), semester(s), rollNo(rN) {}

  // ----- Setters ----- //
  void setProgram(string p) { program = p; }
  void setSemester(string s) { semester = s; }
  void setRollNo(int rN) { rollNo = rN; }

  // ----- Getters ----- //
  string getProgram() { return program; }
  string getSemester() { return semester; }
  int getRollNo() { return rollNo; }

  // ----- Input Setters ----- //
};

// ----- Initializing Static Variables ----- //
int User::totalUsers = 0;
int Student::totalStudents = 0;

int main() {
  return 0;
}