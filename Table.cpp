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

void Table::fillTableFromString(string input) {
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

int Table::getNumberOfSavedSymbols() const {
    return numberOfSavedSymbols;
}

void Table::printTable(int n) {
    for(int i=0;i<n;i++)
    {
        cout << "index " << i << "'s symbol is " << array[i].second << endl;
        cout << "index " << i << "'s counter is " << array[i].first << endl;
    }
}

void Table::setBinaryElement(string& binary, char symbol, int index) {
    binaryArray[index].first = binary;
    binaryArray[index].second = symbol;
}

void Table::printBinaryTable(int n) {
    for(int i=0;i<n;i++)
    {
        cout << "index " << i << "'s symbol is " << binaryArray[i].second << endl;
        cout << "index " << i << "'s binary code is " << binaryArray[i].first << endl;
    }
}

void Table::setBinaryElementBySymbol(string &binary, char symbol) {
    for(int i=0;i<numberOfSavedSymbols;i++)
    {
        if(binaryArray[i].second==symbol)
            binaryArray[i].first = binary;
    }
}

void Table::copySymbolsIntoBinaryArray() {
    for(int i=0;i<numberOfSavedSymbols;i++)
    {
        binaryArray[i].second = array[i].second;
    }
}

string Table::getBinaryNumberBySymbol(char symbol) {
    for(int i=0;i<numberOfSavedSymbols;i++)
    {
        if(binaryArray[i].second == symbol)
            return binaryArray[i].first;
    }
}

string Table::getBinaryNumberByIndex(int index) {
    return binaryArray[index].first;
}

char Table::getBinarySymbolByIndex(int index) {
    return binaryArray[index].second;
}

void Table::setNumberByIndex(int index, string number) {
    int temp=0;
    for(char& c : number)
    {
        temp = temp*10 + ((int)c - 48);
    }
    array[index].first = temp;
}

void Table::setSymbolByIndex(int index, char symbol) {
    array[index].second = symbol;
}

void Table::addNumberAndSymbol(string number, char symbol) {
    array[numberOfSavedSymbols].second = symbol;
    int temp=0;
    for(char& c : number)
    {
        temp = temp*10 + ((int)c - 48);
    }
    array[numberOfSavedSymbols].first = temp;
    numberOfSavedSymbols++;
}
