//
// Created by Teodor Iliev on 2019-11-15.
//

#ifndef HUFFMAN_ALGORITHM_TABLE_H
#define HUFFMAN_ALGORITHM_TABLE_H

#include <iostream>

using namespace std;



class Table {
private:
    int numberOfSavedSymbols;
    pair<int, char> array[256];
public:
    Table();
    Table(string input);
    //void addNumberByIndex(int n) const;
    //void addNumberBySymbol(char a) const;

    int getNumberByIndex(int n) const;
    char getSymbolByIndex(int n) const;
    int getNumberBySymbol(char a) const;

    bool checkIfSaved(char a);
    void addOneCount(char a);




};


#endif //HUFFMAN_ALGORITHM_TABLE_H
