#include "Notebook.hpp"

using ariel::Notebook;

Notebook::Notebook()
{
    _notebook.clear();
    _skipLine = string(LINE_MAX / 2, ' ') + "⋮";    // line for continuity in show mode
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

    writeAfterChecks(page, row, col, direction, str);
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

    // if the page doesn't exist then return blank line with the wanted space
    if (_notebook.find(page) == _notebook.end())
    {
        return (string((unsigned int)len, '_'));
    }
    if (direction == Direction::Horizontal)
    {
        // if the row doesn't exist, return the string: '_' * len
        if (_notebook[page].find(row) == _notebook[page].end())
        {
            return (string((unsigned int)len, '_'));
        }
        
        // return the substring from the col
        return (_notebook[page][row].substr((unsigned int)col, (unsigned int)len));
    }
    
    // else if ver
    string read_str;
    for (int i = row; i < row + len; i++)
    {
        // if the row doesn't not exist, return '_' else the char
        read_str += (_notebook[page].find(i) != _notebook[page].end()) ? _notebook[page][i][(unsigned int)col] : '_'; 
    }
    return (read_str);
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

    writeAfterChecks(page, row, col, direction, string((unsigned int)len, '~'), true);
    
}

void Notebook::show(int page)
{
    isGoodIndex(page, 0, 0);
    cout << "\nNow presenting the page " << page << ":" << endl <<endl;
    if (_notebook.find(page) == _notebook.end())
    {
        cout << "The page is empty" << endl;
        return;
    }

    // a (sorted) set that contains the lines by the order
    set<int> keys;
    for (auto it = _notebook[page].begin(); it != _notebook[page].end(); ++it)
    {
        keys.insert(it->first);
        //cout << it->second << "\t" << "(" << it->first << ")" << endl;
    }

    int key = 0;
    int prev = 0;
    int i = 0;
    // run on the each key and get the line of it from the notebook
    for (auto it = keys.begin(); it != keys.end(); ++it, i++)
    {
        key = *(it);
        // if the previous line is not the next int counting (+1) fron te previous, and not the first
        // then print that there is skip (by 3 vertical dots)
        if (i != 0 && prev + 1 < key)
        {
            cout << "\n" << endl;
            cout << _skipLine  << endl << endl;
        }
        prev = key;
        cout << _notebook[page][key] << "\t" << "(" << key << ")" << endl;
    }
    cout << endl <<endl;
    
}

void Notebook::writeAfterChecks(int page, int row, int col, Direction direction, string str, bool isErase)
{
    int len = str.length();
    if (isErase || checkIfCanWrite(page, row, col, direction, len))
    {
        if (_notebook.find(page) == _notebook.end())
        {
            _notebook[page] = unordered_map<int,string>();
        }

        if (direction == Direction::Horizontal)
        {
            // create a row if doesn't exist
            if (_notebook[page].find(row) == _notebook[page].end())
            {
                _notebook[page][row] = string(LINE_MAX, '_');
            }

            // replace the string with the given str
            _notebook[page][row].replace((unsigned int)col, (unsigned int)len, str);

        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                // if the row is not defined then create it the check
                if (_notebook[page].find(i + row) == _notebook[page].end())
                {
                    _notebook[page][i + row] = string(LINE_MAX, '_');
                }
                
                // set the index
                _notebook[page][i + row][(unsigned int)col] = str[(unsigned int)i];
            }
        }

    }
    else if (!isErase) // if the cause of the failier is not the erase flag
    {
        throw MessageException("string cannot be written over written or erased places");
    }
}

bool Notebook::checkIfCanWrite(int page, int row, int col, Direction direction, int len)
{
    // if the page doesn't exist then it can be overrided
    if (_notebook.find(page) == _notebook.end())
    {
        return true;
    }

    if (direction == Direction::Horizontal)
    {
        // if the row doesn't exist then it can be overrided
        if (_notebook[page].find(row) == _notebook[page].end())
        {
            return true;
        }
        
        char ch = 0;
        for (unsigned int c = (unsigned int)col; c < len + col; c++)
        {
            ch = _notebook[page][row][c];
            if (ch != '_') // if the char is not empty then it is a problem
            {
                return false;
            }
        }
        
    }
    else
    {
        for (int r = row; r < row + len; r++)
        {
            // if the row is not defined then pass the check
            if (_notebook[page].find(r) == _notebook[page].end())
            {
                continue;
            }
            
            // if the char is no empty then it is not legal
            if (_notebook[page][r][(unsigned int)col] != '_')
            {
                return false;
            }
        }
    }
    return true; // if something didn't fool you, the path is clear to writting
}