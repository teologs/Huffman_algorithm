//
// Created by Teodor Iliev on 2019-11-15.
//

#include "Table.h"

Table::Table() {
    numberOfSavedSymbols = 0;
}

bool Table::checkIfSaved(char a) {

    for(auto i : array)
    {
        if (i.second == a)
        {return true;}
    }
    return false;
}

void Table::addOneCount(char a) {
    for(int j=0; j<numberOfSavedSymbols; j++)
    {
        if(array[j].second==a)
            array[j].first++;
    }
}

Table::Table(string input) {
    numberOfSavedSymbols = 0;
    if(input.length() == 0)
        cout << "No input!" << endl;

    for(int i=0; i<input.length(); i++)
    {
        if (!checkIfSaved(input[i]))
        {
            array[numberOfSavedSymbols].second = input[i];
            array[numberOfSavedSymbols].first++;
            numberOfSavedSymbols++;
        }
        else{
            addOneCount(input[i]);
        }
    }
}

int Table::getNumberByIndex(int n) const
{
    return array[n].first;
}

char Table::getSymbolByIndex(int n) const
{
    return array[n].second;
}

int Table::getNumberBySymbol(char a) const {
    for(auto i : array)
    {
        if(i.second == a)
            return i.first;
    }
    return 0;
}

/*int Table::getNumberBySymbol(char a) const {
    for(int i=0; i< 256; i++)
    {
        if(array[i].second == a)
            return array[i].first;
    }
    return 0;
} */
