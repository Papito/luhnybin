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
bool is_valid(const string data);
int get_digit_count(const string cc_no);
//----------------------------------------------------------------------

int main(int argc, char* argv[]) {
    string data;

    while(cin) {
        getline(cin, data);
        cout << mask(data) << endl;
    };

    return 0;
}
//----------------------------------------------------------------------

string mask(const string data) {
    string result(data);
    string cc_no("");

    for(string::const_iterator itr = data.begin(); itr < data.end(); ++itr) {
        const char ch = *itr;
        
        if (!isdigit(ch) && ch != '-' && ch != ' ') {
            cc_no.clear();
            continue;
        }

        cc_no.push_back(ch);

        const int digit_count = get_digit_count(cc_no);

        if (digit_count >  MAX_LEN) {
            cc_no.erase(cc_no.begin(), cc_no.begin() + 1);
            cc_no.resize(MIN_LEN);
            advance(itr, MIN_LEN - MAX_LEN);
        }

        const bool valid = is_valid(cc_no);

        if (valid) {
            string::const_iterator origin_mask_end = itr + 1;
            string::const_iterator origin_mask_begin = itr;
            advance(origin_mask_begin, cc_no.size() * - 1 + 2);

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

bool is_valid(const string cc_no) {
    const int digit_count =  get_digit_count(cc_no);
    if (digit_count < MIN_LEN || digit_count > MAX_LEN) {
        return false;
    }

    vector<int> digits;

    for (string::const_iterator data_itr = cc_no.begin(); data_itr < cc_no.end(); ++data_itr) {
        char ch = *data_itr;

        if (isdigit(ch)) {
            digits.push_back(atoi(&ch));
        }
    }

    vector<int> luhn_product;
    std::stringstream ss;

    for (vector<int>::reverse_iterator itr = digits.rbegin(); itr < digits.rend(); ++itr) {
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
//----------------------------------------------------------------------

int get_digit_count(const string cc_no) {
    return std::count_if(cc_no.begin(), cc_no.end(), ::isdigit);
}

