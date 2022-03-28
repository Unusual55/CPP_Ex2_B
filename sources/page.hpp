#ifndef PAGE_HPP
#define PAGE_HPP
#pragma once
#include <string>
#include "Direction.hpp"
#include <unordered_map>
#include <vector>
#include <iterator>
#include <string>
#include <iostream>
#define LEN 100

using namespace std;

class Page
{
    unordered_map<int, char *> rows;
    void printRow(int rowId)
    {
        for (int i = 0; i < LEN; i++)
        {
            cout << rows.at(rowId)[i];
        }
        cout << endl;
    }

public:
    Page()
    {
        ;
    }
    ~Page()
    {
        int key = -1;
        for (auto it = rows.begin(); it != rows.end(); ++it)
        {
            key = it->first;
            delete[] rows.at(key);
        }
    }

    void validRow(int index)
    {
        if (index < 0)
        {
            std::__throw_invalid_argument("row index cannot be negative number.");
        }
    }

    bool isRowExist(int index)
    {
        validRow(index);
        int count = rows.count(index);
        bool flag=false;
        if(count>0){
            flag=true;
        }
        return flag;
    }

    void addRow(int rowId, int startFrom, string const &str);
    void addRow(int rowId);
    void removeCharAt(int rowId, int colId)
    {
        validRow(rowId);
        if (colId < 0 || colId >= LEN)
        {
            std::__throw_invalid_argument("column index is not within the bounds.");
        }

        if (isRowExist(rowId))
        {
            rows.at(rowId)[colId] = '~';
        }
        else
        {
            addRow(rowId);    
            rows.at(rowId)[colId] = '~';
        }
    }
    void writeToRowHorizontal(int rowId, int colId, string const &str);
    void eraseFromPageHorizontal(int rowId, int colId, int length);
    void writeToRowVertical(int rowId, int colId, string const &str);
    void eraseFromPageVertical(int rowId, int colId, int length);
    void canWriteVertical(int rowId, int colId, string const &str);
    static void validColStr(int startFrom, string const &str)
    {
        unsigned int i = 0;
        int len = str.length();
        if (startFrom < 0 || startFrom >= LEN)
        {
            std::__throw_invalid_argument("column is not within the range.");
        }
        if (startFrom + len >= LEN)
        {
            std::__throw_invalid_argument("cannot write out of bounds");
        }
        char c1 = '~';
        char c2 = '\n';
        char c3 = '\t';
        char c4 = '\r';
        char c = ' ';
        for (i = 0; i < str.length(); i++)
        {
            c = str[i];
            if (c == c1 || c == c2 || c == c3 || c == c4)
            {
                std::__throw_invalid_argument("The string contain invalid character: ~ or \n or \t or \r");
            }
        }
    }
    string readFromRowHorizontal(int rowId, int colId, int length);
    string readFromColumnVertical(int rowId, int colId, int length);
    string getEmptyRow()
    {
        string str = "";
        for (int i = 0; i < LEN; i++)
        {
            str += "_";
        }
        return str + "\n";
    }
    string getEmptyRow(int startFrom, int endAt)
    {

        if (startFrom < 0 || startFrom >= LEN)
        {
            std::__throw_invalid_argument("invalid starting column.");
        }
        if (startFrom>endAt)
        {
            std::__throw_invalid_argument("The length cannot be a negative number.");
        }
        if (endAt> LEN || endAt<0)
        {
            std::__throw_invalid_argument("The inedex you entered is not withing the bounds of a row.");
        }
        string str = "";
        for (int i = startFrom; i < endAt; i++)
        {
            str += "_";
        }
        return str;
    }

    int getMaximalRowId()
    {
        int maxRowId = -1;
        int curr = -1;
        for (auto kv : rows)
        {
            curr = kv.first;
            maxRowId = max(curr, maxRowId);
        }
        return maxRowId;
    }

    void show()
    {
        int maxPage = getMaximalRowId();
        int i;
        for (i = 0; i <= maxPage; i++)
        {
            if (!isRowExist(i))
            {
                cout << getEmptyRow() << endl;
            }
            else
            {
                printRow(i);
            }
        }
    }

    string getRow(int rowId, int startFrom, int length)
    {
        validRow(rowId);
        int i = 0;
        if (startFrom < 0 || startFrom >= LEN)
        {
            std::__throw_invalid_argument("invalid starting column.");
        }
        if (length < 0)
        {
            std::__throw_invalid_argument("The length cannot be a negative number.");
        }
        if (startFrom + length > LEN)
        {
            std::__throw_invalid_argument("The inedex you entered is now withing the bounds of a row....");
        }
        string str;
        if (isRowExist(rowId))
        {
            for (i = startFrom; i < startFrom + length; i++)
            {
                str += rows.at(rowId)[(unsigned)i];
            }
        }
        else{
            str+=getEmptyRow(startFrom, startFrom+length);
        }
        return str;
    }
};

#endif