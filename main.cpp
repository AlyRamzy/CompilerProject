#include "manager/scope_context.h"
#include "manager/quadrubles_generator.h"
#include "nodes.h"
#include "utils.h"

using namespace std;


extern int yyparse();
extern FILE* yyin;
extern StatementNode* program;

string inputFilename;
string outputFilename;
string symbolTableFilename;
string errorFilename;

bool warn = true;

void writeToFile(string data, string filename);
void parseArguments(int argc, char* argv[]);


int main(int argc, char* argv[]) {
    parseArguments(argc, argv);

    ScopeContext scopeContext(inputFilename,errorFilename, warn);
    quadrublesGenerator genContext;

    yyin = fopen(inputFilename.c_str(), "r");

    if (yyin == NULL) {
        fprintf(stderr, "error: could not open the input file '%s'!\n", inputFilename.c_str());
        exit(0);
    }
    yyparse();
   
    if (program != NULL )
    {
        if(program->analyze(&scopeContext)){
            writeToFile(program->generateQuad(&genContext), outputFilename);
            writeToFile(scopeContext.getSymbolTableStr(), symbolTableFilename);
        }else {
            writeToFile("", outputFilename);
        }
    }
    else{
        writeToFile("", outputFilename);
    }
    
    fclose(yyin);

    if (program != NULL) {
        delete program;
    }

    return 0;
}

void writeToFile(string data, string filename) {
    if (filename.empty()) {
        return;
    }

    ofstream fout(filename);

    if (!fout.is_open()) {
        fprintf(stderr, "error: could not write in file '%s'!\n", filename.c_str());
        return;
    }

    fout << data << endl;

    fout.close();
}

void parseArguments(int argc, char* argv[]) {
    while (++argv, --argc) {
        if (**argv == '-') {
            // Set output filename
            if (strcmp(*argv, "-o") == 0) {
                if (--argc < 1) {
                    fprintf(stderr, "error: missing output filename!\n\n");
                }

                outputFilename = string(*(++argv));
            }
            // Set symbol table output filename
            else if (strcmp(*argv, "-s") == 0) {
                if (--argc < 1) {
                    fprintf(stderr, "error: missing output filename!\n\n");
                }

                symbolTableFilename = string(*(++argv));
            }
            // Set error filename
            else if (strcmp(*argv, "-e") == 0) {
                if (--argc < 1) {
                    fprintf(stderr, "error: missing error filename!\n\n");
                }

                errorFilename = string(*(++argv));
                remove(errorFilename.c_str());
            }
            // Invalid command
            else {
                fprintf(stderr, "unknown argument '%s'\n", *argv);
            }
        }
        // Set input filename
        else if (inputFilename.empty()) {
            inputFilename = string(*argv);
        }
        // Other arguments
        else {
            fprintf(stderr, "warning: too many arguments, '%s' ignored\n", *argv);
        }
    }

    // Check if input filename is specified
    if (inputFilename.empty()) {
        fprintf(stderr, "error: missing input filename argument!\n\n");
    }
}
