#ifndef test_c
#define test_c

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctype.h>
#endif

using namespace std;

const int MIN_LEN = 14;
const int MAX_LEN = 16;

string mask(const string data);
bool is_valid(vector<char> data);

int main(int argc, char* argv[]) {
    string data;

    while(cin) {
        getline(cin, data);
        cout << mask(data) << endl;
    };

    return 0;
}
//----------------------------------------------------------------------

void print (char ch) {
    cerr << ch;
}
//----------------------------------------------------------------------

void dump(vector<char> data) {
    for_each(data.begin(), data.end(), print);
}
//----------------------------------------------------------------------

string mask(const string data) {
    cerr << "IN: " << data << "\n----------------------------------------------\n";

    vector<char> digits;

    for(int n=0; n < data.length(); ++n) {
        char ch = data[n]; 
        
        cerr << "Processing: " << ch;
        if (!isdigit(ch) && ch != '-' && ch != ' ') {
            cerr <<  ". Skipping" << endl;
            digits.clear();
            continue;
        }

        if (ch == '-' || ch == ' ') {
            cerr << ". Skip but continue on " << ch << endl;
            continue;
        }

        cerr << ". Adding: " << ch << endl;
        digits.push_back(ch);
        
        dump(digits);
        cerr <<  " - " << digits.size() <<  endl;

        const bool valid = is_valid(digits);

        dump(digits);
        if (valid) {
            cerr << " accepted";
        } 
        else {
            cerr << " rejected";
        }
        cerr << endl;
    }

    return data;
}
//----------------------------------------------------------------------

bool is_valid(const vector<char> data) {
    if (data.size() < MIN_LEN || data.size() > MAX_LEN) {
        return false;
    }

    return true;
}
