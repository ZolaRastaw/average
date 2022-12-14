// C program for generating a
// random number in a given range.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define row 1000
#define column 1000
int main()
{
    char path[] = ".\\input\\test file\\data.txt";
    FILE *fp  = fopen(path, "r+");
    if(!fp){
        printf("file : %s  not found",path);
    }else{
        char output[255];
        int min = 0;
        int max = 10000000;
        // Use current time as
        // seed for random generator
        srand(time(0));
        
        for (int i = 0; i < row; i++) {
            char tempRow[row*column]="";//create an empty string   
            for(int j=0;j<column;j++){
                //the first part will generate integer between min to max, the second part add floating point
                float num = (rand() %(max - min + 1)+min) + ((float)rand()/(float)(RAND_MAX));
                char tempCol[255];
                //covert float to string
                sprintf(tempCol,"%f,",num);
                if(j==column-1){
                    sprintf(tempCol,"%f\n",num);
                }
                //add column to row
                strcat(tempRow,tempCol);
            }
            printf("%s",tempRow);
            fputs(tempRow,fp);
        }
    }
    fclose(fp);
    return 0;
}