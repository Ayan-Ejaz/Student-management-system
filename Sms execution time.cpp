#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <chrono>
#include <thread>
#include <fstream>


struct Student {
    int YearOfAdmission = 0, Age = 0, Rollno = 0;
    std::string Name = "", Department = " ", FeesStatus = "";
    char Section = 'A';
    std::vector<std::string> CoursesRegistered;
    std::vector<bool> Attendance;
    float CGPA = 0.0;
    std::vector<float> GPA;

    Student() {}

    Student(std::string& n, int& age, int& year, int& Rollno, std::string& depart, std::string& feestatus, std::vector<std::string>& courses)
    {
        YearOfAdmission = year;
        Age = age;
        Rollno = Rollno;
        Name = n;
        Department = depart;
        FeesStatus = feestatus;
        CoursesRegistered = courses;
    }
    // Function to Initialize Attendance in accordance with no of Courses->
    void initializeAttendance(int length)
    {
        Attendance.resize(length, false);
    }
    // Function to Intialize GPA in accordance with no of Courses->
    void initializeGPA(int length)
    {
        GPA.resize(length, 0.0);
    }
    // Validators to check if information entered is correct.
    bool isValidName(std::string&) const;
    bool isValidAge(int&) const;
    bool isValidDepartment(std::string&) const;
    bool isValidSection(char&) const;
    bool isValidRollno(int&) const;
    bool isValidYearOfAdmission(int&)const;
    bool isValidFeesStatus(std::string&) const;
    bool isValidNCourses(int&) const;
};


// Function to Validate Student Name
bool Student::isValidName(std::string& name) const
{
    if (name.empty() || name.length() <= 2)
        return false;

    for (char c : name)
    {
        if (std::isdigit(c))
            return false;
    }
    return true;

}

// Function to Validate Student Age
bool Student::isValidAge(int& age) const
{
    return (age >= 17);
}

// Function to Validate Student Department
bool Student::isValidDepartment(std::string& depart) const
{
    return (depart == "CS" || depart == "BSR" || depart == "EE" || depart == "AI" || depart == "SE" || depart == "EL");
}

// Function to Validate Fees Status
bool Student::isValidFeesStatus(std::string& s) const
{
    for (char& c : s)
        c = std::tolower(c);

    return (s == "yes" || s == "no");
}

// Function to Validate Number of Courses
bool Student::isValidNCourses(int& n) const
{
    return (n > 0);
}

// Function to Validate Year Of Admission

bool Student::isValidYearOfAdmission(int& year) const
{
    std::string yearadmission = std::to_string(year);

    return !(yearadmission.length() < 4);
}

// Function to Validate Student Section
bool Student::isValidSection(char& c) const
{
    return !std::isdigit(c);
}

// Funtion to Validate Student Roll no
bool Student::isValidRollno(int& Rollno) const
{
    if (Rollno <= 0)
        return false;
    std::string s = std::to_string(Rollno);
    return (s.length() == 4);
}

struct Node {
    int height = 0;
    Student* s;
    Node* Left = NULL, * Right = NULL;

    Node(Student* ptr) {
        s = ptr;
    }
};

class TreeForStudent {
private:
    Node* root = NULL;

    int getHeight(Node* node) {
        return (node ? node->height : 0);
    }

    int getBalance(Node* node) {
        return getHeight(node->Left) - getHeight(node->Right);
    }

