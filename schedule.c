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

    struct secondaries* sec = malloc(sizeof(*sec));
    sec->scd_d = scd_d; sec->scd_w = scd_w; sec->scd_m = scd_m; sec->scd_s = scd_s; 

    // TIME STRUCT
    struct tm* ct = malloc(sizeof(*ct));

    // LOAD ITEMS
    load_items_primary(scd_p);
    load_items_day(scd_d);
    load_items_week(scd_w);
    load_items_month(scd_m);
    load_items_special(scd_s);

    load_tm(ct);

    int p = 0;
    int pt;
    int p_max = 0;
    int p_min = 1;
    
    system("clear");
    printf("\n\nSchedule Program (work in progress)\n\n'today' to see your schedule for today\n'next' or 'back' to navigate through pages\n'exit' to exit\n\n\n\n\nSCD - Welcome\n\n");

    while(1){
        char buf[97];
        fgets(buf, sizeof(buf), stdin);

        if(strncmp(buf,"exit",4) == 0) break;

        else if(strncmp(buf,"today",5) == 0){
            p = 1;
            system("clear");
            pt = day_items(p,nums,scd_p,sec,ct->tm_mday,(ct->tm_mon)+1,(ct->tm_year)+1900);
        }
        else if(strncmp(buf,"next",4) == 0 && p < pt){
            p++;
            system("clear");
            pt = day_items(p,nums,scd_p,sec,ct->tm_mday,(ct->tm_mon)+1,(ct->tm_year)+1900);
        }
        else if(strncmp(buf,"back",4) == 0 && p > 1){
            p--;
            system("clear");
            pt = day_items(p,nums,scd_p,sec,ct->tm_mday,(ct->tm_mon)+1,(ct->tm_year)+1900);
        }
        else if(strncmp(buf,"add p",5) == 0){
            buf[strcspn(buf, "\n")] = 0;
            add_item_primary(nums,scd_p,atoi(buf+8),atoi(buf+11),atoi(buf+14),atoi(buf+6),buf+20,atoi(buf+17));
        } 
        else if(strncmp(buf,"add d",5) == 0){
            buf[strcspn(buf, "\n")] = 0;
            add_item_day(nums,sec,atoi(buf+6),atoi(buf+9),atoi(buf+12),atoi(buf+15),atoi(buf+18),atoi(buf+21),buf+29,atoi(buf+26));
        } 
        else if(strncmp(buf,"add w",5) == 0){
            buf[strcspn(buf, "\n")] = 0;
            add_item_week(nums,sec,atoi(buf+6),atoi(buf+9),atoi(buf+12),buf+20,atoi(buf+17));
        }
        else if(strncmp(buf,"add w",5) == 0){
            buf[strcspn(buf, "\n")] = 0;
            add_item_week(nums,sec,atoi(buf+6),atoi(buf+9),atoi(buf+12),buf+20,atoi(buf+17));
        }
        else if(strncmp(buf,"add m",5) == 0){
            buf[strcspn(buf, "\n")] = 0;
            add_item_month(nums,sec,atoi(buf+6),atoi(buf+9),buf+17,atoi(buf+14));
        }
        else if(strncmp(buf,"add s",5) == 0){
            buf[strcspn(buf, "\n")] = 0;
            add_item_special(nums,sec,atoi(buf+6),atoi(buf+9),atoi(buf+12),atoi(buf+17),atoi(buf+20),atoi(buf+23),buf+31,atoi(buf+28));
        } 
        else if(strncmp(buf,"delete p",8) == 0){
            buf[strcspn(buf, "\n")] = 0;
            del_item_primary(nums,scd_p,find_primary(nums,scd_p,atoi(buf+9),atoi(buf+11),atoi(buf+14)));
        } 
        else if(strncmp(buf,"delete d",8) == 0){
            buf[strcspn(buf, "\n")] = 0;
            del_item_day(nums,sec,find_day(nums,sec,atoi(buf+15),atoi(buf+18),atoi(buf+21),atoi(buf+9),atoi(buf+12)));
        } 
        else if(strncmp(buf,"delete w",8) == 0){
            buf[strcspn(buf, "\n")] = 0;
            del_item_week(nums,sec,find_week(nums,sec,atoi(buf+9),atoi(buf+12),atoi(buf+15),buf+20));
        }
        else if(strncmp(buf,"delete m",8) == 0){
            buf[strcspn(buf, "\n")] = 0;
            del_item_month(nums,sec,find_month(nums,sec,atoi(buf+9),atoi(buf+12),buf+17));
        }
        else if(strncmp(buf,"delete s",8) == 0){
            buf[strcspn(buf, "\n")] = 0;
            del_item_special(nums,sec,find_special(nums,sec,atoi(buf+9),atoi(buf+12),atoi(buf+15),atoi(buf+20),atoi(buf+23),atoi(buf+26),buf+31));
        }

    }
    printf("\n");

    commit_scd_count(nums); commit_items_primary(nums,scd_p); commit_items_day(nums,sec); commit_items_week(nums,sec); commit_items_month(nums,sec); commit_items_special(nums,sec);

    free(ct); free(scd_p); free(scd_d); free(scd_w); free(scd_m); free(scd_s); free(sec); free(nums);

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

