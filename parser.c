#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize a parser.
Parser parser_init() {
  Parser p;
  p.data = (char *)malloc(sizeof(char) * PARSER_INIT_SZ);
  p.sz   = 0;
  p.cap  = PARSER_INIT_SZ;
  return p;
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
    printf("%c", parser->data[i]);
  }
}

// Free memory allocated in the parser.
void parser_free(Parser *parser) {
  free(parser->data);
}


