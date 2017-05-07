#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 10000

typedef struct code_status_t {
  int parenthesis_diff; 
  int bracket_diff;
  int curl_diff;
  
  int single_quotation_diff;
  int double_quotation_diff; 

  int encloce_comment_diff;
  int slash_comment_flag;
  
  int indent_depth;
  
  char current_char;
  char front_char;

} CodeStatus;

void read_souse_file(FILE* const, char*);
void remove_newline(const char*, char*);
void remove_tab(const char*, char*);
void remove_extra_space(const char*, char*);
void set_status(const char*, CodeStatus*);
void corrent_indent(const CodeStatus*, char*);
  
int count_head_space(const char*);
int count_tale_space(const char*, const int);
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

void remove_newline(const char* input_string, char* newline_none) {
  int i;
  for (i = 0; input_string[i] != '\0'; i++)
    if (input_string[i] == '\n') newline_none[i] = ' ';
    else newline_none[i] = input_string[i];
}

void remove_tab(const char* newline_none, char* tab_none) {
  int i;
  for (i = 0; newline_none[i] != '\0'; i++)
    if (newline_none[i] == '\t') tab_none[i] = ' ';
    else tab_none[i] = newline_none[i];
}

void remove_extra_space(const char* tab_none, char* extra_space_none) {
  int i, j = 0;
  static char copy_buff = '\0';
  for (i = count_head_space(tab_none); tab_none[i] != '\0'; i++) {
    if (copy_buff == ' ' && tab_none[i] == ' ') ;
    else extra_space_none[j++] = tab_none[i];
    copy_buff = tab_none[i];
  }
  extra_space_none[j - count_tale_space(extra_space_none, j)] = '\0';
}

void set_status(const char* extra_space_none, CodeStatus* status) {
}

void correct_indent(const CodeStatus* status, char* clean_code) {
  int i;
  for (i = 0; status[i].front_char != '\0'; i++) {
    clean_code[i] = status[i].front_char;
  }
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

  char extra_space_none[MAX_WIDTH];
  remove_extra_space(tab_none, extra_space_none);

  const int length = get_string_length(extra_space_none);
  CodeStatus status_array[length];  
  set_status(extra_space_none, status_array);

  char clean_code[MAX_WIDTH];
  correct_indent(status_array, clean_code);
  
  puts(clean_code);

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

const int get_string_length(const char* src) {
  int i;
  for (i = 0; src[i] != '\0'; i++) ;
  return i;
}
