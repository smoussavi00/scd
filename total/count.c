#include "count.h"

void load_scd_count(struct scd_count* nums){

    FILE* fp;
    fp = fopen("total/counts","r");

    char line[53];
    
    while(fgets(line,53,fp)){

        line[strcspn(line, "\n")] = 0;

        if(strncmp(line,"num_p",5) == 0) nums->num_p = atoi(&line[strlen("num_p")+1]);
        else if(strncmp(line,"num_d",5) == 0) nums->num_d = atoi(&line[strlen("num_d")+1]);
        else if(strncmp(line,"num_w",5) == 0) nums->num_w = atoi(&line[strlen("num_w")+1]);
        else if(strncmp(line,"num_m",5) == 0) nums->num_m = atoi(&line[strlen("num_m")+1]);
        else if(strncmp(line,"num_s",5) == 0) nums->num_s = atoi(&line[strlen("num_s")+1]);            
    
    }
    fclose(fp);
}

void commit_scd_count(struct scd_count* nums){
    FILE *fp;
    fp = fopen("total/counts","w");

    fprintf(fp,"num_p %i\n",nums->num_p);
    fprintf(fp,"num_d %i\n",nums->num_d);
    fprintf(fp,"num_w %i\n",nums->num_w);
    fprintf(fp,"num_m %i\n",nums->num_m);
    fprintf(fp,"num_s %i",nums->num_s);

    fclose(fp);
}
