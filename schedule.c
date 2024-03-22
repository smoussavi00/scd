#include "schedule.h"

int main(void){

    // LOAD ITEM COUNT FOR ALL CATEGORIES
    struct scd_count* nums = malloc(sizeof(*nums));
    load_scd_count(nums);

    struct scd_item_p* scd_p = malloc(sizeof(*scd_p)*(nums->num_p)*2);
    struct scd_item_d* scd_d = malloc(sizeof(*scd_d)*(nums->num_d)*2);
    struct scd_item_w* scd_w = malloc(sizeof(*scd_w)*(nums->num_w)*2);
    struct scd_item_m* scd_m = malloc(sizeof(*scd_m)*(nums->num_m)*2);
    struct scd_item_s* scd_s = malloc(sizeof(*scd_s)*(nums->num_s)*2);
    struct scd_item_docket* scd_docket = malloc(sizeof(*scd_docket)*(nums->num_docket)*2);

    struct secondaries* sec = malloc(sizeof(*sec));
    sec->scd_d = scd_d; sec->scd_w = scd_w; sec->scd_m = scd_m; sec->scd_s = scd_s; sec->scd_docket = scd_docket;

    // TIME STRUCT
    struct tm* ct = malloc(sizeof(*ct));

    // LOAD ITEMS
    load_items_primary(scd_p);
    load_items_day(scd_d);
    load_items_week(scd_w);
    load_items_month(scd_m);
    load_items_special(scd_s);
    load_items_docket(scd_docket);

    load_tm(ct);

    day_items(scd_p,sec,nums,ct->tm_mday,(ct->tm_mon)+1,(ct->tm_year)+1900);

    free(ct); free(scd_p); free(scd_d); free(scd_w); free(scd_m); free(scd_s); free(scd_docket); free(sec); free(nums);

    return 0;
}

void nearest_sunday(int d, int m, int y, int* d_sun, int* m_sun, int* y_sun){
// RETURNS THE DATE OF THE NEAREST SUNDAY BEFORE INPUT DATE
    struct tm* t = malloc(sizeof(*t));
    char input_time_s[23];

    sprintf(input_time_s,"%i %i %i",d,m,y);

    strptime(input_time_s, "%d %m %Y", t);

    int dow = t->tm_wday;
    if(dow >= t->tm_mday){
        dow -= t->tm_mday;
        if(m == 1){
            *y_sun = y-1;
            *m_sun = 12;
        }  else {
            *y_sun = y;
            *m_sun = m-1;
        }
        if(m == 1 || m == 2 || m == 4 || m == 6 || m == 8 || m == 9 || m == 11) *d_sun = 31 - dow;
        else if(m == 3){
                *d_sun = 29 - dow;
                if(y % 4 == 0) (*d_sun)--;
        }
        else *d_sun = 30 - dow;

    } else {
        *d_sun = t->tm_mday-dow;
        *m_sun = m;
        *y_sun = y;
    } 

    free(t);
}

int within_range(struct scd_item_s* scd_s, int d, int m, int y){
    int a = y > scd_s->year_s || (y == scd_s->year_s && m > scd_s->month_s) || (y == scd_s->year_s && m == scd_s->month_s && d>= scd_s->day_s);
    int b = y < scd_s->year_e || (y == scd_s->year_e && m < scd_s->month_e) || (y == scd_s->year_e && m == scd_s->month_e && d <= scd_s->day_e);
    return a && b;
}

int day_of_week(int d, int m, int y){

    int dw;

    struct tm* t = malloc(sizeof(*t));
    char input_time_s[23];

    sprintf(input_time_s,"%i %i %i",d,m,y);
    strptime(input_time_s, "%d %m %Y", t);

    dw = t->tm_wday;

    free(t);

    return dw;
}

void get_clock(char* line, int* h, int* m){
    *h = 10*(line[3]-'0') + line[4]-'0';
    *m = 10*(line[6]-'0') + line[7]-'0';
}

void day_of_week_convert(int dw, char* dw_s, int abv){
    if(abv == 0){
        if(dw == 0) strcpy(dw_s,"Sunday");
        if(dw == 1) strcpy(dw_s,"Monday");
        if(dw == 2) strcpy(dw_s,"Tuesday");
        if(dw == 3) strcpy(dw_s,"Wednesday");
        if(dw == 4) strcpy(dw_s,"Thursday");
        if(dw == 5) strcpy(dw_s,"Friday");
        if(dw == 6) strcpy(dw_s,"Saturday");
    } else {
        if(dw == 0) strcpy(dw_s,"Sun");
        if(dw == 1) strcpy(dw_s,"Mon");
        if(dw == 2) strcpy(dw_s,"Tue");
        if(dw == 3) strcpy(dw_s,"Wed");
        if(dw == 4) strcpy(dw_s,"Thu");
        if(dw == 5) strcpy(dw_s,"Fri");
        if(dw == 6) strcpy(dw_s,"Sat");
    }
    return;
}

