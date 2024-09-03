#include <fstream>       
#include <iostream>   
#include <string>
#include <vector>
using namespace std; 
// defining the function prototypes
void adminRegister();
bool passcheckAdmin(string password, string username, string instituteID);
void admin();    // all functions of admins are present in this
void studentRegister();
bool passcheckStu(string password, string roll_number);
bool addingDetails(string dataToBeAdded, string target_file);//to add details to the file of newly registered users
void student();     // all functions of students are present in this
void readFile(string filename);    // to print the data of a file
void createProfile(); // creates a report card file for the student
bool registrationCheck(string target, string filename);   //to check whether a user has registered or not
void addingStudentGrades(ofstream &file);  // adding student's grades to his/her report card
/****below three functions are used to edit the grades of the student****/
void readingIntoVector(string fileName, vector<vector<string>> *v, int x);
void modifyingVector(string fileName, vector<vector<string>> *v);
void printingVectorIntoFile(string fileName, vector<vector<string>> *v);
float calculateSPI(float arr[],int courses);
float calculatingCPI(vector<vector<string>> v);
void changePassword(string oldPassword, string newPassword); // changes password of students
bool checkingFileExistance( string target) // to check whether a file exists or not
{
  ifstream file(target);
  return file.good();
}
float calculateSPI(float arr[], int courses) 
{
  float sum = 0, SPI;
  for (int i = 0; i < courses; i++)
  sum += (arr[i] * 4);
  SPI = sum / (courses * 4);
  return SPI;
}
float calculatingCPI(vector<vector<string>> v) {
  float sumofSPI = 0,semCount = 0,ans; //traversing through whole student file(stored in 2D vector) to collect SPI's
  for (int i = 9; i < v.size(); i = i + 6) {
    sumofSPI += stof(v[i][1]);
    semCount++;
  }
  ans = sumofSPI / semCount;
  return ans;
}
void createProfile() {
  string fileName;
  cout << "Enter the details of the student you want to add in the following format:" << endl
       << "firstName,last 4 digit of your roll number.csv" << endl
       << "Example - Abhinav,1004.csv" << endl;
  cin >> fileName; 
  if (checkingFileExistance(fileName) == false) {
    ofstream file(fileName);
    if (file.is_open()) {
      file << "ACADEMIC ROLL RECORD , IIT INDORE," << endl;
      file << "Name," << "    ," << "Roll no.," << "   ," << "Department," << endl;
      string name ,  rn, dep;
      cout << "Enter the name of the student: ";
      cin.ignore();
      getline(cin, name);
      cout << "Enter the roll number of the student: ";
      cin >> rn;
      cout << "Enter the department of the student: ";
      cin.ignore();
      getline(cin, dep);
      file << name << ",    ," << rn << ",    ," << dep << "," << endl;
      file << "....................................," << endl;
      file << "GRADES OF THE CANDIDATE," << endl;
      file.close();
      cout << "Student's profile successfully created." << endl;
      file.close();
      int a;
      cout << "Enter 1 if you want to add grades of the candidate or 0 if you want to skip this for now: "<< endl;
      cin >> a;
      while (a != 0 && a != 1) 
      {
        cout << "Please enter a valid input: " << endl;
        cin >> a;
      }
      if (a == 1) 
      {
        ofstream file(fileName, ios::app);
        addingStudentGrades(file);
      } else if (a == 0)
        cout << "You have successfully created the student's profile" << endl
             << "You can add his/her grades later" << endl;
    }
    else
      cout << "Error in creating/writing the student profile" << endl
           << "Try again later" << endl;
  }
  else {
    string filename;
    cout << "The student's profile already exists" << endl
         << "Please do not try to create the profile again" << endl
         << "You can now add the grades directly" << endl;
    cout << "Enter the details of the student you want to add in the following format:" << endl
         << "firstName,last 4 digit of  roll number.csv" << endl
         << "Example - Abhinav,1004.csv" << endl;
    cin>> fileName;
    ofstream file(fileName, ios::app);
    if (file.is_open())
      addingStudentGrades(file);
  }
}

