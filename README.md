# Compiler
This is a simple compiler for cpp language based on lex , yacc 
## to compile the parser
- bison.yacc -d -o parser.cpp parser.y
## to compile the lexer
- flex -o lexer.cpp lexer.l

## to produce the excutable file
- g++ main.cpp parse_tree/statements/statement_analyzer.cpp parse_tree/statements/statement_generator.cpp parse_tree/expressions/expression_analyzer.cpp parse_tree/expressions/expression_generator.cpp parse_tree/expressions/expression_evaluator.cpp parse_tree/branches/branch_analyzer.cpp parse_tree/branches/branch_generator.cpp parse_tree/functions/function_generator.cpp parse_tree/functions/function_analyzer.cpp lexer.cpp parser.cpp

- ./a.out data/input.mpp -o data/out.quad -s data/symbol_table.txt