void month_convert(int mn, char* mn_s){
    if(mn == 0)strcpy(mn_s,"January");
    if(mn == 1) strcpy(mn_s,"February");
    if(mn == 2) strcpy(mn_s,"March");
    if(mn == 3) strcpy(mn_s,"April");
    if(mn == 4) strcpy(mn_s,"May");
    if(mn == 5) strcpy(mn_s,"June");
    if(mn == 6) strcpy(mn_s,"July");
    if(mn == 7) strcpy(mn_s,"August");
    if(mn == 8) strcpy(mn_s,"September");
    if(mn == 9) strcpy(mn_s,"October");
    if(mn == 10) strcpy(mn_s,"November");
    if(mn == 11) strcpy(mn_s,"December");
}

void time_convert(int h, int m, char* time_s){

    time_s[0] = '(';
    if(h<10){
        time_s[1] = '0';
        time_s[2] = h+'0';
    } else {
        time_s[1] = (h-(h%10))/10 + '0';
        time_s[2] = (h%10)+'0'; 
    }
    time_s[3] = ':';
    if(m<10){
        time_s[4] = '0';
        time_s[5] = m+'0';
    } else {
        time_s[4] = (m-(m%10))/10 + '0';
        time_s[5] = (m%10)+'0'; 
    }
    time_s[6]=')';
    time_s[7]='\0';
}


void mode_colour(int m, char* col){

    if(m == 0){
        strcpy(col,COLOUR_RESET); 
        return;
    } 

    int h = 1;

    for(int x = 0; x < 6; x++){
        if(m >= h*2) h *= 2;
        else{
            if(h == 1) strcpy(col,HYEL);
            else if(h == 2) strcpy(col,HGRN);
            else if(h == 4) strcpy(col,BLU);
            else if(h == 8) strcpy(col,HRED);
            else if(h == 16) strcpy(col,HMAG);
            else if(h == 32) strcpy(col,HCYN);
            return;
        }
    }
    col = BWHT;
}

void load_items_primary(struct scd_item_p* scd_p){
    

    struct scd_item_p* csi = NULL;
    int scd_len = sizeof(*scd_p);

    // OPEN PRIMARY BASE
    FILE* fp;
    char line[53];

    int fl_alt = 0;
    int n = 0;
    int dw = -1;

    fp = fopen("base/primary","r");

    while(fgets(line,53,fp)){
        
        csi = (void *) scd_p + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        if(strcmp(line,"::ALT") == 0) {
            fl_alt = 1;
            continue;   
        }

        if(strncmp("**",line,2) == 0){
            dw++;
            continue;
        }

        csi->mode = 0;
        csi->day_of_week = dw;
        csi->block = 10*(line[0]-'0')+(line[1]-'0');

        get_clock(line,&(csi->hour),&(csi->min));
        strcpy(csi->name,line+9);

        if(fl_alt == 1){
            fl_alt = 0;
            csi->mode += 1;
        }
        n++;
    }
    fclose(fp);
}

void load_items_day(struct scd_item_d* scd_d){
    struct scd_item_d* csi = NULL;
    int scd_len = sizeof(*scd_d);

    FILE *fp;
    char line[53];

    int n = 0;

    fp = fopen("base/sec_day","r");

    while(fgets(line,53,fp)){

        int day, month, year;

        csi = (void *) scd_d + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        if(strncmp("**",line,2) == 0){
            day = 10*(line[3]-'0') + (line[4]-'0');
            month = 10*(line[6]-'0') + (line[7]-'0');
            year = 1000*(line[9]-'0') + 100*(line[10]-'0') + 10*(line[11]-'0') + (line[12]-'0');
            continue;
        }

        csi->mode = 0;
        csi->day = day; csi->month = month; csi->year = year;
        csi->block = 10*(line[0]-'0')+(line[1]-'0');

        get_clock(line,&(csi->hour),&(csi->min));
        strcpy(csi->name,line+9);

        n++;
    }
    fclose(fp);
}