int compare_events_p(struct scd_item_p* scd_p, int a, int b){
    struct scd_item_p* si_a = (void *) scd_p + sizeof(*scd_p)*a;
    struct scd_item_p* si_b = (void *) scd_p + sizeof(*scd_p)*b;

    if(si_a->hour < si_b->hour || (si_a->hour == si_b->hour && si_a->min < si_b->min)) return 1;
    else return 0;
}

int compare_events_d(struct secondaries* sec, int a, int b){
    struct scd_item_p* si_a = (void *) sec->scd_d + sizeof(*(sec->scd_d))*a;
    struct scd_item_p* si_b = (void *) sec->scd_d + sizeof(*(sec->scd_d))*b;

    if(si_a->hour < si_b->hour || (si_a->hour == si_b->hour && si_a->min < si_b->min)) return 1;
    else return 0;
}


void get_clock(char* line, int* h, int* m, int off){
    *h = 10*(line[3+off]-'0') + line[4+off]-'0';
    *m = 10*(line[6+off]-'0') + line[7+off]-'0';
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

    if(h<10){
        time_s[0] = '0';
        time_s[1] = h+'0';
    } else {
        time_s[0] = (h-(h%10))/10 + '0';
        time_s[1] = (h%10)+'0'; 
    }
    time_s[2] = ':';
    if(m<10){
        time_s[3] = '0';
        time_s[4] = m+'0';
    } else {
        time_s[3] = (m-(m%10))/10 + '0';
        time_s[4] = (m%10)+'0'; 
    }
    time_s[5]='\0';
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

    int n = 0;

    fp = fopen("base/primary","r");

    while(fgets(line,53,fp)){
        
        csi = (void *) scd_p + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        csi->day_of_week = line[0]-'0';
        csi->block = 10*(line[2]-'0')+(line[3]-'0');

        csi->mode = 10*(line[11]-'0')+(line[12]-'0');

        get_clock(line,&(csi->hour),&(csi->min),2);   
        strcpy(csi->name,line+14);

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

        csi = (void *) scd_d + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        csi->day = 10*(line[9]-'0') + (line[10]-'0');
        csi->month = 10*(line[12]-'0') + (line[13]-'0');
        csi->year = 1000*(line[15]-'0') + 100*(line[16]-'0') + 10*(line[17]-'0') + (line[18]-'0');
        
        csi->mode = 10*(line[20]-'0')+(line[21]-'0');
        csi->block = 10*(line[0]-'0')+(line[1]-'0');

        get_clock(line,&(csi->hour),&(csi->min),0);
        strcpy(csi->name,line+23);

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
        
        csi = (void *) scd_w + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        csi->day = 10*(line[0]-'0') + (line[1]-'0');
        csi->month = 10*(line[3]-'0') + (line[4]-'0');
        csi->year = 1000*(line[6]-'0') + 100*(line[7]-'0') + 10*(line[8]-'0') + (line[9]-'0');

        csi->mode = 10*(line[11]-'0')+(line[12]-'0');

        strcpy(csi->name,line+14);

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
        
        csi = (void *) scd_m + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        csi->month = 10*(line[0]-'0') + (line[1]-'0');
        csi->year = 1000*(line[3]-'0') + 100*(line[4]-'0') + 10*(line[5]-'0') + (line[6]-'0');

        csi->mode = 10*(line[8]-'0')+(line[9]-'0');

        strcpy(csi->name,line+11);

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

        csi = (void *) scd_s + scd_len*n;
        line[strcspn(line, "\n")] = 0;

        csi->day_s = 10*(line[0]-'0') + (line[1]-'0');
        csi->month_s = 10*(line[3]-'0') + (line[4]-'0');
        csi->year_s = 1000*(line[6]-'0') + 100*(line[7]-'0') + 10*(line[8]-'0') + (line[9]-'0');
        csi->day_e = 10*(line[11]-'0') + (line[12]-'0');
        csi->month_e = 10*(line[14]-'0') + (line[15]-'0');
        csi->year_e = 1000*(line[17]-'0') + 100*(line[18]-'0') + 10*(line[19]-'0') + (line[20]-'0');

        csi->mode = 10*(line[22]-'0')+(line[23]-'0');

        strcpy(csi->name,line+25);

        n++;
    }
    fclose(fp);
}

