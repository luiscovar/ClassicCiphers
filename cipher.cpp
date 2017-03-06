#include <string>
#include "CipherInterface.h"
#include "Playfair.h"
#include "Caesar.h"
#include <sstream>
#include "Railfence.h"
#include "Vignere.h"
#include "RowTransposition.h"
#include <fstream>


using namespace std;

int main(int argc, char** argv)
{
	CipherInterface* cipher;
    string outputText = "";

    if (argc != 6)
    {
        cout << "\n\nYou must input all the arguments";
        cout << "Must be in this format:\n";
        cout << "\t./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>\n\n";
        cout << "Acceptable ciphers names are:\n \
            \tPLF:Playfair\n \
            \tRTS:Row Transposition \n \
            \tRFC:Railfence\n \
            \tVIG:Vigenre\n \
            \tCES:Caesar\n";
        return 0;
    }
    
    //parse arguments
    string ciphertype = argv[1];
    string option = argv[3];
    string key = argv[2];
    string inputFile = argv[4];
    string outputFile_Name = argv[5];

    //read contents of the file
    ifstream inFile;
    inFile.open(inputFile);
    if(!inFile.is_open())
    {
        cout << "Could Not Open FIle\n";
        return 0;
    }
    stringstream strStream;
    strStream << inFile.rdbuf();
    string inputText = strStream.str();
    inFile.close();
    
    if(option != "ENC" && option != "DEC")
    {
        cout << "You must choose ENC or DEC\n";
        return 0;
    }

    if(ciphertype == "CES")
    {
        cipher = new Caesar();
        //if key isnt validated exit
        if(cipher->setKey(key) == false)
            return 0;
    }
    else if(ciphertype == "PLF")
    {
        cipher = new Playfair();
        //if key isnt validated exit
        if(cipher->setKey(key) == false)
            return 0;
    }
    else if(ciphertype == "VIG")
    {
        cipher = new Vignere();
        //if key isnt validated exit
        if(cipher->setKey(key) == false)
            return 0;
    }
    else if(ciphertype == "RFC")
    {
        cipher = new Railfence();
        //if key isnt validated exit
        if(cipher->setKey(key) == false)
            return 0;
    }
    else if(ciphertype == "RTS")
    {
        cipher = new RowTransposition();
        //if key isnt validated exit
        if(cipher->setKey(key) == false)
            return 0;
    }

    //Do Encryption or Decrpytion
    if(option == "DEC")
        outputText = cipher->decrypt(inputText);
    else
        outputText = cipher->encrypt(inputText);

    ofstream outputFile;
    outputFile.open(outputFile_Name);
    outputFile << outputText;
    outputFile.close();
	return 0;
}

