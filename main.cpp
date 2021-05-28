#include <iostream>
using namespace std;

//
// External functions & variables
//
extern int yyparse();

int main() {
    yyparse();
    return 0;
}