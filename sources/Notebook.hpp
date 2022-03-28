#include "page.hpp"
#include <string>
#include <iostream>
#include <unordered_map>
#include "Direction.hpp"
#include <vector>
#include <cctype>
#define LEN 100

namespace ariel
{
    const int LowerBound=33;
    const int UpperBound=126;

    class Notebook
    {
        std::unordered_map<int, Page> pages;

    public:
        ~Notebook()
        {
            // int key = -1;
            // for (auto it = pages.begin(); it != pages.end(); ++it)
            // {
            //     key = it->first;
            //     delete &(pages.at(key));
            // }
        }

        void validRow(int rowId)
        {
            if (rowId < 0)
            {
                std::__throw_invalid_argument("The row you entered is invalid.");
            }
        }

        void validPage(int pageId)
        {
            if (pageId < 0)
            {
                std::__throw_invalid_argument("The page you entered is invalid.");
            }
        }

        void validColumn(int colId)
        {
            if (colId < 0 || colId >= LEN)
            {
                std::__throw_invalid_argument("The col you entered is invalid.");
            }
        }

        void validLength(int length){
            if(length<0){
                std::__throw_invalid_argument("The length you entered is invalid.");
            }
        }

        void validRange(int startFrom, int length)
        {
            validColumn(startFrom);
            validLength(length);
            int endAt=startFrom+length;
            if(endAt>LEN){
                std::__throw_invalid_argument("The range you entered is invalid.");
            }
        }

        void validString(string str)
        {
            unsigned int i;
            char c1 = '~';
            char c2 = '\n';
            char c3 = '\t';
            char c4 = '\r';
            char c;
            for (i = 0; i < str.length(); i++)
            {
                c = str[i];
                if (c == c1 || c == c2 || c == c3 || c == c4 || !isprint(c))
                {
                    std::__throw_invalid_argument("The string contain invalid character: ~ or \n or \t or \r");
                }
            }
        }

        void validDirection(Direction dir)
        {
            if (dir != Direction::Horizontal && dir != Direction::Vertical)
            {
                std::__throw_invalid_argument("The Direction is invalid.");
            }
        }
        
        void write(int pageId, int rowId, int colId, Direction dir, string const &str);
        
        void erase(int pageId, int rowId, int colId, Direction dir, int length);
        
        string read(int pageId, int rowId, int colId, Direction dir, int length);
        
        void show(int pageId);
        
        string getEmptyRow()
        {
            string str;
            for (int i = 0; i < LEN; i++)
            {
                str += "_";
            }
            return str;
        }
        
        bool isPageExist(int pageId)
        {
            validPage(pageId);
            return pages.count(pageId);
        }

        string getEmptyRow(int startFrom, int endAt)
        {
            if (startFrom < 0 || startFrom >= LEN ){
                std::__throw_invalid_argument("invalid starting column.");
            }
            if(endAt < 0 || endAt > LEN){
                std::__throw_invalid_argument("invalid range.");
            }
            if (startFrom > endAt)
            {
                std::__throw_invalid_argument("The inedex you entered is now withing the bounds of a row.");
            }
            string str;
            for (int i = startFrom; i < endAt; i++)
            {
                str += "_";
            }
            return str;
        }
    };
}