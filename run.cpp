#ifndef test_c
#define test_c

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <sstream> 
#include <functional>

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
    string result(data);
    vector<char> digits;
    string::const_iterator itr;

    for(itr = data.begin(); itr < data.end(); ++itr) {
        const char ch = *itr;
        
        if (!isdigit(ch) && ch != '-' && ch != ' ') {
            digits.clear();
            continue;
        }

        digits.push_back(ch);

        int digit_count = count_if(digits.begin(), digits.end(), ::isdigit);

        if (digit_count >  MAX_LEN) {
            digits.erase(digits.begin(), digits.begin() + 1);
            digits.resize(MIN_LEN);
            advance(itr, MIN_LEN - MAX_LEN);

            digit_count =  count_if(digits.begin(), digits.end(), ::isdigit);
        }

        const bool valid = is_valid(digits);

        if (valid) {
            string::const_iterator origin_mask_end = itr + 1;
            string::const_iterator origin_mask_begin = itr;
            advance(origin_mask_begin, digits.size() * - 1 + 2);

            string::iterator mask_begin = result.begin();
            string::iterator mask_end = result.begin();
            advance(mask_begin, origin_mask_begin - data.begin() - 1);
            advance(mask_end, origin_mask_end - data.begin());
            replace_if(mask_begin, mask_end, ::isdigit, 'X');
        }
    }

    return result;
}
//----------------------------------------------------------------------

bool is_valid(const vector<char> data) {
    const int digit_count =  count_if(data.begin(), data.end(), ::isdigit);
    if (digit_count < MIN_LEN || digit_count > MAX_LEN) {
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
