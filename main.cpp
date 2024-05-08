#include "prqueue.h" 
#include <iostream>
#include <cassert>

// Test function for operator=
void testOperatorAssignment() {
    prqueue<int> prq1;
    prq1.enqueue(5, 1);
    prq1.enqueue(4, 2);
    prq1.enqueue(3, 3);
    prq1.enqueue(2, 4);
    prq1.enqueue(1, 5);

    prqueue<int> prq2;
    prq2.enqueue(10, 1);
    prq2.enqueue(20, 2);
    prq2.enqueue(30, 3);
    prq2.enqueue(40, 4);
    prq2.enqueue(50, 5);

    prq2 = prq1; // Test the assignment operator

    // Add assertions to test the values after assignment
    assert(prq2.size() == 5); // Check the size
    // Add more assertions as needed to test the state of prq2 after assignment
}

int main() {
    // Call the test function for operator=
    testOperatorAssignment();

    // Additional test cases for insertBst can be added here

    return 0;
}

