/*
 * Caesar cipher implementation file
 * 
 * Modeled off of Professor Norris' rot13cipher.cpp
 */

#include "cipher.hpp"
#include "caesarcipher.hpp"

// Default constructor
CaesarCipher::CaesarCipher()
:CaesarCipher(13) // Defaults to shifting by 13
{}

// Constructor with integer
CaesarCipher::CaesarCipher(int s)
:shift(s)
{}

// Destructor
CaesarCipher::~CaesarCipher()
{}

// Overloaded encrypt method
std::string 
CaesarCipher::encrypt( std::string &text ){
    std::string str = text;
    std::string::size_type len = str.length();
    
    // NOTE: To preserve capitalization, only lowercase letters
    // can turn into spaces once encoded.
    int lower_min = (int) 'a';
    int lower_max = (int) 'z' + 1;
    int upper_min = (int) 'A';
    int upper_max = (int) 'Z';
    int space = (int) ' ';
    
    for (int i = 0; i < len; i++){
        int ascii_code = (int) str[i];
        
        // Shift the ASCII encoding
        if (lower_min <= ascii_code && ascii_code <= lower_max){
            ascii_code += shift;
            if (ascii_code > lower_max)
                // Loop the character back around if needed
                ascii_code = lower_min + (ascii_code % lower_max);
        } else if (upper_min <= ascii_code && ascii_code <= upper_max) {
            ascii_code += shift;
            if (ascii_code > upper_max)
                // Loop the character back around if needed
                ascii_code = upper_min + (ascii_code % upper_max);
        }
        
        // Test if it needs to be converted to or from space
        if (ascii_code == lower_max)
            ascii_code = space;
        else if (ascii_code == space)
            ascii_code = lower_max;
            
        // Replace the character
        str[i] = (char) ascii_code;
    }
    
    return str;
}

// Overloaded decrypt method
std::string
CaesarCipher::decrypt( std::string &text ){
    std::string str = text;
    std::string::size_type len = str.length();
    
    // NOTE: To preserve capitalization, only lowercase letters
    // can turn into spaces once encoded.
    int lower_min = (int) 'a';
    int lower_max = (int) 'z' + 1;
    int upper_min = (int) 'A';
    int upper_max = (int) 'Z';
    int space = (int) ' ';
    
    for (int i = 0; i < len; i++){
        int ascii_code = (int) str[i];
        
        // Convert back spaces
        if (ascii_code == space)
            ascii_code = lower_max;
        else if (ascii_code == lower_max)
            ascii_code = space;
        
        
        // Shift the ASCII encoding
        if (lower_min <= ascii_code && ascii_code <= lower_max){
            ascii_code -= shift;
            if (ascii_code < lower_min)
                // Loop the character back around if needed
                ascii_code = lower_max - (lower_min - ascii_code);
        } else if (upper_min <= ascii_code && ascii_code <= upper_max) {
            ascii_code -= shift;
            if (ascii_code < upper_min)
                // Loop the character back around if needed
                ascii_code = upper_max - (upper_min - ascii_code);
        }
            
        // Replace the character
        str[i] = (char) ascii_code;
    }
    
    return str;
}