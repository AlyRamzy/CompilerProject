# Compiler
This is a simple compiler for cpp language based on lex , yacc 
## to compile the parser
- bison.yacc -d -o parser.cpp parser.y
## to compile the lexer
- flex -o lexer.cpp lexer.l

## to produce the excutable file
- g++ main.cpp analyzers.cpp generators.cpp evaluators.cpp lexer.cpp parser.cpp 
- ./a.out inputFileName -o outputQuadsFileName -s symbolTableFileName -e errorsFileName

## to run the GUI
- php -S localhost:8888
- http://localhost:8888/gui.php


