#ifndef ROW_H
#pragma once
#define ROW_H
#include <string>
#include <iostream>
#define LEN 100
using namespace std;
class Row
{
    char *Letters;
    public:
        Row();
        Row(string str, int startFrom);
        ~Row();
        void input_check(int startFrom, string str);
        bool canWrite(int startFrom, int endAt);
        int getCharStatus(int index);
        void writeToRow(int startFrom, string str);
        void removeChar(int index);
        void printRow()
        {
            for (int i = 0; i < LEN; i++)
            {
                cout << Letters[i];
            }
            cout << endl;
        }
        void removeFromRow(int startFrom, int length);
        void print_dummy_row(){
            int i;
            for(i=0;i<LEN;i++){
                cout<<"_";
            }
            cout<<endl;
        }
        void writeCharAt(int colId, char c){
            if(colId<0 || colId>=LEN){
                std::__throw_invalid_argument("The inedex you entered is now withing the bounds of a row.");
            }
            if(c=='~' || c=='\n' || c=='\t' || c=='\r'){
                std::__throw_invalid_argument("cannot write invalid characters.");
            }
            if(getCharStatus(colId)==0){
                std::__throw_invalid_argument("cannot overwrite the row.");
            }
            Letters[colId]=c;
        }
};

#endif