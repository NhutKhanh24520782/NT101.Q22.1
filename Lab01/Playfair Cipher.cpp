#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Playfair {
private:
    char matrix[5][5];

    // Hàm chuẩn hóa chuỗi: Viết hoa, thay J thành I, lọc ký tự lạ
    string prepareKey(string key) {
        string res = "";
        transform(key.begin(), key.end(), key.begin(), ::toupper);
        for (char c : key) {
            if (c == 'J') c = 'I';
            if (c >= 'A' && c <= 'Z' && res.find(c) == string::npos) {
                res += c;
            }
        }
        string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
        for (char c : alphabet) {
            if (res.find(c) == string::npos) res += c;
        }
        return res;
    }

public:
    Playfair(string key) {
        string fullKey = prepareKey(key);
        int k = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                matrix[i][j] = fullKey[k++];
            }
        }
    }

    void displayMatrix() {
        cout << "\n--- MA TRẬN PLAYFAIR 5x5 ---" << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << matrix[i][j] << "  ";
            }
            cout << endl;
        }
        cout << "----------------------------\n" << endl;
    }

    void findPos(char c, int& row, int& col) {
        if (c == 'J') c = 'I';
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (matrix[i][j] == c) {
                    row = i; col = j;
                    return;
                }
            }
        }
    }

    string formatPlainText(string text) {
        string res = "";
        for (char c : text) {
            if (isalpha(c)) res += toupper(c == 'J' ? 'I' : c);
        }
        string output = "";
        for (size_t i = 0; i < res.length(); i++) {
            output += res[i];
            if (i + 1 < res.length()) {
                if (res[i] == res[i + 1]) output += 'X';
                else {
                    output += res[i + 1];
                    i++;
                }
            }
        }
        if (output.length() % 2 != 0) output += 'X';
        return output;
    }

    string process(string text, bool encrypt) {
        // Loại bỏ mọi ký tự không phải chữ cái trước khi xử lý
        string cleaned = "";
        for (char c : text) {
            if (isalpha(c)) cleaned += toupper(c == 'J' ? 'I' : c);
        }

        if (cleaned.length() % 2 != 0) cleaned += 'X'; // Đảm bảo luôn chẵn

        string output = "";
        int shift = encrypt ? 1 : 4;

        for (size_t i = 0; i < cleaned.length(); i += 2) {
            int r1, c1, r2, c2;
            findPos(cleaned[i], r1, c1);
            findPos(cleaned[i + 1], r2, c2);

            if (r1 == r2) {
                output += matrix[r1][(c1 + shift) % 5];
                output += matrix[r2][(c2 + shift) % 5];
            }
            else if (c1 == c2) {
                output += matrix[(r1 + shift) % 5][c1];
                output += matrix[(r2 + shift) % 5][c2];
            }
            else {
                output += matrix[r1][c2];
                output += matrix[r2][c1];
            }
        }
        return output;
    }
};

int main() {
    string key, text;
    int choice;

    cout << "Nhap khoa (Key): ";
    getline(cin, key);
    Playfair pf(key);
    pf.displayMatrix();

    cout << "1. Ma hoa\n2. Giai ma\nChon (1/2): ";
    cin >> choice;
    cin.ignore();
    cout << "Nhap van ban: ";
    getline(cin, text);

    if (choice == 1)
        cout << "Ket qua ma hoa: " << pf.process(text, true) << endl;
    else
        cout << "Ket qua giai ma: " << pf.process(text, false) << endl;

    return 0;
}