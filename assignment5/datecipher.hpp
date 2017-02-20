/*
 * Header file for date cipher
 * 
 * Modeled after Professor Norris' rot13cipher.hpp
 */

#ifndef DATECIPHER_HPP_
#define DATECIPHER_HPP_

#include "cipher.hpp"

class DateCipher : public Cipher {
public:
    DateCipher();
    DateCipher(std::string d);
	virtual ~DateCipher();
	virtual std::string encrypt( std::string &text );
	virtual std::string decrypt( std::string &text );    
private:
    std::string date;
    int shift(int code, int s);
};

#endif /* DATECIPHER_HPP_ */