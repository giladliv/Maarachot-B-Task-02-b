#include "MenuProg.hpp"

using ariel::MenuProg;

MenuProg::MenuProg()
{
}

MenuProg::~MenuProg()
{
}

/**
 * @brief get a string with spaces
 * 
 * @param msg message before input
 * @return string 
 */
string MenuProg::getChoice(const string& msg)
{
	string str;
	cout << msg;
    getline(cin, str);
	return str;
}

/**
 * @brief get an integer safely
 * 
 * @param msg message before input
 * @return int 
 */
int MenuProg::getNumber(const string& msg)
{
	string str;
    int retNum = 0;
    do
    {
        try
        {
            str = getChoice(msg);
            retNum = stoi(msg);
            break;
        }
        catch(const std::exception& e)
        {
            cout << "the input must be a number" << endl;
        }
    } while (true);
    
    return retNum;
}

/**
 * @brief get the page number from the input
 * 
 * @return int 
 */
int MenuProg::getInputPageNum()
{
    return getNumber("please enter here the page number: ");
}

/**
 * @brief get the row number from the input
 * 
 * @return int 
 */
int MenuProg::getInputRowNum()
{
    return getNumber("please enter here the row number: ");
}

/**
 * @brief get the column number from the input
 * 
 * @return int 
 */
int MenuProg::getInputColNum()
{
    return getNumber("please enter here the column number: ");
}

/**
 * @brief get the direction from input - h for horizonal, v - for vertical
 * 
 * @return Direction 
 */
Direction MenuProg::getInputDirection()
{
    string strDir;
    Direction dir;
    do
    {
        strDir = getChoice("please enter the direction (h - horizozontal, v - vertical): ");
        if (strDir.length() == 1 && tolower(strDir[0]) == 'h') // if the input is "H" or 'h' then its horizonal 
        {
            dir = Direction::Horizontal;
            break;
        }
        else if (strDir.length() == 1 && tolower(strDir[0]) == 'v')
        {
            dir = Direction::Vertical;
            break;
        }
        else
        {
            cout << "invalid input has been enterd, please follow the intructions" << endl;
        }
        
    } while (true);

    return dir;
    
}

void manageOptins(int choice)
{

}

/**
 * @brief the main function of this program - runs the program for the user
 * 
 */
void MenuProg::run()
{
    cout << "welcome to Gilad's Notebook Program!!" << endl << endl;
    int choice = 0;
    do
    {
        cout << "what can we offer to you?" << endl;
        cout << "1. read from the notebook" << endl;
        cout << "2. write to the notebook" << endl;
        cout << "3. erase prats from the notebook" << endl;
        cout << "4. show a page" << endl;
        cout << "5. clear screen" << endl;
        cout << "6. exit from the program" << endl;

        choice = getNumber("please enter here your choice: ");

        switch (choice)
        {
        case READ:
            break;
        
        default:
            break;
        }

    } while (true);
    
}