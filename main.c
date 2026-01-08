#include <stdio.h>
#include <time.h>
#include <ncurses.h>

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

void fill_calendar(struct calendar c, int calendar[6][7]) {
    int days_count = 1;

    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            if (days_count > c.month_total_days) {
                calendar[row][col] = 0;
                continue;
            }
            if (col < c.first_day_weekday && row == 0) {
                calendar[row][col] = 0;
                continue;
            }

            calendar[row][col] = days_count;

            days_count += 1;
        }
    }
}

void make_time(int day, int month, int year, struct calendar *c) {
    // day, month e year iguais a 0 significa data atual.
    if (day == 0 && month == 0 && year == 0) {
        time_t now = time(NULL);
        struct tm *s_now = localtime(&now);

        struct tm w_day = {0};

        w_day.tm_mday = 1;
        w_day.tm_mon = s_now->tm_mon;
        w_day.tm_year = s_now->tm_year;

        mktime(&w_day);

        c->year = s_now->tm_year + 1900;
        c->month = s_now->tm_mon + 1;
        c->month_total_days = days_in_month(s_now->tm_mon + 1, s_now->tm_year + 1900);
        c->current_month_day = s_now->tm_mday;
        c->first_day_weekday = w_day.tm_wday;

        return;
    }

    struct tm date = {0};

    date.tm_mday = day;
    date.tm_mon = month;
    date.tm_year = year;

    mktime(&date);

    c->year = date.tm_year + 1900;
    c->month = date.tm_mon + 1;
    c->month_total_days = days_in_month(date.tm_mon + 1, date.tm_year + 1900);
    c->current_month_day = date.tm_mday;
    c->first_day_weekday = date.tm_wday;
}

int main() {
    struct calendar c = {0};

    make_time(0, 0, 0, &c);

    int calendar[6][7] = {0};

    fill_calendar(c, calendar);
    
    initscr();
    cbreak();
    noecho();

    int input;

    int day_count = c.current_month_day;
    int month_count = c.month;
    int year_count = c.year;

    do {
        clear();

        make_time(day_count, month_count, year_count, &c);
        fill_calendar(c, calendar);

        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < 7; col++) {
                printw("%d ", calendar[row][col]);
            }

            printw("\n");
        }
    } while ((input = getch()) != 'q');

    endwin();

    return 0;
}
