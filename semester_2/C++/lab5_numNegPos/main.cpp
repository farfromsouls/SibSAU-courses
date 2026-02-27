#include "node.h"

int main() {
    Node* positiveHead = nullptr;
    Node* positiveTail = nullptr;
    Node* negativeHead = nullptr;
    Node* negativeTail = nullptr;

    splitNumbers("input.txt", positiveHead, positiveTail, negativeHead, negativeTail);
    writeListToFile("positive_numbers.txt", positiveHead);
    writeListToFile("negative_numbers.txt", negativeHead);

    clearList(positiveHead, positiveTail);
    clearList(negativeHead, negativeTail);

    return 0;
}
