/*
 * Date cipher implementation file
 * 
 * Modeled off of Professor Norris' rot13cipher.cpp
 */

#include "cipher.hpp"
#include "datecipher.hpp"

// Default constructor
DateCipher::DateCipher()
:DateCipher("12121999") // Release date of Planescape
{}

// Constructor with datestring
// NOTE: Does not format the inbound string!
DateCipher::DateCipher(std::string d)
:date(d)
{}

// Destructor
DateCipher::~DateCipher()
{}

// Overloaded encrypt method
std::string 
DateCipher::encrypt( std::string &text ){
    std::string encode = text;
    std::string::size_type text_len = text.length();
    std::string::size_type date_len = date.length();
    
    for (int i = 0; i < text_len; i++){
        int ascii_code = (int) text[i];
        int mod = date[i % date_len] - '0';
        ascii_code = shift(ascii_code, mod);
        encode[i] = (char) ascii_code;
    }
    
    return encode;
}

// Overloaded decrypt method
std::string
DateCipher::decrypt( std::string &text ){
    std::string decode = text;
    std::string::size_type text_len = text.length();
    std::string::size_type date_len = date.length();
    
    for (int i = 0; i < text_len; i++){
        int ascii_code = (int) text[i];
        int mod = -(date[i % date_len] - '0');
        ascii_code = shift(ascii_code, mod);
        decode[i] = (char) ascii_code;
    }
    
    return decode;
}

int DateCipher::shift( int code, int s ){
    int result = code;
    int lower_min = (int) 'a';
    int lower_max = (int) 'z';
    int upper_min = (int) 'A';
    int upper_max = (int) 'Z';

    // Shift the ASCII encoding
    if (lower_min <= code && code <= lower_max){
        result += s;
        // Loop the character back around if needed
        if (result > lower_max)
            result = lower_min + (result % lower_max);
        else if (result < lower_min)
            result = lower_max - (lower_min - result);
    } else if (upper_min <= result && result <= upper_max) {
        result += s;
        // Loop the character back around if needed
        if (result > upper_max)    
            result = upper_min + (result % upper_max);
        else if (result < upper_min)
            result = upper_max - (upper_min - result);
    }
    
    return result;
}