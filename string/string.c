// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

//https://www.techiedelight.com/implement-strcpy-function-c/
char *strcpy(char *destination, const char *source)
{
	//Copiez in sirul auxiliar sirul destinat
	char *auxiliar = destination;
	while (*source != '\0') {
		*auxiliar = *source;
		source++;
		auxiliar++;
	}
	//Adaug terminatorul de sir la sfarsitul sirului copiat
	*auxiliar = '\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	char *q = destination;
	const char *p = source;
	char sir_aux;
	//nr = contor pentru a copia pana la len caractere
	int nr = 0;
	while (nr < (int)len) {
		sir_aux = *p;
		p++;
		*q = sir_aux;
		q++;
	   	nr++;
	}
	return destination;
}

//inspirat de aici: https://aticleworld.com/strcat-in-c/
char *strcat(char *destination, const char *source)
{
	char *dest = destination;
	const char *src = source;
	char *d = dest;
	//Merg pana la finalul primului sir si apoi concatenez celalalt sir
	while (*d != '\0') {
		d++;
	}
	if (src != NULL)
		strcpy(d, src);
	//Dupa concatenare adaug terminatorul de sir
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	char *dest = destination;
	const char *src = source;
	char *d = dest;
	int nr = 0;
	//Merg pana la finalul primului sir si apoi concatez celalalt sir
	while (*d != '\0') {
		d++;
	}
	//daca primul caracter din src nu e NULL incepe copierea
	if(*src != '\0') {
		while (nr < (int)len) {
		*d = *src;
		d++;
		src++;
		nr++;
		}
	}
	//Dupa concatenare adaug terminatorul de sir
	*d = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	int n_str1 = strlen(str1);
	int n_str2 = strlen(str2);
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 < *str2) {
			return -1;
		} else if (*str1 > *str2) {
			return 1;
		}

		str1++;
		str2++;
	}
	//verific daca unul dintre siruri este mai lung
	if (n_str1 == n_str2) {
		return 0;
	} else if (n_str1 < n_str2) {
		return -1;
	} else {
		return 1;
	}
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	int i = 0;
	while (i < (int)len){
		//daca cele doua caractere nu sunt egale returnez diferenta
		if(str1[i] != str2[i]) {
			return str1[i] - str2[i];
		}
		if(str1[i] == '\0') {
			return 0;
		}
		i++;
	}
	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	int i = 0;
	//daca caracterul este diferit de terminatorul de sir
	while (str[i] != '\0') {
		//daca caracterul este egal cu c returnez adresa lui
		if (str[i] == c)
		//returnez adresa caracterului
			return str + i;
		i++;
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	int i = 0;
	//iau sirul de la capat pentru a cauta ultima aparitie a lui c
	for (i = strlen(str) - 1; i >= 0; i--) {
		if (str[i] == c)
			return str + i;
	}
	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	//daca sirul cautat este NULL returnez sirul initial
	if (*needle == '\0') {
		return (char *)haystack;
	}
	int h_len = strlen(haystack);
	int n_len = strlen(needle);
	int dif = h_len - n_len;
	//parcurg sirul initial si caut sirul cautat
	for (int i = 0; i <= dif; i++) {
		int j = 0;
	//compar caracterele pana cand j va fi egal cu lungimea sirului cautat
		while (j < n_len) {
			if (haystack[i + j] != needle[j]) {
				break;
			}
			j++;
		}
	//daca am gasit sirul cautat returnez adresa lui
		if (j == n_len) {
			return (char *)(haystack + i);
		}
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle) {
	int h_len = strlen(haystack);
	int n_len = strlen(needle);
	//daca sirul cautat este NULL returnez adresa de dupa ultimul caracter
	if (n_len == 0) {
		return (char *)haystack + h_len;
	}
	int dif = h_len - n_len;
	/*acelasi lucru ca la strstr doar ca o iau de la final
		pentru a gasi prima pozitie cea mai din dreapta*/
	for (int i = dif; i >= 0; i--) {
		int j = 0;
		while (j < n_len) {
			if (haystack[i + j] != needle[j])
				break;
			j++;
		}
		if (j == n_len) {
			return (char *)(haystack + i);
		}
		if (i == 0) {
			break;
		}
	}

	return NULL;
}

//inspirat de aici:https://www.geeksforgeeks.org/write-memcpy/
void *memcpy(void *destination, const void *source, size_t num)
{
	char *dest = (char *) destination;
	const char *src = (const char *) source;
	int i = 0;
	while (i < (int)num) {
		*dest = *src;
		dest++;
		src++;
		i++;
	}
	return destination;
}

//ultimele randuri inspirate de aici:https://www.tutorialspoint.com/write-your-own-memcpy-and-memmove-in-cplusplus
void *memmove(void *destination, const void *source, size_t num)
{
	char *dest = (char *) destination;
	const char *src = (const char *) source;
	int i = 0;
	if (dest < src) {
		//este la fel ca la memcpy aceasta conditie
		while (i < (int)num) {
			*dest = *src;
			dest++;
			src++;
			i++;
		}
	} else {
		while (num > 0) {
			//indexarea incepe de la 0
			dest[num - 1] = src[num - 1];
			num--;
		}
	}
	return destination;
}

//inspirat de aici:https://aticleworld.com/memcmp-in-c/
int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const char *p1 = (const char *) ptr1;
	const char *p2 = (const char *) ptr2;
	int i = 0;
	while (i < (int)num) {
		if (p1[i] < p2[i]) {
			return -1;
		} else if (p1[i] > p2[i]) {
			return 1;
		}
		i++;
	}
	return 0;
}

//https://opensource.apple.com/source/gcc/gcc-5026/libiberty/memset.c.auto.html
void *memset(void *source, int value, size_t num)
{
	char *src = (char *) source;
	int i = 0;
	while (i < (int)num) {
		src[i] = value;
		i++;
	}
	return source;
}
