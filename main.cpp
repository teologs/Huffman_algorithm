#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
//#include "Tree.h"
#include "Table.h"
#include "Node.h"

using namespace std;

void deleteTree(Node* current)
{
    if(current==nullptr)
        return;
    deleteTree(current->left);
    deleteTree(current->right);
    delete current;
}

void printTreeWithSpace(Node* root, int space)
{

    if(root==nullptr)
        return;
    space+=10;
    printTreeWithSpace(root->right,space);
    cout << endl;
    for(int i=10;i<space;i++)
        cout << " ";
    cout << root->integer << endl;
    printTreeWithSpace(root->left,space);
    if(root->right==nullptr && root->left == nullptr)
    cout << "Symbol is " << root->symbol << " " << endl;
}

void printTree(Node* root)
{
    printTreeWithSpace(root, 0);
}

void sortArray(Node** array, int arrayElementsCounter )
{
    for(int j=0; j<arrayElementsCounter-1; j++)
    {
        for(int i=0; i<arrayElementsCounter-j-1;i++)
        {
            if(array[i]->integer > array[i+1]->integer)
            {
                Node* temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
            }
        }
    }
}

void printArray(Node** arr, int stop)
{
    for (int i=0;i<stop;i++)
    {
        cout << "number: " << arr[i]->integer << " symbol: " << arr[i]->symbol << endl;
    }
}

/*void fillStringTable(Node* tree, Table& t, int index, string currentBinaryCode)
{
    if(tree->left==nullptr && tree->right==nullptr)
    {

        t.setBinaryElement(currentBinaryCode, tree->symbol, index);
        return;
    }
    else{
        fillStringTable(tree->left, t, index+1, currentBinaryCode+='0');
        fillStringTable(tree->right, t, index+1, currentBinaryCode+='1');
    }
}*/

void fillStringTable(Node* tree, Table& t, string currentBinaryCode)
{
    if(tree->left==nullptr && tree->right==nullptr)
    {

        t.setBinaryElementBySymbol(currentBinaryCode, tree->symbol);
        return;
    }
    else{
        fillStringTable(tree->left, t, currentBinaryCode+'0');
        fillStringTable(tree->right, t, currentBinaryCode+'1');
    }
}

int turnIntoDecimal(char* buffer)
{
    int result = 0;
    for(int i=0;i<8;i++)
    {
        result = result + ((int)buffer[i] - 48) * pow(2,i);
        cout << result << endl;
    }
    return result;
}

void resetBuffer(char* buffer)
{
    for(int i=0; i<8; i++)
        buffer[i] = '0';
}

/*int convertDecimalIntoBinary(string line)
{
    int result=0;
    stack<int> s;
    int temp=0;
    for(char& c : line)
    {
        temp = temp*10 + ((int)c - 48);
    }
    while(temp!=0)
    {
        s.push(temp%2);
        temp=temp/2;
    }
    while(!s.empty())
    {
        result = result*10 + s.top();
        s.pop();
    }
    return result;
}*/

string convertDecimalIntoBinary(string line)
{
     string str;
     int index = 0;
     for(int i=0;i<8;i++)
     {
         str[i]='0';
     }
    int temp=0;
    for(char& c : line)
    {
        temp = temp*10 + ((int)c - 48);
    }
    while(temp!=0)
    {
        if(temp%2==1)
            str[index] = '1';
        temp=temp/2;
        index++;
    }
    return str;
}

/*void decompressIntoFile(ofstream& writingIntoThisFile, Node* tree, string& line)
{
    for(char& c : line)
    {
        if(tree==nullptr)
            return;

        if(tree->right==nullptr && tree->left==nullptr)
        {
            writingIntoThisFile << tree->symbol;
            return;
        }

        if(c=='0')
        {
            line = line.substr(1);
            return decompressIntoFile(writingIntoThisFile,tree->left, line);
        }

        if(c=='1')
        {
            line = line.substr(1);
            return decompressIntoFile(writingIntoThisFile,tree->right, line);
        }
    }
}*/

void dec(string& line, Node* tree, ofstream& writingIntoThisFile)
{
    Node* startingCopy = tree;
    int stop = line.size();
    for(int j=0;j<stop;j++)
    {
        ///is it a leaf
        // yes - write in file, return starting root,erase string char
        // no - erase string char and move tree
        if(tree->right==nullptr && tree->left==nullptr)
            {
                writingIntoThisFile << tree->symbol;
                tree = startingCopy;
                line = line.substr(1);
            }
        else
            {
                   if(line[0]=='0')
                   {
                       tree=tree->left;
                       line = line.substr(1);
                   }
                   else{
                       tree = tree->right;
                       line = line.substr(1);
                   }
            }
    }
}

