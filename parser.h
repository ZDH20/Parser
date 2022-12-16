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

// Parser Init.
Parser *parser_alloc();
void parser_read(Parser *, const char *);
void parser_assign(Parser *, const char *);

// Parser manip.
void parser_append(Parser *, char);
void parser_remove(Parser *, const char *);
void parser_remove_whitespace(Parser *);
void parser_remove_newline(Parser *);

// Parser misc.
void parser_free(Parser *);
void parser_dump(const Parser *);
void parser_debug(const Parser *);

// Tokens Init.
void parser_tokenize_at_delim(Parser *, char/*, bool*/);
void parser_tokenize_lines(Parser *);

// Tokens conditionals.
bool parser_token_empty(const Parser *, int);
bool parser_token_starts_with(Parser *, char, int);
bool parser_token_eq(Parser *, const char *, int);

// Tokens info.
size_t parser_tokens_sz(const Parser *);
void parser_dump_tokens(const Parser *);

// Tokens retrieval.
char *parser_get_token(Parser *, int);
int *parser_tokens_atoi(Parser *, size_t *);

// Tokens misc.
void parser_tokens_clear(Parser *);

#endif // PARSER_H
