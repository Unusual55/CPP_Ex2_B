#include "row.hpp"
#include <string>
#include <iostream>
#include <cctype>
Row::Row()
{
    int i = 0;
    this->Letters = new (nothrow) char[LEN];
    if (this->Letters == nullptr)
    {
        exit(1); // bad allocation;
    }
    for (i = 0; i < LEN; i++)
    {
        this->Letters[i] = '_';
    }
}

Row::Row(string str, int startFrom){
    int i = 0;
    int charTrack=0;
    int endAt=startFrom+str.length();
    input_check(startFrom, str);
    this->Letters = new (nothrow) char[LEN];
    if (this->Letters == nullptr)
    {
        exit(1); // bad allocation;
    }
    for (i = 0; i < LEN; i++)
    {
        if(i<startFrom || i>=endAt){
            this->Letters[i] = '_';
        }
        else{
            this->Letters[i]=str.at(charTrack);
            charTrack++;
        }
    }
}

Row::~Row(){
    delete[] this->Letters;
}

void Row::input_check(int startFrom, string str){
    int len=str.length();
    int i=0;
    if(startFrom<0 || startFrom>=LEN){
        std::__throw_invalid_argument("The column is not within the range.");
    }
    if(startFrom+len>=LEN){
        std::__throw_invalid_argument("cannot write outside the row.");
    }
    for(i=0;i<len;i++){
        if(str.at(i)=='~'||str.at(i)=='\n'||str.at('\t')||str.at('\r')){
            std::__throw_invalid_argument("cannot write invalid characters.");
        }
    }
}


int Row::getCharStatus(int index){
    if(index<0 || index>=LEN){
        std::__throw_invalid_argument("The inedex you entered is now withing the bounds of a row.");
    }
    // return this->Filled[index];
    if(this->Letters[index]=='_'){
        return 1;
    }
    else{
        return 0;
    }
}

bool Row::canWrite(int startFrom, int endAt){
    int i;
    for(i=startFrom;i<endAt;i++){
        //if we found a char which is not available within the given range, then we can't write to this range.
        if(Row::getCharStatus(i)==0){
            return false;
        }
    }
    //if we did not find any unavailable character within the given range, then we can write to this row.
    return true;
}

void Row::writeToRow(int startFrom, string str){
    input_check(startFrom, str);
    
    int endAt=startFrom+str.length();
    int i;
    int charTrack=0;
    if(!Row::canWrite(startFrom,endAt)){
        std::__throw_invalid_argument("you can't write to this letters in this range");
    }
    for(i=startFrom;i<endAt;i++){
        this->Letters[i]=str.at(charTrack);
        charTrack++;
    }
}



void Row::removeChar(int index){
    if(index<0 || index>=LEN){
        std::__throw_invalid_argument("The inedex you entered is now withing the bounds of a row.");
    }
    this->Letters[index]='~';
}

void Row::removeFromRow(int startFrom, int length){
    int endAt=startFrom+length;
    int i;
    if(startFrom<0 || startFrom>=LEN || endAt<0 || endAt>=LEN || length<0){
        std::__throw_invalid_argument("The inedex you entered is now withing the bounds of a row.");
    }
    for(i=startFrom;i<endAt;i++){
        removeChar(i);
    }
}