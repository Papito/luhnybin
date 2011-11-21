/***********************************************************************
 * Copyright (C) 2012  Andrei Taranchenko

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/
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

// forward declarations
string process(const string & data);
bool is_valid(const string & data, string::const_iterator itr1, string::const_iterator itr2);
int get_digit_count(const string & cc_no);

int main(int argc, char* argv[]) {
    // read standard input, line by line
    string data;
    while(cin) {
        getline(cin, data);
        cout << process(data) << endl;
    };
    return 0;
}
//----------------------------------------------------------------------

bool is_invalid_char(const char ch) {
    return !isdigit(ch) && ch != '-' && ch != ' ';
}
//----------------------------------------------------------------------

void mask(const string & data, string & result, string::const_iterator itr1, string::const_iterator itr2) {
    int digit_count = count_if(itr1, itr2, ::isdigit);
    int invalid_char_count = count_if(itr1, itr2, is_invalid_char);

    while (digit_count <= MAX_LEN && invalid_char_count == 0 && itr2 <= data.end()) {
        const bool isvalid = is_valid(data, itr1, itr2);

        if (isvalid) {
            string::iterator mask_begin = result.begin() + distance(data.begin(), itr1);
            string::iterator mask_end   = result.begin() + distance(data.begin(), itr2);
            replace_if(mask_begin, mask_end, ::isdigit, 'X');
        }

        ++itr2;
        digit_count = count_if(itr1, itr2, ::isdigit);
        invalid_char_count = count_if(itr1, itr2, is_invalid_char);
    }
}
//----------------------------------------------------------------------

string process(const string & data) {
    string result(data);
    string::const_iterator itr1 = data.begin();
    string::const_iterator itr2 = itr1 + MIN_LEN;

    while (itr2 <= data.end()) {
        mask(data, result, itr1, itr2);
        ++itr1;
        ++itr2;
    }

    return result;
}
//----------------------------------------------------------------------

bool is_valid(const string & data, string::const_iterator itr1, string::const_iterator itr2) {
    const int digit_count = count_if(itr1, itr2, ::isdigit);
    if (digit_count < MIN_LEN || digit_count > MAX_LEN) {
        return false;
    }

    vector<int> digits;
    
    // get digits-only vector from raw character input
    for (itr1; itr1 < itr2; ++itr1) {
        char ch = *itr1;
        if (isdigit(ch)) {
            digits.push_back(atoi(&ch));
        }
    }

    vector<int> luhn_product;

    // for translating digits to strings
    std::stringstream ss;

    // go in reverse
    for (vector<int>::reverse_iterator itr = digits.rbegin(); itr < digits.rend(); ++itr) {
        int digit = *itr;
        const int dist = distance(digits.rbegin(), itr);

        if (dist % 2 != 0) { // one of every other digits
            digit = digit * 2;
        }

        // convert the digit to string, so we can split digits
        ss.str("");
        ss << digit;
        const string as_string = ss.str();

        // add the separate digits, in case there is more than one, to luhn container
        for (int n = 0; n < as_string.size(); ++n) {
            char ch = as_string[n];
            int num = atoi(&ch);
            luhn_product.push_back(num);
        }
    }
    
    // w00t
    const int luhn_sum = accumulate(luhn_product.begin(), luhn_product.end(), 0);
    return luhn_sum % 10 == 0;
}
