//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Jesenia Roberts
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : A project made to read a file that held course IDs, the name of the courses, 
// and their prerequisites, insert the data into a binary search tree, and then 
// have the data be accessible and editable to the user
//============================================================================
using namespace std;

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

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
    void inOrderCourses(Node* node, string courseId1, string courseId2);
    Node* removeNode(Node* node, string courseId);
    Node* findSuccessorNode(Node* node, string courseId);
    Node* findPredNode(Node* node, string courseId);

    void destroyRecursive(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void InOrderCourses(string courseId1, string courseId2);
    void Insert(Course course);
    void Remove(string courseId);
    Course FindSuccessor(string courseId);
    Course FindPredecessor(string courseId);
    Course Search(string courseId);
    vector<Course> SearchCourses(string courseId1, string courseId2);
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
    if (!root) {
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
 * Time complexity of O(log(n))
 */
Course BinarySearchTree::Search(string courseId) {
    // set current node equal to root
    Node* current = root;

    // keep looping downwards until bottom reached or matching courseId found
    while (current) {
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
 * Given a courseId, find its successor
 * Time complexity of O(log(n))
 *
 * @param courseId The courseId to find the successor of
 */
Course BinarySearchTree::FindSuccessor(string courseId) {
    Node* current = root;
    Node* successor = findSuccessorNode(root, courseId);
    // If no successor then return an empty course
    if (current->course.courseId == successor->course.courseId)
    {
        Course course;
        return course;
    }
    return successor->course;
}

/**
 * Given a courseId, find its predecessor
 * Time complexity of O(log(n))
 *
 * @param courseId The courseId to find the predecessor of
 */
Course BinarySearchTree::FindPredecessor(string courseId) {
    Node* current = root;
    Node* predecessor = findPredNode(root, courseId);
    // If no predecessor then return an empty course
    if (current->course.courseId == predecessor->course.courseId)
    {
        Course course;
        return course;
    }
    return predecessor->course;
}

/**
 * Given a course, find its successor node
 * Time complexity of O(log(n))
 *
 * @param node Current node in tree
 * @param successor Course successor if found
 */
Node* BinarySearchTree::findSuccessorNode(Node* node, string courseId) {
    // base case
    Node* successor = node;

    // keep looping downwards until bottom reached or matching courseId found
    while (node) {
        // if match found, return current course
        if (node->course.courseId.compare(courseId) == 0) {
            return successor;
        }

        // if course is smaller than current node then traverse left
        if (node->course.courseId.compare(courseId) > 0) {
            // When traversing left we can keep track of the successor
            // so we don't need to continue searching when we find the 
            // node with the corresponding courseId.
            successor = node;
            node = node->left;
        }
        // else larger so traverse right
        else {
            node = node->right;
        }
    }

    return node;
}

/**
 * Given a node, find its predecessor
 * Time complexity O(log(n))
 *
 * @param node Current node in tree
 * @param courseId Course to find the pred of
 */
Node* BinarySearchTree::findPredNode(Node* node, string courseId) {
    // base case
    Node* predecessor = node;

    // keep looping downwards until bottom reached or matching courseId found
    while (node) {
        // if match found, return current course
        if (node->course.courseId.compare(courseId) == 0) {
            return predecessor;
        }

        // if course is smaller than current node then traverse left
        if (node->course.courseId.compare(courseId) > 0) {
            node = node->left;
        }
        // else larger so traverse right
        else {
            // When traversing right we can keep track of the predecessor
            // so we don't need to continue searching when we find the 
            // node with the corresponding courseId.
            predecessor = node;
            node = node->right;
        }
    }

    return node;
}

/**
 * Add a course to some node (recursive)
 * Time complexity O(log(n))
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
    if (node->course.courseId.compare(course.courseId) > 0) {
        // if no left node
        if (!(node->left)) {
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
        if (!(node->right)) {
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

/**
 * Remove a node (recursive)
 * Time complexity O(log(n))
 *
 * @param node Current node in tree
 * @param course Course to be removed
 */
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

/**
 * Displays the courses in order (recursive)
 * Time complexity O(n)
 *
 * @param node Current node in tree
 */
void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node) {
        //InOrder not left
        inOrder(node->left);
        //output courseId, title, amount, fund
        displayCourse(node->course);
        //InOrder right
        inOrder(node->right);
    }
}

/**
 * Displays the courses in order between courseId1 and courseId2 inclusive (recursive)
 * Time complexity O(n)
 *
 * @param courseId1 The earlier course
 * @param courseId2 The later course
 */
void BinarySearchTree::InOrderCourses(string courseId1, string courseId2)
{
    Node* node = root;
    inOrderCourses(node, courseId1, courseId2);
}

void BinarySearchTree::inOrderCourses(Node* node, string courseId1, string courseId2) {
    //if node is not equal to null ptr
    if (node) {
        //InOrder not left
        inOrderCourses(node->left, courseId1, courseId2);
        //output courseId, title, amount, fund
        if((node->course.courseId.compare(courseId1) >= 0) && (node->course.courseId.compare(courseId2) <= 0))
        {
            displayCourse(node->course);
        }
        //InOrder right
        inOrderCourses(node->right, courseId1, courseId2);
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
    cout << "\nPlease provide the file path that contains the course data: " << endl;
 
    cin >> filePath;

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst = new BinarySearchTree();
    Course course;
    vector<Course> courses;
    string courseId;
    string courseId2;

    // menu
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  4. Find Successor Node" << endl;
        cout << "  5. Find Predecessor Node" << endl;
        cout << "  6. Find range of courses" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        auto start = std::chrono::system_clock::now();
        auto end = std::chrono::system_clock::now();

        switch (choice) {

            case 1:
                delete bst;
                bst = new BinarySearchTree();
                loadCourses(filePath, bst);
                break;

            case 2:
                start = std::chrono::system_clock::now();
                bst->InOrder();
                end = std::chrono::system_clock::now();
                std::cout << "Executed in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;
                break;

            case 3:
                cout << "Provide a Course ID to search for: " << endl;
                cin >> courseId;

                start = std::chrono::system_clock::now();
                course = bst->Search(courseId);
                end = std::chrono::system_clock::now();
                std::cout << "Executed in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;
                if (!course.courseId.empty()) {
                    displayCourse(course);
                }
                else {
                    cout << "Course ID " << courseId << " not found." << endl;
                }
                break;
            case 4:
                cout << "Provide a Course ID to find the successor node of: " << endl;
                cin >> courseId;

                start = std::chrono::system_clock::now();
                course = bst->FindSuccessor(courseId);
                end = std::chrono::system_clock::now();
                std::cout << "Executed in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;
                if (!course.courseId.empty()) {
                    displayCourse(course);
                }
                else {
                    cout << "Successor to Course ID " << courseId << " not found." << endl;
                }
                break;
            case 5:
                cout << "Provide a Course ID to find the predecessor node of: " << endl;
                cin >> courseId;

                start = std::chrono::system_clock::now();
                course = bst->FindPredecessor(courseId);
                end = std::chrono::system_clock::now();
                std::cout << "Executed in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;
                if (!course.courseId.empty()) {
                    displayCourse(course);
                }
                else {
                    cout << "Predecessor to Course ID " << courseId << " not found." << endl;
                }
                break;
            case 6:
                cout << "Provide the first Course ID: " << endl;
                cin >> courseId;
                cout << "Provide the second Course ID: " << endl;
                cin >> courseId2;

                start = std::chrono::system_clock::now();
                bst->InOrderCourses(courseId, courseId2);
                end = std::chrono::system_clock::now();
                std::cout << "Executed in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;
                break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
