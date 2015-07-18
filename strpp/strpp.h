#ifndef __STRPP__
#define __STRPP__

#include <string>
#include <vector>

namespace str {
    // Join a list of strings to be separated by a specified string.
    std::string join(const std::vector<std::string>& strs, const std::string& separator);

    // Split a string on a specified separator string.
    std::vector<std::string> split(const std::string& str, const std::string& separator);
}

#endif

