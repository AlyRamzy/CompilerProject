#ifndef __CONTEXT_H_
#define __CONTEXT_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

#include "../nodes.h"
#include "../utils.h"

using namespace std;

typedef unordered_map<string, DeclarationNode*> SymbolTable;

class Scope {
public:
    scopeType type;         
    Node* ptr;              
    SymbolTable table;      

    Scope(scopeType type, Node* ptr = NULL) {
        this->type = type;
        this->ptr = ptr;
    }
};

class ScopeContext {
private:
    string sourceFilename;
    vector<string> sourceCode;
    vector<Scope*> scopes;
    unordered_map<string, int> aliases;
    vector<pair<int, DeclarationNode*>> symbols;    // Used just for printing the symbol table. NOT IMPORTANT!
    bool warn;
    Utils utils;

    void readSourceCode() {
        ifstream fin(sourceFilename);
        if (!fin.is_open()) {
            return;
        }

        string line;
        while (getline(fin, line)) {
            sourceCode.push_back(utils.replaceTabsWithSpaces(line));
        }
        fin.close();
    }

public:
    bool declareFuncParams = false;
    bool initializeVar = false;

    ScopeContext(const string& sourceFilename, bool warn = false) {
        this->sourceFilename = sourceFilename;
        this->readSourceCode();
        this->warn = warn;
    }

    void addScope(scopeType type, Node* ptr = NULL) {
        scopes.push_back(new Scope(type, ptr));
    }

    void popScope() {
        Scope* scope = scopes.back();
        scopes.pop_back();

        for (auto& it : scope->table) {
            DeclarationNode* sym = it.second;

            if (sym->used <= 0) {
                if (dynamic_cast<VarDeclarationNode*>(sym)) {
                    log("the value of variable '" + sym->declaredHeader() + "' is never used", sym->ident->loc, LOG_WARNING);
                }
                else if (sym->ident->name != "main") {
                    log("function '" + sym->declaredHeader() + "' is never called", sym->ident->loc, LOG_WARNING);
                }
            }
            
            aliases[sym->ident->name]--;
        }

        delete scope;
    }

    bool isGlobalScope() {
        return scopes.size() == 1;
    }

    FunctionNode* getFunctionScope() {
        for (int i = (int) scopes.size() - 1; i >= 0; --i) {
            if (scopes[i]->type == FUNCTION) {
                return (FunctionNode*) scopes[i]->ptr;
            }
        }
        return NULL;
    }

    SwitchNode* getSwitchScope() {
        for (int i = (int) scopes.size() - 1; i >= 0; --i) {
            if (scopes[i]->type == SWITCH) {
                return (SwitchNode*) scopes[i]->ptr;
            }
        }
        return NULL;
    }

    bool declareSymbol(DeclarationNode* sym) {
        SymbolTable& table = scopes.back()->table;

        if (table.count(sym->ident->name)) {
            return false;
        }

        symbols.push_back({ scopes.size() - 1, sym });

        int num = aliases[sym->ident->name]++;

        if (num > 0) {
            sym->alias = sym->ident->name + "@" + to_string(num);
        } else {
            sym->alias = sym->ident->name;
        }

        table[sym->ident->name] = sym;
        return true;
    }

    DeclarationNode* getSymbol(const string& identifier) {
        for (int i = (int) scopes.size() - 1; i >= 0; --i) {
            if (scopes[i]->table.count(identifier)) {
                return scopes[i]->table[identifier];
            }
        }
        return NULL;
    }

    bool hasBreakScope() {
        for (int i = (int) scopes.size() - 1; i >= 0; --i) {
            if (scopes[i]->type == LOOP || scopes[i]->type == SWITCH) {
                return true;
            }
        }

        return false;
    }

    bool hasSwitchScope() {
        for (int i = (int) scopes.size() - 1; i >= 0; --i) {
            if (scopes[i]->type == SWITCH) {
                return true;
            }
        }

        return false;
    }

    bool hasLoopScope() {
        for (int i = (int) scopes.size() - 1; i >= 0; --i) {
            if (scopes[i]->type == LOOP) {
                return true;
            }
        }

        return false;
    }

    bool hasFunctionScope() {
        for (int i = (int) scopes.size() - 1; i >= 0; --i) {
            if (scopes[i]->type == FUNCTION) {
                return true;
            }
        }

        return false;
    }

    void log(const string& what, const Location& loc, logLevel level) {
        string logLvl;

        switch (level) {
            case LOG_ERROR:
                logLvl = "error";
                break;
            case LOG_WARNING:
                if (!warn) {
                    return;
                }
                logLvl = "warning";
                break;
            case LOG_NOTE:
                logLvl = "note";
                break;
        }

        fprintf(stdout, "%s:%d:%d: %s: %s\n", sourceFilename.c_str(), loc.lineNum, loc.pos, logLvl.c_str(), what.c_str());
        fprintf(stdout, "%s\n", sourceCode[loc.lineNum - 1].c_str());
        fprintf(stdout, "%*s", loc.pos, "^");

        if (loc.len > 1) {
            fprintf(stdout, "%s", string(loc.len - 1, '~').c_str());
        }

        fprintf(stdout, "\n");
    }

    string getSymbolTableStr() {
        stringstream ss;

        ss << "+-------+---------------------------------------------------+---------------------+---------------------+-------+\n";
        ss << "| scope | type                                              | identifier          | alias               | used  |\n";
        ss << "+-------+---------------------------------------------------+---------------------+---------------------+-------+\n";

        for (int i = 0; i < symbols.size(); ++i) {
            int scope = symbols[i].first;
            DeclarationNode* sym = symbols[i].second;

            ss << "| " << left << setw(6) << scope;
            ss << "| " << left << setw(50) << sym->declaredType();
            ss << "| " << left << setw(20) << sym->ident->name;
            ss << "| " << left << setw(20) << sym->alias;
            ss << "| " << left << setw(6) << sym->used << "|\n";
            ss << "+-------+---------------------------------------------------+---------------------+---------------------+-------+\n";
        }

        return ss.str();
    }
};

#endif