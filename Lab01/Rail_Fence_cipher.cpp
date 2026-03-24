#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

/*---------------------------------------
  Ham chuan hoa du lieu
  Chuyen tat ca ky tu ve chu thuong
---------------------------------------*/
string normalize(string text) {
    string result = "";
    for(char &c : text) {
        if(!isspace(c)) { 
            result += toupper(c);
        }
    }
    return result;
}
/*---------------------------------------
  Ham ma hoa Rail Fence
---------------------------------------*/
string encryptRailFence(string text, int key) {

    vector<string> rail(key);

    int row = 0;
    bool down = true;

    for(char c : text) {

        rail[row] += c;

        if(row == 0)
            down = true;
        else if(row == key - 1)
            down = false;

        row += down ? 1 : -1;
    }

    string result;

    for(int i = 0; i < key; i++)
        result += rail[i];

    return result;
}

/*---------------------------------------
  Ham giai ma Rail Fence
---------------------------------------*/
string decryptRailFence(string cipher, int key) {

    int n = cipher.length();
    vector<vector<char>> rail(key, vector<char>(n, '\n'));

    bool down;
    int row = 0, col = 0;

    // Danh dau zigzag
    for(int i = 0; i < n; i++) {

        if(row == 0) down = true;
        if(row == key - 1) down = false;

        rail[row][col++] = '*';
        row += down ? 1 : -1;
    }

    // Dien ciphertext vao bang
    int index = 0;

    for(int i = 0; i < key; i++)
        for(int j = 0; j < n; j++)
            if(rail[i][j] == '*' && index < n)
                rail[i][j] = cipher[index++];

    // Doc zigzag de lay plaintext
    string result;

    row = 0;
    col = 0;

    for(int i = 0; i < n; i++) {

        if(row == 0) down = true;
        if(row == key - 1) down = false;

        result += rail[row][col++];
        row += down ? 1 : -1;
    }

    return result;
}

/*---------------------------------------
  Chuong trinh chinh
---------------------------------------*/
int main() {

    int choice, key;
    string text;

    cout << "===== RAIL FENCE CIPHER =====\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter choice: ";
    cin >> choice;

    cin.ignore();

    if(choice == 1) {

        cout << "Enter plaintext: ";
        getline(cin, text);

        text = normalize(text);

        cout << "Enter key (rails): ";
        cin >> key;

        string cipher = encryptRailFence(text, key);

        cout << "\nCiphertext:\n" << cipher << endl;
    }

    else if(choice == 2) {

        cout << "Enter ciphertext: ";
        getline(cin, text);

        cout << "Enter key (rails): ";
        cin >> key;

        string plain = decryptRailFence(text, key);

        cout << "\nPlaintext:\n" << plain << endl;
    }

    else {

        cout << "Invalid choice!" << endl;
    }

    return 0;
}