#include "Notebook.hpp"

namespace ariel
{
    void Notebook::show(int pageId)
    {
        int const CASE5=5;
        int i=0;
        validPage(pageId);
        if(!isPageExist(pageId)){
            for(i=0;i<CASE5;i++){
                cout<<getEmptyRow()<<endl;
            }
        }
        else{
            pages.at(pageId).show();
        }
    }

    string Notebook::read(int pageId, int rowId, int colId, Direction dir, int length){
        validPage(pageId);
        validRow(rowId);
        validColumn(colId);
        validDirection(dir);
        validLength(length);
        string str;
        if(dir==Direction::Horizontal){
            validRange(colId, length);
            if(!isPageExist(pageId)){
                str=getEmptyRow(colId, colId+length);
            }
            else{
                str=pages.at(pageId).readFromRowHorizontal(rowId, colId, length);
            }
        }
        else{
            if(!isPageExist(pageId)){
                for(int i=rowId;i<=rowId+length;i++){
                    str+="_";
                }
                str+="\n";
            }
            else{
                str=pages.at(pageId).readFromColumnVertical(rowId, colId, length);
            }
        }
        return str;
    }

    void Notebook::write(int pageId, int rowId, int colId, Direction dir, string const &str){
        validPage(pageId);
        validRow(rowId);
        if (colId < 0 || colId >= LEN)
        {
            std::__throw_invalid_argument("The col you entered is invalid.");
        }
        validString(str);
        int const id=pageId;
        if(dir==Direction::Horizontal){
            validRange(colId, str.length());
            if(!isPageExist(pageId)){
                pages.insert({id, Page()});
            }
            pages.at(pageId).writeToRowHorizontal(rowId, colId, str);
        }
        else{
            if(!isPageExist(pageId)){
                pages.insert({id, Page()});
            }
            pages.at(pageId).writeToRowVertical(rowId, colId, str);
        }        
    }

    void Notebook::erase(int pageId, int rowId, int colId, Direction dir, int length){
        validPage(pageId);
        validRow(rowId);
        validColumn(colId);
        validLength(length);
        validDirection(dir);
        if(!isPageExist(pageId)){
            pages.insert({pageId, Page()});
        }
        if(dir!=Direction::Vertical){
            validRange(colId, length);
            pages.at(pageId).eraseFromPageHorizontal(rowId, colId, length);
        }
        else{
            pages.at(pageId).eraseFromPageVertical(rowId, colId, length);
        }        
    }
};
 
//  int main(){
//      ariel::Notebook notebook;
//      cout<<"111";
//  }