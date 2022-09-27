#include "parser.h"
#include <stdio.h>


int main(void) {
  Parser p = parser_init();
  parser_read(&p, "input.txt");
  parser_trim(&p);
  parser_tokenize_at_delim(&p, ',', true);
  parser_dump_tokens(&p);
  // parser_dump(&p);
  parser_free(&p);
  return 0;
}

