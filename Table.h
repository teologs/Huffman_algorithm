#ifndef HUFFMAN_ALGORITHM_TABLE_H
#define HUFFMAN_ALGORITHM_TABLE_H

#include <iostream>

using namespace std;



class Table {
private:
    int numberOfSavedSymbols;
    pair<int, char> array[256];
    pair<string, char> binaryArray[256];
public:
    Table();
    Table(string input);

    //void addNumberByIndex(int n) const;
    //void addNumberBySymbol(char a) const;

    int getNumberByIndex(int n) const;
    char getSymbolByIndex(int n) const;
    int getNumberBySymbol(char a) const;
    void fillTableFromString(string input);
    int getNumberOfSavedSymbols() const;
    void setSymbolByIndex(int index, char symbol);
    void setNumberByIndex(int index, string number);
    void addNumberAndSymbol(string number, char symbol);


    bool checkIfSaved(char a);
    void addOneCount(char a);

    void printTable(int n);
    ///----------------------------

    void setBinaryElement(string& binary, char symbol, int index);
    void printBinaryTable(int n);
    void setBinaryElementBySymbol(string& binary, char symbol);
    void copySymbolsIntoBinaryArray();
    string getBinaryNumberBySymbol(char symbol);
    string getBinaryNumberByIndex(int index);
    char getBinarySymbolByIndex(int index);




};


#endif //HUFFMAN_ALGORITHM_TABLE_H
