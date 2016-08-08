#include <stdio.h>

#define MAX 4096

void flat_string(char src[], char artifact[]);
void replace_newline(char src[], char dist[]);
void del_extra_space(char src[], char dist[]);
int count_head_space(char* src);
int count_tale_space(char* src, int length);
void split_string_space(char* src, char** dist);
int find_next_space(char* src);

int main(int argc, char* argv[]){

  FILE *fp;

  int i;
  int input_buff;

  char reader[MAX] = {0};
  char scanner[MAX] = {0};
  char* output[MAX] = {0};

  if((fp=fopen(argv[1], "r")) != NULL){
    for(i = 0; (input_buff = fgetc(fp)) != EOF; i++){
      reader[i] = (char)input_buff;
    }
  }


  printf("\n\n[%s]\n\n", reader);
  
  //flat_string(reader, scanner);
  replace_newline(reader, scanner);

  printf("\n\n[%s]\n\n", scanner);
  
  del_extra_space(scanner, reader); 

  printf("\n\n[%s]\n\n", reader);

  split_string_space(reader, output);


  for (i = 0; output[i] != NULL; i++)
    printf("%s\n", output[i]);

  return 0;
 }

void replace_newline(char src[], char dist[]){
  int i;
  for (i = 0; i < 300/* src[i] != '\0'*/; i++){
    if(src[i] == '\n') dist[i] = ' ';
    else dist[i] = src[i];
  }
  dist[i+1] = '\0';
}

int count_head_space(char* src) {
  int count;
  for (count = 0; src[count] == ' '; count++);
  return count;
}

int count_tale_space(char* src, int length){
  int i, count;
  //  for (i = length - 1; src[i] == ' '; i--) count++;
  //  return count;
  for (i = length -1; src[i] == ' '; i--);
  return length - 1 - i;
}

void del_extra_space(char src[], char dist[]){
  int i, j = 0;
  const int head_space_count = count_head_space(src);
  for (i = head_space_count; src[i] != '\0'; i++){
    if ((src[i] != ' ') || (src[i+1] != ' ')){ 
      dist[j] = src[i];
      j++;
    }
  }
  const int tale_space_count = count_tale_space(dist, j);
  dist[j - tale_space_count] = '\0';
}

void split_string_space(char* src, char** dist){
  int i;
  int offset = 0;
  int brank;

  for (i = 0; (brank = find_next_space(src + offset)) != -1; i++){
    dist[i] = src + offset;
    offset += brank + 1;
    dist[i][brank] = '\0';
  }
  dist[i] = src + offset;
  dist[i+1] = NULL;
}

int find_next_space(char* src){
  int count;
  for (count = 0; src[count] != ' '; count++)
    if (src[count] == '\0') return -1;
  return count;
}
