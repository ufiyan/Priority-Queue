/// @file prqueue.h
/// @author Sufiyan Ahmed Syed
/// @date October 20, 2023
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template <typename T>
class prqueue
{
private:
    struct NODE
    {
        int priority; // used to build BST
        T value;      // stored data for the p-queue
        bool dup;     // marked true when there are duplicate priorities
        NODE *parent; // links back to parent
        NODE *link;   // links to linked list of NODES with duplicate priorities
        NODE *left;   // links to left child
        NODE *right;  // links to right child
    };
    NODE *root; // pointer to root node of the BST
    int sz;     // # of elements in the prqueue
    NODE *curr; // pointer to next item in prqueue (see begin and next)

public:
    prqueue()
    {
        root = nullptr;
        sz = 0;
        curr = nullptr;
    }
    // Overloads the assignment operator to assign one prqueue to another.
    prqueue &operator=(const prqueue &other)
    {
        //Checking for self-assignment by comparing the address of the current object
        // with the address of the 'other' object.
        if (this == &other)
        {
            return *this;
        }
        clear();
        sz = other.sz;
        //this if statement checks if the otherroot is not null and then copies the object of the other root to the this obejct root
        //by allocating a new node and then passing the other root to the this root obejct
        if (other.root != nullptr)
        {
            this->root = new NODE;
            root->priority = other.root->priority;
            root->value = other.root->value;
            root->dup = other.root->dup;
            root->link = nullptr;
            root->parent = nullptr;
            root->left = nullptr;
            root->right = nullptr;
            insertBst(other.root, root);
        }
        else
        {
            root = nullptr;
        }
        return *this;
    }
    ///this function basically adds the right and left subtree nodes by allocating space using new operator and cpying the data of the other obejct 
    ///to this obejct. It also copies the trees of the other nodes to this object 
    void insertBst(NODE *otherRoot, NODE *thisRootNode)
    {
        // Copy the left subtree
        if (otherRoot->left != nullptr)
        {
            thisRootNode->left = new NODE(*otherRoot->left);
            thisRootNode->left->parent = thisRootNode;
            thisRootNode->left->left = nullptr;
            thisRootNode->left->right = nullptr;
            thisRootNode->left->link = nullptr;
            copyLinks(otherRoot->left, thisRootNode->left);
            insertBst(otherRoot->left, thisRootNode->left);
        }

        // Copy the right subtree
        if (otherRoot->right != nullptr)
        {
            thisRootNode->right = new NODE(*otherRoot->right);
            thisRootNode->right->parent = thisRootNode;
            thisRootNode->right->left = nullptr;
            thisRootNode->right->right = nullptr;
            thisRootNode->right->link = nullptr;
            copyLinks(otherRoot->right, thisRootNode->right);
            insertBst(otherRoot->right, thisRootNode->right);
        }
    }

    // Helper method to copy linked nodes
    void copyLinks(NODE *sourceNode, NODE *targetNode)
    {
        NODE *currSourceLink = sourceNode->link;
        NODE **currTargetLinkPtr = &targetNode->link;
        while (currSourceLink != nullptr)
        {
            *currTargetLinkPtr = new NODE(*currSourceLink);
            (*currTargetLinkPtr)->parent = targetNode;
            (*currTargetLinkPtr)->link = nullptr; // The new node's link should initially be null
            currTargetLinkPtr = &((*currTargetLinkPtr)->link);
            currSourceLink = currSourceLink->link;
        }
    }

    void clear()
    {
        deleteBSt(root);
        root = nullptr;
        sz = 0;
        curr = nullptr;
    }
    void deleteBSt(NODE *thisRoot)
    {
        if (thisRoot != nullptr)
        {
            deleteBSt(thisRoot->left);
            deleteBSt(thisRoot->right);
            NODE *linkNodes = thisRoot->link;
            while (linkNodes != nullptr)
            {
                NODE *delNode = linkNodes;
                linkNodes = linkNodes->link;
                delete delNode;
            }
            delete thisRoot;
        }
        return;
    }

