#ifndef test_c
#define test_c

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <sstream> 

#endif

using namespace std;

const int MIN_LEN = 14;
const int MAX_LEN = 16;

string mask(const string data);
bool is_valid(vector<int> data);

int main(int argc, char* argv[]) {
    string data;

    while(cin) {
        getline(cin, data);
        const string masked = mask(data);
        cerr << masked;
        cout << masked << endl;
        cerr << "\n----------------------------------------------\n";
    };

    return 0;
}
//----------------------------------------------------------------------

void print (int ch) {
    cerr << ch;
}
//----------------------------------------------------------------------

void dump(vector<int> data) {
    for_each(data.begin(), data.end(), print);
}
//----------------------------------------------------------------------

string mask(const string data) {
    if (data.size()) {
        cerr << "IN: " << data << "\n----------------------------------------------\n";
    }

    string result;

    vector<int> digits;

    string::const_iterator itr = data.begin();

    for(itr; itr < data.end(); ++itr) {
        const char ch = *itr;
        
        //cerr << "Processing: " << ch;
        if (!isdigit(ch) && ch != '-' && ch != ' ') {
            //cerr <<  ". Skipping" << endl;
            digits.clear();
            result.append(1, ch);
            continue;
        }

        if (ch == '-' || ch == ' ') {
            //cerr << ". Skip but continue on " << ch << endl;
            result.append(1, ch);
            continue;
        }

        //cerr << ". Adding: " << ch << endl;
        int digit = atoi(&ch);
        digits.push_back(digit);
        
        //dump(digits);
        //cerr <<  " - " << digits.size() <<  endl;

        const bool valid = is_valid(digits);

        if (valid) {
            cerr << "masking: "; dump(digits); cerr << endl;
            result = result.append(digits.size(), 'X');
        }
    }

    return result;
}
//----------------------------------------------------------------------

bool is_valid(const vector<int> data) {
    if (data.size() < MIN_LEN || data.size() > MAX_LEN) {
        return false;
    }

    vector<int> luhn_product;

    vector<int>::const_reverse_iterator itr = data.rbegin();

    std::stringstream ss;
    for (itr; itr < data.rend(); ++itr) {
        int digit = *itr;

        const int dist = distance(data.rbegin(), itr);

        if (dist % 2 != 0) {
            digit = digit * 2;
        }

        ss.str("");
        ss << digit;
        const string as_string = ss.str();

        for (int n = 0; n < as_string.size(); ++n) {
            char ch = as_string[n];
            int num = atoi(&ch);
            luhn_product.push_back(num);
        }

    }
    
    const int luhn_sum = accumulate(luhn_product.begin(), luhn_product.end(), 0);

    return luhn_sum % 10 == 0;
}
