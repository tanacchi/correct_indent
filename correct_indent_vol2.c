#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 100000

int count_head_space(const char*);
int count_tale_space(const char*, const int);
void read_souse_file(FILE* const fp, char* input_string);
void remove_newline(char* input_string, char* newline_none);
void remove_tab(char* newline_none, char* tab_none);
void remove_extra_space(char* tab_none, char* space_less);

void read_souse_file(FILE* const fp, char* input_string) {
  int input_buff;
  int i;
  for (i = 0; (input_buff = fgetc(fp)) != EOF; i++) {
    if (i > MAX_WIDTH - 1) { puts("Too large file !"); exit(-3); }
    input_string[i] = (char)input_buff;
  }
  input_string[++i] = '\0';
}

void remove_newline(char* input_string, char* newline_none) {
  int i;
  for (i = 0; input_string[i] != '\0'; i++)
    if (input_string[i] == '\n') newline_none[i] = ' ';
    else newline_none[i] = input_string[i];
}

void remove_tab(char* newline_none, char* tab_none) {
  int i;
  for (i = 0; newline_none[i] != '\0'; i++)
    if (newline_none[i] == '\t') newline_none[i] = ' ';
    else tab_none[i] = newline_none[i];
}

void remove_extra_space(char* tab_none, char* space_less) {
  int i, j = 0;
  static char copy_buff = '\n';
  for (i = count_head_space(tab_none); tab_none[i] != '\0'; i++) {
    if (copy_buff == ' ' && tab_none[i] == ' ') ;
    else space_less[j++] = tab_none[i];
    copy_buff = tab_none[i];
  }
  space_less[j - count_tale_space(space_less, j)] = '\0';
}
 
int main(int argc, char** argv) {
  
  if (argc < 2) { puts("Please set a sourse file !"); return -1; }

  FILE* fp;
  if ((fp = fopen(argv[1], "r")) == NULL) { puts("Sorry, could not open the file"); return -2; }

  char input_string[MAX_WIDTH];
  read_souse_file(fp, input_string);

  char newline_none[MAX_WIDTH];
  remove_newline(input_string, newline_none);

  char tab_none[MAX_WIDTH];
  remove_tab(newline_none, tab_none);

  char space_less[MAX_WIDTH];
  remove_extra_space(tab_none, space_less);

  puts(space_less);
  
  return 0;
}

int count_head_space(const char* src) {
  int count = 0;
  while (src[count] == ' ') count++;
  return count;
}

int count_tale_space(const char* src, const int prev_tale) {
  int i = prev_tale;
  while (src[i] == ' ') i--;
  return prev_tale - i + 1;
}
