#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 1025

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

int main(int argc, char** argv) {
  
  if (argc < 2) { puts("Please set a sourse file !"); return -1; }

  FILE* fp;
  if ((fp = fopen(argv[1], "r")) == NULL) { puts("Sorry, could not open the file"); return -2; }

  char input_string[MAX_WIDTH];
  read_souse_file(fp, input_string);

  char newline_none[MAX_WIDTH];
  remove_newline(input_string, newline_none);

  puts(newline_none);
  
  return 0;
}