int day_items(int page, struct scd_count* nums, struct scd_item_p* scd_p, struct secondaries* sec, int d, int m, int y){
    
    struct scd_item_p* csi_p = NULL;
    struct scd_item_d* csi_d = NULL;
    struct scd_item_w* csi_w = NULL;
    struct scd_item_m* csi_m = NULL;
    struct scd_item_s* csi_s = NULL;

    int scd_p_len = sizeof(*scd_p);
    int scd_d_len = sizeof(*(sec->scd_d));
    int scd_w_len = sizeof(*(sec->scd_w));
    int scd_m_len = sizeof(*(sec->scd_m));
    int scd_s_len = sizeof(*(sec->scd_s));

    int dw = day_of_week(d,m,y);

    char dw_s[17];
    char col[11];
    char time_s[11];
    int has_entry = 0;
    int has_also = 0;

    day_of_week_convert(dw,dw_s,0);

    int ps = 13;
    int c = 0;
    int min = (page-1)*(ps-6);
    int max = page*(ps-6)-1;

    int l1[37];
    int l2[37];

    int k = 0;

    printf("\n%sSchedule for %s%s\n\n",BWHT,dw_s,COLOUR_RESET); 

    for(int x = 0; x < nums->num_p; x++){
        csi_p = (void *) scd_p + scd_p_len*x;

        mode_colour(csi_p->mode,col);
        time_convert(csi_p->hour,csi_p->min,time_s);

        if(csi_p->day_of_week == dw){
            if(has_also == 0) has_also++;
            l1[k] = x; k++;
            has_entry = 1;
        } 
    }

    int k2 = 0;

    for(int x = 0; x < nums->num_d; x++){
        csi_d = (void *) sec->scd_d + scd_d_len*x;

        mode_colour(csi_d->mode,col);
        time_convert(csi_d->hour,csi_d->min,time_s);

        if((csi_d->day == d) && (csi_d->month == m)  && (csi_d->year == y)){
            if(has_also == 1) has_also++;
            l2[k2] = x; k2++;
            has_entry = 1;
        }
    }

    int min_1;
    int min_index_1;
    int min_2;
    int min_index_2;
    int temp;

    for(int i = 0; i < k-1; i++){
        min_1 = l1[i];
        min_index_1 = i;

        for(int j = i; j < k; j++){
            if(compare_events_p(scd_p,l1[j],min_1)){
                min_1 = l1[j];
                min_index_1 = j;
            } 
        }   
        temp = l1[i];
        l1[i] = min_1;
        l1[min_index_1] = temp;
    }

    for(int i = 0; i < k2-1; i++){
        min_2 = l2[i];
        min_index_2 = i;

        for(int j = i; j < k2; j++){
            if(compare_events_d(sec,l2[j],min_2)){
                min_2 = l2[j];
                min_index_2 = j;
            } 
        }   
        temp = l2[i];
        l2[i] = min_2;
        l2[min_index_2] = temp;
    }
    
    for(int i = 0 ; i < k; i++){
        mode_colour(csi_p->mode,col);
        time_convert(csi_p->hour,csi_p->min,time_s);
        if(c >= min && c <= max) printf("  %s\t%s%s%s %s\n",time_s,COLOUR_RESET,col,csi_p->name,COLOUR_RESET);
        c++;
        csi_p = (void *) scd_p + scd_p_len*(l1[i]);   
    }

    if(has_also == 2){
        if(c >= min && c <= max) printf("\n");  
        c++;
    } 

    for(int i = 0 ; i < k2; i++){
        mode_colour(csi_d->mode,col);
        time_convert(csi_d->hour,csi_d->min,time_s);
        if(c >= min && c <= max) printf("  %s\t%s%s%s %s\n",time_s,COLOUR_RESET,col,csi_d->name,COLOUR_RESET);
        c++;
        csi_d = (void *) (sec->scd_d) + scd_d_len*(l2[i]);  
    }

    if(has_entry){
        if(c >= min && c <= max) printf("\n");  
        c++;
    } 

    int d_sun, m_sun, y_sun;
    nearest_sunday(d,m,y,&d_sun,&m_sun,&y_sun);

    for(int x = 0; x < nums->num_w; x++){
        csi_w = (void *) sec->scd_w + scd_w_len*x;

        mode_colour(csi_w->mode,col);

        if((csi_w->day == d_sun) && (csi_w->month == m_sun)  && (csi_w->year == y_sun)){
            if(c >= min && c <= max) printf("   WEEK\t%s%s%s %s\n",COLOUR_RESET,col,csi_w->name,COLOUR_RESET);
            c++;
        }
    }

    for(int x = 0; x < nums->num_m; x++){
        csi_m = (void *) sec->scd_m + scd_m_len*x;

        mode_colour(csi_m->mode,col);

        if(csi_m->month == m){ 
            if(c >= min && c <= max) printf("  MONTH\t%s%s%s %s\n",COLOUR_RESET,col,csi_m->name,COLOUR_RESET);
            c++;
        }
    }

    for(int x = 0; x < nums->num_s; x++){
        csi_s = (void *) sec->scd_s + scd_s_len*x;

        mode_colour(csi_s->mode,col);
        if(within_range(csi_s,d,m,y)){
            if(c >= min && c <= max) printf("   SPEC\t%s%s%s %s\n",COLOUR_RESET,col,csi_s->name,COLOUR_RESET);
            c++;
        }    
    }

    if(page == (c-1)/(ps-6)+1){
        for(int x = 0; x < (ps-6)-(c%(ps-6)); x++){
            printf("\n");
        }
    }

    printf("\n%sPage %i/%i%s\t\n\n",BWHT,page,(c-1)/(ps-6)+1,COLOUR_RESET);

    return (c-1)/(ps-6)+1;
}

