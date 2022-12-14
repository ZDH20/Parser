#ifndef PARSER_H
#define PARSER_H
#define PARSER_INIT_SZ 3000
#define TOKEN_SZ 3000

#include <stdbool.h>
#include <stdlib.h>

typedef struct Parser {
  char *data;
  size_t sz, cap;
  char tokens[TOKEN_SZ][TOKEN_SZ];
  size_t tokens_sz;
} Parser;

Parser *parser_alloc();
void parser_read(Parser *, const char *);
void parser_dump(const Parser *);
void parser_append(Parser *, char);
void parser_remove(Parser *, const char *);
void parser_free(Parser *);
void parser_assign(Parser *, const char *);
void parser_remove_whitespace(Parser *);
void parser_remove_newline(Parser *);

void parser_tokenize_at_delim(Parser *, char, bool);
bool parser_token_starts_with(Parser *, char, int);
void parser_tokens_clear(Parser *);
void parser_tokenize_at_line(Parser *);
void parser_dump_tokens(const Parser *);
bool parser_token_eq(Parser *, const char *, int);
char *parser_get_token(Parser *, int);
int *parser_tokens_atoi(Parser *, size_t *);

#endif // PARSER_H
