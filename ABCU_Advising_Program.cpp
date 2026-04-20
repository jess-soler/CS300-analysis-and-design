//===========================================================================
// Name        : ABCU_Advising_System.cpp
// Author      : Jessica Soler
// Version     : 1.0
// Description : Project Two ABCU Advising System
//===========================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

//===========================================================================
// Course Structure
//
// Defines a course with a course number, title, and list of prerequisites
//===========================================================================
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

//===========================================================================
// Node Structure
//
// Defines a node in the binary search tree
//===========================================================================
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

//===========================================================================
// Binary Search Tree Class
//
// Defines a BST used to store course data
// Insert courses into the tree based on course number
// Search for courses by course number
// Print all courses in alphanumeric order
//===========================================================================
class BST {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:
    BST();
    virtual ~BST();
    void deleteTree(Node* node);

    void Insert(Course course);
    Course Search(string courseNumber);
    void PrintCourseList();
};

//===========================================================================
// Helper Function Declarations
//
// Load courses from file into BST
// Search for a course and print course information
//===========================================================================
bool loadCourses(string fileName, BST& bst, vector<Course>& allCourses);
void searchPrintCourse(BST& bst, string courseNumber);

//===========================================================================
// BST Functions
//
// Constructor and Destructor
// Delete the entire tree
// Insert a course
// Add a course to some node
// Search for a course
// Traverse the tree in order
// Print all courses in alphanumeric order
//===========================================================================

// Constructor
BST::BST() {
    root = nullptr;
}

// Destructor
BST::~BST() {
    deleteTree(root);
    root = nullptr;
}

// Delete the entire tree
void BST::deleteTree(Node* node) {
    // base case
    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Insert a course
void BST::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    } else {
        addNode(root, course);
    }
}

// Add a course to some node
void BST::addNode(Node* node, Course course) {
    // if course number is smaller, go left
    if (course.courseNumber.compare(node->course.courseNumber) < 0) {
        // if there is no left child
        if (node->left == nullptr) {
            // insert course here
            node->left = new Node(course);
        } else {
            // otherwise keep going left
            addNode(node->left, course);
        }
    }
    // otherwise go right
    else if (course.courseNumber.compare(node->course.courseNumber) > 0) {
        // if there is no right child
        if (node->right == nullptr) {
            // insert course here
            node->right = new Node(course);
        } else {
            // otherwise keep going right
            addNode(node->right, course);
        }
    }
}

// Search for a course
Course BST::Search(string courseNumber) {
    // set current node to root
    Node* current = root;

    // loop until we find the course or reach the end of the tree
    while (current != nullptr) {
        // if we found the course, return it
        if (current->course.courseNumber == courseNumber) {
            return current->course;
        }
        // if course number is smaller, go left
        else if (courseNumber.compare(current->course.courseNumber) < 0) {
            current = current->left;
        }
        // otherwise go right
        else {
            current = current->right;
        }
    }

    Course course;
    return course;
}

// Traverse the tree in order
void BST::inOrder(Node* node) {
    // if node is not null
    if (node != nullptr) {
        // go left, print current node, then go right
        inOrder(node->left);
        cout << node->course.courseNumber << ": " << node->course.title << endl;
        inOrder(node->right);
    }
}

// Print all courses in alphanumeric order
void BST::PrintCourseList() {
    inOrder(root);
}

//===========================================================================
// Load CSV File and Build BST
//
// Opens and reads the CSV file line by line
// Parse each line into course object and insert into BST
// Validate each course has a course number and title
// Verify all prerequisites exist in the BST
//===========================================================================

