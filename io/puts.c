#include <stdio.h>
#include <unistd.h>
#include <internal/io.h>
#include <string.h>
#include <stddef.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#define EOF (-1)

int puts(const char *s)
{
    if (s == NULL)
        return EOF;

    int len = (int)strlen(s);
    /*Scriu sirul pe iesirea standard sau eroare daca lungimea sirului este mai
    /scurta decat lungimea data*/
    if (write(STDOUT_FILENO, s, len) != len)
        return EOF;
    //Adaug un caracter de linie noua sau returnez eroarea daca nu poate
    if (write(STDOUT_FILENO, "\n", 1) != 1)
        return EOF;

    return 0;
}
