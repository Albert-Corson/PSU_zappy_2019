/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** strtotab
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static size_t get_word_len(const char *str, const char *sep, bool *quoted)
{
    size_t i = 0;

    if (str[0] != '\"') {
        *quoted = false;
        return (strcspn(str, sep));
    }
    *quoted = true;
    ++str;
    while (str[i] && str[i] != '\"') {
        i += strcspn(str + i, "\"");
        if (str[i] && i > 0 && str[i - 1] == '\\') {
            ++i;
        } else if (str[i] && !strchr(sep, str[i + 1])) {
            ++i;
        }
    }
    return (i);
}

static size_t count_words(const char *str, const char *sep, bool skip_chained)
{
    size_t count = 0;
    bool quoted = false;

    while (*str) {
        if (strchr(sep, *str)) {
            str += skip_chained ? strspn(str, sep) : 1;
        }
        if (*str) {
            str += get_word_len(str, sep, &quoted);
            str += quoted * 2;
            count += 1;
        }
    }
    return (count);
}

static size_t extract_word(char **dest, const char *src, const char *sep, \
bool skip_chained)
{
    bool quoted = false;
    size_t word_len = get_word_len(src, sep, &quoted);

    *dest = calloc(word_len + 1, sizeof(**dest));
    strncpy(*dest, src + quoted, word_len);
    return (word_len + (quoted * 2));
}

char **strtotab(const char *str, const char *sep, bool skip_chained)
{
    char **tab = NULL;
    size_t i = 0;

    if (!str || !sep)
        return (NULL);
    tab = calloc(count_words(str, sep, skip_chained) + 1, sizeof(*tab));
    while (*str) {
        if (strchr(sep, *str)) {
            str += skip_chained ? strspn(str, sep) : 1;
        }
        if (*str) {
            str += extract_word(&tab[i], str, sep, skip_chained);
            i += 1;
        }
    }
    return (tab);
}
