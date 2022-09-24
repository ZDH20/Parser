#ifndef PARSER_H
#define PARSER_H
#define PARSER_INIT_SZ 1000

#include <stdlib.h>

typedef struct Parser {
  char *data;
  size_t sz, cap;
} Parser;

Parser parser_init();
void parser_read(Parser *, const char *);
void parser_dump(const Parser *);
void parser_append(Parser *, char);
void parser_remove(Parser *, char *);
void parser_free(Parser *);

#endif // PARSER_H
