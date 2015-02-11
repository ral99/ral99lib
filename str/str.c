#include <stdlib.h>
#include <string.h>

#include "str/str.h"
#include "adt/adt.h"
#include "mem/mem.h"

int str_equals(char *str1, char *str2) {
    return (strcmp(str1, str2) == 0) ? 1 : 0;
}

char *str_dup(char *str) {
    return strcpy(memalloc(strlen(str) + 1), str);
}

char *str_random(int len) {
    char str[len + 1];
    for (int i = 0; i < len; i++) {
        int alphanum = rand() % 62;
        if (alphanum < 10)
            str[i] = '0' + alphanum;
        else if (alphanum < 36)
            str[i] = 'a' + (alphanum - 10);
        else 
            str[i] = 'A' + (alphanum - 36);
    }
    str[len] = 0;
    return str_dup(str);
}

char *str_substr(char *str, int start, int len) {
    char *substr = memalloc(len + 1);
    substr[len] = 0;
    return strncpy(substr, str + start, len);
}

char *str_cat(char *str1, char *str2) {
    return strcat(strcpy(memalloc(strlen(str1) + strlen(str2) + 1), str1), str2);
}

char *str_reverse(char *str) {
    int len = strlen(str);
    char reversed[len + 1];
    for (int i = 0; i < len; i++)
        reversed[i] = str[len - i - 1];
    reversed[len] = 0;
    return str_dup(reversed);
}

char *str_escape(char *str, char *escape) {
    int k = 0;
    int len = strlen(str);
    int escape_len = strlen(escape);
    char escaped[2 * len + 1];
    for (int i = 0; i < len; i++) {
        int add_backslash = 0;
        if (str[i] == '\\')
            add_backslash = 1;
        for (int j = 0; j < escape_len; j++)
            if (str[i] == escape[j])
                add_backslash = 1;
        if (add_backslash)
            escaped[k++] = '\\';
        escaped[k++] = str[i];
    }
    escaped[k++] = 0;
    return str_dup(escaped);
}

char *str_unescape(char *str) {
    int k = 0;
    int len = strlen(str);
    char unescaped[len + 1];
    for (int i = 0, escaped = 0; i < len; i++) {
        if (str[i] == '\\' && !escaped)
            escaped = 1;
        else {
            unescaped[k++] = str[i];
            escaped = 0;
        }
    }
    unescaped[k++] = 0;
    return str_dup(unescaped);
}

int str_find(char *str, char *pat) {
    int len = strlen(str);
    int pat_len = strlen(pat);
    for (int i = 0, j = 0; i < len; i++) {
        if (str[i] == pat[j]) {
            j++;
            if (j == pat_len)
                return i - pat_len + 1;
        }
        else
            j = 0;
    }
    return -1;
}

char *str_join(ADTList strs, char *sep) {
    int len = (list_max(strs, (int (*)(void *)) strlen) + strlen(sep)) * list_size(strs);
    char join[len + 1];
    join[0] = 0;
    for (ADTListItem it = list_head(strs); it; it = list_next(it)) {
        strcat(join, list_value(it));
        if (list_next(it))
            strcat(join, sep);
    }
    return str_dup(join);
}

ADTList str_split(char *str, char *sep) {
    int index;
    int start = 0;
    int len = strlen(str);
    int sep_len = strlen(sep);
    ADTList list = list_new();
    while ((index = str_find(str + start, sep)) >= 0) {
        list_append(list, str_substr(str, start, index));
        start += index + sep_len;
    }
    if (len > 0)
        list_append(list, str_substr(str, start, len - start));
    return list;
}

