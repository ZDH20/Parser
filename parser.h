#ifndef PARSER_H
#define PARSER_H
#define PARSER_INIT_SZ 1000
#define TOKEN_SZ 1000

#include <stdbool.h>
#include <stdlib.h>

typedef struct Parser {
  char *data;
  size_t sz, cap;
  char tokens[TOKEN_SZ][TOKEN_SZ];
  size_t tokens_sz;
} Parser;

Parser parser_init();
void parser_read(Parser *, const char *);
void parser_dump(const Parser *);
void parser_append(Parser *, char);
void parser_remove(Parser *, const char *);
void parser_free(Parser *);
void parser_assign(Parser *, const char *);
void parser_tokenize_at_delim(Parser *, char, bool);
char *parser_get_token(Parser *, int);
void parser_remove_whitespace(Parser *);
void parser_remove_newline(Parser *);
void parser_dump_tokens(const Parser *, bool);
int *parser_tokens_atoi(Parser *, size_t *);
void parser_tokenize_at_line(Parser *);
bool parser_token_eq(Parser *, const char *, int);

#endif // PARSER_H
