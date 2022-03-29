/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: Gilad Livshitz
 * 
 * Date: 2022-03-07
 */

#include "doctest.h"
#include "Notebook.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

TEST_CASE("Bad pages")
{
    Notebook notebook;
    CHECK_THROWS(notebook.read(-1, 0, 60, Direction::Horizontal, 0));
	CHECK_THROWS(notebook.write(-10, 5, 20, Direction::Vertical, "dfd"));
    CHECK_THROWS(notebook.erase(-3, 300, 60, Direction::Horizontal, 5));
    CHECK_THROWS(notebook.show(-50));
    CHECK_THROWS(notebook.show(-1));
    CHECK_THROWS(notebook.show(-1000));
}

TEST_CASE("Bad rows")
{
    Notebook notebook;
    CHECK_THROWS(notebook.read(30, -5, 60, Direction::Horizontal, 0));
	CHECK_THROWS(notebook.write(10, -60, 20, Direction::Vertical, "dfd"));
    CHECK_THROWS(notebook.erase(50, -12, 60, Direction::Horizontal, 5));
}

TEST_CASE("Bad columns")
{
    Notebook notebook;
    CHECK_THROWS(notebook.read(30, 1, -1, Direction::Horizontal, 0));
	CHECK_THROWS(notebook.write(10, 30, -200, Direction::Vertical, "dfd"));
    CHECK_THROWS(notebook.erase(50, 50, -300, Direction::Horizontal, 5));

    CHECK_THROWS(notebook.read(30, 1, 100, Direction::Horizontal, 0));
	CHECK_THROWS(notebook.write(10, 30, 2000, Direction::Vertical, "dfd"));
    CHECK_THROWS(notebook.erase(50, 50, 301, Direction::Horizontal, 5));
}

TEST_CASE("Bad length")
{
    Notebook notebook;

    // bad length by number
    CHECK_THROWS(notebook.read(30, 1, 0, Direction::Horizontal, -1));
    CHECK_THROWS(notebook.erase(50, 50, 50, Direction::Vertical, -100));

    // bad length by horizontal - out of bounds horizontal
    CHECK_THROWS(notebook.read(30, 1, 0, Direction::Horizontal, 200));
    CHECK_THROWS(notebook.erase(50, 50, 0, Direction::Horizontal, 151));
    CHECK_THROWS(notebook.read(30, 1, 0, Direction::Horizontal, 101));

    // out of bounds - horizontal
    CHECK_THROWS(notebook.read(30, 1, 5, Direction::Horizontal, 100));
    CHECK_THROWS(notebook.erase(50, 50, 50, Direction::Horizontal, 51));
    CHECK_THROWS(notebook.write(10, 30, 0, Direction::Horizontal, string(101, 'a')));
    CHECK_THROWS(notebook.write(10, 30, 10, Direction::Horizontal, string(91, 'a')));
}

TEST_CASE("Bad writings")
{
    Notebook notebook;

    CHECK_THROWS(notebook.write(10, 30, 0, Direction::Horizontal, "hello\tworld"));
    CHECK_THROWS(notebook.write(10, 30, 0, Direction::Horizontal, "hello~~~~world"));
    
    string str = "mememe";
    str[3] = 16;
    CHECK_THROWS(notebook.write(10, 30, 0, Direction::Horizontal, str));


    // write over the same thing - Horizontal
    notebook.write(10, 30, 0, Direction::Horizontal, "hello world");
    CHECK_THROWS(notebook.write(10, 30, 0, Direction::Horizontal, "hello world"));
    
    notebook.erase(10, 30, 0, Direction::Horizontal, 11);
    CHECK_THROWS(notebook.write(10, 30, 0, Direction::Horizontal, "hello world"));

    //// write over the same thing - Vertical
    notebook.write(20, 30, 0, Direction::Vertical, "hello world");
    CHECK_THROWS(notebook.write(20, 30, 0, Direction::Vertical, "hello world"));
    
    // tests when is writed horizontal that vriting on it vertically will throw exception
    notebook.write(104, 50, 20, Direction::Horizontal, "alice in wonderland");
    notebook.write(104, 53, 20, Direction::Horizontal, "we are all mad here alice");
    CHECK_THROWS(notebook.write(105, 49, 23, Direction::Vertical, "abanibi"));

    // tests when is writed vertical that vriting on it horizontically will throw exception
    notebook.write(105, 20, 30, Direction::Vertical, "alice in wonderland");
    notebook.write(105, 20, 31, Direction::Vertical, "we are all mad here alice");
    CHECK_THROWS(notebook.write(105, 22, 27, Direction::Horizontal, "abanibi"));

    // checking writing on erased spot 
    notebook.write(106, 50, 20, Direction::Horizontal, "alice in wonderland");
    notebook.write(106, 53, 20, Direction::Horizontal, "we are all mad here alice");
    notebook.erase(106, 49, 23, Direction::Vertical, 50);
    CHECK_THROWS(notebook.write(105, 49, 23, Direction::Vertical, "abanibi"));

    // checking writing on erased spot 
    notebook.write(206, 20, 30, Direction::Vertical, "alice in wonderland");
    notebook.write(206, 20, 31, Direction::Vertical, "we are all mad here alice");
    notebook.erase(206, 22, 28, Direction::Horizontal, 4);
    CHECK_THROWS(notebook.write(105, 22, 27, Direction::Horizontal, "abanibi"));
}

