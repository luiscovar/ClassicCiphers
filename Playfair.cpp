#include "Playfair.h"

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Playfair::setKey(const string& key)
{ 
    initMap();
    //create and check valid key
    for(auto &c: key)
    {
        char letter = c;
        letter = toupper(letter);
        //Ignore J and use I
        if(letter == 'J')
            letter = 'I';

        //if its not alphabet then not valid, stop
        if(!isalpha(letter))
            return false;
        else
        {
            if(lettersUsed.count(letter) > 0)
            {
                _key += letter;
                lettersUsed.erase(letter);
            }
        }
    }

    matrix = doMatrix();

    displayMatrix();
	return true;  
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Playfair::encrypt(const string& plaintext)
{ 
    string ciphertext = "";
    string pairedText = pairUp(plaintext);
    if(doAction(false, pairedText, ciphertext) == false)
    {
        cout << "Issue encountered while encrypting " << endl;
    }
	return ciphertext; 
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Playfair::decrypt(const string& cipherText) 
{ 
    string plainText = "";
    cout << cipherText << endl;
    if(doAction(true, cipherText, plainText) == false)
    {
        cout << "Issue encountered while decrypt " << endl;
    }
	return plainText; 
}

vector<vector<string>> Playfair::doMatrix()
{
    vector<vector<string>> matrix(5, vector<string>(5,""));
    int row = 0;
    int column = 0;
    //insert key into matrix
    for(auto c: _key)
    {
        if(column > 4) 
        {
            column = 0;
            row++;
        }
        matrix[row][column] = c;
        column++;
    }

    //insert the rest of the alphabet
    for(auto c: lettersUsed)
    {
        if(column > 4) 
        {
            column = 0;
            row++;
        }
        matrix[row][column] = c.first;
        column++;
    }

    return matrix;
}

void Playfair::initMap(){
    for(int i = 65; i <= 90; i++)
    {
        if (i == 74)
            continue;
        lettersUsed[char(i)] = 0;
    }
}

void Playfair::displayMatrix(){
    for(auto &row: matrix){
        cout << endl;
        for (auto &col: row)
            cout << col; 
    }
    cout << endl;
}

string Playfair::pairUp(string plaintext){
    string pairedText = "";
    string alphaonly = "";

    //ignore all not alpha characters
    for(auto c: plaintext)
    {
        if(isalpha(c))
        {
            if(toupper(c) == 'I' || toupper(c) == 'J')
                c = 'I';
            alphaonly += toupper(c);
        }
    }

    int textsize = alphaonly.length();
    for(int i = 0; i < textsize; i=i+2)
    {
        pairedText += alphaonly[i];
        if(i + 1 < textsize)
        {
            if(alphaonly[i] == alphaonly[i+1])
            {
                pairedText += "X";
                i--;
            }
            else
                pairedText += alphaonly[i+1];
        }
    }

    if(pairedText.length() % 2 != 0)
        pairedText += "X";
    return pairedText;
}
    
bool Playfair::findLocation(int &x, int &y, string letter){
    int rows = matrix.size();
    int cols = matrix[0].size();

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
           if( matrix[i][j] == letter)
           {
               x = i;
               y = j;
               return true;
           }

        }
    }
    return false;
}


void Playfair::moveVertical(string &text, pair<int,int> firstLetter, pair<int,int> secondLetter, bool decrypt)
{
    int direction = 1;
    if(decrypt == true)
        direction = -1;
    int firstLetterRow = firstLetter.first;
    int secondLetterRow = secondLetter.first;

    firstLetterRow = (firstLetterRow + direction) % 5; 
    secondLetterRow = (secondLetterRow + direction) % 5; 

    if(firstLetterRow < 0)
        firstLetterRow = 4;
    if(secondLetterRow < 0)
        secondLetterRow = 4; 

    //cout << firstLetterRow << " " << secondLetterRow << endl;
    text += matrix[firstLetterRow][firstLetter.second];
    text += matrix[secondLetterRow][secondLetter.second];


}

void Playfair::moveHorizontal(string &text, pair<int,int> firstLetter, pair<int,int> secondLetter, bool decrypt)
{
    int direction = 1;
    if(decrypt == true)
        direction = -1;
    int firstLetterCol = firstLetter.second;
    int secondLetterCol = secondLetter.second;

    firstLetterCol = (firstLetterCol + direction) % 5; 
    secondLetterCol = (secondLetterCol + direction) % 5; 

    cout << firstLetterCol << " " << secondLetterCol << endl;

    if(firstLetterCol < 0)
        firstLetterCol = 4;
    if(secondLetterCol < 0)
        secondLetterCol = 4;

    cout << firstLetterCol << " " << secondLetterCol << endl;

    text += matrix[firstLetter.first][firstLetterCol];
    text += matrix[secondLetter.first][secondLetterCol];

}

void Playfair::move(string &text, pair<int,int> firstLetter, pair<int,int> secondLetter, bool decrypt)
{
    text += matrix[firstLetter.first][secondLetter.second];
    text += matrix[secondLetter.first][firstLetter.second];
} 

bool Playfair::doAction(bool decrypt, string pairedText, string &outputText)
{
    pair<int,int> firstLetterPos;
    pair<int,int> secondLetterPos;
    pair<bool,bool> foundpos;
    string first, second;

    int size = pairedText.size();
    for(int i=0; i < size; i=i+2)
    {
        first = pairedText[i];
        second = pairedText[i+1];

        foundpos.first = findLocation(firstLetterPos.first, firstLetterPos.second, first);
        foundpos.second = findLocation(secondLetterPos.first, secondLetterPos.second, second);

        if(foundpos.first == false || foundpos.second == false)
            return false;
        if(firstLetterPos.first == secondLetterPos.first)
            moveHorizontal(outputText, firstLetterPos, secondLetterPos, decrypt);
        else if(firstLetterPos.second == secondLetterPos.second)
            moveVertical(outputText, firstLetterPos, secondLetterPos, decrypt);
        else
            move(outputText, firstLetterPos, secondLetterPos, decrypt);
    }
    return true;
}