void load_items_week(struct scd_item_w* scd_w){
    struct scd_item_w* csi = NULL;
    int scd_len = sizeof(*scd_w);

    FILE *fp;
    char line[53];

    int n = 0;

    fp = fopen("base/sec_week","r");

    while(fgets(line,53,fp)){
        
        int day, month, year;

        csi = (void *) scd_w + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        if(strncmp("**",line,2) == 0){
            day = 10*(line[3]-'0') + (line[4]-'0');
            month = 10*(line[6]-'0') + (line[7]-'0');
            year = 1000*(line[9]-'0') + 100*(line[10]-'0') + 10*(line[11]-'0') + (line[12]-'0');
            continue;
        }

        csi->mode = 0;
        csi->day = day; csi->month = month; csi->year = year;
        strcpy(csi->name,line);

        n++;
    }
    fclose(fp);
}

void load_items_month(struct scd_item_m* scd_m){
   struct scd_item_m* csi = NULL;
    int scd_len = sizeof(*scd_m);

    FILE *fp;
    char line[53];

    int n = 0;

    fp = fopen("base/sec_month","r");

    while(fgets(line,53,fp)){
        
        int month, year;

        csi = (void *) scd_m + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        if(strncmp("**",line,2) == 0){
            month = 10*(line[3]-'0') + (line[4]-'0');
            year = 1000*(line[6]-'0') + 100*(line[7]-'0') + 10*(line[8]-'0') + (line[9]-'0');
            continue;
        }

        csi->mode = 0;
        csi->month = month; csi->year = year;
        strcpy(csi->name,line);

        n++;
    }
    fclose(fp);
}

void load_items_special(struct scd_item_s* scd_s){

   struct scd_item_s* csi = NULL;
    int scd_len = sizeof(*scd_s);

    FILE *fp;
    char line[53];

    int n = 0;

    fp = fopen("base/sec_special","r");

    while(fgets(line,53,fp)){
        
        int day_s, month_s, year_s;
        int day_e, month_e, year_e;

        csi = (void *) scd_s + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        if(strncmp("**",line,2) == 0){
            day_s = 10*(line[3]-'0') + (line[4]-'0');
            month_s = 10*(line[6]-'0') + (line[7]-'0');
            year_s = 1000*(line[9]-'0') + 100*(line[10]-'0') + 10*(line[11]-'0') + (line[12]-'0');
            day_e = 10*(line[14]-'0') + (line[15]-'0');
            month_e = 10*(line[17]-'0') + (line[18]-'0');
            year_e = 1000*(line[20]-'0') + 100*(line[21]-'0') + 10*(line[22]-'0') + (line[23]-'0');
            continue;
        }

        csi->mode = 0;
        csi->day_s = day_s; csi->month_s = month_s; csi->year_s = year_s;
        csi->day_e = day_e; csi->month_e = month_e; csi->year_e = year_e;
        strcpy(csi->name,line);

        n++;
    }
    fclose(fp);
}

void load_items_docket(struct scd_item_docket* scd_docket){
    struct scd_item_docket* csi = NULL;
    int scd_len = sizeof(*scd_docket);

    FILE *fp;
    char line[373];

    int n = 0;

    fp = fopen("base/sec_docket","r");

    while(fgets(line,373,fp)){

        int day, month, year;

        csi = (void *) scd_docket + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        if(strncmp("**",line,2) == 0){
            day = 10*(line[3]-'0') + (line[4]-'0');
            month = 10*(line[6]-'0') + (line[7]-'0');
            year = 1000*(line[9]-'0') + 100*(line[10]-'0') + 10*(line[11]-'0') + (line[12]-'0');
            continue;
        }

        strncpy(csi->name,line,strlen(line));
        csi->day = day; csi->month = month; csi->year = year;
 
        n++;
    }
    fclose(fp);
}