TEST_CASE("Good readings")
{
    Notebook notebook;

    // empty read
    CHECK(notebook.read(42, 50, 3, Direction::Horizontal, 0) == "");
    CHECK(notebook.read(42, 50, 3, Direction::Vertical, 0) == "");

    //read at the end
    CHECK(notebook.read(42, 50, 99, Direction::Horizontal, 1) == "_");

    //reding nothing
    CHECK(notebook.read(42, 50, 3, Direction::Horizontal, 50) == string(50, '_'));
    CHECK(notebook.read(42, 50, 50, Direction::Vertical, 50) == string(50, '_'));
    CHECK(notebook.read(42, 50, 4, Direction::Horizontal, 16) == string(16, '_'));
    CHECK(notebook.read(42, 50, 3, Direction::Vertical, 16) == string(16, '_'));

    //erasing nothing and on erased
    notebook.erase(42, 50, 0, Direction::Horizontal, 100);
    notebook.erase(42, 48, 50, Direction::Vertical, 50);
    CHECK(notebook.read(42, 50, 3, Direction::Horizontal, 50) == string(50, '~'));

    //read whts writen horz
    notebook.write(206, 20, 30, Direction::Horizontal, "alice in wonderland");
    CHECK(notebook.read(206, 20, 30, Direction::Horizontal, 19) == "alice in wonderland");

    // read vert
    notebook.write(206, 21, 31, Direction::Vertical, "We are all mad here alice");
    CHECK(notebook.read(206, 21, 31, Direction::Vertical, 25) == "We are all mad here alice");
    CHECK(notebook.read(206, 20, 31, Direction::Vertical, 26) == "aWe are all mad here alice");
    
    // read combination
    CHECK(notebook.read(206, 18, 31, Direction::Vertical, 28) == "__aWe are all mad here alice");
    CHECK(notebook.read(206, 18, 31, Direction::Vertical, 30) == "__aWe are all mad here alice__");

    // read from distance
    notebook.write(206, 20, 25, Direction::Vertical, "yaba daba du");
    notebook.write(206, 20, 26, Direction::Vertical, "yaba daba du");
    CHECK(notebook.read(206, 20, 25, Direction::Vertical, 10) == "yy___alice");

    // erase and read
    notebook.erase(206, 20, 31, Direction::Horizontal, 17);
    CHECK(notebook.read(206, 21, 31, Direction::Vertical, 25) == "a~~~~~~~~~~~~~~~~~d");
    
    // erase and read both
    notebook.erase(206, 20, 30, Direction::Horizontal, 1);
    CHECK(notebook.read(206, 21, 31, Direction::Vertical, 25) == "~~~~~~~~~~~~~~~~~~d");
    
    CHECK(notebook.read(206, 18, 31, Direction::Vertical, 28) == "__~We are all mad here alice");
    CHECK(notebook.read(206, 18, 31, Direction::Vertical, 30) == "__~We are all mad here alice__");

    notebook.erase(206, 20, 25, Direction::Vertical, 12);
    CHECK(notebook.read(206, 21, 31, Direction::Vertical, 25) == string(12, '~'));
}