    ~prqueue()
    {
        clear();
    }

    void enqueue(T value, int priority)
    {
        NODE *addNode = new NODE;
        addNode->priority = priority;
        addNode->value = value;
        addNode->left = nullptr;
        addNode->right = nullptr;
        addNode->dup = false;
        addNode->link = nullptr;
        addNode->parent = nullptr;

        if (root == nullptr)
        {
            root = addNode;
            sz++;
            return;
        }
        NODE *currNode = root;
        NODE *parentNode = nullptr;
        while (true)
        { // Changed from while(currNode != nullptr) to avoid dangling else
            parentNode = currNode;
            if (addNode->priority < currNode->priority)
            {
                if (currNode->left == nullptr)
                {
                    currNode->left = addNode;
                    addNode->parent = parentNode;
                    sz++;
                    break;
                }
                currNode = currNode->left;
            }
            else if (addNode->priority > currNode->priority)
            {
                if (currNode->right == nullptr)
                {
                    currNode->right = addNode;
                    addNode->parent = parentNode;
                    sz++;
                    break;
                }
                currNode = currNode->right;
            }
            else
            { // Priority is equal
                if (!currNode->dup)
                {
                    currNode->dup = true;
                    currNode->link = addNode;
                    sz++;
                    break;
                }
                else
                {
                    NODE *temp = currNode;
                    while (temp->link != nullptr)
                    {
                        temp = temp->link;
                    }
                    temp->link = addNode;
                    sz++;
                    break;
                }
            }
        }
    }
    T dequeue()
    {
        if (root == nullptr)
        {
            throw std::runtime_error("Priority queue is empty.");
        }

        // Find the leftmost node since we're implementing an in-order traversal.
        NODE *delNode = root, *parent = nullptr;
        while (delNode->left != nullptr)
        {
            parent = delNode;
            delNode = delNode->left;
        }
        T valueOut = delNode->value;

        // Case where the node has a duplicate linked list.
        if (delNode->dup)
        {
            NODE *dupNode = delNode->link;
            delNode->link = dupNode->link;
            delete dupNode; // delete the duplicate node only, not the entire linked list.
        }
        // Case where the node to delete is a leaf node.
        else if (delNode->left == nullptr && delNode->right == nullptr)
        {
            if (parent != nullptr)
            {
                // Unlink delNode from its parent.
                if (parent->left == delNode)
                {
                    parent->left = nullptr;
                }
                else
                {
                    parent->right = nullptr;
                }
            }
            else
            {
                root = nullptr;
            }
            delete delNode;
        }
        // Case where the node to delete has one child.
        else if (delNode->right == nullptr || delNode->left != nullptr)
        {
            NODE *child = (delNode->left != nullptr) ? delNode->left : delNode->right;
            if (parent != nullptr)
            {
                if (parent->left == delNode)
                {
                    parent->left = child;
                }
                else
                {
                    parent->right = child;
                }
            }
            else
            {
                root = child;
            }
            child->parent = parent;
            delete delNode;
        }
        // Case where the node to delete has two children.
        else
        {
            // Find the in-order successor (smallest in the right subtree).
            NODE *successor = delNode->right;
            NODE *successorParent = delNode;
            while (successor->left != nullptr)
            {
                successorParent = successor;
                successor = successor->left;
            }
            // Copy the successor's value and priority to delNode.
            delNode->value = successor->value;
            delNode->priority = successor->priority;
            // Fix the successor's parent's child pointer.
            if (successorParent->left == successor)
            {
                successorParent->left = successor->right;
            }
            else
            {
                successorParent->right = successor->right;
            }
            // If successor has a right child, update its parent pointer.
            if (successor->right != nullptr)
            {
                successor->right->parent = successorParent;
            }
            delete successor;
        }
        sz--; // Update size.
        return valueOut;
    }

