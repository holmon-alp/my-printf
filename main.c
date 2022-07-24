#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>


void printDecimal(int num) {
    int l = 0;
    int size = 1;
    int* str = (int *) malloc(size * sizeof(int));
    while (num > 0) {
    str[l] = num % 10;
        num /= 10;
        size++;
        str = (int *) realloc(str, size * sizeof(int));
        l++;
    }
    for (l = l - 1; l >= 0; l--) {
        //printf("\n%d\n", str[l]);
        char n = (char)(str[l] + 48);
        write(1, &n, sizeof(char));
    }
    free(str);
}


void printOctal(unsigned int num) {
    int l = 0;
    int size = 1;
    int* str = (int *) malloc(size * sizeof(int));
    while (num > 0) {
        str[l] = num % 8;
        num /= 8;
        size++;
        str = (int *) realloc(str, size * sizeof(int));
        l++;
    }
    for (l = l - 1; l >= 0; l--) {
        //printf("\n%d\n", str[l]);
        char n = (char)(str[l] + 48);
        write(1, &n, sizeof(char));
    }
    free(str);
}


void printHex(unsigned int num) {
    int l = 0;
    int size = 1;
    int* str = (int *) malloc(size * sizeof(int));
    while (num > 0) {
        if (num % 16 < 10) {
            str[l] = num % 16 + 48;
        }
        else {
            str[l] = num % 16 + 55;
        }
        num /= 16;
        size++;
        str = (int *) realloc(str, size * sizeof(int));
        l++;
    }
    for (l = l - 1; l >= 0; l--) {
        //printf("\n%d\n", str[l]);
        char n = (char) str[l];
        write(1, &n, sizeof(char));
    }
    free(str);
}


void printUnsigned(unsigned int n) {

    int div;
	unsigned int num;

	div = 1;

	num = n;

	while (num / div > 9) {
        div *= 10;
    }

	while (div != 0) {
        unsigned int l = '0' + num / div;
        write(1, &l, 1);
		num %= div;
		div /= 10;
	}
}


void printPtr(unsigned long long int num) {
    int l = 0;
    int size = 1;
    unsigned long long int* str = (unsigned long long int *) malloc(size * sizeof(unsigned long long int));
    while (num > 0) {
        if (num % 16 < 10) {
            str[l] = num % 16 + 48;
        }
        else {
            str[l] = num % 16 + 55;
        }
        //str[l] = num % 16;
        num /= 16;
        size++;
        str = (unsigned long long int *) realloc(str, size * sizeof(unsigned long long int));
        l++;
        if (num == 0) {
            str[l] = 'x';
            size += 2;
            str = (unsigned long long int *) realloc(str, size * sizeof(unsigned long long int));
            l++;
            str[l] = '0';
            l++;
        }
    }
    //printf("\n%c\n", str);

    for (l = l - 1; l >= 0; l--) {
        //printf("\n%d\n", str[l]);
        char n = (char) str[l];
        write(1, &n, sizeof(char));
    }
    free(str);
}


int my_printf(char * restrict format, ...) {
    va_list va;
    va_start(va, format);
    int i = 0;

    while (format[i]) {
        if (format[i] == '%') {
            if (format[i+1] == 'd') {
                int num = va_arg(va, int);
                //printf("\n%d\n", num);
                printDecimal(num);
            } else if (format[i+1] == 'c') {
                char c = (char) va_arg(va, int);
                //printf("\n%c\n", c);
                write(1, &c, 1);
            } else if (format[i+1] == 's') {
                char* s = va_arg(va, char*);
                //printf("\n%s\n", s);
                int l = 0;
                while (s[l]) {
                    write(1, &s[l], sizeof(s[l])); 
                    l++;   
                }
            } else if (format[i+1] == 'o') {
                unsigned int num = va_arg(va, unsigned int);
                //printf("\n%d\n", num);
                printOctal(num);
            } else if (format[i+1] == 'x') {
                unsigned int num = va_arg(va, unsigned int);
                //printf("\n%d\n", num);
                printHex(num);
            } else if (format[i+1] == 'p') {
                unsigned long long int num = va_arg(va, unsigned long long int);
                //printf("%u", va_arg(va, unsigned int));
                printPtr(num);
            } else if (format[i+1] == 'u') {
                unsigned int num = va_arg(va, unsigned int);
                //printf("%u", va_arg(va, unsigned int));
                printUnsigned(num);
            } else if (format[i+1] == '%') {
                char percentChar = '%';
                write(1, &percentChar, sizeof(char));
            }
            i++;
        } else {
            char c = format[i];
            write(1, &c, 1);
        }
        i++;
    }

    va_end(va);
    return 1;
}

int main () {
    char str[] = "Holmon";
    char lang = 'C';
    int years = 19;
    int* ptr = &years;
    unsigned int u = -7869;
    //printf("%p\n", ptr);
    my_printf("Hey, My name is %s. I'm %d years old. %%I'm learning '%c' language. Here is my ptr address - %p. Unsigned int - %u\nMy age in octal is %o, and in hex is %x", str, years, lang, ptr, u, years, years);

    return 0;
}
