#ifndef PAGE_HPP
#define PAGE_HPP
#pragma once
#include <string>
#include "row.hpp"
#include "Direction.hpp"
#include <unordered_map>
class Page{
    unordered_map<int, Row> rows;
    ~Page(){
        rows.clear();
    }
    public:
        Page(){;}
        void validRow(int index){
            if(index<0){
                std::__throw_invalid_argument("row index cannot be negative number.");
            }
        }
        bool isRowExist(int index){
            validRow(index);
            return rows.contains(index);
        }
        void addRow(int rowId, int startFrom, string str);
        void addRow(int rowId);
        void removeCharAt(int rowId, int colId){
            validRow(rowId);
            if(isRowExist(rowId)){
                rows.at(rowId).removeChar(colId);
            }
            else{
                if(colId<0 || colId>=LEN){
                    std::__throw_invalid_argument("column index is not within the bounds.");
                }
                else{
                    rows.insert({rowId, Row()});
                    rows.at(rowId).removeChar(colId);
                }
            }
        }
        void writeToRowHorizontal(int rowId, int colId, string str);
        void eraseFromPageHorizontal(int rowId, int colId, int length);
        void writeToRowVertical(int rowId, int colId, string str);
        void eraseFromPageHorizontal(int rowId, int colId, int length);
        void canWriteVertical(int rowId, int colId, string str);
        void validColStr(int startFrom, string str);
};




#endif