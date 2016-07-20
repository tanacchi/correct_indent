#include <stdio.h>

#define MAX 1024

void flat_string(char src[], char artifact[]);

int main(void){

  FILE *fp;

  int input_buff;

  char reader[MAX] = {0};
  char scanner[MAX] = {0};
  char output[MAX] = {0};

  if((fp=fopen("work.c", "r")) != NULL){
    int i;
    for(i = 0; (input_buff = fgetc(fp)) != EOF; i++){
      reader[i] = (char)input_buff;
    }
  }

  printf("\n\n printf = [%s]\n\n", reader);

  flat_string(reader, scanner);

  printf("\n\n[%s]\n\n", scanner);

  return 0;
 }
