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
string mask(const string data);
bool is_valid(const string data);
int get_digit_count(const string cc_no);
//----------------------------------------------------------------------

int main(int argc, char* argv[]) {
    // read standard input, line by line
    string data;
    while(cin) {
        getline(cin, data);
        cout << mask(data) << endl;
    };
    return 0;
}
//----------------------------------------------------------------------

string mask(const string data) {
    // copy input into mutable result string
    string result(data);

    // credit card number
    string cc_no("");

    // build cc no, character by character
    for(string::const_iterator itr = data.begin(); itr < data.end(); ++itr) {
        const char ch = *itr;
        
        // skip non-digits and non-delimiters
        if (!isdigit(ch) && ch != '-' && ch != ' ') {
            // if we hit a foreign character, void whatever cc # we have
            cc_no.clear();
            continue;
        }

        // add this character to cc #
        cc_no.push_back(ch);

        const int digit_count = get_digit_count(cc_no);

        // if we go over allowed max digits
        if (digit_count >  MAX_LEN) {
            // erase the first one
            cc_no.erase(cc_no.begin(), cc_no.begin() + 1);
            // erase the last x digits to get shortest possible valid cc #
            cc_no.resize(MIN_LEN);

            /*
                Rewind main string iterator by same amount.
                In this fashion we move the pointer forward by one,
                and check again for next possible valid cc.
            */
            advance(itr, (MAX_LEN - MIN_LEN) * -1); 
        }

        const bool valid = is_valid(cc_no);

        if (valid) {
            // get constant iterator range to be masked, from immutable input
            string::const_iterator origin_mask_end = itr + 1;
            string::const_iterator origin_mask_begin = itr;
            advance(origin_mask_begin, cc_no.size() * - 1 + 2);

            // translate to same range on the mutable copy
            string::iterator mask_begin = result.begin();
            string::iterator mask_end = result.begin();
            advance(mask_begin, origin_mask_begin - data.begin() - 1);
            advance(mask_end, origin_mask_end - data.begin());

            // mask digits
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
    
    // get digits-only vector from raw character input
    for (string::const_iterator data_itr = cc_no.begin(); data_itr < cc_no.end(); ++data_itr) {
        char ch = *data_itr;

        if (isdigit(ch)) {
            digits.push_back(atoi(&ch));
        }
    }

    // bucket of integers to be summed up
    vector<int> luhn_product;

    // for translating digits to strings
    std::stringstream ss;

    // go in reverse
    for (vector<int>::reverse_iterator itr = digits.rbegin(); itr < digits.rend(); ++itr) {
        int digit = *itr;

        // we double every other digit starting from back of this container
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
            // to integer
            int num = atoi(&ch);
            // add to luhn container
            luhn_product.push_back(num);
        }
    }
    
    // w00t
    const int luhn_sum = accumulate(luhn_product.begin(), luhn_product.end(), 0);

    return luhn_sum % 10 == 0;
}
//----------------------------------------------------------------------

int get_digit_count(const string cc_no) {
    return std::count_if(cc_no.begin(), cc_no.end(), ::isdigit);
}

