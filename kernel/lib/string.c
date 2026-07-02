#include "./stddef.h"
#include "string.h"


int atoi(const char *str)
{
    int sign = 1;
    int value = 0;

    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    while (*str)
    {
        if (*str < '0' || *str > '9')
            break;

        value = value * 10 + (*str - '0');
        str++;
    }

    return value * sign;
}

void itoa(int value, char *buffer)
{
    char temp[16];
    int i = 0;
    int sign = 0;

    if (value == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0)
    {
        sign = 1;
        value = -value;
    }

    while (value > 0)
    {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }

    if (sign)
        temp[i++] = '-';

    int j = 0;

    while (i > 0)
        buffer[j++] = temp[--i];

    buffer[j] = '\0';
}

int strcmp(const char *a, const char *b)
{
    while (*a && (*a == *b))
    {
        a++;
        b++;
    }

    return (unsigned char)*a - (unsigned char)*b;
}

char *strtok(char *str, const char *delim) {
    static char *next = NULL;

    if (str != NULL)
        next = str;

    if (next == NULL)
        return NULL;

    while (*next) {
        int is_delim = 0;

        for (const char *d = delim; *d; d++) {
            if (*next == *d) {
                is_delim = 1;
                break;
            }
        }

        if (!is_delim)
            break;

        next++;
    }

    if (*next == '\0') {
        next = NULL;
        return NULL;
    }

    char *token = next;

    while (*next) {
        for (const char *d = delim; *d; d++) {
            if (*next == *d) {
                *next = '\0';
                next++;
                return token;
            }
        }

        next++;
    }

    next = NULL;
    return token;
}