void add_item_primary(struct scd_count* nums, struct scd_item_p* scd_p, int block, int hour, int min, int day_of_week, char* name, int mode){
    
    struct scd_item_p* csi = NULL;
    int scd_p_len = sizeof(*scd_p);

    csi = (void *) scd_p + scd_p_len*(nums->num_p);
    nums->num_p++;

    csi->block = block;
    csi->hour = hour;
    csi->min = min;
    csi->day_of_week = day_of_week;

    strncpy(csi->name,name,strlen(name));
    csi->mode = mode;

}

void add_item_day(struct scd_count* nums, struct secondaries* sec, int block, int hour,  int min, int day, int month, int year, char* name, int mode){
    
    struct scd_item_d* csi = NULL;
    int scd_d_len = sizeof(*(sec->scd_d));

    csi = (void *) sec->scd_d + scd_d_len*(nums->num_d);
    nums->num_d++;

    csi->block = block;
    csi->hour = hour;
    csi->min = min;
    csi->day = day;
    csi->month = month;
    csi->year = year;

    strncpy(csi->name,name,strlen(name));
    csi->mode = mode;
}

void add_item_week(struct scd_count* nums, struct secondaries* sec, int day, int month, int year, char* name, int mode){
    
    struct scd_item_w* csi = NULL;
    int scd_w_len = sizeof(*(sec->scd_w));

    csi = (void *) sec->scd_w + scd_w_len*(nums->num_w);
    nums->num_w++;

    csi->day = day;
    csi->month = month;
    csi->year = year;

    strncpy(csi->name,name,strlen(name));
    csi->mode = mode;
}

void add_item_month(struct scd_count* nums, struct secondaries* sec, int month, int year, char* name, int mode){
    
    struct scd_item_m* csi = NULL;
    int scd_m_len = sizeof(*(sec->scd_m));

    csi = (void *) sec->scd_m + scd_m_len*(nums->num_m);
    nums->num_m++;

    csi->month = month;
    csi->year = year;

    strncpy(csi->name,name,strlen(name));
    csi->mode = mode;
}

