#ifndef SCD
#define SCD

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util/colour.h"
#include "total/count.h"

/*

struct scd_item_p
    hour 0-23
    min 0-59
    week 0-6
    mode 0-63

*/

struct scd_item_p{
    int block; 
    int hour; 
    int min;
    int day_of_week;
    char name[53];
    int mode;
};

struct scd_item_d{
    int block; 
    int hour; 
    int min;
    int day;
    int month;
    int year;
    char name[53];
    int mode; 
};

struct scd_item_w{
    int day;
    int month;
    int year;
    char name[53];
    int mode;
};

struct scd_item_m{
    int month;
    int year;
    char name[53];
    int mode;
};

struct scd_item_s{
    int day_s;
    int month_s;
    int year_s;
    int day_e;
    int month_e;
    int year_e;
    char name[53];
    int mode;
};

struct scd_item_docket{
    int day;
    int month;
    int year;
    int n;
    char name[371];
};

struct secondaries{
    struct scd_item_d* scd_d;
    struct scd_item_w* scd_w;
    struct scd_item_m* scd_m;
    struct scd_item_s* scd_s;
    struct scd_item_docket* scd_docket;
};

void nearest_sunday(int d, int m, int y, int* d_sun, int* m_sun, int* y_sun);
int within_range(struct scd_item_s* scd_s, int d, int m, int y);
int day_of_week(int d, int m, int y);

void get_clock(char* line, int* h, int* m);

void day_of_week_convert(int dw, char* dw_s, int abv);
void month_convert(int mn, char* mn_s);
void time_convert(int h, int m, char* time_s);
void mode_colour(int m, char* col);

void day_items(struct scd_item_p* scd_p, struct secondaries* sec, struct scd_count* nums, int d, int m, int y);

void load_items_primary(struct scd_item_p* scd_p);
void load_items_day(struct scd_item_d* scd_d);
void load_items_week(struct scd_item_w* scd_w);
void load_items_month(struct scd_item_m* scd_m);
void load_items_special(struct scd_item_s* scd_s);
void load_items_docket(struct scd_item_docket* scd_docket);

void load_tm(struct tm* ct);

#endif