void addingStudentGrades(ofstream &file) {
  int a = 1;
  while (a == 1) {
    int sem_no, courses;
    cout << "Enter the semester number :";
    cin >> sem_no;
    file << "Semester" + to_string(sem_no) + "," << endl;
    cout << "Enter the number of courses :";
    cin >> courses;
    file << "Number of courses for this semester :," << courses << "," << endl;
    file << "Subject code :-,";
    float grades[courses];
    for (int i = 0; i < courses; i++) {
      string course_name;
      cout << "Enter the course code :";
      cin.ignore();
      getline(cin, course_name);
      cout << "Enter the grades of the course :";
      cin >> grades[i];
      file << course_name << ",";
    }
    file << endl;
    file << "Grades alloted:-,";
    for (int i = 0; i < courses; i++)
      file << grades[i] << ",";
    file << endl;
    float SPI = calculateSPI(grades, courses);   // ppassing the array of grades to the calculateSPI function
    file << "SPI for this semester :," << SPI << "," << endl
         << "....................," << endl;
    cout << "If you want to add grades of another semester, enter 1 else enter 0 :";
    cin >> a;
    while (a != 0 && a != 1) {
      cout << "Please enter a valid input" << endl;
      cin >> a;
    }
  }
  cout << "Okay, the student's record has been stored"<< endl;
  file.close();
}
void readingIntoVector(string fileName, vector<vector<string>> *v,int x)
// x is used for checking from where the func is called and then execute this function accordingly
{
  if (x != 1) {
    cout << "Currently , the student's profile looks like :" << endl
         << endl
         << endl;
    readFile(fileName);
  }
  ifstream file2(fileName);
  string line;
  vector<string> row;
  int start, end;
  if(file2.is_open()){
  while (getline(file2, line))
  {
    start = 0;
    end = line.find(',', start);
    while (end != -1 && start < line.length())
    {
      row.push_back(line.substr(start, end - start));
      start = end + 1;
      end = line.find(',', start);
    }
    (*v).push_back(row);
    row.clear();
  }
    file2.close();
 }
  else
    cout<< "Error! File not found"<<endl;
}
// the logic used in modifyingVector function is based on the format of the student's profile
void modifyingVector(string fileName, vector<vector<string>> *v) {
  int n;
  cout << "Enter the number of semesters for which you want to modify :";
  cin >> n;
  // looping for editing multiple semesters at a time 
  for(int m=1 ; m<=n ; m++) {           // outer for loop started
    int sem , k=0;    // k is used to check whether the semester is present or not
    cout << "Enter the semester number whose grades you want to modify :";
    cin >> sem;
    string s = "Semester" + to_string(sem);
    for (int i = 5; i < (*v).size(); i = i + 6) {           // inner for loop started
      if ((*v)[i][0] == s) 
      {                   //primary if block started
        k++;   // if the semester is present then k is incremented which will to be used to break inner for loop
        cout << "At present, the number of courses for this semester is :"
             << (*v)[i + 1][1] << endl;
        int a;
        cout << "Press 1 to add courses in this semester" << endl
             << "Press 2 to delete courses in this semester" << endl
             << "Press 3 to modify grades of these courses" << endl;
        cin >> a;
        while ( a<1 || a>3) {    // admin is not allowed to proceed further if he enters a wrong input
          cout << "Please enter a valid input" << endl;
          cin >> a;
        }
        if(a==1) {  
          int b;
          cout << "Enter the number of courses you want to add :";
          cin >> b;
          for (int j = 1; j <= b; j++) {
            string course_name;
            float grades;
            cout << "Enter the course code :";
            cin.ignore();
            getline(cin, course_name);
            cout << "Enter the grades of the course :";
            cin >> grades;
            (*v)[i + 2].push_back(course_name);
            (*v)[i + 3].push_back(to_string(grades));
          }
          (*v)[i + 1][1] = to_string( stoi((*v)[i + 1][1]) + b); //updating the number of courses in the smester
          cout << "Courses successfully added to this semester" << endl; 
        }
        
        else if(a==2) {    
          int c;
          cout << "Enter the number of courses you want to delete :";
          cin >> c;
          for (int j = 1; j <= c; j++) {
            int d = 0;
            string course_name;
            cout << "Enter the code of the course you want to delete :";
            cin.ignore();         // if a particular course is present two times , then its first occurence is deleted
            getline(cin, course_name);
            vector<string>:: iterator k = (*v)[i+2].begin() + 1 , t ,u ;     // k is used for finding porition of course
            for (  ; k != (*v)[i + 2].end(); k++) {      // t is used for copying value of k beacuse we will change k
              if (*k == course_name) {                   // u is used for deleting grades the course
                t=k;                                      
                d++;       // d is incremented if the course is found
                break;
              }
            }
            auto w = t - (*v)[i+2].begin();       // w is used to pass on the position to u
            k-- ;          //changing k because k should not point the element which is going to be deleted
            if (d == 0)
              cout << "Course is already not present in this semester" << endl;
            else {
              (*v)[i+2].erase(t);
               u =  (*v)[i+3].begin() + w; 
              (*v)[i+3].erase(u);
              cout << "Courses successfully deleted from this semester" << endl;
            }
          }
              (*v)[i + 1][1] = to_string( stoi((*v)[i + 1][1]) -c); //updating the number of courses in the smester
        }
        
        else if(a==3){  
          int e;
          cout << "Enter the number of courses whose grades you want to modify "
                  ":";
          cin >> e;
          for (int j = 1; j <= e && j < (*v)[i + 2].size(); j++) {
            string course_name;
            float grades;
            int f = 0;
            cout << "Enter the code of the course whose grades you want to "
                    "modify :";
            cin.ignore();
            getline(cin, course_name);
            cout << "Enter the new grades of the course :";
            cin >> grades;
            for (int k = 1; k < (*v)[i + 2].size(); k++) {
              if ((*v)[i + 2][k] == course_name) {
                (*v)[i + 3][k] = to_string(grades);
                f++;
              }
            }
            if (f == 0)
              cout << "Course is not present in this semester" << endl;
          }
          cout << "Grades updated successfully" << endl; 
        }
        
     }     // primary if block ended
  
        float arr[(*v)[i+3].size() - 1]; // storing new grades in an array
        for (int j = 1; j < (*v)[i+3].size(); j++)
          arr[j - 1] = stof((*v)[i + 3][j]);
        
        float SPI = calculateSPI(arr, (*v)[i+3].size() - 1); // passing the array of new grades to find new SPI and then update it in the vector
         (*v)[i + 4][1] = to_string(SPI);
            
      if (k == 1) // k was incremented when the semester was present,so no need to check for the further semester
        break;     // hence breaking the inner for loop
    }  // inner for loop ended   (grades of the semester edited)

      if (k == 0)   // if the semester asked by the admin to edit is not present in the academic record, k wont be                                                       incremented and hence the following code will be executed 
      cout << "This semester you asked previously was not present in the student record" << endl;
  } // closure of outer loop
}
void printingVectorIntoFile(string fileName, vector<vector<string>> *v) {
  ofstream file9(fileName);
  for (int i = 0; i < (*v).size(); i++) {
    for (int j = 0; j < (*v)[i].size(); j++)
      file9 << (*v)[i][j] << ",";
    file9 << endl;
  }
   
}
void adminValid() {
  cout << "Press 1 to register.\nPress 2 if you have already registered"<< endl;
  int a;
  cin >> a;
  if (a == 1)
    adminRegister();
  else if (a == 2) {

    string name, instituteID, password;
    cout << "Enter your name" << endl;
    cin.ignore();
    getline(cin, name);
    cout << "Enter the institute ID" << endl;
    cin >> instituteID;
    if ((registrationCheck(instituteID, "adminDetails.csv")) == true) {    // checking if already registered or not
      cout << "Enter the password"<< endl; // password details in readme file in github
      cin >> password;
      if (passcheckAdmin(password, name, instituteID) == true) 
        admin();  // admin is allowed to access the admin menu only when he uses correct password
      else
        cout << "WRONG PASSWORD \nTry again with the correct password" << endl;
    }
    else if ((registrationCheck(instituteID, "adminDetails.csv")) == false) {
      int a = -1;
      cout << "You have not registered yet" << endl
           << "Do you want to register now?" << endl
           << "Press 1 for yes and 0 for no" << endl;
      cin >> a;
      while (a != 0 && a != 1) {
        cout << "Please enter a valid input: " << endl;
        cin >> a;
      }
      if (a == 1)
        adminRegister();
      else
        cout << "Okay. You can register later" << endl;
    }
  } else
    cout << "Please enter a valid option" << endl;
}
void adminRegister() {
  string name, username, instituteID, department, contact_no,
      password;
  cout << "Enter the name" << endl;
  cin.ignore();
  getline(cin, name);
  cout << "Enter the institute ID" << endl;
  cin >> instituteID;
  cout << "Enter your department(eg. CSE , Electrical Engineering etc.)"<< endl;
  cin.ignore();
  getline(cin, department);
  cout << "Enter your contact number" << endl;
  cin >> contact_no;
  string forAddingDetails = name + "," + instituteID + "," +department + "," + contact_no + ",";
  cout << "Enter the password" << endl;   // password details in readme file in github
  cin >> password;
  if(registrationCheck(instituteID, "adminDetails.csv") == false) //cannot register again if already registered
  {
  if (passcheckAdmin(password, name, instituteID)) //admin is registered only when he enters correct password
   {
    if (addingDetails(forAddingDetails, "adminDetails.csv"))//checking whether registration is done or not
      admin(); //admin is allowed to access the admin menu only when his details are registered in adminDetails.csv
  } 
  else
    cout << "WRONG PASSWORD \nTry again with the correct password" << endl;
  }
  else {
    if(passcheckAdmin(password , name, instituteID)){
    cout << "You have already registered" << endl
         << "Please don't register again." << endl;
         admin();
       }
    else
      cout<< "WRONG PASSWORD \nTry again with correct password" << endl;
    }
}
bool passcheckAdmin(string password, string name,string instituteID) {
  string verify;
  for (int i = 0; i < name.length(); i++) {
    if (name[i] >= 'A' && name[i] <= 'Z')
      verify += name[i];
  }
  verify += "*" + instituteID;
  if (verify == password)
    return true;
  else
    return false;
}
void admin() {
  cout << "WELCOME TO THE ADMINISTRATION PORTAL" << endl << endl;
  int t=1;
  while(t==1){
  int a;
  cout << "Press 1 to create a studentProfile." << endl
       << "Press 2 to view and add grades to a already created student profile."<< endl
       << "Press 3 to view and edit student's academic record. " << endl
       << "Press 4 to only view a student's academic record." << endl
       << "Press 5 to view the studentDetails.csv file." << endl
       << "Press 6 to view the adminDetails.csv file." << endl
       << "Press 7 to exit.\n\n";
  cin >> a;
  // admin wont be able to proceed ahead if he enters a wrong input
  while (a < 1 || a > 7) {
    cout << "Please enter a valid input" << endl;
    cin >> a;
  }
  switch (a) {
  case 1:
    createProfile();
    break;
  case 2: {
    string fileName; 
    cout << "Enter the details of the student for whom you want to add grades in the following format."<< endl
         << "firstName,last 4 digit of your roll number.csv" << endl
         << "Example - Abhinav,1004.csv" << endl;
    cin >> fileName;
    if (checkingFileExistance(fileName)) {
      cout << "Currently , the student profile looks like this: " << endl << endl;
      readFile(fileName);
      ofstream file(fileName, ios::app);
      if (file.is_open())
        addingStudentGrades(file);
      else
        cout << "Error in adding grades the student profile." << endl;
    } else {
      cout << "The student's profile does not exist" << endl
           << "Please create the profile first" << endl;
      createProfile();
    }
  } break;
  case 3: {
    cout << "Enter the student's information in the following format :"<< endl
         << "firstName,last 4 digit of roll number.csv" << endl
         << "Example - Abhinav,1004.csv" << endl;
    string fileName;
    cin >> fileName;
    if (checkingFileExistance(fileName)) {
      vector<vector<string>> fileData;
      readingIntoVector(fileName, &fileData, 0);
       
      modifyingVector(fileName, &fileData);
       
      printingVectorIntoFile(fileName, &fileData);
      int a;
      cout << "The student's profile has been updated" << endl
           << "If you want to see the updated profile , enter 1 else enter 0 :";
      cin >> a;
      while (a != 0 && a != 1) {
        cout << "Please enter a valid input" << endl;
        cin >> a;
      }
      if (a == 1)
        readFile(fileName);
      else
        cout << "Okay. You can see the updated profile later" << endl;
    } else {
      cout << "The student's profile does not exist" << endl
           << "Please create the profile first" << endl;
      createProfile();
    }

  } break;
  case 4: {
    cout << "Enter the student's information in the following format :" << endl
         << "firstName,last 4 digit of roll number.csv" << endl
         << "Example - Abhinav,1004.csv" << endl;
    string fileName;
    cin >> fileName;
    readFile(fileName);
  } break;
  case 5:
    readFile("studentDetails.csv");
    break;
  case 6:
    readFile("adminDetails.csv");
    break;
  case 7:
    cout << "THANKYOU FOR VISITING THE ADMINISTRATION PORTAL" << endl;
    break;
   
  }
    if(a==7)    // means admin want to exit
      break;
    cout << "Do you want to continue in the admin portal?" << endl 
         << "Press 1 for yes and 0 for no" << endl;
    cin >> t;
    while (t != 0 && t != 1)
      {
        cout << "Please enter a valid input" << endl;
        cin >> t;
      }
    if(t==0)
      cout << "THANKYOU FOR VISITING THE ADMIN PORTAL" << endl;
 }  
}
void studentValid() {
  cout << "Press 1 to register.\nPress 2 if you have already registered."<< endl;
  int a;
  cin >> a;
  while(a!=1 && a!=2)
    {
       cout << "Please input a valid option" << endl;
       cin >> a;
    }
  if (a == 1)
    studentRegister();
  else  {
    string  roll_number, password;
    cout << "Enter the roll number" << endl;
    cin >> roll_number;
    if ((registrationCheck(roll_number, "studentDetails.csv")) == true) {
      cout <<"Enter the password"<<endl;//password details in readme file and studentDetails.csv in password column
      cin >> password;
      if (passcheckStu(password , roll_number))
        student();
      else
        cout << "WRONG PASSWORD \nTry again with the correct password" << endl;
    } else if ((registrationCheck(roll_number, "studentDetails.csv")) == false) {
      int m = -1;
      cout << "You have not registered yet" << endl
           << "Do you want to register now? " << endl
           << "Press 1 for yes and 0 for no" << endl;
      cin >> m;
      while (m != 0 && m != 1) {
        cout << "Please enter a valid input: " << endl;
        cin >> m;
      }
      if (m == 1)
        studentRegister();
      else
        cout << "Okay. You can register later" << endl;
    }
  }
}
void studentRegister() {               
  string name, roll_number, department, password;
  cout << "Enter the name" << endl;
  cin.ignore();
  getline(cin, name);
  cout << "Enter the roll number" << endl;
  cin >> roll_number;
  cout << "Enter your department(eg. CSE , Electrical Engineering etc.)"<< endl;
  cin.ignore();
  getline(cin, department);
  if(registrationCheck(roll_number , "studentDetails.csv") == false)
  {
  string forAddingDetails = name + "," + roll_number + "," + department + "," + roll_number + ",";
  cout << "Enter the password" << endl;
  cin >> password;
  if (roll_number == password)   // student is registered only when he enters the correct password
  {
    if (addingDetails(forAddingDetails, "studentDetails.csv"))
      student();   // student is allowed to access the student menu only when his details are successfully                                registered in studentDetails.csv
  } else
    cout << "WRONG PASSWORD \nTry again with the correct password" << endl;
  }
  else    // student is not allowed to register if he has already registered
    cout << "You are already registered , please don't register again" << endl;
}
bool addingDetails(string dataToBeAdded, string target_file) {
  ofstream file(target_file, ios::app);
  if (file.is_open()) {
  file<<dataToBeAdded<<endl;
    file.close();
    cout << "You are registered successfully" << endl;
    return true;
  } else {
    cout << "Error in registering!!" << endl
         << " Please try again later." << endl;
    return false;
  }
}
bool passcheckStu(string password,string roll_number) 
{                                     
  string line , targetCheck="", passCheck="";
  int k=0;
  ifstream file("studentDetails.csv");
  while (getline(file, line)) 
  {
    int start = 0, end = line.find(',');
    while (end != -1 && start < line.length()) 
    {
      targetCheck = line.substr(start, end - start);
      if (targetCheck == roll_number) {
        k++;
        start = end + 1;        //verifying password logic is based on the format of studentDetails.csv file
        end = line.find(',', start);
        start = end + 1;
        end = line.find(',', start);
        passCheck = line.substr(start, end - start);
        break;
      }
      start = end + 1;
      end = line.find(',', start);
    }
    if(k==1)
      break;
  }
  if (passCheck == password)//password-entered by user while signin //// passCheck-password in studentDetails.csv file
    return true;
  else
    return false;
}
bool registrationCheck(string target, string filename) 
// for admins, the registration is checked by their unique instituteID
// for students, the registration is checked by their unique roll number
{
  ifstream file(filename);
  string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      int start = 0, end = line.find(',');
      string targetCheck;
      while (end != -1 && start < line.length()) {
        targetCheck = line.substr(start, end - start);
        if (targetCheck == target) {
          file.close();
          return true;
        }
        start = end + 1;
        end = line.find(',', start);
      }
    }
    file.close();
    return false;

  } else {
    cout << "Registration verification denied.\nError in accessing the details file"<< endl;
    return false;
  }
}
void student() {
  int a;
  cout << "Press 1 to view your academic record." << endl
       << "Press 2 to change your password." << endl
       << "Press 3 to exit." << endl;
  cin >> a;
  while (a != 1 && a != 2 && a!=3) {
    cout << "Please enter a valid input" << endl;
    cin >> a;
  }
  if (a == 1) {
    cout << "WELCOME TO THE STUDENT ACADEMIC ROLL\n\n";
    cout << "For viewing your academic details , Enter the information in the following format :"<< endl
         << "firstName,last 4 digit of your roll number.csv" << endl
         << "Example - Abhinav,1004.csv" << endl;
    string fileName;
    cin >> fileName;
    cout << endl << endl;
    readFile(fileName);
    vector<vector<string>> forCPI;   
    readingIntoVector(fileName, &forCPI, 1);   // to store the data of the student in a  2D vector
    float CPI = calculatingCPI(forCPI);
    cout << "Your CPI(for given semesters) is : " << CPI << endl;  // if the  student file is not there then CPI                                                                           will be shown as nan
  } else if(a==2)
  {
    string oldPass, newPass;
    cout << "Enter your current password" << endl;
    cin.ignore();
    getline(cin, oldPass);
    cout << "Enter your new password" << endl;
    cin.ignore();
    getline(cin, newPass);
    changePassword(oldPass, newPass);
  }
  else
    cout << "THANKYOU FOR VISITING THE STUDENT PORTAL" << endl;
}
void changePassword(string old_password, string new_password) {
  string line,newFileData="";//newFileData is the data which will be written in the new file(having updated pass)
  ifstream file0("studentDetails.csv");
  if(file0.is_open())
  {
  while (getline(file0, line))   {
    int start = 0, end = line.find(',');
    string targetCheck;
    while (end != -1 && start < line.length())  {
      targetCheck = line.substr(start, end - start);
      if (targetCheck == old_password && end==line.length()-1) 
      //end==line.length()-1 (needed to use this because in beginning,password is same as roll number.)                   // So this is to prevent the replacement of roll number with new password.
        newFileData += new_password + ",";
      else 
        newFileData+=targetCheck + ",";
      start = end + 1;
      end = line.find(',', start);
    }
    newFileData+= "\n";
    line="";
  }                
  file0.close();
}
  else
    cout<< "Password change failed(There is an issue in reading studentDetails.csv file)" << endl; 
  ofstream file1("studentDetails.csv");
  if(file1.is_open()) {
    file1 << newFileData;   // overwriting the old file with new data(having updated password)
    cout << "Your password has been changed successfully. Please remember this password." << endl 
         << "If you forget it, you may take help of a admin who has the access of password details" << endl;
    file1.close();                
  }
  else
  cout<< "Password change failed(There is an issue in writing to studentDetails.csv file)"<< endl; 
}
  void readFile(string filename) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
      while (getline(file, line)) {
        cout << line << endl;
      }
      file.close();
    } else {
      cout
          << "Error: Unable to open file(Maybe the file is not made or uploaded yet)"<< endl
          << "THANK YOU FOR VISITING" << endl;
    }
  }
  int main() 
{  
//the files studentDetails.csv & adminDetails.csv need to be uploaded in the same directory as the mainPrg.cpp file
//absence of these files will lead to the creation of them using ofstream
 // if new will create , then registration should be again done 
// below are two if blocks which are used to create the files if they are not present
//program cannot proceed ahead without presence of these files(whole registration process is based on these files)
  if(checkingFileExistance("studentDetails.csv") == false )
    {
      ofstream file6( "studentDetails.csv");
      if(file6.is_open())
      {
        file6 << "Welcome to students details file," << endl;
        file6 << "Name,Roll_number,Department,Password," << endl;
        file6.close();
      }
      else{
        cout << "Error in creating/writing to studentDetails.csv file" << endl
             << "Program terminated" << endl;
        return 0;
      }
    }
    if(checkingFileExistance("adminDetails.csv") == false )
      {
        ofstream file7( "adminDetails.csv");
        if(file7.is_open())
        {
          file7 << "Welcome to admin details file," << endl;
          file7 << "Name,institute ID,Department,Contact no.," << endl;
          file7.close();
        }
        else{
          cout << "Error in creating/writing to adminDetails.csv file" << endl
               << "Program terminated" << endl;
          return 0;
        }
      }
    
    cout << "Welcome to IIT INDORE student record roll system" << endl << endl;
    int a;
    cout << "Press 1 if you are a student." << endl
         << "Press 2 if you are a admin." << endl;
    cin >> a;
    while ( a!=1 && a!=2) {
      cout << "Please enter a valid option" << endl;
      cin >> a;
    }
    if (a == 1) {
      studentValid();
    } else {
      adminValid();
    }
    return 0;
  }