void add_item_special(struct scd_count* nums, struct secondaries* sec, int day_s, int month_s, int year_s, int day_e, int month_e, int year_e, char* name, int mode){
    
    struct scd_item_s* csi = NULL;
    int scd_s_len = sizeof(*(sec->scd_s));

    csi = (void *) (sec->scd_s) + scd_s_len*(nums->num_s);
    nums->num_s++;

    csi->day_s = day_s;
    csi->month_s = month_s;
    csi->year_s = year_s;
    csi->day_e = day_e;
    csi->month_e = month_e;
    csi->year_e = year_e;


    strncpy(csi->name,name,strlen(name));
    csi->mode = mode;
}


void load_tm(struct tm* ct){

    time_t current_time;
    char* current_time_s;

    current_time = time(NULL);
    current_time_s = ctime(&current_time);

    strptime(current_time_s, "%a %h %d %H:%M:%S %Y", ct);
}

int find_primary(struct scd_count* nums, struct scd_item_p* scd_p, int dw, int hour, int min){
    
    struct scd_item_p* csi = NULL;
    int scd_p_len = sizeof(*scd_p);
    
    for(int i = 0; i < nums->num_p; i++){
        csi = (void *) scd_p + scd_p_len*i;
        if(csi->hour == hour && csi->min == min && csi->day_of_week == dw){
            return i;
        }
    }
    return -1;
 
}

int find_day(struct scd_count* nums, struct secondaries* sec, int d, int m, int y, int hour, int min){

    struct scd_item_d* csi = NULL;
    int scd_d_len = sizeof(*(sec->scd_d));

    for(int i = 0; i < nums->num_d; i++){
        csi = (void *) (sec->scd_d) + scd_d_len*i;
        if(csi->hour == hour && csi->min == min && csi->day == d && csi->month == m && csi->year == y){
            return i;
        }
    }
    return -1;

}

int find_week(struct scd_count* nums, struct secondaries* sec, int d, int m, int y, char* name){
    
    struct scd_item_w* csi = NULL;
    int scd_w_len = sizeof(*(sec->scd_w));

    for(int i = 0; i < nums->num_w; i++){
        csi = (void *) (sec->scd_w) + scd_w_len*i;
        if(csi->day == d && csi->month == m && csi->year == y && strncmp(name,csi->name,strlen(csi->name)) == 0){
            return i;
        }
    }
    return -1;
}

int find_month(struct scd_count* nums, struct secondaries* sec, int m, int y, char* name){
    
    struct scd_item_m* csi = NULL;
    int scd_m_len = sizeof(*(sec->scd_m));

    for(int i = 0; i < nums->num_m; i++){
        csi = (void *) (sec->scd_m) + scd_m_len*i;
        if(csi->month == m && csi->year == y && strncmp(name,csi->name,strlen(csi->name)) == 0){
            return i;
        }
    }
    return -1;   
}

int find_special(struct scd_count* nums, struct secondaries* sec, int d_s, int m_s, int y_s, int d_e, int m_e, int y_e, char* name){
        
    struct scd_item_s* csi = NULL;
    int scd_s_len = sizeof(*(sec->scd_s));

    for(int i = 0; i < nums->num_s; i++){
        csi = (void *) (sec->scd_s) + scd_s_len*i;
        if(csi->day_s == d_s && csi->month_s == m_s && csi->year_s == y_s && csi->day_e == d_e && csi->month_e == m_e && csi->year_e == y_e && strncmp(name,csi->name,strlen(csi->name))==0){
            return i;
        }
    }
    return -1;
}

void del_item_primary(struct scd_count* nums, struct scd_item_p* scd_p, int i){
    
    struct scd_item_p* csi = NULL;
    int scd_p_len = sizeof(*scd_p);
    int buffer_size_p = scd_p_len*(nums->num_p)*2;

    csi = (void *) scd_p + scd_p_len*i;

    memmove(csi,(void *)csi+scd_p_len,buffer_size_p-(i+1)*scd_p_len);

    nums->num_p--;
}

