#include "page.hpp"

void Page::validColStr(int startFrom, string str){
    int i;
    int len = str.length();
    if (startFrom < 0 || startFrom >= LEN)
    {
        std::__throw_invalid_argument("column is not within the range.");
    }
    if (startFrom + len >= LEN)
    {
        std::__throw_invalid_argument("cannot write out of bounds");
    }
    for (i = 0; i < len; i++)
    {
        if (str.at(i) == '~' || str.at(i) == '\n' || str.at('\t') || str.at('\r'))
        {
            std::__throw_invalid_argument("cannot write invalid characters.");
        }
    }

}

void Page::addRow(int rowId, int startFrom, string str)
{
    int i;
    validRow(rowId);
    if (isRowExist(rowId))
    {
        std::__throw_invalid_argument("row already exist.");
    }
    validColStr(startFrom, str);
    int len = str.length();
    
    rows.insert({rowId,Row(str, startFrom)});
}

void Page::addRow(int rowId){
    int i;
    validRow(rowId);
    if (isRowExist(rowId))
    {
        std::__throw_invalid_argument("row already exist.");
    }
    rows.insert({rowId,Row()});
}

void Page::writeToRowHorizontal(int rowId, int colId, string str){
    validRow(rowId);
    if(isRowExist(rowId)){
        rows.at(rowId).writeToRow(colId, str);
    }
    else{
        validColStr(colId, str);
        addRow(rowId, colId, str);
    }
}

void Page::eraseFromPageHorizontal(int rowId, int colId, int length){
    validRow(rowId);
    if(isRowExist(rowId)){
        rows.at(rowId).removeFromRow(colId, length);
    }
    else{
        if(colId<0 || colId>=LEN || length<0 || length+colId>LEN){
            std::__throw_invalid_argument("cannot remove outside of bounds");
        }
        addRow(rowId);
        rows.at(rowId).removeFromRow(colId, length);
    }
}

void Page::canWriteVertical(int rowId, int colId, string str){
    validRow(rowId);
    int i, len=str.length(), j, track1=0, k;
    if(colId<0 || colId>=LEN){
        std::__throw_invalid_argument("cannot write outside of bounds");
    }
    for (i = 0; i < len; i++)
    {
        if (str.at(i) == '~' || str.at(i) == '\n' || str.at('\t') || str.at('\r'))
        {
            std::__throw_invalid_argument("cannot write invalid characters.");
        }
    }
   for(j=rowId; j<rowId+len;j++){
       if(isRowExist(j)){
           if(rows.at(j).getCharStatus(track1)==0){
                std::__throw_invalid_argument("cannot overwrite the row.");
           }
           track1++;
       }
   }
}

void Page::writeToRowVertical(int rowId, int colId, string str){
    int i, track=0, len=str.length();
    canWriteVertical(rowId, colId, str);
    for(i=rowId; i<rowId+len;i++){
        if(isRowExist(i)){
            rows.at(i).writeCharAt(colId,str.at(track));
        }
        else{
            addRow(i);
            rows.at(i).writeCharAt(colId, str.at(track));
        }
        track++;
    }
}

void Page::eraseFromPageHorizontal(int rowId, int colId, int length){
    validRow(rowId);
    int i;
    if(colId<0 || colId>=LEN || length<0){
        std::__throw_invalid_argument("cannot write outside of bounds");
    }
    for(i=rowId;i<rowId+length;i++){

        if(!isRowExist(rowId)){
            addRow(i);
        }
        rows.at(i).removeChar(colId);
    }
}



