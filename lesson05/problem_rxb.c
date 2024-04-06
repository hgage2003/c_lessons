/*
Problem RXB — простые регулярные выражения
Ваша задача написать программу, распознающую корректные адреса электронной почты.

Адрес электронной почты имеет вид something@domain.extension

Где нечто может включать разделение точками и цифры, а домен и расширение буквенные.

Ваша задача отличить правильные адреса от неправильных. Для правильных выводите на stdout число
1, для неправильных 0.

Пример 1

Вход: vasya1976@mail.ru

Выход: 1

Пример 2

Вход: vasya1976@mail@ru

Выход: 0
*/

#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATCHES 10

int main()
{
    const char *cemail = "^[[:alnum:].]+@[[:alpha:]]+[.][[:alpha:].]+$";
    int res;
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];

    char input[1024];
    res = scanf("%s", input);
    if (res != 1)
    {
        fprintf(stderr, "Error in input");
        abort();
    }

    res = regcomp(&regex, cemail, REG_EXTENDED);
    if (res)
    {
        fprintf(stderr, "Could not compile regex");
        abort();
    }

    res = regexec(&regex, input, MAX_MATCHES, matches, 0);

#if 0
    printf("str = [%s]\nregex  = [%s]\n", input, cemail);
    if (!res) 
    {
        for (size_t i = 0; i <= regex.re_nsub; i++) 
        {
            char buff[20] = "";
            printf("szso[%zu]=%d\n", i, matches[i].rm_so);
            printf("szeo[%zu]=%d\n", i, matches[i].rm_eo);
            memcpy(buff, input + matches[i].rm_so, matches[i].rm_eo - matches[i].rm_so);
            printf("group[%zu]: [%s]\n", i, buff);
        }
    }
    else if (res == REG_NOMATCH)
        printf("No match\n");
    else 
    {
        char BUFFER[128];
        regerror(res, &regex, BUFFER, sizeof(BUFFER));
        fprintf(stderr, "Regex match failed: %s\n", BUFFER);
        abort();
    }
#endif
    
    if (res == 0)
        printf("1\n");
    if (res == REG_NOMATCH)
        printf("0\n");
    
    regfree(&regex);
}