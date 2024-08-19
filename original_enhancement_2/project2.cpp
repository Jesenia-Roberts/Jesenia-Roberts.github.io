//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Jesenia Roberts
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold course information
struct Course {
    string courseId;
    string title;
    vector<string> prerequisiteIds;

    Course() {
    };

    Course(string aCourseId, string aTitle, vector<string> aPrerequisiteIds) {
        courseId = aCourseId;
        title = aTitle;
        prerequisiteIds = aPrerequisiteIds;
    };

    void AddPrerequisite(string prerequisiteId) {
        if (!std::count(prerequisiteIds.begin(), prerequisiteIds.end(), prerequisiteId)) {
            prerequisiteIds.push_back(prerequisiteId);
        }
    };
};

void displayCourse(Course course);

// Internal structure for tree node
struct Node {
    Course course;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
            Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string courseId);

    void destroyRecursive(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    void Remove(string courseId);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    destroyRecursive(root);
}

void BinarySearchTree::destroyRecursive(Node* node) {
    if (node != nullptr) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
        node = nullptr;
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    }
    // else
    else {
        // add Node root and course
        addNode(root, course);
    }
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseId) {
    // remove node root courseId
    removeNode(root, courseId);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {
    // set current node equal to root
    Node* current = root;

    // keep looping downwards until bottom reached or matching courseId found
    while (current != nullptr) {
        // if match found, return current course
        if (current->course.courseId.compare(courseId) == 0) {
            return current->course;
        }

        // if course is smaller than current node then traverse left
        if (current->course.courseId.compare(courseId) > 0) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
    if (node->course.courseId.compare(course.courseId) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else {
            addNode(node->left, course);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        //else
        else {
            // recurse down the right node
            addNode(node->right, course);
        }
    }
}

Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    if (node == nullptr) {
        return node;
    }

    if (courseId.compare(node->course.courseId) < 0) {
        node->left = removeNode(node->left, courseId);
    }
    else if (courseId.compare(node->course.courseId) > 0) {
        node->right = removeNode(node->right, courseId);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        else if (node->left == nullptr && node->right != nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->course = temp->course;
            node->right = removeNode(node->right, temp->course.courseId);
        }
    }

    return node;
}

void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output courseId, title, amount, fund
        displayCourse(node->course);
        //InOder right
        inOrder(node->right);
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << course.courseId << ": " << course.title << " | " << "Prerequisites: ";
    for (int i = 0; i < course.prerequisiteIds.size(); i++) {
        cout << course.prerequisiteIds[i];
        if (i != course.prerequisiteIds.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    return;
}

/**
 * Load a txt file containing courses into a container
 *
 * @param txtPath the path to the txt file to load
 * @return a container holding all the courses read
 */
void loadCourses(string txtPath, BinarySearchTree* bst) {
    cout << "Loading txt file " << txtPath << endl;

    ifstream inFile;
    inFile.open(txtPath);

    if (inFile.is_open()) {
        string line;
        vector<string> allPrerequisites;

        while (getline(inFile, line)) {
            int start = 0;
            vector<string> courseParams;

            //split line into course params
            while (start != -1) {
                int commaLocation = line.find(",", start);

                if (commaLocation > -1) {
                    courseParams.push_back(line.substr(start, commaLocation - start));
                    commaLocation++;
                }
                else if (start != line.length() - 1) {
                    courseParams.push_back(line.substr(start, line.length() - start));
                }

                start = commaLocation;
            }

            if (courseParams.size() < 2) {
                cout << "ERROR: found a line with less than 2 course params" << endl;
            }

            vector<string> prerequisites;
            string courseId = courseParams[0];
            string title = courseParams[1];
            for (int i = 2; i < courseParams.size(); i++) {
                prerequisites.push_back(courseParams[i]);
                if (!std::count(allPrerequisites.begin(), allPrerequisites.end(), courseParams[i])) {
                    allPrerequisites.push_back(courseParams[i]);
                }
            }

            Course course(courseId, title, prerequisites);
            bst->Insert(course);
        }

        for (string prerequisite : allPrerequisites) {
            if (bst->Search(prerequisite).courseId.empty()) {
                cout << "ERROR: non-existant prerequisite: " << prerequisite << endl;
            }
        }

        inFile.close();
    }
    else {
        cout << "Could not read file " << txtPath << endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // load courses from file
    string filePath;
    cout << "Please provide the file name that contains the course data: " << endl;
    cin >> filePath;

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst = new BinarySearchTree();
    Course course;
    string courseId;

    // menu
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                delete bst;
                bst = new BinarySearchTree();
                loadCourses(filePath, bst);
                break;

            case 2:
                bst->InOrder();
                break;

            case 3:
                cout << "Provide a Course ID to search for: " << endl;
                cin >> courseId;

                course = bst->Search(courseId);
                if (!course.courseId.empty()) {
                    displayCourse(course);
                }
                else {
                    cout << "Course ID " << courseId << " not found." << endl;
                }
                break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
