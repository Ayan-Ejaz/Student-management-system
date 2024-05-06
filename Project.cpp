#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>


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

    return (depart == "CS" || depart == "BSR" || depart == "EE" || depart == "AI" || depart == "SE" || depart == "EL"  ||depart == "cs" || depart == "bsr" || depart == "ee" || depart == "ai" || depart == "se" || depart == "el");
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

    return (yearadmission.length() == 4 && year>=2000 && year<2024);
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

    Node* FindSuccessor(Node* node) {
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

                Node* temp = FindSuccessor(root->Right);


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
    void AddAStudent() {

        Student* s = new Student();
        int n;
        std::cin.ignore();

        std::cout << "\n\n\t\t\t\t\t\t\t\tEnter the Name: ";
        std::getline(std::cin, s->Name);

        while (!s->isValidName(s->Name))
        {
            std::cout << "\t\t\t\t\t\t\t\tInvalid Information, Enter again: ";
            std::getline(std::cin, s->Name);
        }

        std::cout << "\t\t\t\t\t\t\t\tEnter the Age of Student: ";
        std::cin >> s->Age;

        while (!s->isValidAge(s->Age))
        {
            std::cout << "\t\t\t\t\t\t\t\tInvalid Information, Enter again: ";
            std::cin >> s->Age;
        }

        std::cout << "\t\t\t\t\t\t\t\tEnter the Department of Student: ";
        std::cin >> s->Department;
        while (!s->isValidDepartment(s->Department))
        {
            std::cout << "\t\t\t\t\t\t\t\tInvalid Information, Enter again: ";
            std::cin >> s->Department;
        }



        std::cout << "\t\t\t\t\t\t\t\tEnter the Section of Student: ";
        std::cin >> s->Section;
        while (!s->isValidSection(s->Section))
        {
            std::cout << "\t\t\t\t\t\t\t\tInvalid Information, Enter again: ";
            std::cin >> s->Section;
        }


        s->Rollno = counter++;

        std::cout << "\t\t\t\t\t\t\t\tEnter the Year of Admission of Student: ";
        std::cin >> s->YearOfAdmission;

        while (!s->isValidYearOfAdmission(s->YearOfAdmission))
        {
            std::cout << "\t\t\t\t\t\t\t\tInvalid Information, Enter again: ";
            std::cin >> s->YearOfAdmission;
        }

        std::cout << "\t\t\t\t\t\t\t\tHas the Student paid fees?: ";
        std::cin >> s->FeesStatus;
        while (!s->isValidFeesStatus(s->FeesStatus))
        {
            std::cout << "\t\t\t\t\t\t\t\tInvalid Information, Enter again: ";
            std::cin >> s->FeesStatus;
        }


        if (s->FeesStatus == "yes") {
            std::cout << "\t\t\t\t\t\t\t\tIn how many Courses is the student registered?: ";
            std::cin >> n;
            while (!s->isValidNCourses(n))
            {
                std::cout << "\t\t\t\t\t\t\t\tInvalid Information, Enter again: ";
                std::cin >> n;
            }
            s->initializeAttendance(n);
            s->initializeGPA(n);

            for (int i = 0; i < n; i++)
            {
                std::cin.ignore();
                std::string temp;
                std::cout << "\t\t\t\t\t\t\t\tEnter The Course Name for Course # " << i + 1 << ": " << " ";
                std::getline(std::cin, temp);
                s->CoursesRegistered.push_back(temp);

            }
        }

        Node* newStudent = new Node(s);
        rollnoTree.insert(s);
        Department.insert(s);
        newStudent->s->CGPA = 0.0;


        std::cout << "\n\n\t\t\t\t\t\t\t\t***Student Added Successfully!*\n\n";
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

    TreeForStudent& getRollnoInformation()
    {
        return rollnoTree;
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

    while (selection != 3)
    {
        std::cout << "\t\t\t\t\t\t\t\t1. Admin\n\t\t\t\t\t\t\t\t2. Teacher\n\t\t\t\t\t\t\t\t3. Exit" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\tEnter your choice ( 1-3 ): ";
        std::cin >> selection;

        switch (selection)
        {
        case 1:
        {
            std::string password;
            char ch;
            std::cout << "\t\t\t\t\t\t\t\tEnter the password: ";
            while (true)
            {
                ch = _getch();
                if (ch == 13)
                    break;
                password.push_back(ch);
                std::cout << "*";
            }

            if (password == "12345")
            {
                int choice = 0;
                while (choice != 6) {
                    std::cout << "\n\t\t\t\t\t\t\t\t1. Add a Student \n\t\t\t\t\t\t\t\t2. Delete a Student \n\t\t\t\t\t\t\t\t3. Modify Data \n\t\t\t\t\t\t\t\t4. Report By Roll no \n\t\t\t\t\t\t\t\t5. Report By Department \n\t\t\t\t\t\t\t\t6. Exit" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\tEnter your choice (1 - 6): ";
                    std::cin >> choice;
                    std::string department;
                    int rollno;

                    switch (choice)
                    {
                    case 1:
                        a.AddAStudent();
                        break;
                    case 2: {
                        std::cout << "\t\t\t\t\t\t\t\tEnter department: ";
                        std::cin >> department;
                        while (!(student->s->isValidDepartment(department)))
                        {
                            std::cout << "\t\t\t\t\t\t\t\tPlease Enter Valid Department: ";
                            std::cin >> department;
                        }
                        std::cout << "\t\t\t\t\t\t\t\tEnter roll no: ";
                        std::cin >> rollno;
                        a.DeleteAStudent(rollno, department);
                        break;
                    }
                    case 3:
                        std::cout << "\t\t\t\t\t\t\t\tEnter department: ";
                        std::cin >> department;
                        std::cout << "\t\t\t\t\t\t\t\tEnter roll no: ";
                        std::cin >> rollno;
                        a.ModifyData(rollno, department);
                        break;
                    case 4:
                        std::cout << "\t\t\t\t\t\t\t\tEnter roll no: ";
                        std::cin >> rollno;
                        a.ReportByRollNo(rollno);
                        break;
                    case 5:
                        std::cout << "\t\t\t\t\t\t\t\tEnter department: ";
                        std::cin >> department;
                        a.ReportByDepartment(department);
                        break;
                    case 6:
                        break;
                    default:
                        std::cout << "\t\t\t\t\t\t\t\tInvalid Input";
                    }
                }
            }
            else
            {
                std::cout << std::endl;
                std::cout << "\t\t\t\t\t\t\t\tIncorrect Password" << std::endl;
                return;
            }
        }
        break;
        case 2:
        {
            int TeacherChoice = 0;
            while (TeacherChoice != 5)
            {
                std::cout << "\t\t\t\t\t\t\t\t1. Mark Attendance\n\t\t\t\t\t\t\t\t2. Update CGPA \n\t\t\t\t\t\t\t\t3. Sort CGPA \n\t\t\t\t\t\t\t\t4. Generate Attendance Report\n\t\t\t\t\t\t\t\t5. Exit" << std::endl;
                std::cout << "\t\t\t\t\t\t\t\tEnter your choice (1 - 5): ";
                std::cin >> TeacherChoice;
                switch (TeacherChoice)
                {
                case 1:
                {
                    std::string department = "", section = "";
                    std::cout << "\t\t\t\t\t\t\t\tEnter the department: ";
                    std::cin >> department;

                    while (!(student->s->isValidDepartment(department)))
                    {
                        std::cout << "\t\t\t\t\t\t\t\tPlease Enter Valid Department: ";
                        std::cin >> department;
                    }
                    std::cout << "\t\t\t\t\t\t\t\tEnter the section: ";
                    std::cin >> section;
                    TreeForStudent& obj = a.getDepartmentInformation();
                    std::vector<Node*> students =
                        obj.searchStudentsByDepartment(department);
                    std::vector<Node*> SelectedStudents;
                    for (Node* student : students)
                    {
                        if (student->s->Section == section[0])
                            SelectedStudents.push_back(student);
                    }
                    if (!SelectedStudents.empty()) {
                        std::cout << "\t\t\t\t\t\t\t\tStudents in the Department are: " << std::endl;
                        for (auto student : SelectedStudents)
                            std::cout << "\t\t\t\t\t\t\t\tRoll no: " << student->s->Rollno << " , \t\t\t\t\t\t\t\tName: " << student->s->Name << std::endl;

                        for (auto student : SelectedStudents)
                        {
                            if (student->s->FeesStatus == "yes") {
                                std::cout << "\t\t\t\t\t\t\t\tRoll no of the student: " << student->s->Rollno << std::endl;

                                int length = student->s->Attendance.size();
                                student->s->initializeAttendance(length);
                                for (int i = 0; i < length; i++)
                                {
                                    std::cout << "\t\t\t\t\t\t\t\tCourse " << student->s->CoursesRegistered[i] << ": " << "1(Present) OR 0(False): ";
                                    bool temp;
                                    std::cin >> temp;
                                    student->s->Attendance[i] = temp;
                                }
                            }
                        }
                        std::cout << "\t\t\t\t\t\t\t\tAttendance marked." << std::endl;
                    }
                    else
                    {
                        std::cout << "\t\t\t\t\t\t\t\tNo Students Registered" << std::endl;
                        std::cout << std::endl;
                    }
                    break;
                }
                case 2:
                {
                    std::string department = "", section = "";
                    std::cout << "\t\t\t\t\t\t\t\tEnter the department: ";
                    std::cin >> department;

                    while (!(student->s->isValidDepartment(department)))
                    {
                        std::cout << "\t\t\t\t\t\t\t\tPlease Enter Valid Department: ";
                        std::cin >> department;
                    }

                    std::cout << "\t\t\t\t\t\t\t\tEnter the section: ";
                    std::cin >> section;

                    TreeForStudent& obj = a.getDepartmentInformation();
                    std::vector<Node*> students = obj.searchStudentsByDepartment(department);
                    std::vector<Node*> SelectedStudents;

                    for (Node* student : students)
                    {
                        if (student->s->Section == section[0])
                            SelectedStudents.push_back(student);
                    }

                    if (!SelectedStudents.empty())
                    {
                        std::cout << "\t\t\t\t\t\t\t\tStudents in the Department are: " << std::endl;
                        for (auto student : SelectedStudents)
                            std::cout << "Roll no:" << student->s->Rollno << " , Name: " << student->s->Name << std::endl;

                        for (auto student : SelectedStudents)
                        {
                            if (student->s->FeesStatus == "yes") {
                                std::cout << "\t\t\t\t\t\t\t\tUpdate CGPA of " << student->s->Name << ": " << std::endl;
                                float totalGradePoints = 0.0;
                                float totalCredits = 0.0;
                                int length = student->s->CoursesRegistered.size();
                                student->s->initializeGPA(length);
                                for (int i = 0; i < length; i++)
                                {
                                    std::cout << "\t\t\t\t\t\t\t\tEnter GPA for Course " << student->s->CoursesRegistered[i] << ": ";
                                    float tempGPA;
                                    std::cin >> tempGPA;

                                    std::cout << "\t\t\t\t\t\t\t\tEnter credit hours for Course " << student->s->CoursesRegistered[i] << ": ";
                                    float tempCredits;
                                    std::cin >> tempCredits;

                                    student->s->GPA[i] = tempGPA;
                                    totalGradePoints += tempGPA * tempCredits;
                                    totalCredits += tempCredits;
                                }
                                if (totalCredits > 0.0)
                                {
                                    student->s->CGPA = totalGradePoints / totalCredits;
                                    std::cout << "\t\t\t\t\t\t\t\tCGPA updated successfully." << std::endl;
                                }
                                else
                                {
                                    std::cout << "\t\t\t\t\t\t\t\tTotal credit hours are zero. Cannot calculate CGPA." << std::endl;
                                }
                            }
                        }
                    }
                    else
                    {
                        std::cout << "\t\t\t\t\t\t\t\tNo Students Registered" << std::endl;
                    }
                    break;
                }
                case 3: {
                    std::string department = "", section = "";
                    std::cout << "\t\t\t\t\t\t\t\tEnter the department: ";
                    std::cin >> department;

                    while (!(student->s->isValidDepartment(department))) {
                        std::cout << "\t\t\t\t\t\t\t\tPlease Enter Valid Department: ";
                        std::cin >> department;
                    }

                    std::cout << "\t\t\t\t\t\t\t\tEnter the section: ";
                    std::cin >> section;

                    TreeForStudent& obj = a.getDepartmentInformation();
                    std::vector<Node*> students = obj.searchStudentsByDepartment(department);
                    std::vector<Node*> SelectedStudents;

                    for (Node* student : students) {
                        if (student->s->Section == section[0])
                            SelectedStudents.push_back(student);
                    }

                    if (!SelectedStudents.empty()) {
                        std::cout << "\t\t\t\t\t\t\t\tStudents in the Department are: " << std::endl;
                        for (auto student : SelectedStudents)
                            std::cout << "\n\n\t\t\t\t\t\t\t\tRoll no: " << student->s->Rollno << " , Name: " << student->s->Name << std::endl;

                        SortByCGPA(SelectedStudents);
                    }
                    else {
                        std::cout << "\n\n\t\t\t\t\t\t\t\tNo Students Registered" << std::endl;
                    }
                    break;
                }
                case 4:
                {
                    std::string department, studentName;
                    int rollno;
                    std::cout << "\t\t\t\t\t\t\t\tEnter department: ";
                    std::cin >> department;
                    while (!(student->s->isValidDepartment(department)))
                    {
                        std::cout << "\t\t\t\t\t\t\t\tPlease Enter Valid Department: ";
                        std::cin >> department;
                    }

                    while (!(student->s->isValidName(studentName))) {
                        std::cout << "\t\t\t\t\t\t\t\tEnter student name: ";
                        std::cin.ignore();
                        std::getline(std::cin, studentName);
                    }
                    while (!(student->s->isValidRollno(rollno))) {
                        std::cout << "\t\t\t\t\t\t\t\tEnter roll no: ";
                        std::cin >> rollno;
                    }

                    TreeForStudent& obj = a.getRollnoInformation();;
                    Node* foundStudent = obj.searchStudentByRollno(rollno);

                    if (foundStudent)
                    {
                        std::cout << "\n\t\t\t\t\t\t\t\tAttendance Percentage for " << studentName << " (Roll No: " << rollno << ") in Department " << department << ":\n\n";


                        for (int i = 0; i < foundStudent->s->CoursesRegistered.size(); ++i)
                        {
                            std::cout << "\t\t\t\t\t\t\t\t" << foundStudent->s->CoursesRegistered[i] << " ";
                            if (foundStudent->s->Attendance.size() > i)
                            {
                                int presentCount = (foundStudent->s->Attendance[i] == true) ? 1 : 0;
                                double attendancePercentage = (static_cast<double>(presentCount) / 48) * 100;

                        
                                std::cout << attendancePercentage << "%" << std::endl;
                            }
                            else
                            {
                                std::cout << "No attendance recorded yet" << std::endl;
                            }
                        }
                    }
                    else
                    {
                        std::cout << "\n\t\t\t\t\t\t\t\tStudent not found." << std::endl;
                    }
                    break;
                }

                case 5:
                    break;
                default:
                    std::cout << "\t\t\t\t\t\t\t\tInvalid Selection\n\n" << std::endl;
                }
            }
            break;
        }
    case 3 :
        break;
        default:
            std::cout << "\t\t\t\t\t\t\t\tIncorrect Input" << std::endl;
        }
    }
}


int main() {
    DisplayHeader();
    UserRoleAndAccess();
}