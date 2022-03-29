#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <cctype>
#include "Direction.hpp"

using ariel::Direction;
using namespace std;

#define LINE_MAX 100

namespace ariel
{
    class Notebook
    {
        private:
            bool isGoodIndex(int page, int row, int col);
            bool isGoodLen(int col, int len, Direction direction);
            bool isGoodString(string str);

            unordered_map<int, unordered_map<int,string>> _notebook;
        public:
            Notebook();
            void write(int page, int row, int col, Direction direction, const string& str);
            string read(int page, int row, int col, Direction direction, int len);
            void erase(int page, int row, int col, Direction direction, int len);
            void show(int page);
            ~Notebook();

    
    };
}

class MessageException : public exception
{
    // this class is for throwing exceptions by given string
    // the what method will return the given string
    // altough the best solution is to create for each case its own exception'
    // in this task it would be easier and more efficient
    // to just make an exception that returns its given string

    public:
        MessageException(string str) : _msg(str) {}     // using init line (for c'tor)
        const char* what() const noexcept {return _msg.c_str();}    // return the saved string as const char *
    private:
        string _msg;

};