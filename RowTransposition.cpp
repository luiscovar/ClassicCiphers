#include "RowTransposition.h"


/**
* Sets the key to use
* @param key - the key to use
* @return - True if the key is valid and False otherwise
*/
bool RowTransposition::setKey(const string& key)
{
	if (!key.empty()){
		secretKey = key;
        for(auto c : secretKey)
        {
            if(!isdigit(c))
            {
                cout << "Key Must be Digit\n";
                return false;
            }
        }
		return true;
	}
	return false;
}


/**
* Encrypts a plaintext string
* @param plaintext - the plaintext string
* @return - the encrypted ciphertext string
*/
string RowTransposition::encrypt(const string& plaintext)
{
    string sanitizedText = "";
    for(auto c: plaintext)
    {
        if(isalpha(c))
            sanitizedText += toupper(c);
    }
	int rows = (sanitizedText.size() / secretKey.size()) + 1;
	int col;
	vector<vector<char>> charMatrix(rows, vector<char>(secretKey.size()));
	string result = "";

	int index = 0;
	for (int i = 0; i < rows;  i++){
		for (int j = 0; j < secretKey.size(); j++, index++){
			if (index < sanitizedText.size())
				charMatrix[i][j] = sanitizedText[index];
		}
	}

	index = 0;
	for (int i = 0; i < secretKey.size(); i++){
		col = (secretKey[i] - '0')-1;
		for (int j = 0; j < rows; j++, index++){
			if (charMatrix[j][col] != NULL)
				result += charMatrix[j][col];
		}
	}
	return result;
}

/**
* Decrypts a string of ciphertext
* @param cipherText - the ciphertext
* @return - the plaintext
*/
string RowTransposition::decrypt(const string& cipherText)
{

    string sanitizedText = "";
    for(auto c: cipherText)
    {
        if(isalpha(c))
            sanitizedText += toupper(c);
    }
	int rows = sanitizedText.size() / secretKey.size();
	int col;
	vector<vector<char>> charMatrix(rows, vector<char>(secretKey.size()));
	string result = "";

	int index = 0;
	for (int i = 0; i < secretKey.size(); i++){
		col = (secretKey[i] - '0') - 1;
		for (int j = 0; j < rows; j++, index ++){
			if (index < sanitizedText.size())
				charMatrix[j][col] = sanitizedText[index];
		}
	}

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < secretKey.size(); j++, index++){
			result += charMatrix[i][j];
		}
	}
	return result;
}
