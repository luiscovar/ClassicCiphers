#include <string>
#include "CipherInterface.h"
//#include "Playfair.h"
#include "Caesar.h"
#include <sstream>
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

        if(option == "DEC")
            outputText = cipher->decrypt(inputText);
        else
            outputText = cipher->encrypt(inputText);
    }
    else if(ciphertype == "PLF")
    {
        cout << "Playfair Chosen";
    }


    ofstream outputFile;
    outputFile.open(outputFile_Name);
    outputFile << outputText;
    outputFile.close();
	return 0;
}

