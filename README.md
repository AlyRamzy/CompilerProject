# Compiler
This is a simple compiler for cpp language based on lex , yacc 
## to compile the parser
- bison.yacc -d -o parser.cpp parser.y
## to compile the lexer
- flex -o lexer.cpp lexer.l

## to produce the excutable file
- g++ main.cpp parser.cpp lexer.cpp
