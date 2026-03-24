#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// ─── Chuẩn hóa dữ liệu: chuyển về chữ thường ───
string normalize(string text) {
    for (char &c : text)
        c = tolower(c);
    return text;
}

// ─── Sinh chuỗi khóa lặp lại ───
string generateKey(string text, string key) {
    key = normalize(key);
    string newKey = "";
    int keyIndex = 0;

    for (char c : text) {
        if (isalpha(c)) {
            newKey += key[keyIndex % key.length()];
            keyIndex++;
        } else {
            newKey += c;
        }
    }
    return newKey;
}

// ─── Hàm mã hóa ───
// Ci = (pi + ki) mod 26
string encrypt(string plaintext, string key) {
    plaintext = normalize(plaintext);
    string fullKey = generateKey(plaintext, key);

    string cipher = "";

    for (int i = 0; i < plaintext.length(); i++) {
        char p = plaintext[i];

        if (isalpha(p)) {
            int pi = p - 'a';
            int ki = fullKey[i] - 'a';

            int ci = (pi + ki) % 26;

            cipher += char('A' + ci);
        } else {
            cipher += p;
        }
    }

    return cipher;
}

// ─── Hàm giải mã ───
// pi = (Ci − ki + 26) mod 26
string decrypt(string cipher, string key) {
    cipher = normalize(cipher);
    string fullKey = generateKey(cipher, key);

    string plain = "";

    for (int i = 0; i < cipher.length(); i++) {
        char c = cipher[i];

        if (isalpha(c)) {
            int ci = c - 'a';
            int ki = fullKey[i] - 'a';

            int pi = (ci - ki + 26) % 26;

            plain += char('a' + pi);
        } else {
            plain += c;
        }
    }

    return plain;
}
// ─── Main ───
int main() {

    int choice;
    string text, key;

    cout << "===== Vigenere Cipher =====\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Choose: ";
    cin >> choice;
    cin.ignore();
    if (choice == 1) {

        cout << "Enter plaintext:\n";
        getline(cin, text);

        cout << "Enter key: ";
        getline(cin, key);

        string cipher = encrypt(text, key);

        cout << "\nCiphertext:\n" << cipher << endl;
    }
    else if (choice == 2) {

        cout << "Enter ciphertext:\n";
        getline(cin, text);

        cout << "Enter key: ";
        getline(cin, key);
        string plain = decrypt(text, key);
        cout << "\nDecrypted text:\n" << plain << endl;
    }
    return 0;
}