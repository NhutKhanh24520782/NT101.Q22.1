#include <iostream>
#include <string>

using namespace std;

char shiftChar(char c, int key)
{
    if(c >= 'A' && c <= 'Z')
    {
        return (c - 'A' + key + 26) % 26 + 'A';
    }
    else if(c >= 'a' && c <= 'z')
    {
        return (c - 'a' + key + 26) % 26 + 'a';
    }

    return c;
}

string caesarCipher(string text, int key)
{
    string result = text;

    for(int i = 0; i < text.length(); i++)
    {
        result[i] = shiftChar(text[i], key);
    }

    return result;
}

bool isValidPlaintext(string text)
{
    if(text.find(" the ") != string::npos) return true;
    if(text.find(" and ") != string::npos) return true;
    if(text.find(" that ") != string::npos) return true;
    if(text.find(" for ") != string::npos) return true;
    if(text.find(" was ") != string::npos) return true;

    return false;
}

void bruteForce(string cipherText)
{
    int correctKey = -1;
    string correctPlaintext;

    for(int key = 0; key < 26; key++)
    {
        string decrypted = caesarCipher(cipherText, -key);

        cout << "Key " << key << " : " << decrypted << endl;

        if(isValidPlaintext(decrypted) && correctKey == -1)
        {
            correctKey = key;
            correctPlaintext = decrypted;
        }
    }

    if(correctKey != -1)
    {
        cout << "\nCorrect Key: " << correctKey << endl;
        cout << "Plaintext: " << correctPlaintext << endl;
    }
    else
    {
        cout << "\nNo valid plaintext found." << endl;
    }
}

int main()
{
    int choice;
    string text;
    int key;

    cout << "===== Caesar Cipher =====" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "3. Brute Force" << endl;
    cout << "Choose: ";
    cin >> choice;

    cin.ignore();

    switch(choice)
    {
        case 1:
        {
            cout << "Enter plaintext: ";
            getline(cin, text);

            cout << "Enter key: ";
            cin >> key;

            cout << "Ciphertext: " << caesarCipher(text, key) << endl;
            break;
        }

        case 2:
        {
            cout << "Enter ciphertext: ";
            getline(cin, text);

            cout << "Enter key: ";
            cin >> key;

            cout << "Plaintext: " << caesarCipher(text, -key) << endl;
            break;
        }

        case 3:
        {
            cout << "Enter ciphertext: ";
            getline(cin, text);

            bruteForce(text);
            break;
        }

        default:
        {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}