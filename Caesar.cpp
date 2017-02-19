#include "Caesar.h"

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Caesar::setKey(const string& key)
{ 
    int intkey;
    try {
        intkey = stoi(key);
    }catch(invalid_argument &e)
    {
        cout << "Key must be Integer\n";
        return false;
    }
    
    _key = intkey % 26;
    return true;
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Caesar::encrypt(const string& plaintext)
{ 
	return doRotation(plaintext, true); 
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Caesar::decrypt(const string& cipherText) 
{ 
	return doRotation(cipherText, false); 
	
}

string Caesar::doRotation(string word, bool option)
{
    //convert all to uppercase
    string ouput_str = "";
    for(auto &c: word)
        c = toupper(c);
    //look the opposite way for decryption
    if(option == false)
        _key = _key * -1;
    for(auto &c : word)
    {
        if(isalpha(c))
        {
            int alphaToInt = (int(c) - 65);
            alphaToInt = alphaToInt + _key;
            alphaToInt = alphaToInt % 26;
            alphaToInt = alphaToInt + 65; //back to ASCII
            ouput_str += char(alphaToInt);
        }
        else
            ouput_str += c;
    }

    return ouput_str;
}
