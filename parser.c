#include "parser.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Initialize a parser.
Parser parser_init() {
  Parser p;
  p.data = (char *)malloc(sizeof(char) * PARSER_INIT_SZ);
  p.sz   = 0;
  p.cap  = PARSER_INIT_SZ;
  p.tokens_sz = 0;
  for (size_t i = 0; i < TOKEN_SZ; i++) {
    memset(p.tokens[i], '\0', sizeof(p.tokens[i][0]) * TOKEN_SZ);
  }
  return p;
}

// Adds a token to the parser.
void parser_add_token(Parser *parser, char *token) {
  assert(parser->tokens_sz < TOKEN_SZ);
  strcpy(parser->tokens[parser->tokens_sz++], token);
}

// Tokenizes the parser at a given delimiter.
void parser_tokenize_at_delim(Parser *parser, char delim, bool ignore_newline) {

  // Reset the tokens.
  for (size_t i = 0; i < TOKEN_SZ; i++) {
    memset(parser->tokens[i], '\0', sizeof(parser->tokens[i][0]) * TOKEN_SZ);
  }

  // Begin.
  const size_t tmp_str_cap = 1000;
  int idx = -1;
  for (size_t i = 0; i < parser->sz; i++) {
    if (parser->data[i] != delim && idx == -1) {
      idx = i;
    }
    else if (parser->data[i] == delim) {
      char tmp[tmp_str_cap];
      size_t tmp_str_sz = 0;
      memset(tmp, '\0', sizeof(char) * tmp_str_cap);
      // Build the temporary string as a token.
      for (int j = idx; j < i; j++) {
        assert(tmp_str_sz < tmp_str_cap);
        if (parser->data[j] == '\n' && ignore_newline) continue;
        tmp[tmp_str_sz++] = parser->data[j];
      }
      // Add the token.
      parser_add_token(parser, tmp);
      idx = -1;
    }
  }
}

// Dump all tokens in the parser.
void parser_dump_tokens(const Parser *parser) {
  for (size_t i = 0; i < parser->tokens_sz; i++) {
    printf("%s", parser->tokens[i]);
  }
}

// Appends a character to the parser. If the size
// exceeds the capacity of the parser, it will reallocate.
void parser_append(Parser *parser, char data) {
  if (parser->sz == parser->cap) {
    parser->cap *= 2;
    parser->data = realloc(parser->data, sizeof(char *) * parser->cap);
  }
  parser->data[parser->sz++] = data;
}

// Takes a parser pointer and a path. It will read
// everything from the file and put it into the parser.
void parser_read(Parser *parser, const char *path) {
  FILE *fp = fopen(path, "r");
  if (!fp) {
    fprintf(stderr, "ERROR: could not open file %s.\n", path);
    exit(EXIT_FAILURE);
  }

  // TODO: protect from buffer overflow.
  char line[1000];
  while(fgets(line, sizeof(line), fp) != NULL) {
    for (int i = 0; line[i] != '\0'; i++) {
      parser_append(parser, line[i]);
    }
  }

  fclose(fp);
}

// Assigns a char * into parser.
void parser_assign(Parser *parser, const char *word) {
  for (int i = 0; *(word + i) != '\0'; i++) {
    parser_append(parser, *(word + i));
  }
}

// Takes a parser pointer, a start index, and end index,
// and a replace character. It will then replace everything
// in the range from start -> end with the replace character.
// It will then shift all elements left and change the size
// of the parser if the replace character is '\0'.
void cleanup(Parser *parser, int start, int end, char replace) {
  for (int i = start; i <= end; i++) {
    parser->data[i] = replace;
  }
  for (int i = end + 1, ptr = start; i < parser->sz; i++) {
    parser->data[ptr++] = parser->data[i];
  }
  if (replace == '\0') {
    parser->sz -= end - start + 1;
  }
}

// Removes all newlines from the parser.
void parser_remove_whitespace(Parser *parser) {
  parser_remove(parser, " ");
}

void *s_malloc(size_t bytes) {
  void *p = malloc(bytes);
  if (!p) {
    fprintf(stderr, "ERROR: failed to safely allocate %zu bytes.\n", bytes);
    exit(EXIT_FAILURE);
  }
  return p;
}

long *parser_tokens_strtol(Parser *parser) {
  assert(false && "BROKEN");
  assert(parser->tokens_sz > 0);
  long *arr = s_malloc(sizeof(long) * parser->tokens_sz);
  char *tmp;
  for (size_t i = 0; i < parser->tokens_sz; i++) {
    arr[i] = strtol(parser->tokens[i], &tmp, 10);
  }
}

// Removes all whitespace from the parser.
void parser_remove_newline(Parser *parser) {
  parser_remove(parser, "\n");
}

// This will find all occurrences of `word` in the
// parser and will find the start and end
// indices and send them to cleanup() to remove them.
void parser_remove(Parser *parser, const char *word) {
  size_t i;
  int word_idx = 0, start = -1, end = -1;
  for (size_t i = 0; i < parser->sz; i++) {
    if (parser->data[i] != word[word_idx]) {
      word_idx = 0;
      continue;
    }
    if (word_idx == 0) {
      start = i;
    }
    word_idx += 1;
    if (word[word_idx] == '\0') {
      end = i;
      cleanup(parser, start, end, '\0');
      word_idx = 0;
    }
  }
}

// Dump the contents of the parser.
void parser_dump(const Parser *parser) {
  for (size_t i = 0; i < parser->sz; i++) {
    putchar(parser->data[i]);
  }
}

// Free memory allocated in the parser.
void parser_free(Parser *parser) {
  free(parser->data);
}


