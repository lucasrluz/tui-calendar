#include <stdio.h>
#include <time.h>

int days_in_month(int month, int year) {
    if (month == 2) {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
            return 29;
        }

        return 28;
    }

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31;
    }

    return 30;
}

int main() {
    time_t now = time(NULL);
    struct tm *s_now = localtime(&now);

    printf("Dia da semana atual: %d\n", s_now->tm_wday);
    printf("Dia atual: %d\n", s_now->tm_mday);
    printf("Mês atual: %d\n", s_now->tm_mon + 1);
    printf("Ano atual: %d\n", s_now->tm_year + 1900);

    printf("Total de dias do mês: %d\n", days_in_month(s_now->tm_mon + 1, s_now->tm_year + 1900));

    struct tm w_day = {0};

    w_day.tm_mday = 1;
    w_day.tm_mon = s_now->tm_mon;
    w_day.tm_year = s_now->tm_year;

    mktime(&w_day);
    
    printf("Dia da semana para o primeiro dia do mês: %d\n", w_day.tm_wday);

    return 0;
}
