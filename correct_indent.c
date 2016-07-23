#include <stdio.h>

#define MAX 1024

void flat_string(char src[], char artifact[]);
void replace_newline(char src[], char dist[]);
void del_extra_space(char src[], char dist[]);

int main(void){

  FILE *fp;

  int input_buff;

  char reader[MAX] = {0};
  char scanner[MAX] = {0};
  char output[MAX] = {0};

  if((fp=fopen("C:\\Users\\bata\\Desktop\\work.c", "r")) != NULL){
    int i;
    for(i = 0; (input_buff = fgetc(fp)) != EOF; i++){
      reader[i] = (char)input_buff;
    }
  }

  printf("\n\nprintf = [%s]\n\n", reader);

  //flat_string(reader, scanner);
  replace_newline(reader, scanner);
 

  printf("\n\n[%s]\n\n", scanner);

  return 0;
 }

void flat_string(char src[], char artifact[]){
  int i;
  for (i = 0; src[i] != '\0'; i++){
    if (src[i] == '\n') artifact[i] = ' ';
    else artifact[i] = src[i];
  }
}

void replace_newline(char src[], char dist[]){
  int i;
  for (i = 0; src[i] != NULL; i++){
    if(src[i] = '\n') dist[i] = ' ';
    else dist[i] = src[i];
  }
  dist[i+1] = '\0';
}
void del_extra_space(char src[], char dist[]){
  int i, j = 0;
  for (i = 0; src[i] != NULL; i++){
    if ((src[i] = ' ') && (src[i+1] = ' ')) ;
    else {
      dist[j] = src[i];
      j++;    
    }
    dist[j+1] = ' ';
  }
}