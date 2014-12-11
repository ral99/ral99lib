#ifndef __ADT__STR__
#define __ADT__STR__

#include "adt/list/list.h"

/* Return 1 if strings are equal. 0, otherwise. */
int str_equals(char *str1, char *str2);

/* Return the duplicated string. */
char *str_dup(char *str);

/* Return an alphanumeric random string with the specified lenght. */
char *str_random(int len);

/* Return the substring from start position with the specified lenght. */
char *str_substr(char *str, int start, int len);

/* Return the concatenation of the strings. */
char *str_cat(char *str1, char *str2);

/* Return the reversed string. */
char *str_reverse(char *str);

/* Return the escaped string. */
char *str_escape(char *str, char *escape);

/* Return the unescaped string. */
char *str_unescape(char *str);

/* Return the first occurence of pattern in string or -1. */
int str_find(char *str, char *pat);

/* Return the concatenation of strings separated by sep. */
char *str_join(List strs, char *sep);

/* Return the list of the strings separated by sep. */
List str_split(char *str, char *sep);

#endif

