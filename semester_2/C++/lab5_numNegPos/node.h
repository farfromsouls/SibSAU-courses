#include <fstream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

void append(Node*& head, Node*& tail, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void clearList(Node*& head, Node*& tail) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

void splitNumbers(const string& inputFile, Node*& positiveHead, Node*& positiveTail, Node*& negativeHead, Node*& negativeTail) {
    ifstream inFile(inputFile);

    int number;
    while (inFile >> number) {
        if (number >= 0) {
            append(positiveHead, positiveTail, number);
        } else {
            append(negativeHead, negativeTail, number);
        }
    }

    inFile.close();
}

void writeListToFile(const string& outputFile, Node* head) {
    ofstream outFile(outputFile);

    Node* current = head;
    while (current) {
        outFile << current->data << " ";
        current = current->next;
    }

    outFile.close();
}