void del_item_day(struct scd_count* nums, struct secondaries* sec, int i){

    struct scd_item_d* csi = NULL;
    int scd_d_len = sizeof(*(sec->scd_d));

    int buffer_size_d = scd_d_len*(nums->num_d)*2;

    csi = (void *) (sec->scd_d) + scd_d_len*i;

    memmove(csi,(void *)csi+scd_d_len,buffer_size_d-(i+1)*scd_d_len);

    nums->num_d--;
}

void del_item_week(struct scd_count* nums, struct secondaries* sec, int i){

    struct scd_item_w* csi = NULL;
    int scd_w_len = sizeof(*(sec->scd_w));

    int buffer_size_w = scd_w_len*(nums->num_w)*2;

    csi = (void *) (sec->scd_w) + scd_w_len*i;

    memmove(csi,(void *)csi+scd_w_len,buffer_size_w-(i+1)*scd_w_len);

    nums->num_w--;
}

void del_item_month(struct scd_count* nums, struct secondaries* sec, int i){

    struct scd_item_m* csi = NULL;
    int scd_m_len = sizeof(*(sec->scd_m));

    int buffer_size_m = scd_m_len*(nums->num_m)*2;

    csi = (void *) (sec->scd_m) + scd_m_len*i;

    memmove(csi,(void *)csi+scd_m_len,buffer_size_m-(i+1)*scd_m_len);

    nums->num_s--;
}

void del_item_special(struct scd_count* nums, struct secondaries* sec, int i){

    struct scd_item_s* csi = NULL;
    int scd_s_len = sizeof(*(sec->scd_s));

    int buffer_size_s = scd_s_len*(nums->num_s)*2;

    csi = (void *) (sec->scd_s) + scd_s_len*i;

    memmove(csi,(void *)csi+scd_s_len,buffer_size_s-(i+1)*scd_s_len);

    nums->num_s--;
}

void commit_items_primary(struct scd_count* nums, struct scd_item_p* scd_p){

    FILE *fp;
    fp = fopen("base/primary","w");

    struct scd_item_p* csi = NULL;
    int scd_p_len = sizeof(*scd_p);

    for(int i = 0 ; i < nums->num_p; i++){
        csi = (void *) scd_p + scd_p_len*i;

        fprintf(fp,"%i ",csi->day_of_week);
        if(csi->block < 10) fprintf(fp,"0%i ",csi->block); else fprintf(fp,"%i ",csi->block);
        if(csi->hour < 10) fprintf(fp,"0%i:",csi->hour); else fprintf(fp,"%i:",csi->hour);
        if(csi->min < 10) fprintf(fp,"0%i ",csi->min); else fprintf(fp,"%i ",csi->min);
        if(csi->mode < 10) fprintf(fp,"0%i ",csi->mode); else fprintf(fp,"%i ",csi->mode);
        fprintf(fp,"%s",csi->name);

        if(nums->num_p - 1 != i) fprintf(fp,"\n");
    }

    fclose(fp);
}

void commit_items_day(struct scd_count* nums, struct secondaries* sec){

    FILE *fp;
    fp = fopen("base/sec_day","w");

    struct scd_item_d* csi = NULL;
    int scd_d_len = sizeof(*(sec->scd_d));


    for(int i = 0 ; i < nums->num_d; i++){
        csi = (void *) (sec->scd_d) + scd_d_len*i;

        if(csi->block < 10) fprintf(fp,"0%i ",csi->block); else fprintf(fp,"%i ",csi->block);
        if(csi->hour < 10) fprintf(fp,"0%i:",csi->hour); else fprintf(fp,"%i:",csi->hour);
        if(csi->min < 10) fprintf(fp,"0%i ",csi->min); else fprintf(fp,"%i ",csi->min);
        if(csi->day < 10) fprintf(fp,"0%i ",csi->day); else fprintf(fp,"%i ",csi->day);
        if(csi->month < 10) fprintf(fp,"0%i ",csi->month); else fprintf(fp,"%i ",csi->month);
        if(csi->year < 10) fprintf(fp,"000%i ",csi->year);
        else if(csi->year < 100) fprintf(fp,"00%i ",csi->year);
        else if(csi->year < 1000) fprintf(fp,"0%i ",csi->year);
        else fprintf(fp,"%i ",csi->year);
        if(csi->mode < 10) fprintf(fp,"0%i ",csi->mode); else fprintf(fp,"%i ",csi->mode);

        fprintf(fp,"%s",csi->name);

        if(nums->num_d - 1 != i) fprintf(fp,"\n");
    }

    fclose(fp);
}

