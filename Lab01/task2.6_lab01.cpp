#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>

using namespace std;

double englishFreq[26] = {
8.2,1.5,2.8,4.3,12.7,2.2,2.0,6.1,7.0,0.15,
0.77,4.0,2.4,6.7,7.5,1.9,0.095,6.0,
6.3,9.1,2.8,1.0,2.4,0.15,2.0,0.074
};

string normalize(string text) {
    string result="";
    for(char c:text)
        if(isalpha(c))
            result+=tolower(c);
    return result;
}

double indexOfCoincidence(string text){

    int freq[26]={0};

    for(char c:text)
        freq[c-'a']++;

    int N=text.size();

    double num=0;

    for(int i=0;i<26;i++)
        num+=freq[i]*(freq[i]-1);

    return num/(N*(N-1.0));
}

int findKeyLength(string text){

    int bestLen=1;
    double bestDiff=1e9;
    double target=0.065;

    for(int len=1;len<=12;len++){

        double avgIC=0;

        for(int i=0;i<len;i++){

            string group="";

            for(int j=i;j<text.size();j+=len)
                group+=text[j];

            avgIC+=indexOfCoincidence(group);
        }

        avgIC/=len;

        double diff=abs(avgIC-target);

        if(diff<bestDiff){
            bestDiff=diff;
            bestLen=len;
        }
    }

    return bestLen;
}

double chiSquare(string text){

    int freq[26]={0};

    for(char c:text)
        freq[c-'a']++;

    int n=text.size();

    double chi=0;

    for(int i=0;i<26;i++){

        double expected=n*englishFreq[i]/100;

        chi+=pow(freq[i]-expected,2)/expected;
    }

    return chi;
}

char findKeyChar(string group){

    double bestScore=1e18;
    int bestShift=0;

    for(int s=0;s<26;s++){

        string decoded="";

        for(char c:group)
            decoded+=char('a'+(c-'a'-s+26)%26);

        double sc=chiSquare(decoded);

        if(sc<bestScore){
            bestScore=sc;
            bestShift=s;
        }
    }

    return 'a'+bestShift;
}

string findKey(string text,int keyLen){

    string key="";

    for(int i=0;i<keyLen;i++){

        string group="";

        for(int j=i;j<text.size();j+=keyLen)
            group+=text[j];

        key+=findKeyChar(group);
    }

    return key;
}

string decrypt(string text,string key){

    string plain="";
    int m=key.size();

    for(int i=0;i<text.size();i++){

        int ci=text[i]-'a';
        int ki=key[i%m]-'a';

        plain+=char('a'+(ci-ki+26)%26);
    }

    return plain;
}

int main(){

    string input,line;

    cout<<"Enter ciphertext (end with empty line):\n";

    while(true){
        getline(cin,line);
        if(line.empty()) break;
        input+=line;
    }

    string cipher=normalize(input);

    cout<<"\nCipher length: "<<cipher.size()<<endl;

    int keyLen=findKeyLength(cipher);

    cout<<"Estimated key length: "<<keyLen<<endl;

    string key=findKey(cipher,keyLen);

    cout<<"Recovered key: "<<key<<endl;

    string plain=decrypt(cipher,key);

    cout<<"\nDecrypted plaintext:\n";
    cout<<plain<<endl;

    return 0;
}