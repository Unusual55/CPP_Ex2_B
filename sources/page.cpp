#include "page.hpp"

void Page::addRow(int rowId, int startFrom, string const &str)
{
    int i = 0;
    validRow(rowId);
    if (isRowExist(rowId))
    {
        std::__throw_invalid_argument("row already exist.");
    }
    validColStr(startFrom, str);
    char * row = new char[LEN];
    for(int i=0;i<LEN;i++){
        row[i]='_';
    }
    int len=str.size();
    unsigned int track=0;
    for(int j=startFrom;j<startFrom+len;j++){
        row[j]=str[track];
        track++;
    }

    rows.insert({rowId, row});
}

void Page::addRow(int rowId)
{
    int i = 0;
    validRow(rowId);
    if (isRowExist(rowId))
    {
        std::__throw_invalid_argument("row already exist.");
    }
    char * row = new char[LEN];
    for(i=0;i<LEN;i++){
        row[i]='_';
    }
    rows.insert({rowId, row});
}

void Page::writeToRowHorizontal(int rowId, int colId, string const &str)
{
    unsigned int track=0;
    validRow(rowId);
    validColStr(colId, str);
    if (isRowExist(rowId))
    {
        int j=0;
        for(j=colId;j<(int)str.size()+colId;j++){
            if(rows.at(rowId)[(unsigned)j]!='_'){
                std::__throw_invalid_argument("cannot overwrite rows.");
            }
        }
        for(j=colId;j<(int)str.size()+colId;j++, track++){
            rows.at(rowId)[(unsigned)j]=str[track];
        }
    }
    else
    {
        addRow(rowId, colId, str);
    }
}

void Page::eraseFromPageHorizontal(int rowId, int colId, int length)
{
    int i=0;
    validRow(rowId);
    if (colId < 0 || colId >= LEN || length < 0 || length + colId > LEN)
    {
        std::__throw_invalid_argument("cannot remove outside of bounds");
    }
    if (isRowExist(rowId))
    {
        for(i=colId;i<colId+length;i++){
            rows.at(rowId)[i]='~';
        }
    }
    else
    {
        addRow(rowId);
        for(i=colId;i<colId+length;i++){
            rows.at(rowId)[i]='~';
        }
    }
}

string Page::readFromRowHorizontal(int rowId, int colId, int length)
{
    validRow(rowId);
    if (colId < 0 || colId >= LEN || length < 0 || length + colId > LEN)
    {
        std::__throw_invalid_argument("cannot remove outside of bounds");
    }
    int endAt = colId + length;
    string str;
    if (isRowExist(rowId))
    {
        str = getRow(rowId, colId, length);
    }
    else
    {
        str = getEmptyRow(colId, endAt);
    }
    return str;
}

void Page::canWriteVertical(int rowId, int colId, string const &str)
{
    validRow(rowId);
    unsigned int i = 0;
    int len = str.length();
    int j = 0;
    unsigned int track1 = 0;
    int k = 0;
    if (colId < 0 || colId >= LEN)
    {
        std::__throw_invalid_argument("cannot write outside of bounds");
    }
    char c1 = '~';
    char c2 = '\n';
    char c3 = '\t';
    char c4 = '\r';
    char c=' ';
    for (i = 0; i < str.length(); i++)
    {
        c = str[i];
        if (c == c1 || c == c2 || c == c3 || c == c4)
        {
            std::__throw_invalid_argument("The string contain invalid character: ~ or \n or \t or \r");
        }
    }

    for (j = rowId; j < rowId + len; j++)
    {
        if (isRowExist(j))
        {
            if (rows.at(j)[colId] != '_')
            {
                std::__throw_invalid_argument("cannot overwrite the row.");
            }
        }
        track1++;
    }
}

void Page::writeToRowVertical(int rowId, int colId, string const &str)
{
    int i = 0;
    unsigned int track = 0;
    int len = str.length();
    string c;
    canWriteVertical(rowId, colId, str);
    for (i = rowId; i < rowId + len; i++)
    {
        c=str[track];
        if (isRowExist(i))
        {
            rows.at(i)[colId]=c[0];
        }
        else
        {
            addRow(i);
            rows.at(i)[colId]=c[0];
        }
        track++;
    }
}

void Page::eraseFromPageVertical(int rowId, int colId, int length)
{
    validRow(rowId);
    int i=0;
    if (colId < 0 || colId >= LEN || length < 0)
    {
        std::__throw_invalid_argument("cannot write outside of bounds");
    }
    for (i = rowId; i < rowId + length; i++)
    {
        if (!isRowExist(i))
        {
            addRow(i);
            rows.at(i)[colId]='~';
        }
        else{
            rows.at(i)[colId]='~';
        }
    }
}

string Page::readFromColumnVertical(int rowId, int colId, int length)
{
    validRow(rowId);
    int i=0;
    if (colId < 0 || colId >= LEN || length < 0)
    {
        std::__throw_invalid_argument("cannot read outside of bounds");
    }
    string str;
    for (i = rowId; i < rowId + length; i++)
    {
        if (!isRowExist(i))
        {
            str += "_";
        }
        else
        {
            str += rows.at(i)[colId];
        }
    }
    return str;
}
