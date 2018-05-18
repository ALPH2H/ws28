#ifndef CURSORS_BASE64_H
#define CURSORS_BASE64_H

#include <string>

namespace ws28 {
	std::string base64_encode(unsigned char const* , unsigned int len);
	std::string base64_decode(std::string const& s);
}

#endif