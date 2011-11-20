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
        cout << mask(data) << endl;
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
    cerr << "IN: " << data << "\n----------------------------------------------\n";

    vector<int> digits;

    for(int n=0; n < data.length(); ++n) {
        char ch = data[n]; 
        
        //cerr << "Processing: " << ch;
        if (!isdigit(ch) && ch != '-' && ch != ' ') {
            //cerr <<  ". Skipping" << endl;
            digits.clear();
            continue;
        }

        if (ch == '-' || ch == ' ') {
            //cerr << ". Skip but continue on " << ch << endl;
            continue;
        }

        //cerr << ". Adding: " << ch << endl;
        int digit = atoi(&ch);
        digits.push_back(digit);
        
        //dump(digits);
        //cerr <<  " - " << digits.size() <<  endl;

        if (digits.size() >= MIN_LEN && digits.size() <= MAX_LEN) {
            const bool valid = is_valid(digits);

            cerr << endl;
            if (valid) {
                cerr << "ACCEPTED";
            } 
            else {
                cerr << "REJECTED";
            }
            cerr << endl;
        }
    }

    return data;
}
//----------------------------------------------------------------------

bool is_valid(vector<int> data) {
    cerr << "processing: ";
    dump(data);
    cerr << endl;

    vector<int> luhn_product;

    vector<int>::reverse_iterator itr = data.rbegin();

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
