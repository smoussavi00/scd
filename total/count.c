#include "count.h"

void load_scd_count(struct scd_count* nums){

    FILE* fp;
    fp = fopen("total/counts","r");

    char line[53];
    int read = 0;
    
    while(fgets(line,52,fp)){

        line[strcspn(line, "\n")] = 0;

        if(strcmp(line,"**SCD") == 0){
            read = 1;
            continue;
        } 
        else if(strncmp(line,"**",2) == 0 && read == 1) break;

        if(read == 1){ 
            if(strncmp(line,"num_p",5) == 0) nums->num_p = atoi(&line[strlen("num_p")+1]);
            else if(strncmp(line,"num_docket",10) == 0) nums->num_docket = atoi(&line[strlen("num_docket")+1]);
            else if(strncmp(line,"num_d",5) == 0) nums->num_d = atoi(&line[strlen("num_d")+1]);
            else if(strncmp(line,"num_w",5) == 0) nums->num_w = atoi(&line[strlen("num_w")+1]);
            else if(strncmp(line,"num_m",5) == 0) nums->num_m = atoi(&line[strlen("num_m")+1]);
            else if(strncmp(line,"num_s",5) == 0) nums->num_s = atoi(&line[strlen("num_s")+1]);            
        } 
    }
    fclose(fp);
}