void day_items(struct scd_item_p* scd_p, struct secondaries* sec, struct scd_count* nums, int d, int m, int y){
    
    struct scd_item_p *csi_p = NULL;
    struct scd_item_d *csi_d = NULL;
    struct scd_item_w *csi_w = NULL;
    struct scd_item_m *csi_m = NULL;
    struct scd_item_s *csi_s = NULL;
    struct scd_item_docket *csi_docket = NULL;

    int scd_p_len = sizeof(*scd_p);
    int scd_d_len = sizeof(*(sec->scd_d));
    int scd_w_len = sizeof(*(sec->scd_w));
    int scd_m_len = sizeof(*(sec->scd_m));
    int scd_s_len = sizeof(*(sec->scd_s));
    int scd_docket_len = sizeof(*(sec->scd_docket));

    int dw = day_of_week(d,m,y);

    char dw_s[17];
    char col[11];
    char time_s[11];
    int has_entry = 0;

    day_of_week_convert(dw,dw_s,0);

    printf("\n%sSchedule for %s%s\n\n",BWHT,dw_s,COLOUR_RESET);

    for(int x = 0; x < nums->num_p; x++){
        csi_p = (void *) scd_p + scd_p_len*x;

        mode_colour(csi_p->mode,col);
        time_convert(csi_p->hour,csi_p->min,time_s);

        if(csi_p->day_of_week == dw){
            has_entry = 1;
            printf("%s\t%s%s%s %s\n",time_s,COLOUR_RESET,col,csi_p->name,COLOUR_RESET);
        } 
    }
    if(has_entry) printf("\n");
    has_entry = 0;

    for(int x = 0; x < nums->num_d; x++){
        csi_d = (void *) sec->scd_d + scd_d_len*x;

        mode_colour(csi_d->mode,col);
        time_convert(csi_d->hour,csi_d->min,time_s);

        if((csi_d->day == d) && (csi_d->month == m)  && (csi_d->year == y)){
            printf("%s\t%s%s%s %s\n",time_s,COLOUR_RESET,col,csi_d->name,COLOUR_RESET);
            has_entry = 1;
        }
    }
    if(has_entry) printf("\n");
    has_entry = 0;

    char buff[53];


    for(int x = 0; x < nums->num_docket; x++){
        csi_docket = (void *) sec->scd_docket + scd_docket_len*x;

        int j = 0;
        int start = 0;

        if((csi_docket->day == d) && (csi_docket->month == m)  && (csi_docket->year == y)){
            for(int y = 0; y < 371; y++){
                if((csi_docket->name)[y] != ',' && (csi_docket->name)[y] != '\0') j++;
                else {
                    strncpy(buff, &((csi_docket->name)[start]), j);
                    j = 0;
                    start = y + 1;
                    printf("\t%s\n",buff);
                    memset(buff,0,strlen(buff));
                    if(csi_docket->name[y] == '\0') break;
                }
            }
            has_entry = 1;
        }
    }
    if(has_entry) printf("\n");
    has_entry = 0;    

    int d_sun, m_sun, y_sun;
    nearest_sunday(d,m,y,&d_sun,&m_sun,&y_sun);

    for(int x = 0; x < nums->num_w; x++){
        csi_w = (void *) sec->scd_w + scd_w_len*x;

        mode_colour(csi_w->mode,col);

        if((csi_w->day == d_sun) && (csi_w->month == m_sun)  && (csi_w->year == y_sun)){
            printf("(WEEK )\t%s%s%s %s\n",COLOUR_RESET,col,csi_w->name,COLOUR_RESET);
            has_entry = 1;
        }
    }
    if(has_entry) printf("\n");
    has_entry = 0;

    for(int x = 0; x < nums->num_m; x++){
        csi_m = (void *) sec->scd_m + scd_m_len*x;

        mode_colour(csi_m->mode,col);

        if(csi_m->month == m){ 
            printf("(MONTH)\t%s%s%s %s\n",COLOUR_RESET,col,csi_m->name,COLOUR_RESET);
            has_entry = 1;
        }
    }
    if(has_entry) printf("\n");
    has_entry = 0;

    for(int x = 0; x < nums->num_m; x++){
        csi_s = (void *) sec->scd_s + scd_s_len*x;

        mode_colour(csi_s->mode,col);

        if(within_range(csi_s,d,m,y)){
            printf("(SPECL)\t%s%s%s %s\n",COLOUR_RESET,col,csi_s->name,COLOUR_RESET);
            has_entry = 1;
        }
        
    }
    if(has_entry) printf("\n");

}

void load_tm(struct tm* ct){

    time_t current_time;
    char* current_time_s;

    current_time = time(NULL);
    current_time_s = ctime(&current_time);

    strptime(current_time_s, "%a %h %d %H:%M:%S %Y", ct);
}


//if(x!=0) if(csi->day_of_week != (scd + scd_len*(x-1))->day_of_week ) printf("\n");
/*
    char cmd[53];

    while(1){
        scanf("%s",cmd);
        if(strcmp(cmd,"exit") == 0) break;
        if(strcmp(cmd,"show today") == 0) day_items(scd_p,ct.tm_wday,num);
        //if(strcmp(cmd,"show week ag:"))
        
    } 
*/