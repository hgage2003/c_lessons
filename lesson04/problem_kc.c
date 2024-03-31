/*
Problem KC — алгоритм Рабина-Карпа с учётом коллизий
Считайте что где-то для вас уже написаны следующие функции

// подсчитать хеш строки от start до fin
int get_hash(const char *start, const char *fin);

// обновить хеш current, удалив из него cprev и добавив в него cnext
// здесь n это pow_mod(R, right - 1, Q)
// возвращает новый хеш
int update_hash(int current, int n, char cprev, char cnext);

// raise n to power k modulo m
unsigned long long pow_mod (unsigned n, unsigned k, unsigned m);
Считайте что для вас также уже объявлены константы R и Q

Алгоритм Рабина-Карпа без учёта коллизий выглядит следующим образом

// возвращает номер позиции на которой needle расположена внутри haystack
// или -1 если ничего не найдено
int rabin_karp(const char *needle, const char *haystack) {
  unsigned n, target, cur, count = 0, left = 0, right = strlen(needle);
  
  target = get_hash(needle, needle + right);
  cur = get_hash(haystack, haystack + right);
  n = pow_mod(R, right - 1, Q);

  while(target != cur && haystack[right] != 0) {
    cur = update_hash(cur, n, haystack[left], haystack[right]);
    left += 1;
    right += 1;
  }
  
  return (target == cur) ? left : -1;
}
Вам нужно изменить и отправить на проверку алгоритм Рабина-Карпа, учтя в нём возможные коллизии

В посылке должна быть только указанная функция, отправлять функцию main не нужно
*/

#ifdef NDEBUG
#include <stdio.h>
#include <string.h>

#define R 4
#define Q 32 

// подсчитать хеш строки от start до fin
int get_hash(const char *start, const char *fin)
{
    int hash = 0;
    for (; start != fin; ++start)
    {
        hash += *start;
    }
    return hash;
}

// обновить хеш current, удалив из него cprev и добавив в него cnext
// здесь n это pow_mod(R, right - 1, Q)
// возвращает новый хеш
int update_hash(int current, int n, char cprev, char cnext)
{
    return current - cprev + cnext;
}

// raise n to power k modulo m
unsigned long long pow_mod (unsigned n, unsigned k, unsigned m)
{
    return 0;
}
#endif

// возвращает номер позиции на которой needle расположена внутри haystack
// или -1 если ничего не найдено
int rabin_karp(const char *needle, const char *haystack) 
{
    unsigned n, target, cur, left = 0, right = strlen(needle);
    int res = -1;
    
    target = get_hash(needle, needle + right);
    cur = get_hash(haystack, haystack + right);
    n = pow_mod(R, right - 1, Q);

    while (haystack[right])
    {        
        if (target == cur && !strncmp(needle, &haystack[left], strlen(needle)))
        {
            res = left;
            break;
        }

        cur = update_hash(cur, n, haystack[left], haystack[right]);
        left += 1;
        right += 1;
    }
    
    return res;
}

#ifdef NDEBUG
int main()
{
    char *hay = "there is a neelde needle in a haystack";
    char *needle = "needle";

    printf("%d\n", rabin_karp(needle, hay));
}
#endif