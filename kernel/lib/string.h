#ifndef STRING_H
#define STRING_H

void itoa(int value, char *buffer);
int atoi(const char *str);

char *strtok(char *str, const char *delim);
int strcmp(const char *a, const char *b);

#endif
