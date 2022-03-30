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
            retNum = atoi(msg.c_str());
            cout << retNum << endl;
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
        if (strDir.length() == 1 && tolower(strDir[0]) == 'v') // if the input is "V" or 'v' then its vertical
        {
            dir = Direction::Vertical;
            break;
        }
        // not "h" nor "v"
        cout << "invalid input has been enterd, please follow the intructions" << endl;
        
    } while (true);

    return dir;
    
}

/**
 * @brief by given choice number act accordingly to the option 
 * 
 * @param choice - the users choice
 * @return true - the user enter exit
 * @return false 
 */
bool MenuProg::manageOptins(int choice)
{
    try
    {
        if (choice == READ)
        {
            cout << "for reading from the notebook, we need some data from you" << endl;
            int page = getInputPageNum();
            int row = getInputRowNum();
            int col = getInputColNum();
            Direction dir = getInputDirection();
            int len = getNumber("please here how many charaters you want to read: ");

            cout << "From notebook:" << endl;
            cout << _notebook.read(page, row, col, dir, len) << endl << endl;
        }
        else if (choice == WRITE)
        {
            cout << "for writting from the notebook, we need some data from you" << endl;
            int page = getInputPageNum();
            int row = getInputRowNum();
            int col = getInputColNum();
            Direction dir = getInputDirection();
            string line = MenuProg::getChoice("please here your line: ");

            _notebook.write(page, row, col, dir, line);
            cout << "your string has been added successfuly" << endl << endl;
        }
        else if (choice == ERASE)
        {
            cout << "for erasing from the notebook, we need some data from you" << endl;
            int page = getInputPageNum();
            int row = getInputRowNum();
            int col = getInputColNum();
            Direction dir = getInputDirection();
            int len = getNumber("please here how many charaters you want to erase: ");

            _notebook.erase(page, row, col, dir, len);
            cout << "your erasing has been done successfuly" << endl << endl;
        }
        else if (choice == SHOW)
        {
            cout << "***show option***" << endl;
            int page = getInputPageNum();
            _notebook.show(page);
        }
        else if (choice == CLEAR_SCREN)
        {
            system("clear");
        }
        else if (choice == WRITE)
        {
            cout << "Goodbye!!" << endl << endl;
            return (true);      // return that the program is done
        }
        else
        {
            cout << "invalid choice - please try again" << endl << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << endl << "cannot manage to perform your action because:" << endl;
        std::cerr << e.what() << endl << endl;
    }
    return (false);
    
}

/**
 * @brief the main function of this program - runs the program for the user
 * 
 */
void MenuProg::run()
{
    cout << "welcome to Gilad's Notebook Program!!" << endl << endl;
    int choice = 0;
    bool toStop = false;
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
        toStop = manageOptins(choice);

    } while (!toStop);
    
}