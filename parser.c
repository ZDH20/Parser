#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Parser parser_init() {
  Parser p;
  p.data = (char *)malloc(sizeof(char) * PARSER_INIT_SZ);
  p.sz   = 0;
  p.cap  = PARSER_INIT_SZ;
  return p;
}

void parser_append(Parser *parser, char data) {
  if (parser->sz == parser->cap) {
    parser->cap *= 2;
    parser->data = realloc(parser->data, sizeof(char *) * parser->cap);
  }
  parser->data[parser->sz++] = data;
}

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

void cleanup(Parser *parser, int start, int end, char replace) {
  for (int i = start; i <= end; i++) {
    parser->data[i] = replace;
  }
  for (int i = end + 1, ptr = start; i < parser->sz; i++) {
    parser->data[ptr++] = parser->data[i];
  }
  parser->sz -= end - start + 1;
}

void parser_remove(Parser *parser, char *word) {
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

void parser_dump(const Parser *parser) {
  for (size_t i = 0; i < parser->sz; i++) {
    printf("%c", parser->data[i]);
  }
}

void parser_free(Parser *parser) {
  free(parser->data);
}


