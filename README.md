# Parser
Provides a way to parse and handle strings in C.

* Functions Overview

- Parser *parser_alloc()
  - Must call this function first.
  - Allocates memory for the parser.
- void parser_read(Parser *, const char *)
  - Read a file and put the contents in the parser.
- void parser_assign(Parser *, const char *)
  - Hard-code data into the parser.
- void parser_append(Parser *, char)
  - Append a char at the end of the parser data.
- void parser_remove(Parser *, const char *)
  - Remove a series of characters from the parser.
- void parser\_remove\_whitespace(Parser *)
  - Removes all whitespace.

TODO



