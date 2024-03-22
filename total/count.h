#ifndef T_TL
#define T_TL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct scd_count{
    //Primary Items
    int num_p;
    //Secondary Items
    int num_d; 
    int num_w;
    int num_m;
    int num_s;
    int num_docket;
};

void load_scd_count(struct scd_count* nums);


#endif