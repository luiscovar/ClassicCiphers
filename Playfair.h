#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <vector>   /* For vectors */
#include <map>
#include <iostream>
#include <unordered_set>
#include <string>   /* For C++ strings */
#include <stdio.h>  /* For standard I/O */
#include <stdlib.h> /* For miscellenous C functions */
#include "CipherInterface.h"

using namespace std;

/**
 * This class implements the playfair cipher.
 * The class extends the abstract class 
 * CipherInterface.
 */

class Playfair: public CipherInterface
{
	/** The public members **/
	public:
        Playfair() {}
        ~Playfair() {}

		/**
		 * Sets the key to use
		 * @param key - the key to use
		 * @return - True if the key is valid and False otherwise
		 */
		virtual bool setKey(const string& key);

		/**	
		 * Encrypts a plaintext string
		 * @param plaintext - the plaintext string
		 * @return - the encrypted ciphertext string
		 */
		virtual string encrypt(const string& plaintext);

		/**
		 * Decrypts a string of ciphertext
		 * @param ciphertext - the ciphertext
		 * @return - the plaintext
		 */
		virtual string decrypt(const string& ciphertext);
			
		/**
		 * Prints the Playfair matrix
		 * @param fp - the file pointer
		 */
		//void printMatrix(FILE* fp);
		
		/* The protected members */
	protected:
        string _key;
        vector<vector<string>> matrix;

    private:
        map<char,int> lettersUsed;
        vector<vector<string>> doMatrix(); 
        void initMap();
        void displayMatrix();
        string pairUp(string plaintext);
        bool findLocation(int &x, int &y, string letter);
        void moveVertical(string &text, pair<int,int> firstLetter, pair<int,int> secondLetter, bool decrypt);
        void moveHorizontal(string &text, pair<int,int> firstLetter, pair<int,int> secondLetter, bool decrypt);
        void move(string &text, pair<int,int> firstLetter, pair<int,int> secondLetter, bool decrypt);
        bool doAction(bool decrypt, string pairedText, string &outputText);


};

#endif
