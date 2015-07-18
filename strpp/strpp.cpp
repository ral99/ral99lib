#include <stdlib.h>
#include <string>
#include <vector>

#include "adt/list/list/list.h"
#include "adt/list/list_item/list_item.h"
#include "str/str.h"
#include "strpp/strpp.h"

std::string str::join(const std::vector<std::string>& strs, const std::string& separator) {
    ADTList c_strs = list_new();
    for (std::vector<std::string>::const_iterator it = strs.begin(); it != strs.end(); it++)
        list_append(c_strs, (char *) it->c_str());
    char *c_joined = str_join(c_strs, (char *) separator.c_str());
    std::string joined(c_joined);
    list_release(c_strs);
    free(c_joined);
    return joined;
}

std::vector<std::string> str::split(const std::string& str, const std::string& separator) {
    std::vector<std::string> splitted;
    ADTList c_splitted = str_split((char *) str.c_str(), (char *) separator.c_str());
    for (ADTListItem it = list_head(c_splitted); it; it = list_next(it))
        splitted.push_back(std::string((char *) list_value(it)));
    list_full_release(c_splitted, free);
    return splitted;
}

