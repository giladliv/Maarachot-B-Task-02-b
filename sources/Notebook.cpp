#include "Notebook.hpp"

using ariel::Notebook;

Notebook::Notebook(/* args */)
{
    _notebook.clear();
}

Notebook::~Notebook()
{
    _notebook.clear();
}

/**
 * @brief checks if indexsing is good
 * will throw exception if bad
 * 
 * @param page page index
 * @param row 
 * @param col 
 * @return true 
 * @return false 
 */
bool Notebook::isGoodIndex(int page, int row, int col)
{
    if (page < 0)
    {
        throw MessageException("page index must be non-negative value");
    }
    if (row < 0)
    {
        throw MessageException("row index must be non-negative value");
    }
    if (col < 0 || col >= LINE_MAX)
    {
        throw MessageException("column index must be non-negative value");
    }

    return true;
}

/**
 * @brief checks if given col direction and len is not out of bounds
 * 
 * @param col 
 * @param len 
 * @param direction 
 * @return true 
 * @return false 
 */
bool Notebook::isGoodLen(int col, int len, Direction direction)
{
    if (len < 0)
    {
        throw MessageException("length must be non-negative value");
    }
    if (direction != Direction::Horizontal && direction != Direction::Vertical)
    {
        throw MessageException("the direction must be horizonl or vertical");
    }
    // if horizonal and passed the bound of line than throw exception
    if (direction == Direction::Horizontal && len + col > LINE_MAX)
    {
        throw MessageException("you try to reach a a pleace that is out of boundries");
    }
    return true;
}

/**
 * @brief checks if string has only readable chars and not '~'
 * 
 * @param str 
 * @return true 
 * @return false 
 */
bool Notebook::isGoodString(string str)
{
    char ch = '\0';
    for (unsigned int i = 0; i < str.length(); i++)
    {
        ch = str[i];
        if (isprint(ch) == 0 || ch == '~')  // check if the char of string is legal
        {
            throw MessageException("The string is not good\nMust be ptintable char and not \'~\'");
        }
    }
    return true;
}


/**
 * @brief write to the notebook
 * 
 * @param page 
 * @param row 
 * @param col 
 * @param direction 
 * @param str 
 */
void Notebook::write(int page, int row, int col, Direction direction, const string& str)
{
    isGoodIndex(page, row, col);                // check indexing
    isGoodLen(col, str.length(), direction);    // check vilidty of the bounds
    isGoodString(str);                          // check if the string is ok
    
    // if reached here no exception was thrown - YAY!
    
}

/**
 * @brief read from the notebook
 * 
 * @param page 
 * @param row 
 * @param col 
 * @param direction 
 * @param len 
 * @return string 
 */
string Notebook::read(int page, int row, int col, Direction direction, int len)
{
    isGoodIndex(page, row, col);
    isGoodLen(col, len, direction);
    // if reached here no exception was thrown - YAY!

    return "";
}

/**
 * @brief erase from notebook
 * 
 * @param page 
 * @param row 
 * @param col 
 * @param direction 
 * @param len 
 */
void Notebook::erase(int page, int row, int col, Direction direction, int len)
{
    isGoodIndex(page, row, col);
    isGoodLen(col, len, direction);
}

void Notebook::show(int page)
{
    isGoodIndex(page, 0, 0);
}