void commit_items_week(struct scd_count* nums, struct secondaries* sec){

    FILE *fp;
    fp = fopen("base/sec_week","w");

    struct scd_item_w* csi = NULL;
    int scd_w_len = sizeof(*(sec->scd_w));

    for(int i = 0 ; i < nums->num_w; i++){
        csi = (void *) (sec->scd_w) + scd_w_len*i;

        if(csi->day < 10) fprintf(fp,"0%i ",csi->day); else fprintf(fp,"%i ",csi->day);
        if(csi->month < 10) fprintf(fp,"0%i ",csi->month); else fprintf(fp,"%i ",csi->month);
        if(csi->year < 10) fprintf(fp,"000%i ",csi->year);
        else if(csi->year < 100) fprintf(fp,"00%i ",csi->year);
        else if(csi->year < 1000) fprintf(fp,"0%i ",csi->year);
        else fprintf(fp,"%i ",csi->year);
        if(csi->mode < 10) fprintf(fp,"0%i ",csi->mode); else fprintf(fp,"%i ",csi->mode);

        fprintf(fp,"%s",csi->name);

        if(nums->num_w - 1 != i) fprintf(fp,"\n");
    }

    fclose(fp);
}

void commit_items_month(struct scd_count* nums, struct secondaries* sec){

    FILE *fp;
    fp = fopen("base/sec_month","w");

    struct scd_item_m* csi = NULL;
    int scd_m_len = sizeof(*(sec->scd_m));

    for(int i = 0 ; i < nums->num_m; i++){
        csi = (void *) (sec->scd_m) + scd_m_len*i;

        if(csi->month < 10) fprintf(fp,"0%i ",csi->month); else fprintf(fp,"%i ",csi->month);
        if(csi->year < 10) fprintf(fp,"000%i ",csi->year);
        else if(csi->year < 100) fprintf(fp,"00%i ",csi->year);
        else if(csi->year < 1000) fprintf(fp,"0%i ",csi->year);
        else fprintf(fp,"%i ",csi->year);
        if(csi->mode < 10) fprintf(fp,"0%i ",csi->mode); else fprintf(fp,"%i ",csi->mode);

        fprintf(fp,"%s",csi->name);

        if(nums->num_m - 1 != i) fprintf(fp,"\n");
    }

    fclose(fp);
}

void commit_items_special(struct scd_count* nums, struct secondaries* sec){

    FILE *fp;
    fp = fopen("base/sec_special","w");

    struct scd_item_s* csi = NULL;
    int scd_s_len = sizeof(*(sec->scd_s));

    for(int i = 0 ; i < nums->num_s; i++){
        csi = (void *) (sec->scd_s) + scd_s_len*i;

        if(csi->day_s < 10) fprintf(fp,"0%i ",csi->day_s); else fprintf(fp,"%i ",csi->day_s);
        if(csi->month_s < 10) fprintf(fp,"0%i ",csi->month_s); else fprintf(fp,"%i ",csi->month_s);
        if(csi->year_s < 10) fprintf(fp,"000%i ",csi->year_s);
        else if(csi->year_s < 100) fprintf(fp,"00%i ",csi->year_s);
        else if(csi->year_s < 1000) fprintf(fp,"0%i ",csi->year_s);
        else fprintf(fp,"%i ",csi->year_s);
        if(csi->day_e < 10) fprintf(fp,"0%i ",csi->day_e); else fprintf(fp,"%i ",csi->day_e);
        if(csi->month_e < 10) fprintf(fp,"0%i ",csi->month_e); else fprintf(fp,"%i ",csi->month_e);
        if(csi->year_e < 10) fprintf(fp,"000%i ",csi->year_e);
        else if(csi->year_e < 100) fprintf(fp,"00%i ",csi->year_e);
        else if(csi->year_e < 1000) fprintf(fp,"0%i ",csi->year_e);
        else fprintf(fp,"%i ",csi->year_e);        
        if(csi->mode < 10) fprintf(fp,"0%i ",csi->mode); else fprintf(fp,"%i ",csi->mode);

        fprintf(fp,"%s",csi->name);

        if(nums->num_s - 1 != i) fprintf(fp,"\n");
    }

    fclose(fp);
}