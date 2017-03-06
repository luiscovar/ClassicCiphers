#include "Railfence.h"


/**
* Sets the key to use
* @param key - the key to use
* @return - True if the key is valid and False otherwise
*/
bool Railfence::setKey(const string& key)
{
	if (!key.empty()){
        try{
            depth = stoi(key);
        }catch(invalid_argument &e)
        {
            cout << "Key must be an integer\n";
            return false;
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
string Railfence::encrypt(const string& plaintext)
{
	string result = "";
	int index(0);
    string sanitizedText = "";
    for(auto c: plaintext)
    {
        if(isalpha(c))
            sanitizedText += toupper(c);
    }
	int col = (sanitizedText.size() / depth) + 1;
	vector<vector<char>> charMatrix(depth, vector<char>(col));

	for (int i = 0; i < col; i++){
		for (int j = 0; j < depth; j++, index++){
			charMatrix[j][i] = sanitizedText[index];
		}
	}

	for (int i = 0; i < depth; i++){
		for (int j = 0; j < col; j++, index++){
			cout <<  charMatrix[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < depth; i++){
		for (int j = 0; j < col; j++){
			if (charMatrix[i][j] != NULL)
				result += charMatrix[i][j];
		}
	}
	return result;
}

/**
* Decrypts a string of ciphertext
* @param cipherText - the ciphertext
* @return - the plaintext
*/
string Railfence::decrypt(const string& cipherText)
{
	string result = "";
	int index(0);
    string sanitizedText = "";

    for(auto c: cipherText)
    {
        if(isalpha(c))
            sanitizedText += toupper(c);
    }

    cout << sanitizedText << endl;

	int col = (sanitizedText.length() / depth) + 1;
    int extra = sanitizedText.length() % 3;
	vector<vector<char>> charMatrix(depth, vector<char>(col));

	for (int i = 0; i < depth; i++){
		for (int j = 0; j < col; j++, index++){
            if(extra > 0 && j+1 == col)
            {
                charMatrix[i][j] = sanitizedText[index];
                extra--;
            }
            else if (extra <= 0 && j+1 == col)
            {
                index--;
                continue;
            }
            else
                charMatrix[i][j] = sanitizedText[index];

		}
	}

	for (int i = 0; i < depth; i++){
		for (int j = 0; j < col; j++, index++){
			cout <<  charMatrix[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < col; i++){
		for (int j = 0; j < depth; j++, index++){
			result += charMatrix[j][i];
		}
	}
	return result;

}
