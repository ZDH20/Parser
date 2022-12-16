# Parser
Provides a way to parse and handle strings in C.

## Parser Functions Overview

### Parser *parser_alloc()
  - Must call this function first.
  - Allocates memory for the parser.
### void parser_read(Parser *, const char *)
  - Read a file and put the contents in the parser.
### void parser_assign(Parser *, const char *)
  - Hard-code data into the parser.
### void parser_append(Parser *, char)
  - Append a char at the end of the parser data.
### void parser_remove(Parser *, const char *)
  - Remove a series of characters from the parser.
### void parser\_remove\_whitespace(Parser *)
  - Removes all whitespace.
### void parser\_remove\_newline(Parser *)
  - Removes all newlines.
### void parser_free(Parser *)
  - Free()'s all memory allocated by the parser.
### void parser_dump(const Parser *)
  - Dump all contents of the parser.
### void parser_debug(const Parser *)
  - Print some information from the parser.

## Parser Tokens Functions Overview

### void parser\_tokenize\_at_delim(Parser *)
  - Create tokens at a given delimiter.
### void parser\_tokenize\_lines(Parser *)
  - Create tokens at newlines.
### bool parser\_token\_empty(const Parser *, int)
  - Determines whether a given token is empty.
### bool parser\_token\_starts_with(Parser *, char, int)
  - Determines whether a given token starts with a character.
### bool parser\_token\_eq(Parser *, const char *, int)
  - Determines whether a given token is equal to a char* using strcmp().
### size\_t parser\_tokens_sz(const Parser *)
  - Retrives the number of tokens created.
### void parser\_dump\_tokens(const Parser *)
  - Dump all tokens.
### char *parser\_get\_token(Parser *, int)
  - Retrieve a given token.
### int *parser\_tokens\_atoi(Parser *, size_t *)
  - Creates a pointer of integers from the tokens.
  - The size of the array will be put into the size_t *.
  - Ignores all tokens that are not numbers.
  - Must free() this memory yourself.
### void parser\_tokens\_clear(Parser *)
  - Clears all tokens.
