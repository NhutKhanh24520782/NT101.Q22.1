#include <iostream>
#include <algorithm>
#include <map>
#include <ctime>
#include <string>

using namespace std;

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


map<string, double> bigram = {
{"TH",-1.0},{"HE",-1.1},{"IN",-1.3},{"ER",-1.3},{"AN",-1.4},
{"RE",-1.5},{"ND",-1.6},{"AT",-1.6},{"ON",-1.7},{"NT",-1.7},
{"HA",-1.8},{"ES",-1.8},{"ST",-1.9},{"EN",-1.9},{"ED",-2.0},

};


// Hàm loại bỏ những kí tự không phải là chữ cái và chuển tất cả thành chữ hoa
string cleanText(string text)
{
    string result;

    for (char c : text)
    {
        if (isalpha(c))
            result += toupper(c);
    }
    return result;
}


// /hàm tạo key ngẫu nhiên
string randomKey()
{
    string key = alphabet;
    random_shuffle(key.begin(), key.end());
    return key;
}

// Hàm giải mã bằng cách sử dụng key 
string decrypt(string cipher, string key)
{
    string plain = cipher;

    for (int i = 0; i < cipher.size(); i++)
    {
        int pos = cipher[i] - 'A';
        plain[i] = key[pos];
    }

    return plain;
}

// tính điểm cho văn bản giải mã dựa trên tần suất của các bigram
double scoreText(string text)
{
    double point = 0;

    for (int i = 0; i < text.size() - 1; i++){
        string bg = text.substr(i, 2);

        if (bigram.count(bg))
            point += bigram[bg];
        else
            point -= 3;
    }
    return point;
}

// hoán đổi 2 vị trí trong key
string swapKey(string key)
{
    int a = rand() % 26;
    int b = rand() % 26;

    swap(key[a], key[b]);

    return key;
}

// Hàm thực hiện thuật toán Hill Climbing để tìm key tốt nhất
string hillClimb(string cipher, double& bestScore)
{
    string key = randomKey();
    string bestKey = key;

    string plain = decrypt(cipher, key);
    bestScore = scoreText(plain);

    for (int i = 0; i < 5000; i++)
    {
        string newKey = swapKey(key);

        string newPlain = decrypt(cipher, newKey);
        double newScore = scoreText(newPlain);

        if (newScore > bestScore)        {
            bestScore = newScore;
            key = newKey;
            bestKey = newKey;
        }
    }

    return bestKey;
}

int main()
{
    srand(time(0));

    string cipher;

    cout << "Nhap ciphertext:\n";
    getline(cin, cipher);

    cipher = cleanText(cipher);

    string bestKey;
    string bestPlain;

    double globalBestScore = -1e9;

    int restarts = 100;

    for (int i = 0; i < restarts; i++)
    {
        double score;

        string key = hillClimb(cipher, score);

        if (score > globalBestScore)
        {
            globalBestScore = score;
            bestKey = key;
        }
    }

    bestPlain = decrypt(cipher, bestKey);

    cout << "KET QUA TOT NHAT" << endl;

    cout << "Key: " << bestKey << endl;

    cout << "\nPlaintext:\n" << bestPlain << endl;

    return 0;
}

