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
bool is_valid(vector<char> data);

int main(int argc, char* argv[]) {
    string data;

    while(cin) {
        getline(cin, data);
        const string masked = mask(data);
        cout << masked << endl;
        cerr << "\n----------------------------------------------\n";
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
    if (data.size()) {
        cerr << "IN: " << data << "\n----------------------------------------------\n";
    }

    string result(data);

    vector<char> digits;

    string::iterator itr = result.begin();

    for(itr; itr < result.end(); ++itr) {
        const char ch = *itr;
        
        //cerr << "Processing: " << ch;
        if (!isdigit(ch) && ch != '-' && ch != ' ') {
            //cerr <<  ". Skipping" << endl;
            digits.clear();
            continue;
        }

        cerr << ". Adding: " << ch << endl;
        digits.push_back(ch);

        const int digit_count =  count_if(digits.begin(), digits.end(), ::isdigit);
        if (digit_count >  MAX_LEN) {
            digits.erase(digits.begin(), digits.begin() + 1);
            digits.resize(MIN_LEN);
            advance(itr, MIN_LEN - MAX_LEN);
        }
        
        dump(digits);
        cerr <<  " - " << digit_count <<  endl;

        const bool valid = is_valid(digits);

        if (valid) {
            cerr << "masking: "; dump(digits); cerr << endl;
            string::iterator mask_end = itr + 1;
            string::iterator mask_begin = itr;
            advance(mask_begin, digits.size() * -1 + 1);
            replace_if(mask_begin, mask_end, ::isdigit, 'X');
        }
    }

    return result;
}
//----------------------------------------------------------------------

bool is_valid(const vector<char> data) {
    const int digit_count =  count_if(data.begin(), data.end(), ::isdigit);
    if (digit_count < MIN_LEN || digit_count > MAX_LEN) {
        //cerr << "at: "; dump(data); cerr << endl;
        return false;
    }

    vector<char>::const_iterator data_itr;

    vector<int> digits;
    for (data_itr = data.begin(); data_itr < data.end(); ++data_itr) {
        char ch = *data_itr;

        if (isdigit(ch)) {
            digits.push_back(atoi(&ch));
        }
    }

    vector<int>::reverse_iterator itr;

    vector<int> luhn_product;

    std::stringstream ss;
    for (itr = digits.rbegin(); itr < digits.rend(); ++itr) {
        int digit = *itr;

        const int dist = distance(digits.rbegin(), itr);

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
