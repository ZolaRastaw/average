#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

//task number 2

#define maxRow 1000
#define maxColumn 1000
#define rowSize maxColumn*255 //size of a row, each row contain 1000 columns with size 255

int main(int argc, char* argv[]) {
	
	clock_t start = clock();

	FILE *fp  = NULL;
	if(argc>1){
		printf("Read file from: %s\n",argv[1]);
		fp  = fopen(argv[1], "r"); // read only 
	}
	else{
		printf("Read file from: .\\input\\test file\\data.txt\n");
		char path[] = ".\\input\\test file\\data.txt";
		fp  = fopen(path, "r"); // read only 
	}
	//create a vector for storing matrix average, set all column to 0
	float output[maxRow]={0}; //i tried to set it to NULL but not working

	if (! fp  ) // equivalent to saying if ( in_file == NULL ) 
	{  
		printf("file unable to open\n");
	}
	else{
		//row
		char buffer[rowSize];
		char comma[2] = ",";//data separate by comma
		float average;
		int i,j;
		float sum =0.0;
		char *token;
#pragma omp parallel for private(buffer,token,j,sum)///each processor take multiple line and fine the average
		for (i =0;i<maxRow; i++)//read every row one row at a time
		{
			fgets(buffer,rowSize,fp);//get one row at a time
			sum = 0.0;
			token = strtok(buffer,comma);
			//run though all the column, 
			//cannot parallel because sum is shared variable
			for (j=0;j<maxColumn;j++){ 
				printf("token: %s\n",token);
				sum = sum + strtof(token, NULL);
				token = strtok(NULL,comma);
			}
			average = sum/j;
			output[i]= average;
		}
		
	}
	
	printf("\nMatrix average:\n");//print out the result, cannot parallel because column have order
	int i =0;
	for (i;i<maxRow;i++){
		printf("%f ", output[i]);
	}
	
	clock_t end = clock();
	double time_spent = (double)(end-start)/CLOCKS_PER_SEC;

	printf("\nTime: %f",time_spent);
	fclose(fp);	
	return 0;
}
