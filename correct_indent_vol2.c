#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 100000

typedef struct code_status_t{
  int parenthesis_diff; 
  int bracket_diff;
  int curl_diff;
  
  int single_quotation_diff;
  int double_quotation_diff; 

  int encloce_comment_diff;
  int slash_comment_flag;
  
  int indent_depth;
  
  char char_stock;
  char prev_char;

} CodeStatus;

int count_head_space(const char*);
int count_tale_space(const char*, const int);
int get_str_length(const char*);
int check_status_error(CodeStatus);
void set_indent(int);

void read_souse_file(FILE* const, char*);
void remove_newline(char*, char*);
void remove_tab(char*, char*);
void remove_extra_space(char*, char*);
void set_status(const char*, CodeStatus*);
void corrent_indent(const CodeStatus*, char*);
  
void read_souse_file(FILE* const fp, char* input_string) {
  int input_buff;
  int i;
  for (i = 0; (input_buff = fgetc(fp)) != EOF; i++) {
    if (i > MAX_WIDTH - 1) { puts("Too large file !"); exit(-3); }
    input_string[i] = (char)input_buff;
  }
  input_string[i] = '\0';
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
  static char copy_buff = '\0';
  for (i = count_head_space(tab_none); tab_none[i] != '\0'; i++) {
    if (copy_buff == ' ' && tab_none[i] == ' ') ;
    else space_less[j++] = tab_none[i];
    copy_buff = tab_none[i];
  }
  space_less[j - count_tale_space(space_less, j)] = '\0';
}

void set_status(const char* space_less, CodeStatus* status) {
  int i;
  for (i = 0; space_less[i] != '\0'; i++) {
    const char current_char = space_less[i];
    if (status[i].prev_char != '\\') {
      switch (current_char) {
      case '\'': status[i].single_quotation_diff = ++status[i].single_quotation_diff % 2; break;
      case '\"': status[i].double_quotation_diff = ++status[i].double_quotation_diff % 2; break;      
      case '/' :
        if (status[i].prev_char == '*') status[i].encloce_comment_diff--; 
        if (status[i].prev_char == '/') status[i].slash_comment_flag = 1;      
        break;
      case '*' :
        if (status[i].prev_char == '/') status[i].encloce_comment_diff++;
        break;
      }
    }
    if (!status[i].slash_comment_flag && !status[i].encloce_comment_diff/* && !status[i].single_quotation_diff && !status[i].double_quotation_diff*/) {
      switch (current_char) {
      case '(' : status[i].parenthesis_diff++; break;
      case ')' : status[i].parenthesis_diff--; break;
      case '[' : status[i].bracket_diff++; break;
      case ']' : status[i].bracket_diff--; break;
      case '{' : status[i].curl_diff++; break;
      case '}' : status[i].curl_diff--; break;
      }      
    }
    status[i].indent_depth = status[i].bracket_diff;
    if (check_status_error(status[i])) { puts("There are some synthax error!"); exit(-4); }
    status[i].prev_char = current_char;
    status[i+1] = status[i];
  }
  status[i].prev_char = '\0';
}

void correct_indent(const CodeStatus* status, char* clean_code) {
  int i;
  for (i = 0; status[i].prev_char != '\0'; i++) {
    clean_code[i] = status[i].prev_char;
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

  char space_less[MAX_WIDTH];
  remove_extra_space(tab_none, space_less);

  const int length = get_str_length(space_less);
  CodeStatus status_array[length];  
  set_status(space_less, status_array);

  char clean_code[MAX_WIDTH];
  correct_indent(status_array, clean_code);
  
  puts(clean_code);

  printf("%d\n%d\n%d\n\n%d\n%d\n\n%d\n%d\n%c\n"

         , status_array[length-1].parenthesis_diff
         , status_array[length-1].bracket_diff
         , status_array[length-1].curl_diff
         
         , status_array[length-1].single_quotation_diff
         , status_array[length-1].double_quotation_diff

         , status_array[length-1].slash_comment_flag
         , status_array[length-1].encloce_comment_diff
         , status_array[length-1].prev_char);

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

int get_str_length(const char* src) {
  int i;
  for (i = 0; src[i] != '\0'; i++) ;
  return i;
}

int check_status_error(CodeStatus status) {
  return (status.parenthesis_diff < 0) || (status.bracket_diff < 0) || (status.curl_diff < 0) ;
}

void set_indent(int depth) {
  int i;
  for (i = 0; i < depth*2; i++) putchar(' ');
}
