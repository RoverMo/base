#pragma once

size_t _strlen(const char *);

int	_strcmp(const char *, const char *);
int _strncmp(const char *, const char *, size_t);
int _memcmp(const void *, const void *, size_t);

char *_strchr(const char *, int);
char *_strrchr(const char *, int);
char *_strchrnul(const char *s, int c);
void *_memchr(const void *s, int c, size_t n);
void *_memrchr(const void *s, int c, size_t n);

char *_strstr(const char *haystack, const char *needle);

char *_strcpy(char *, const char *);
char *_strncpy(char *, const char *, size_t);
void *_memcpy(void *, const void *, size_t);
void *_memccpy(void *dest, const void *src, int c, size_t n);
void *_memmove(void *, const void *, size_t);

void *_memset(void *, int, size_t);

char *_strcat(char *, const char *);
char *_strncat(char *, const char *, size_t);

size_t _strspn(const char *, const char *);
size_t _strcspn(const char *, const char *);
