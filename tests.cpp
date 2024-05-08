/// @file tests.cpp
/// @author Adam T Koehler
/// @date October 20, 2023

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

// Catch 2.x - Single Include Framework Testing
#define CATCH_CONFIG_MAIN

#include "prqueue.h"
#include "catch.hpp"
#include <string>

using namespace std;

// This is a basic test case example with sections.
// Requires: <no oter functions>
TEST_CASE("Test 0: The Null Test")
{
    SECTION("Test 0: Empty Truths")
    {
        REQUIRE(true == true);
    }

    SECTION("Test 0: Empty Falsehoods")
    {
        REQUIRE(false == false);
    }
}
TEST_CASE("Testing Enqueue functionality")
{
    prqueue<int> prq;
    SECTION("Enqueue elements with unique values and priorities")
    {
        prq.enqueue(5, 2);
        prq.enqueue(10, 4);
        prq.enqueue(6, 1);
        prq.enqueue(14, 3);

        REQUIRE(prq.size() == 4);
        cout << endl;
    }

    SECTION("Enqueue elments with duplciate priorities")
    {
        prq.enqueue(5, 2);
        prq.enqueue(10, 4);
        prq.enqueue(1, 1);
        prq.enqueue(17, 2);
        prq.enqueue(20, 2);
        REQUIRE(prq.size() == 5);
    }
}
TEST_CASE("Test clear function for memory leaks, [clear]")
{
    prqueue<int> prq;
    prq.enqueue(5, 2);
    prq.enqueue(10, 1);
    prq.enqueue(15, 3);

    SECTION("Clear Function test")
    {
        prq.clear();
        REQUIRE(prq.size() == 0);
        REQUIRE(prq.toString() == "");
    }
}
TEST_CASE("Testing Operator assignment")
{
    prqueue<int> prq1;
    prq1.enqueue(5, 1);
    prq1.enqueue(4, 2);
    prq1.enqueue(3, 3);
    prq1.enqueue(2, 4);
    prq1.enqueue(1, 5);

    prqueue<int> prq2;
    prq1.enqueue(10, 1);
    prq1.enqueue(20, 2);
    prq1.enqueue(30, 3);
    prq1.enqueue(40, 4);
    prq1.enqueue(50, 5);

    prq2 = prq1;
    SECTION("Testing if size is updated correctly")
    {
        REQUIRE(prq2.size() == 5);
    }
    SECTION("Testing the toString correct output")
    {
        string output = "1 value: 5\n2 value: 4\n3 value: 3\n4 value: 2\n5 value: 1\n";
        REQUIRE(prq2.toString() == output);
    }
}
TEST_CASE("Testing peek and empty functions")
{
    prqueue<int> pq;

    SECTION("enqueue and peek")
    {
        pq.enqueue(10, 1);
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.peek() == 10);

        pq.enqueue(20, 2);
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.peek() == 10);
    }

    SECTION("enqueue with same priority and peek")
    {
        pq.enqueue(10, 1);
        pq.enqueue(20, 1);
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.peek() == 10);
    }
}
TEST_CASE("Testing toSTring Function")
{
    SECTION("toString operation")
    {
        pq.enqueue(10, 1);
        pq.enqueue(20, 1);
        string expected = "1 value: 10\n1 value: 20\n";
        REQUIRE(pq.toString() == expected);
    }
}
TEST_CASE("Testing Functions for toString") {
    prqueue<int> pq;
    string expected;

    SECTION("Empty priority queue ") {
        expected = ""; 
        REQUIRE(pq.toString() == expected);
    }

    SECTION("Single element priority queue returns correct string") {
        pq.enqueue(10, 5);
        expected = "[Value: 10, Priority: 5]"; 
        REQUIRE(pq.toString() == expected);
    }

    SECTION("Multiple elements are represented correctly") {
        pq.enqueue(10, 5);
        pq.enqueue(20, 4);
        pq.enqueue(30, 3);
        expected = "[Value: 30, Priority: 3], [Value: 20, Priority: 4], [Value: 10, Priority: 5]";
        REQUIRE(pq.toString() == expected);
    }

    SECTION("Duplicate priorities are handled correctly") {
        pq.enqueue(10, 5);
        pq.enqueue(20, 5);
        
        expected = "[Value: 10, Priority: 5], [Value: 20, Priority: 5]";
        REQUIRE(pq.toString() == expected);
    }
}