// Load courses from file into BST
bool loadCourses(string fileName, BST& bst, vector<Course>& allCourses) {
    cout << "Loading CSV file: " << fileName << endl;

    // open file and check if it opened successfully
    ifstream file(fileName);
    string line;
    bool fileIsValid = true;
    allCourses.clear();

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return false;
    }

    // read file line by line
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string token;
        vector<string> tokens;

        // split line by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // validate course number and course title cannot be empty
        if (tokens.size() < 2 || tokens[0].empty() || tokens[1].empty()) {
            cout << "Error: Missing course number or course title." << endl;
            fileIsValid = false;
            continue;
        }

        // create course object
        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];

        // add prerequisites
        for (unsigned int i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        // insert course into tree
        bst.Insert(course);

        // store course in vector for validation
        allCourses.push_back(course);
    }

    file.close();

    // validate prerequisites
    for (unsigned int i = 0; i < allCourses.size(); ++i) {
        for (unsigned int j = 0; j < allCourses[i].prerequisites.size(); ++j) {
            Course foundCourse = bst.Search(allCourses[i].prerequisites[j]);

            if (foundCourse.courseNumber.empty()) {
                cout << "Error: Prerequisite " << allCourses[i].prerequisites[j]
                     << " does not exist." << endl;
                fileIsValid = false;
            }
        }
    }

    if (!fileIsValid) {
        cout << "Error: Course data failed validation." << endl;
        return false;
    }

    cout << "Courses loaded successfully." << endl;
    return true;
}

//===========================================================================
// Search and Output Course Information
//
// Search BST for a specific course using course number
// Displays course number, title, and prerequisites
// If course not found, display error message
//===========================================================================

// Search for a course and print course information
void searchPrintCourse(BST& bst, string courseNumber) {
    Course currentCourse = bst.Search(courseNumber);

    // if course is not found
    if (currentCourse.courseNumber.empty()) {
        cout << "Course " << courseNumber << " not found." << endl;
        return;
    }

    // print course number and title
    cout << currentCourse.courseNumber << ": " << currentCourse.title << endl;

    // print prerequisites
    if (currentCourse.prerequisites.size() > 0) {
        cout << "Prerequisites: ";

        for (unsigned int i = 0; i < currentCourse.prerequisites.size(); ++i) {
            Course prerequisiteCourse = bst.Search(currentCourse.prerequisites[i]);

            if (!prerequisiteCourse.courseNumber.empty()) {
                cout << prerequisiteCourse.courseNumber << ": "
                     << prerequisiteCourse.title;
            }

            if (i < currentCourse.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    } else {
        cout << "Prerequisites: None" << endl;
    }
}

//===========================================================================
// Main Menu
//
// Allows user to:
// 1. Load course data from a CSV file into the BST
// 2. Display all courses in alphanumeric order
// 3. Search for and display specific course information
// 9. Exit the program
//===========================================================================
int main() {
    int choice = 0;
    BST bst;
    vector<Course> allCourses;
    bool dataLoaded = false;

    while (choice != 9) {
        cout << "\nMenu:" << endl;
        cout << "\t1. Load Data Structure" << endl;
        cout << "\t2. Print Course List" << endl;
        cout << "\t3. Print Course" << endl;
        cout << "\t9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Error: Invalid selection. Please enter 1, 2, 3, or 9." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
            continue;
        }

        switch (choice) {

        case 1: {
            if (dataLoaded) {
                cout << "Error: Data has already been loaded." << endl;
            } else {
                string fileName;
                cout << "Enter file name: ";
                cin.ignore(1000, '\n');
                getline(cin, fileName);

                dataLoaded = loadCourses(fileName, bst, allCourses);
            }
            break;
        }

        case 2:
            if (!dataLoaded) {
                cout << "Error: Please load data first." << endl;
            } else {
                bst.PrintCourseList();
            }
            break;

        case 3:
            if (!dataLoaded) {
                cout << "Error: Please load data first." << endl;
            } else {
                string courseNumber;
                cout << "Enter course number: ";
                cin >> courseNumber;

                transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
                searchPrintCourse(bst, courseNumber);
            }
            break;

        case 9:
            cout << "Good bye." << endl;
            break;

        default:
            cout << "Error: Invalid selection. Please enter 1, 2, 3, or 9." << endl;
            break;
        }
    }

    return 0;
}