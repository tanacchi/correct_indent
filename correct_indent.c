#include <stdio.h>
#include <string.h>

#define MAX 8000

void flat_string(char src[], char artifact[]);
void replace_newline(char src[], char dest[]);
void del_extra_space(char src[], char dest[]);
int count_head_space(char* src);
int count_tale_space(char* src, int length);
void split_string_space(char* src, char** dest);
int find_next_space(char* src);
int check_tale_char(char* src, char c);
char get_tale_char(char* src);
void put_indent_level(int level);
int find_char(char* src, char c);
void output_vol1(char* src[]);
void output_vol2(char* src[]);

int main(int argc, char* argv[]){

  FILE *fp;

  int i;
  int input_buff;
  
  char reader[MAX] = {0};
  char scanner[MAX] = {0};
  char* array[MAX] = {0};
  
  if((fp=fopen(argv[1], "r")) != NULL){
    for(i = 0; (input_buff = fgetc(fp)) != EOF; i++){
      reader[i] = (char)input_buff;
    }
  }

  printf("\n\n[%s]\n\n", reader);
  
  replace_newline(reader, scanner);

  printf("\n\n[%s]\n\n", scanner);
  
  del_extra_space(scanner, reader);

  printf("\n\n[%s]\n\n", reader);

  split_string_space(reader, array);


  for (i = 0; array[i] != '\0'; i++){
    printf("%s\n", array[i]);
  }
  putchar('\n');
  
  for (i = 0; array[i] != '\0'; i++){
    printf("%d\n", strlen(array[i]));
  }
  putchar('\n');
  
  output_vol1(array); 

  return 0;
 }

void replace_newline(char src[], char dest[]){
  int i;
  for (i = 0; src[i] != '\0'; i++){
    if(src[i] == '\n') dest[i] = ' ';
    else dest[i] = src[i];
  }
  dest[i+1] = '\0';
}

int count_head_space(char* src) {
  int count;
  for (count = 0; src[count] == ' '; count++);
  return count;
}

int count_tale_space(char* src, int length){
  int i, count;
  for (i = length -1; src[i] == ' '; i--);
  return length - 1 - i;
}

void del_extra_space(char src[], char dest[]){
  int i, j = 0;
  const int head_space_count = count_head_space(src);
  for (i = head_space_count; src[i] != '\0'; i++){
    if ((src[i] != ' ') || (src[i+1] != ' ')){ 
      dest[j] = src[i];
      j++;
    }
  }
  const int tale_space_count = count_tale_space(dest, j);
  dest[j - tale_space_count] = '\0';
}

void split_string_space(char* src, char** dest){
  int i;
  int offset = 0;
  int brank;

  for (i = 0; (brank = find_next_space(src + offset)) != -1; i++){
    dest[i] = src + offset;
    offset += brank + 1;
    dest[i][brank] = '\0';
  }
  dest[i] = src + offset;
  dest[i+1] = NULL;
}

int find_next_space(char* src){
  int count;
  for (count = 0; src[count] != ' '; count++)
    if (src[count] == '\0') return -1;
  return count;
}


void output_vol1(char* src[]){
  int i;
  int level = 0;
  
  for (i = 0; src[i] != NULL; i++){
    
    if (find_char(src[i], '{')){
      printf("%s\n", src[i]);
      level++;
    }
    else if (!strcmp(src[i], "}")){
      level--;
      put_indent_level(level);
      printf("%s\n", src[i]);
    } 
    else{
      put_indent_level(level);
      if (!strcmp(src[i], "#include")){
	printf("%s %s\n", src[i], src[i+1]);
	i++;
      }
      else if (!strcmp(src[i], "#define")){
	printf("%s %s %s\n", src[i], src[i+1], src[i+2]);
	i += 2;
      }
      else if (!strcmp(src[i], "int")){
	if (!(strcmp(src[i+1], "main(void)"))){
	  printf("%s %s", src[i], src[i+1]);
	  i++;
	}
	else{
	  while (!check_tale_char(src[i], ';')){
	    printf("%s ", src[i]);
	    i++;
	  }
	  printf("%s\n", src[i]);
	}
      }
      else if (!strcmp(src[i], "for")){
	while (!check_tale_char(src[i], ')')){
	  printf("%s ", src[i]);
	  i++;
	}
	printf("%s", src[i]);
      }
      else if (!strncmp(src[i], "printf", 6)){
	while (!check_tale_char(src[i], ';')){
	  printf("%s ", src[i]);
	  i++;
	}
	printf("%s\n", src[i]);
      }
      else if (!strcmp(src[i], "return")){
	printf("%s %s\n", src[i], src[i+1]);
	i++;
      }
    }
  }
}

void output_vol2(char* src[]){
  
  
  
  
  
  
  
  
}

int check_tale_char(char* src, char c){
  if (get_tale_char(src) == c) return 1;
  else return 0;
}

int get_string_length(char* src){
  char* start_point = src;
  while (*(src++) != '\0') ;
  return src - start_point -1;
}

int get_string_length_vol2(char* src){
  int i;
  for (i = 0; src[i] != '\0'; i++) ;
  return i;
}

char get_tale_char(char* src){
  int length = get_string_length(src);
  if (length == 0) return '\0';
  return src[length - 1];
}

void put_indent_level(int level){
  int i;
  for (i = 0; i < level; i++)
    printf("  ");
}

