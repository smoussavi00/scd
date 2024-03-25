#ifndef SCD
#define SCD

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util/colour.h"
#include "total/count.h"

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

struct secondaries{
    struct scd_item_d* scd_d;
    struct scd_item_w* scd_w;
    struct scd_item_m* scd_m;
    struct scd_item_s* scd_s;
};

void nearest_sunday(int d, int m, int y, int* d_sun, int* m_sun, int* y_sun);
int within_range(struct scd_item_s* scd_s, int d, int m, int y);
int day_of_week(int d, int m, int y);

int compare_events_p(struct scd_item_p* scd_p, int a, int b);
int compare_events_d(struct secondaries* sec, int a, int b);

void get_clock(char* line, int* h, int* m, int off);

void day_of_week_convert(int dw, char* dw_s, int abv);
void month_convert(int mn, char* mn_s);
void time_convert(int h, int m, char* time_s);
void mode_colour(int m, char* col);

int day_items(int page, struct scd_count* nums, struct scd_item_p* scd_p, struct secondaries* sec, int d, int m, int y);

void load_items_primary(struct scd_item_p* scd_p);
void load_items_day(struct scd_item_d* scd_d);
void load_items_week(struct scd_item_w* scd_w);
void load_items_month(struct scd_item_m* scd_m);
void load_items_special(struct scd_item_s* scd_s);

void add_item_primary(struct scd_count* nums, struct scd_item_p* scd_p, int block, int hour, int min, int day_of_week, char* name, int mode);
void add_item_day(struct scd_count* nums, struct secondaries* sec, int block, int hour,  int min, int day, int month, int year, char* name, int mode);
void add_item_week(struct scd_count* nums, struct secondaries* sec, int day, int month, int year, char* name, int mode);
void add_item_month(struct scd_count* nums, struct secondaries* sec, int month, int year, char* name, int mode);
void add_item_special(struct scd_count* nums, struct secondaries* sec, int day_s, int month_s, int year_s, int day_e, int month_e, int year_e, char* name, int mode);

void del_item_primary(struct scd_count* nums, struct scd_item_p* scd_p, int i);
void del_item_day(struct scd_count* nums, struct secondaries* sec, int i);
void del_item_week(struct scd_count* nums, struct secondaries* sec, int i);
void del_item_month(struct scd_count* nums, struct secondaries* sec, int i);
void del_item_special(struct scd_count* nums, struct secondaries* sec, int i);

void commit_items_primary(struct scd_count* nums, struct scd_item_p* scd_p);
void commit_items_day(struct scd_count* nums, struct secondaries* sec);
void commit_items_week(struct scd_count* nums, struct secondaries* sec);
void commit_items_month(struct scd_count* nums, struct secondaries* sec);
void commit_items_special(struct scd_count* nums, struct secondaries* sec);

void load_tm(struct tm* ct);

#endif