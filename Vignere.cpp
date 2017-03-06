#include "Vignere.h"


/**
* Sets the key to use
* @param key - the key to use
* @return - True if the key is valid and False otherwise
*/
bool Vignere::setKey(const string& key)
{
	if (!key.empty()){
		secretKey = key;
        for(auto &c: secretKey)
        {
            if(!isalpha(c))
                return false;
            c = toupper(c);
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
string Vignere::encrypt(const string& plaintext)
{

	string result = "";
    string santiziedText = "";

    for(auto c: plaintext)
    {
        if(isalpha(c))
            santiziedText += toupper(c);
    }

    for(int i = 0, j=0; i < santiziedText.length(); i++)
    {
        char letter = santiziedText[i];
        result += (letter + secretKey[j]) % 26 + 'A';
        j = (j+1) % secretKey.length();
    }

    return result;

}

/**
* Decrypts a string of ciphertext
* @param cipherText - the ciphertext
* @return - the plaintext
*/
string Vignere::decrypt(const string& cipherText)
{
	string result = "";
    string santiziedText = "";

    for(auto c: cipherText)
    {
        if(isalpha(c))
            santiziedText += toupper(c);
    }

    for(int i = 0, j=0; i < santiziedText.length(); i++)
    {
        char letter = santiziedText[i];
        result += (letter - secretKey[j] + 26) % 26 + 'A';
        j = (j+1) % secretKey.length();
    }

    return result;
}
