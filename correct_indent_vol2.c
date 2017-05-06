#include <stdio.h>

int main(int argc, char** argv) {

  if (argc < 2) { puts("Please set a sourse file !"); return -1; }

  FILE* fp;
  char input[1024];
  if ((fp = fopen(argv[1], "r")) == NULL) { puts("Sorry, could not open the file"); return -2; }

  int i;
  int input_buff;
  for (i = 0; (input_buff = fgetc(fp) != EOF); i++) {
    if (i > 1024) { puts("Too large file !"); return -3; }
    input[i] = (char)input_buff;
  }

  puts(input);
  
  return 0;
}
