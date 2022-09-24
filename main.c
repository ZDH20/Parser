#include "parser.h"
#include <stdio.h>

int main(void) {
  Parser p = parser_init();
  // parser_read(&p, "input.txt");
  parser_assign(&p, "Hello world!\n");
  parser_remove(&p, "o");
  parser_dump(&p);
  parser_free(&p);
  return 0;
}

