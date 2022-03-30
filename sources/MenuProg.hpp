#pragma once

#include "Notebook.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;

#define READ 1
#define WRITE 2
#define ERASE 3
#define SHOW 4
#define CLEAR_SCREN 5
#define EXIT 6

namespace ariel
{
    class MenuProg
    {
        public:
            MenuProg(/* args */);
            void run();
            static string getChoice(const string& msg = "");
            static int getNumber(const string& msg = "");
            
            ~MenuProg();

        private:
            Notebook _notebook;
            static int getInputPageNum();
            static int getInputRowNum();
            static int getInputColNum();
            static Direction getInputDirection();
            bool manageOptins(int choice);
            //static int getInputLenNum(); //return getNumber("please enter here the length number for: ");
            
            
    };
}