    int size()
    {
        return sz; // TODO: update this return
    }

    void begin()
    {
        if (root == nullptr)
        {
            curr = nullptr;
            return;
        }
        curr = root;
        while (curr->left != nullptr)
        {
            curr = curr->left;
        }
    }
    bool next(T &value, int &priority)
    {
        if (curr == nullptr)
        {
            return false; // No more elements in the priority queue
        }

       //case when handling the duplicates items in a list
        if (curr->dup && curr->link != nullptr)
        {
            curr = curr->link;
            value = curr->value;
            priority = curr->priority;
            return true;
        }

        // Return the current value
        value = curr->value;
        priority = curr->priority;

        // moving to the next element, which is the next larger element in the tree
        if (curr->right != nullptr)
        {
            curr = curr->right;
            while (curr->left != nullptr)
            {
                curr = curr->left;
            }
        }
        else
        {
            NODE *last;
            do
            {
                last = curr;
                curr = curr->parent;
            } while (curr != nullptr && curr->right == last);
        }
        return curr != nullptr;
    }

    string toString()
    { 
        stringstream myoutput;
        recursiveFunction(root, myoutput);
        return myoutput.str();
    }
    void recursiveFunction(NODE *rootNode, stringstream &output)
    {
        if (rootNode == nullptr)
        {
            return;
        }
        recursiveFunction(rootNode->left, output);
        if (rootNode->dup)
        {
            NODE *temp = rootNode;
            while (temp != nullptr)
            {
                output << temp->priority << " value: " << temp->value << endl;
                temp = temp->link;
            }
        }
        else
        {
            output << rootNode->priority << " value: " << rootNode->value << endl;
        }
        recursiveFunction(rootNode->right, output);
    }

    T peek()
    {
        if (root == NULL)
        {
            return T();
        }
        NODE *currNode = root;
        while (currNode->left != nullptr)
        {
            currNode = currNode->left;
        }
        if (currNode->dup && currNode->link != nullptr)
        {
            return currNode->link->value;
        }
        return currNode->value;
    }
    bool operator==(const prqueue &other) const
    {
        return isIdentical(this->root, other.root);
    }
    bool isIdentical(const NODE *thisRoot, const NODE *otherRoot) const
    {
        // If both nodes are null, trees are identical up to this point
        if (thisRoot == nullptr && otherRoot == nullptr)
        {
            return true;
        }
        // If one node is null and the other is not, trees are not identical
        if (thisRoot == nullptr || otherRoot == nullptr)
        {
            return false;
        }
        // Check current nodes for value, priority, and duplicate status
        bool isSameValue = thisRoot->value == otherRoot->value;
        bool isSamePriority = thisRoot->priority == otherRoot->priority;
        bool isSameDup = thisRoot->dup == otherRoot->dup;

        // Recursively check left and right subtrees
        bool isLeftIdentical = isIdentical(thisRoot->left, otherRoot->left);
        bool isRightIdentical = isIdentical(thisRoot->right, otherRoot->right);

        // If current nodes match and both subtrees are identical, check duplicates if necessary
        if (isSameValue && isSamePriority && isSameDup && isLeftIdentical && isRightIdentical)
        {
            if (!thisRoot->dup)
            {
                // No duplicates, trees are identical up to this point
                return true;
            }

            // Check linked list of duplicates
            NODE *thisLink = thisRoot->link;
            NODE *otherLink = otherRoot->link;
            while (thisLink && otherLink)
            {
                if (thisLink->value != otherLink->value || thisLink->priority != otherLink->priority)
                {
                    return false;
                }
                thisLink = thisLink->link;
                otherLink = otherLink->link;
            }

            // If one has more duplicates than the other, trees are not identical
            return thisLink == nullptr && otherLink == nullptr;
        }

        // Trees are not identical if any of the above checks fail
        return false;
    }
    void *getRoot()
    {
        return root;
    }
};
