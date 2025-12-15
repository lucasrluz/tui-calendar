#include <stdio.h>
#include <time.h>

int main() {
    time_t now = time(NULL);
    struct tm *s_now = localtime(&now);

    printf("Dia da semana atual: %d\n", s_now->tm_wday);
    printf("Dia atual: %d\n", s_now->tm_mday);
    printf("Mês atual: %d\n", s_now->tm_mon + 1);
    printf("Ano atual: %d\n", s_now->tm_year + 1900);

    return 0;
}