    void updateHeight(Node* node) {
        node->height = 1 + std::max(getHeight(node->Left), getHeight(node->Right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->Left;
        Node* T2 = x->Right;

        x->Right = y;
        y->Left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->Right;
        Node* T2 = y->Left;

        y->Left = x;
        x->Right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insertNode(Node* node, Student* student) {
        if (node == nullptr) {
            return new Node(student);
        }

        if (student->Rollno < node->s->Rollno) {
            node->Left = insertNode(node->Left, student);
        }
        else if (student->Rollno > node->s->Rollno) {
            node->Right = insertNode(node->Right, student);
        }
        else {
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);


        if (balance > 1 && student->Rollno < node->Left->s->Rollno) {
            return rotateRight(node);
        }


        if (balance < -1 && student->Rollno > node->s->Rollno) {
            return rotateLeft(node);
        }


        if (balance > 1 && student->Rollno > node->Left->s->Rollno) {
            node->Left = rotateLeft(node->Left);
            return rotateRight(node);
        }


        if (balance < -1 && student->Rollno < node->Right->s->Rollno) {
            node->Right = rotateRight(node->Right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->Left != nullptr) {
            current = current->Left;
        }
        return current;
    }

    Node* removeNode(Node* root, int Rollno) {
        if (root == nullptr) {
            return root;
        }

        if (Rollno < root->s->Rollno) {
            root->Left = removeNode(root->Left, Rollno);
        }
        else if (Rollno > root->s->Rollno) {
            root->Right = removeNode(root->Right, Rollno);
        }
        else {

            if (root->Left == nullptr || root->Right == nullptr) {
                Node* temp = root->Left ? root->Left : root->Right;


                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else {
                    *root = *temp;
                }

                delete temp;
            }
            else {

                Node* temp = minValueNode(root->Right);


                root->s = temp->s;


                root->Right = removeNode(root->Right, temp->s->Rollno);
            }
        }


        if (root == nullptr) {
            return root;
        }


        updateHeight(root);


        int balance = getBalance(root);


        if (balance > 1 && getBalance(root->Left) >= 0) {
            return rotateRight(root);
        }


        if (balance > 1 && getBalance(root->Left) < 0) {
            root->Left = rotateLeft(root->Left);
            return rotateRight(root);
        }


        if (balance < -1 && getBalance(root->Right) <= 0) {
            return rotateLeft(root);
        }


        if (balance < -1 && getBalance(root->Right) > 0) {
            root->Right = rotateRight(root->Right);
            return rotateLeft(root);
        }

        return root;
    }

    void searchByDepartment(Node* node, const std::string& department, std::vector<Node*>& result) const {
        if (!node) {
            return;
        }

        searchByDepartment(node->Left, department, result);
        if (node->s->Department == department) {
            result.push_back(node);
        }
        searchByDepartment(node->Right, department, result);
    }

    Node* searchByRollno(Node* node, int rollno) const {
        if (!node || node->s->Rollno == rollno) {
            return node;
        }

        if (rollno < node->s->Rollno) {
            return searchByRollno(node->Left, rollno);
        }
        else {
            return searchByRollno(node->Right, rollno);
        }
    }

public:
    TreeForStudent() : root(nullptr) {}


    void insert(Student* student) {
        root = insertNode(root, student);
    }

    void remove(int rollNo) {
        root = removeNode(root, rollNo);
    }

    Node* searchStudentByRollno(int rollno) const {
        return searchByRollno(root, rollno);
    }

    std::vector<Node*> searchStudentsByDepartment(const std::string& department) const {
        std::vector<Node*> result;
        searchByDepartment(root, department, result);
        return result;
    }
};

class Admin {
private:
    TreeForStudent rollnoTree;
    TreeForStudent Department;
    static int counter;
public:
	
    void AddAStudentS(int num) {
    
       
    const std::string filepath = "data.txt";


    std::ifstream file(filepath);
 
    const int targetLineNumber = num;  

    
    

    file.seekg(0, std::ios::beg);

    
    for (int currentLineNumber = 1; currentLineNumber < targetLineNumber; ++currentLineNumber) {
        if (!file.ignore(std::numeric_limits<std::streamsize>::max(), '\n')) {
            std::cerr << "File has fewer lines than the target line number." << std::endl;
            file.close();
            
        }
    }
    

  
    std::string line1, line2, line3,line4, line5, line6,line7, line8, line9; 
    std::getline(file, line1);
    std::getline(file, line2);
    std::getline(file, line3);
    std::getline(file, line4);
    std::getline(file, line5);
    std::getline(file, line6);
    std::getline(file, line7);
    std::getline(file, line8);
    std::getline(file, line9);
    
	// Add more lines as needed

    // Close the file (not strictly necessary as it will be closed when the ifstream is destructed)
    file.close();

        Student* s = new Student();
        int n;
    
        s->Name=line1;
         
		int intValue = std::stoi(line2);
        s->Age=intValue;


        s->Department=line3;

        s->Section=line4[0];


        s->Rollno = counter++;

     
        int intValue2 = std::stoi(line5);
        s->YearOfAdmission=intValue2;

      
        s->FeesStatus=line6;


        if (s->FeesStatus == "yes") {
           
            int intValue3 = std::stoi(line7);
            n=intValue3;

            s->initializeAttendance(n);
            s->initializeGPA(n);
            
                std::string temp;
              
                temp=line8;
                s->CoursesRegistered.push_back(temp);
                 temp=line9;
                s->CoursesRegistered.push_back(temp);

            }
        line1 = "";
        line2 = "";
        line3 = "";
        line4 = "";
        line5 = "";
        line6 = "";
        line7 = "";
        line8 = "";
        line9 = "";
        
        Node* newStudent = new Node(s);
        rollnoTree.insert(s);
        Department.insert(s);
        newStudent->s->CGPA = 0.0;

     
       
    }
    
    void AddAStudent() {
    
      
    const std::string filepath = "data.txt";

    std::ifstream file(filepath);
   
   
    
    std::string line1, line2, line3,line4, line5, line6,line7, line8, line9; 

    
    std::getline(file, line1);
    std::getline(file, line2);
    std::getline(file, line3);
    std::getline(file, line4);
    std::getline(file, line5);
    std::getline(file, line6);
    std::getline(file, line7);
    std::getline(file, line8);
    std::getline(file, line9);
    

    file.close();

        Student* s = new Student();
        int n;
    
        s->Name=line1;


         int intValue = std::stoi(line2);
        s->Age=intValue;


        s->Department=line3;

        s->Section=line4[0];



        s->Rollno = counter++;

    
        int intValue2 = std::stoi(line5);
        s->YearOfAdmission=intValue2;


        s->FeesStatus=line6;



        if (s->FeesStatus == "yes") {

           int intValue3 = std::stoi(line7);
            n=intValue3;

            s->initializeAttendance(n);
            s->initializeGPA(n);
             
                std::string temp;
               
                temp=line8;
                s->CoursesRegistered.push_back(temp);
                 temp=line9;
                s->CoursesRegistered.push_back(temp);

            }
        line1 = "";
        line2 = "";
        line3 = "";
        line4 = "";
        line5 = "";
        line6 = "";
        line7 = "";
        line8 = "";
        line9 = "";
        
        Node* newStudent = new Node(s);
        rollnoTree.insert(s);
        Department.insert(s);
        newStudent->s->CGPA = 0.0;

     
       
    }


    void DeleteAStudent(int rollno, const std::string& department) {

        Node* student = rollnoTree.searchStudentByRollno(rollno);

        if (student) {

            rollnoTree.remove(rollno);
            Department.remove(rollno);
        }
        else {
            std::cout << "\t\t\t\t\t\t\t\tNo such student exists." << std::endl;
        }
    }
    void ReportByRollNo(int rollno) {
        Node* temp = rollnoTree.searchStudentByRollno(rollno);
        if (temp) {
            std::cout << "\t\t\t\t\t\t\t\tSTUDENT REPORT: " << std::endl;
            std::cout << "\t\t\t\t\t\t\t\tStudent Name: " << temp->s->Name << std::endl;
            std::cout << "\t\t\t\t\t\t\t\tStudent Age: " << temp->s->Age << std::endl;
            std::cout << "\t\t\t\t\t\t\t\tStudent Year Of Admission: " << temp->s->YearOfAdmission << std::endl;
            std::cout << "\t\t\t\t\t\t\t\tStudent Roll no: " << temp->s->Rollno << std::endl;
            std::cout << "\t\t\t\t\t\t\t\tStudent Department: " << temp->s->Department << std::endl;
            if (temp->s->FeesStatus == "yes")
            {
                std::cout << "\t\t\t\t\t\t\t\tFees Status: Paid" << std::endl;
                std::cout << "\t\t\t\t\t\t\t\tCourses Registered: " << std::endl;
                for (const std::string& s : temp->s->CoursesRegistered)
                    std::cout << "\t\t\t\t\t\t\t\t" << s << std::endl;
            }
            else
            {
                std::cout << "\t\t\t\t\t\t\t\t*Fees Status: Pending*" << std::endl;
            }


        }
        else {
            std::cout << "\t\t\t\t\t\t\t\tNo such student exists.\n\n" << std::endl;
        }
    }
    void ModifyData(int rollno, const std::string& department) {
        Node* student = rollnoTree.searchStudentByRollno(rollno);

        if (student && student->s->Department == department) {
            std::cout << "\n\n\t\t\t\t\t\t\t\tWhat information would you like to modify?: " << std::endl;
            std::cout << "\n\t\t\t\t\t\t\t\t1. Name\n\t\t\t\t\t\t\t\t2. Age\n\t\t\t\t\t\t\t\t3. Year of Admission\n\t\t\t\t\t\t\t\t4. Section\n\t\t\t\t\t\t\t\t5. Roll no\n\t\t\t\t\t\t\t\t6. Department\n\t\t\t\t\t\t\t\t7. Fees Status\n";
            int choice;
            std::cout << "\t\t\t\t\t\t\t\tEnter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1: {
                std::cout << "\t\t\t\t\t\t\t\tEnter the new name: ";
                std::string newName;
                std::cin.ignore();
                std::getline(std::cin, newName);
                if (student->s->isValidName(newName)) {
                    student->s->Name = newName;
                    std::cout << "\n\n\t\t\t\t\t\t\t\tName updated successfully.\n\n" << std::endl;
                }
                else {
                    std::cout << "\n\n\t\t\t\t\t\t\t\tInvalid name. Name not updated.\n\n" << std::endl;
                }
                break;
            }
            case 2: {
                std::cout << "\t\t\t\t\t\t\t\tEnter the new age: ";
                int newAge;
                std::cin >> newAge;
                if (student->s->isValidAge(newAge)) {
                    student->s->Age = newAge;
                    std::cout << "\n\n\t\t\t\t\t\t\t\tAge updated successfully.\n\n" << std::endl;
                }
                else {
                    std::cout << "\n\n\t\t\t\t\t\t\t\tInvalid age. Age not updated.\n\n" << std::endl;
                }
                break;
            }
            case 3: {
                std::cout << "\t\t\t\t\t\t\t\tEnter the new Year of Admission: \n\n";
                int newYearofAdmission;
                std::cin >> newYearofAdmission;
                if (student->s->isValidYearOfAdmission(newYearofAdmission)) {
                    student->s->YearOfAdmission = newYearofAdmission;
                    std::cout << "\n\n\t\t\t\t\t\t\t\tYear of Admission updated successfully.\n" << std::endl;
                }
                else {
                    std::cout << "\n\n\t\t\t\t\t\t\t\tInvalid Year of Admission. Year of Admission not updated.\n\n" << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "\t\t\t\t\t\t\t\tEnter the new Year of Section: ";
                char newSection;
                std::cin >> newSection;
                if (student->s->isValidSection(newSection)) {
                    student->s->Section = newSection;
                    std::cout << "\n\n\t\t\t\t\t\t\t\tSection updated successfully.\n\n" << std::endl;
                }
                else {
                    std::cout << "\n\n\t\t\t\t\t\t\t\tInvalid Section. Section not updated.\n\n" << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "\n\n\t\t\t\t\t\t\t\tEnter the new Roll no: ";
                int newRollno;
                std::cin >> newRollno;
                if (student->s->isValidRollno(newRollno)) {
                    student->s->Rollno = newRollno;
                    std::cout << "\n\n\t\t\t\t\t\t\t\tRollno updated successfully.\n\n" << std::endl;
                }
                else {
                    std::cout << "\n\n\t\t\t\t\t\t\t\tInvalid Rollno. Rollno not updated.\n\n" << std::endl;
                }
                break;
            }
            case 6: {
                std::cout << "\t\t\t\t\t\t\t\tEnter the new Department: ";
                std::string newDepartment;
                std::cin >> newDepartment;
                if (student->s->isValidDepartment(newDepartment)) {
                    student->s->Department = newDepartment;
                    std::cout << "\n\n\t\t\t\t\t\t\t\tDepartment updated successfully.\n\n" << std::endl;
                }
                else {
                    std::cout << "\t\t\t\t\t\t\t\tInvalid Department. Department not updated." << std::endl;
                }
                break;
            }
            case 7: {
                std::cout << "\t\t\t\t\t\t\t\tEnter the new Fees status: ";
                std::string newFeesStatus;
                std::cin >> newFeesStatus;
                if (student->s->isValidFeesStatus(newFeesStatus)) {
                    student->s->FeesStatus = newFeesStatus;
                    std::cout << "\t\t\t\t\t\t\t\tFeesStatus updated successfully." << std::endl;
                }
                else {
                    std::cout << "\t\t\t\t\t\t\t\tInvalid FeesStatus. FeesStatus not updated." << std::endl;
                }
                break;
            }
            default:
                std::cout << "\t\t\t\t\t\t\t\tInvalid choice. No information modified." << std::endl;
            }
        }
        else {
            std::cout << "\t\t\t\t\t\t\t\tNo such student in the specified department exists." << std::endl;
        }
    }
    void ReportByDepartment(const std::string& department) {
        std::vector<Node*> result = Department.searchStudentsByDepartment(department);
        if (!result.empty()) {

            std::cout << "\t\t\t\t\t\t\t\tSTUDENT REPORTS FOR DEPARTMENT " << department << ": " << std::endl;
            for (const auto& temp : result) {
                std::cout << "\t\t\t\t\t\t\t\tStudent Name: " << temp->s->Name << std::endl;
                std::cout << "\t\t\t\t\t\t\t\tStudent Age: " << temp->s->Age << std::endl;
                std::cout << "\t\t\t\t\t\t\t\tStudent Year Of Admission: " << temp->s->YearOfAdmission << std::endl;
                std::cout << "\t\t\t\t\t\t\t\tStudent Section: " << temp->s->Section << std::endl;
                std::cout << "\t\t\t\t\t\t\t\tStudent Roll no: " << temp->s->Rollno << std::endl;
                std::cout << "\t\t\t\t\t\t\t\tStudent Department: " << temp->s->Department << std::endl;
                if (temp->s->FeesStatus == "yes")
                {
                    std::cout << "\t\t\t\t\t\t\t\tFees Status: Paid" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\tStudent CGPA: " << temp->s->CGPA << std::endl;

                    std::cout << "\t\t\t\t\t\t\t\tCourses Registered: " << std::endl;
                    for (const std::string& s : temp->s->CoursesRegistered)
                        std::cout << "\t\t\t\t\t\t\t\t" << s << std::endl;
                }
                else
                {
                    std::cout << "\n\n\t\t\t\t\t\t\t\t*Fees Status: Pending*\n\n" << std::endl;
                }
            }
        }
        else {
            std::cout << "\n\n\t\t\t\t\t\t\t\tNo students found in the department \n\n" << department << std::endl;
        }
    }
    TreeForStudent& getDepartmentInformation()
    {
        return Department;
    }


};

int Admin::counter = 1000;

void Merge(std::vector<Node*>& students, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Node*> leftArray(students.begin() + left, students.begin() + left + n1);
    std::vector<Node*> rightArray(students.begin() + mid + 1, students.begin() + mid + 1 + n2);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArray[i]->s->CGPA >= rightArray[j]->s->CGPA) {
            students[k] = leftArray[i];
            i++;
        }
        else {
            students[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        students[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        students[k] = rightArray[j];
        j++;
        k++;
    }
}

void MergeSort(std::vector<Node*>& students, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSort(students, left, mid);
        MergeSort(students, mid + 1, right);

        Merge(students, left, mid, right);
    }
}

void SortByCGPA(std::vector<Node*>& students) {
    MergeSort(students, 0, students.size() - 1);


    std::cout << "\n\n\t\t\t\t\t\t\t\tSorted Students by CGPA:" << std::endl;
    for (const auto& student : students) {
        std::cout << "\n\n\t\t\t\t\tName: " << student->s->Name << "\t\tDepartment: " << student->s->Department
            << "\t\tRoll No: " << student->s->Rollno << "\t\tCGPA: " << student->s->CGPA << std::endl;
    }
    std::cout << "\n\n" << std::endl;
}

void setConsoleColor(int text, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (background << 4));
}


void DisplayHeader()
{

    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    int P = 11;
    SetConsoleTextAttribute(console_color, P);
    std::cout << "\n";

    std::cout << "\t\t\t\t\t" << "##############################################################################\n"
        "\t\t\t\t\t""#                                                                            #\n"
        "\t\t\t\t\t""#              *  WELCOME TO THE STUDENT MANAGEMENT SYSTEM  *                #\n"
        "\t\t\t\t\t""#                                                                            #\n"
        "\t\t\t\t\t""#                        **  FAST  NUCES  **                                 #\n"
        "\t\t\t\t\t""#                                                                            #\n"
        "\t\t\t\t\t""##############################################################################\n";

}



void UserRoleAndAccess()
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    int P = 11;
    SetConsoleTextAttribute(console_color, P);
    std::cout << "\n";
    int selection = 0;
    Admin a;
    Student* p = new Student();
    Node* student = new Node(p);

    a.AddAStudent();
    int k=10;
    for(int i=0;i<15000;i++)
    {
    	a.AddAStudentS(k);
	k=k+9;	
	}
    
    a.ReportByDepartment("CS");	 
 
}


int main() {

    DisplayHeader();
    UserRoleAndAccess();
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution Time: " << duration.count() / 10000.0 << " seconds" << std::endl;
}