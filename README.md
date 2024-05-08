# Priority Queue Implementation
# Overview
This project involves creating a priority queue implemented with a custom binary search tree (BST) in C++. Unlike a standard queue that processes elements in a first-in, first-out (FIFO) manner, a priority queue uses priority-based sorting to determine the dequeue order. Here, smaller integers represent greater urgency, meaning an item with priority 1 will be dequeued before an item with priority 2, and so forth.

# Project Features
Binary Search Tree Implementation: The priority queue is implemented using a binary search tree, with nodes storing both priority and value. Nodes have additional pointers to handle duplicates via a linked list structure.
Duplicate Handling: If multiple items have the same priority, they are arranged in a linked list, maintaining FIFO ordering within that priority.
In-Order Traversal: An in-order traversal should yield the nodes sorted by priority. Duplicate priorities are sorted using the linked list attached to each node.
Core Methods:
enqueue: Add an element to the priority queue.
dequeue: Remove and return the element with the highest priority.
peek: View the element with the highest priority without removing it.
toString: Convert the priority queue to a string for debugging and testing.
begin/next: Traverse the queue in sorted order, similar to an iterator.

# Development Guidelines
Node Structure: Each node in the BST contains priority, value, and pointers to left and right children, a parent node, and a linked list of duplicates.
Project Phases:
Initial Setup: Start with basic methods like the constructor, enqueue, and size.
Functionality: Implement core methods like clear, dequeue, and traversal.
Advanced Features: Handle duplicate priorities, iterators, and equality operators.
Testing: A comprehensive test suite is required using the Catch Framework to ensure accurate functionality and memory management. Each public function should have a multitude of assertions for proper validation.

# Requirements
API Adherence: Do not change the provided API; all private and public functions must remain as specified.
Memory Management: Ensure no memory leaks via a clean Valgrind report.
Test Coverage: Include hundreds of assertions across all public methods.
No Globals: Avoid global or static variables in the priority queue implementation.