int main() {

    char operatingMode;
    string fileName;

    do {
        cout << "Choose an operating mode: " << endl <<
             "-c[ompress] – параметър, указващ че програмата ще работи в режим компресия;\n"
             "-d[ecompress] – параметър, указващ че програмата ще работи в режим декомпресия;\n"
             "-i <filename> – параметър указващ името на входния файл (подлежащ на компресиране или декомпресиране);\n"
             "-o <filename> – параметър указващ името на изходния файл;\n";
        cin>>operatingMode;
        ///kak da zapazvam mnogo failove i da im generiram izhodni imena - trqbva li?
    }while(!(operatingMode=='c' || operatingMode=='d'));

    if(operatingMode=='c')
    {
        cout << "Compress file: " << endl;
        //cin >> fileName;
        //ofstream file2;
        //file2.open("test2.txt");
        //file2 << "ala bala";
        //file2.close();//
        ifstream file;
        //file.open(fileName);
        file.open("/Users/teodoriliev/Documents/Huffman_algorithm/test.txt");
        string line;
        Table t;
        while(getline(file,line))
        {
            cout << line << endl;
            t.fillTableFromString(line);
        }
        file.close();
        //t.print(7);
        Node* array[t.getNumberOfSavedSymbols()];
        int arrayElementsCounter = t.getNumberOfSavedSymbols();

        ///fill the array with nodes
        for(int i=0; i<t.getNumberOfSavedSymbols(); i++)
        {
            array[i] = new Node;
            array[i]->integer = t.getNumberByIndex(i);
            array[i]->symbol = t.getSymbolByIndex(i);
            array[i]->left = nullptr;
            array[i]->right = nullptr;
        }

        ///sort
        //cout << "broi elementi: "<<arrayElementsCounter << endl;
        /*for(int j=0; j<arrayElementsCounter-1; j++)
        {
            for(int i=0; i<arrayElementsCounter-j-1;i++)
            {
                if(array[i]->integer > array[i+1]->integer)
                {
                    Node* temp = array[i];
                    array[i] = array[i+1];
                    array[i+1] = temp;
                }
            }
        }*/
        sortArray(array, arrayElementsCounter);
        printArray(array, arrayElementsCounter);


        ///count all symbols
        int allSymbolsCounter=0;
        for(int i=0;i<arrayElementsCounter;i++)
        {
            allSymbolsCounter = allSymbolsCounter + t.getNumberByIndex(i);
        }
        ///build huffman tree
        while(array[0]->integer!=allSymbolsCounter)
        {
            ///build new node to connect last 2
            Node* temp = new Node;
            temp->left = array[0];
            temp->right = array[1];
            //cout << "first el: " << array[0]->integer << " second el is: " << array[1]->integer << endl;
            temp->integer = array[0]->integer + array[1]->integer;
            array[0] = temp;
            /// move elements
            for(int i=1; i<arrayElementsCounter-1; i++)
            {
                array[i] = array[i+1];
            }
            arrayElementsCounter = arrayElementsCounter-1;
            sortArray(array,arrayElementsCounter);
        }
        /*cout << "all symbols counter: " << array[0]->integer << endl;
        cout << "symbol: "<<array[0]->symbol << "-;" << endl;
        cout << "------------------" << endl;*/
        printTree(array[0]);
        ///fill string table
        t.copySymbolsIntoBinaryArray();
        string str;
        fillStringTable(array[0],t,str);
        t.printBinaryTable(t.getNumberOfSavedSymbols());

        ///make test file with 1 and 0
        string newFileName;
        cout << "Enter the file in which you want to compress " << endl;
        cin>>newFileName;
        file.open("/Users/teodoriliev/Documents/Huffman_algorithm/test.txt");
        ofstream writingInThisFile;
        writingInThisFile.open("/Users/teodoriliev/Documents/Huffman_algorithm/cmake-build-debug/test2.txt");
        while(getline(file,line))
        {
            for(int j=0;j<line.size();j++)
            {
                writingInThisFile << t.getBinaryNumberBySymbol(line[j]);
            }
            //writingInThisFile << endl;
        }
        writingInThisFile.close();
        file.close();

        ///write huffman table in the file
        writingInThisFile.open(newFileName);
        for(int l=0;l<t.getNumberOfSavedSymbols();l++)
        {
            writingInThisFile << t.getSymbolByIndex(l) << t.getNumberByIndex(l) << endl;
        }
        writingInThisFile << "-" << endl;

        ///convert binary test file into decimal
        file.open("/Users/teodoriliev/Documents/Huffman_algorithm/cmake-build-debug/test2.txt");

        char buffer[8];
        char singleSymbol;
        int current=0;

        while(!file.eof())
        {
            if(current<8)
            {
                file >> buffer[current];
                current++;
            }
            else{
                writingInThisFile << turnIntoDecimal(buffer) << endl;
                current = 0;
                resetBuffer(buffer);
            }
        }
        cout << "======================="<<endl;
        for(int i=0;i<8;i++)
        cout << buffer[i] << endl;
        cout << "=======================" <<endl;
        writingInThisFile << turnIntoDecimal(buffer) << endl;



        writingInThisFile.close();
        file.close();

        /*t.addNumberAndSymbol("145",'H');
        cout << "+++++++++++++++" <<endl;
        cout << t.getNumberBySymbol('H') << endl;
        cout << "+++++++++++++++" <<endl;*/

        //cout << "symbol a binary code: 10" << endl;
        //cout << "symbol A binary code: 01" << endl;
        //cout << "symbol b binary code: 00" << endl;
        //cout << "symbol B binary code: 111" << endl;
        //cout << "symbol c binary code: 1101" << endl;
        //cout << "symbol C binary code: 1100" << endl;
        deleteTree(array[0]);
    }

    else
        {
            ifstream readingFromThisFile;
            ofstream writingInThisFile;
            ofstream testfile;
            testfile.open("test3.txt");
            Table t;
            readingFromThisFile.open("/Users/teodoriliev/Documents/Huffman_algorithm/cmake-build-debug/testfail");
            writingInThisFile.open("decompress.txt");

            string line;
            bool flag = true;
            while(getline(readingFromThisFile,line))
            {
                if(flag==true)
                {
                    if(line.compare("-")==0)
                        flag = false;
                    else{
                        string temp;
                        temp = line.substr(1);
                        cout << "symbol: " << line[0] << " temp: " << temp << endl;
                    }
                }
                else
                {
                    cout << "penis";
                    cout << " " << convertDecimalIntoBinary(line) <<endl ;
                    testfile << convertDecimalIntoBinary(line);
                }
            }
            testfile.close();
            ifstream testFileForReading;
            testFileForReading.open("test3.txt");
            getline(testFileForReading,line);

            ///==================================

            Node* array[t.getNumberOfSavedSymbols()];
            int arrayElementsCounter = t.getNumberOfSavedSymbols();

            ///fill the array with nodes
            for(int i=0; i<t.getNumberOfSavedSymbols(); i++)
            {
                array[i] = new Node;
                array[i]->integer = t.getNumberByIndex(i);
                array[i]->symbol = t.getSymbolByIndex(i);
                array[i]->left = nullptr;
                array[i]->right = nullptr;
            }

            ///sort
            //cout << "broi elementi: "<<arrayElementsCounter << endl;
            for(int j=0; j<arrayElementsCounter-1; j++)
            {
                for(int i=0; i<arrayElementsCounter-j-1;i++)
                {
                    if(array[i]->integer > array[i+1]->integer)
                    {
                        Node* temp = array[i];
                        array[i] = array[i+1];
                        array[i+1] = temp;
                    }
                }
            }
            sortArray(array, arrayElementsCounter);
            printArray(array, arrayElementsCounter);


            ///count all symbols
            int allSymbolsCounter=0;
            for(int i=0;i<arrayElementsCounter;i++)
            {
                allSymbolsCounter = allSymbolsCounter + t.getNumberByIndex(i);
            }
            ///build huffman tree
            while(array[0]->integer!=allSymbolsCounter)
            {
                ///build new node to connect last 2
                Node* temp = new Node;
                temp->left = array[0];
                temp->right = array[1];
                //cout << "first el: " << array[0]->integer << " second el is: " << array[1]->integer << endl;
                temp->integer = array[0]->integer + array[1]->integer;
                array[0] = temp;
                /// move elements
                for(int i=1; i<arrayElementsCounter-1; i++)
                {
                    array[i] = array[i+1];
                }
                arrayElementsCounter = arrayElementsCounter-1;
                sortArray(array,arrayElementsCounter);
            }
            //cout << "all symbols counter: " << array[0]->integer << endl;
            //cout << "symbol: "<<array[0]->symbol << "-;" << endl;
            //cout << "------------------" << endl;
            printTree(array[0]);

            ///==================================
            dec(line, array[0], writingInThisFile);

            testFileForReading.close();
            readingFromThisFile.close();
            writingInThisFile.close();
            deleteTree(array[0]);
        }
}
