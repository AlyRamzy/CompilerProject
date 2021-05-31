#ifndef __UTILS_H_
#define __UTILS_H_

#include<string>
#include<map>
#include<vector>
#include<unordered_map>


using namespace std;


struct Location {
    int lineNum;
    int pos;
    int len;
};
struct Token {
    char* value;
    Location loc;
};

enum operations {
    ASSIGN = 100,    

    //Arithmetic   
    ADD,                
    U_PLUS,             
    SUB,                
    U_MINUS,            
    MUL,                
    DIV,                
    MOD,   

    //bitwise             
    AND,                
    OR,                 
    XOR,                
    NOT,     

    //logical           
    LOGICAL_AND,        
    LOGICAL_OR,         
    LOGICAL_NOT,    
    GT,            
    GTE,      
    LT,               
    LTE,         
    EQ,              
    NEQ,          

    //quads
	PUSH,				
	POP, 				
	JMP,				
    JNZ,                
	JZ, 				
};


enum dataTypes {
    VOID = 200,
    BOOL,
    CHAR,
    INT,
    FLOAT,
    FUNC_PTR,
    ENUM,
    ERROR,
    UNKNOWN
};


enum scopeType {
    BLOCK = 300,
    FUNCTION,
    LOOP,
    IF,
    SWITCH,
};


enum logLevel {
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTE
};

union value {
    bool boolVal;
    char charVal;
    int intVal;
    float floatVal;
};


class Utils {
    private:
    map<int, pair<string, string>> mapper;
    map<int, pair<string, string>> dTypes;
    public:
    Utils(){
        mapper[ASSIGN]      = {"=", ""};
        mapper[ADD]         = {"+", "ADD_"};
        mapper[SUB]         = {"-", "SUB_"};
        mapper[MUL]         = {"*", "MUL_"};
        mapper[DIV]         = {"/", "DIV_"};
        mapper[MOD]         = {"%", "MOD_"};
        mapper[AND]         = {"&", "AND_"};
        mapper[OR]          = {"|", "OR_"};
        mapper[XOR]         = {"^", "XOR_"};
        mapper[NOT]         = {"~", "NOT_"};
        mapper[LOGICAL_AND] = {"&&", "AND_"};
        mapper[LOGICAL_OR]  = {"||", "OR_"};
        mapper[LOGICAL_NOT] = {"!", "NOT_"};
        mapper[GT]          = {">", "GT_"};
        mapper[GTE]         = {">=", "GTE_"};
        mapper[LT]          = {"<", "LT_"};
        mapper[LTE]         = {"<=", "LTE_"};
        mapper[EQ]          = {"==", "EQU_"};
        mapper[NEQ]         = {"!=", "NEQ_"};
        mapper[U_PLUS]      = {"+", ""};
        mapper[U_MINUS]     = {"-", "NEG_"};
        mapper[PUSH]        = {"", "PUSH_"};
        mapper[POP]         = {"", "POP_"};
        mapper[JMP]         = {"", "JMP_"};
        mapper[JNZ]         = {"", "JNZ_"};
        mapper[JZ]          = {"", "JZ_"};

        dTypes[VOID]  = {"void", "VOID"};
        dTypes[BOOL]  = {"bool", "BOOL"};
        dTypes[CHAR]  = {"char", "CHR"};
        dTypes[INT]   = {"int", "INT"};
        dTypes[FLOAT] = {"float", "FLOAT"};
        dTypes[ENUM]  = {"enum", "ENUM"};
        dTypes[ERROR] = {"type error", "TYPERR"};
        dTypes[FUNC_PTR] = {"pointer to function", "FNCPTR"};
    }
    string replaceTabsWithSpaces(const string& str) {
        string ret;
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == '\t') {
                ret += "    ";
            } else {
                ret += str[i];
            }
        }
        return ret;
    }

    bool isArithmetic(operations opr) {
        return opr>= ADD && opr<=MOD;
    }

    bool isLogical(operations opr) {
        return opr >= LOGICAL_AND && opr <= NEQ;
    }

    bool isBitwise(operations opr) {
        return opr >= AND && opr<= NOT;
    }

    bool isAssign(operations opr) {
        return opr == ASSIGN;
    }

    string oprToString(operations opr) {
        if(mapper.count(opr) && mapper[opr].first != "")
            return mapper[opr].first;
        return "#";
    }

    string operationToQuadrables(operations opr, dataTypes type = UNKNOWN) {
		if(mapper.count(opr) && mapper[opr].second != "")
            return mapper[opr].second + dtypeToQuad(type);
        return "#";
    }
   
    bool isValidInt(dataTypes type) {
        return (type >= BOOL && type <= INT);
    }

    string dtypeToStr(dataTypes type) {
        if(dTypes.count(type))
            return dTypes[type].first;
        return "unknown";
    }

    string dtypeToQuad(dataTypes type) {
        if(dTypes.count(type))
            return dTypes[type].second;
        return "unknown";
    }

    string dtypeConvQuad(dataTypes t1, dataTypes t2) {
        return (t1 != t2 ? dtypeToQuad(t1) + "_TO_" + dtypeToQuad(t2) + "\n" : "");
    }
};
#endif