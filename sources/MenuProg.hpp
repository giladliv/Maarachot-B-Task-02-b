#pragma once

#include "Notebook.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;


namespace ariel
{
    class MenuProg
    {
        public:
            MenuProg(/* args */);
            void run();
            static string getChoice(const string& msg = "");
            static int getNumber(const string& msg = "");
            static Direction getInputDirection();
            ~MenuProg();

        private:
            Notebook _notebook;
            static int getInputPageNum();
            static int getInputRowNum();
            static int getInputColNum();
            
            //static int getInputLenNum(); //return getNumber("please enter here the length number for: ");
            
            
    };

    // enum
    enum {
		READ = 1,
		WRITE,
        ERASE,
        SHOW,
        CLEAR_SCREN,
        EXIT

	};
}




