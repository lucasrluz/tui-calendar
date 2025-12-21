#include <stdio.h>
#include <time.h>

struct calendar {
    int year;
    int month;
    int month_total_days;
    int current_month_day;
    int first_day_weekday;
};

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

void fill_calendar(struct calendar c) {
    int calendar[6][7] = {0};

    int days_count = 1;

    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            if (days_count > c.month_total_days) continue;
            if (col < c.first_day_weekday && row == 0) continue;

            calendar[row][col] = days_count;

            days_count += 1;
        }
    }

    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            printf("%d ", calendar[row][col]);
        }

        printf("\n");
    }
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

    struct calendar c = {
        .year = s_now->tm_year + 1900,
        .month = s_now->tm_mon + 1,
        .month_total_days = days_in_month(s_now->tm_mon + 1, s_now->tm_year + 1900),
        .current_month_day = s_now->tm_mday,
        .first_day_weekday = w_day.tm_wday
    };

    fill_calendar(c);

    return 0;
}
