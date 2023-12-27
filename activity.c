#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct job{
    char jobid[20];
    int starttime;
    int finishtime;
    int compatibility;
};

int numofjobs;
struct job jobs[100];

void readInput(){
    scanf("%d",&numofjobs);
    for(int i=0; i<numofjobs; i++){
        scanf("%s %d %d", jobs[i].jobid, &jobs[i].starttime, &jobs[i].finishtime);
        jobs[i].compatibility = 1;
    }
    for(int i=0; i<numofjobs; i++){
        printf("%s %d %d %d\n", jobs[i].jobid, jobs[i].starttime, jobs[i].finishtime, jobs[i].compatibility);

    }
}

int compare(const void *a, const void *b){
    return ((struct job *)a)->finishtime - ((struct job *)b)->finishtime;
}

void iterative(){
    for(int i=0; i<numofjobs; i++){
        if(jobs[i].compatibility !=0){
            for(int j=i+1; j<numofjobs; j++){
                if(jobs[i].finishtime>jobs[j].starttime){
                    jobs[j].compatibility = 0;
                }
            }
        }
    }
}

void recursiveSelection(int i){
    int m= i+1;
    while(m<=numofjobs && jobs[i].finishtime>jobs[m].starttime){
        jobs[m].compatibility = 0;
        m++;
    }
    if(m<=numofjobs){
        recursiveSelection(m);
    }
    else{
        return;
    }
}

int main(void){
    freopen("input.txt", "r", stdin);
    readInput();
    printf("-------------------------------------------\n");
    qsort(jobs, numofjobs, sizeof(struct job), compare);
    for(int i=0; i<numofjobs; i++){
        printf("%s %d %d %d\n", jobs[i].jobid, jobs[i].starttime, jobs[i].finishtime, jobs[i].compatibility);

    }
    printf("----------------------------------------------\n");
    //iterative();
     recursiveSelection(0);

    for(int i=0; i<numofjobs; i++){
        if(jobs[i].compatibility != 0){
             printf("%s %d %d %d\n", jobs[i].jobid, jobs[i].starttime, jobs[i].finishtime, jobs[i].compatibility);
        }


    }
    return 0;
}