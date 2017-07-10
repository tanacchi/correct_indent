#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH    10000
#define INDENT_WIDTH 2

typedef struct code_status_t {
  int parenthesis_diff; // ()
  int bracket_diff;     // []
  int curly_diff;       // {}
  int angle_diff;       // <>
  
  int single_quot_num;
  int double_quot_num; 

  char current_char;
  char prev_char;
  
} CodeStatus;

void read_souse_file(FILE* const, char*);
void replace_newline(const char*, char*);
void replace_tab(const char*, char*);
void remove_extra_space(const char*, char*);
void set_status(const char*, CodeStatus*);
void corrent_indent(const CodeStatus*, char*);

const int count_head_space(const char*);
const int count_tale_space(const char*, const int);
const int get_string_length(const char*);

void read_souse_file(FILE* const fp, char* input_string) {
  int input_buff;
  int i;
  for (i = 0; (input_buff = fgetc(fp)) != EOF; i++) {
    if (i > MAX_WIDTH - 1) { puts("Too large file !"); exit(-3); }
    input_string[i] = (char)input_buff;
  }
  input_string[i] = '\0';
}

void replace_newline(const char* input_string, char* newline_none) {
  int i;
  for (i = 0; input_string[i] != '\0'; i++)
    if (input_string[i] == '\n') newline_none[i] = ' ';
    else newline_none[i] = input_string[i];
}

void replace_tab(const char* newline_none, char* tab_none) {
  int i;
  for (i = 0; newline_none[i] != '\0'; i++)
    if (newline_none[i] == '\t') tab_none[i] = ' ';
    else tab_none[i] = newline_none[i];
}

void remove_extra_space(const char* tab_none, char* extra_space_none) {
  int i, j = 0;
  char copy_buff = '\0';
  for (i = count_head_space(tab_none); tab_none[i] != '\0'; i++) {
    if (copy_buff == ' ' && tab_none[i] == ' ') ;
    else extra_space_none[j++] = tab_none[i];
    copy_buff = tab_none[i];
  }
  extra_space_none[j - count_tale_space(extra_space_none, j)] = '\0';
}

void set_status(const char* extra_space_none, CodeStatus* status) {
  const CodeStatus initializer = {0, 0, 0, 0, 0, 0, '\0', '\0'};
  status[0] = initializer;
  int i;
  char target_c;
  for (i = 0; i < MAX_WIDTH-2 && (target_c = extra_space_none[i]) != '\0'; i++) {
    if (i > 0) {
      status[i] = status[i-1]; status[i];
      status[i].prev_char = status[i-1].current_char;
    }
    status[i].current_char = target_c;
    switch (target_c) {
    case '(':  status[i].parenthesis_diff++; break;
    case ')':  status[i].parenthesis_diff--; break;
    case '[':  status[i].bracket_diff++;     break;
    case ']':  status[i].bracket_diff--;     break;
    case '{':  status[i].curly_diff++;       break;
    case '}':  status[i].curly_diff--;       break;
    case '<':  status[i].angle_diff++;       break;
    case '>':  status[i].angle_diff--;       break;
    case '\'': status[i].single_quot_num++;  break;
    case '"':  status[i].double_quot_num++;  break;
    }
  }
  status[i] = initializer;
  status[i].current_char = '\0';
}

void correct_indent(const CodeStatus* status, char* clean_code) {
  int i, j, k;
  while () {

  }
  clean_code[j] = '\n';
  clean_code[j+1] = '\0';
}

int main(int argc, char** argv) {
  
  if (argc < 2) { puts("Please set a sourse file !"); return -1; }

  FILE* fp;
  if ((fp = fopen(argv[1], "r")) == NULL) { puts("Sorry, could not open the file"); return -2; }

  char input_string[MAX_WIDTH];
  read_souse_file(fp, input_string);

  char newline_none[MAX_WIDTH];
  replace_newline(input_string, newline_none);

  char tab_none[MAX_WIDTH];
  replace_tab(newline_none, tab_none);

  char extra_space_none[MAX_WIDTH];
  remove_extra_space(tab_none, extra_space_none);

  CodeStatus status_array[get_string_length(extra_space_none)];
  set_status(extra_space_none, status_array);

  /* int i; */
  /* for (i = 0; status_array[i].current_char != '\0'; i++) { */
  /*   puts("------------------------------------"); */
  /*   printf("parenthesis_diff = %d\n" */
  /*          "bracket_diff = %d\n" */
  /*          "curly_diff = %d\n" */
  /*          "angle_diff = %d\n" */
  /*          "single_quot_num = %d\n" */
  /*          "double_quot_num = %d\n" */
  /*          "current_char = %c\n" */
  /*          "prev_char = %c\n", */
  /*          status_array[i].parenthesis_diff, */
  /*          status_array[i].bracket_diff, */
  /*          status_array[i].curly_diff, */
  /*          status_array[i].angle_diff, */
  /*          status_array[i].single_quot_num, */
  /*          status_array[i].double_quot_num, */
  /*          status_array[i].current_char, */
  /*          status_array[i].prev_char); */
  /* } */
  
  char clean_code[MAX_WIDTH];
  correct_indent(status_array, clean_code);
  
  puts(clean_code);

  return 0;
}

const int count_head_space(const char* src) {
  int count = 0;
  while (src[count] == ' ') count++;
  return count;
}

const int count_tale_space(const char* src, const int prev_tale) {
  int i = prev_tale;
  while (src[i] == ' ') i--;
  return prev_tale - i + 1;
}

const int get_string_length(const char* src) {
  int count = 0;
  while (src[count] != '\0') count++;
  return count;
}
