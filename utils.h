#ifndef __UTILS_H_
#define __UTILS_H_
#include<string>
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
    ADD,                
    U_PLUS,             
    SUB,                
    U_MINUS,            
    MUL,                
    DIV,                
    MOD,                
    AND,                
    OR,                 
    XOR,                
    NOT,                
    LOGICAL_AND,        
    LOGICAL_OR,         
    LOGICAL_NOT,      
    GT,            
    GTE,      
    LT,               
    LTE,         
    EQ,              
    NEQ,          

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

struct Utils {

    
    static string replaceTabsWithSpaces(const string& str) {
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

    
    static bool isArithmetic(operations opr) {

        return opr>= ADD && opr<=MOD;
        
    }

    
    static bool isLogical(operations opr) {
        return opr >= LOGICAL_AND && opr <= LOGICAL_OR;
        
    }

  
    static bool isBitwiseOpr(operations opr) {

        return opr >= AND && opr<= NOT;
        
    }

    
    static bool isLvalue(operations opr) {
        return opr == ASSIGN;
    }

   
    static string oprToString(operations opr) {
        switch (opr) {
            case ASSIGN:
                return "=";
            case ADD:
            case U_PLUS:
                return "+";
            case SUB:
            case U_MINUS:
                return "-";
            case MUL:
                return "*";
            case DIV:
                return "/";
            case MOD:
                return "%";
            case AND:
                return "&";
            case OR:
                return "|";
            case XOR:
                return "^";
            case NOT:
                return "~";
            case LOGICAL_AND:
                return "&&";
            case LOGICAL_OR:
                return "||";
            case LOGICAL_NOT:
                return "!";
            case GT:
                return ">";
            case GTE:
                return ">=";
            case LT:
                return "<";
            case LTE:
                return "<=";
            case EQ:
                return "==";
            case NEQ:
                return "!=";
        }

        return "#";
    }

   
    static string operationToQuadrables(operations opr, dataTypes type = UNKNOWN) {
		switch (opr) {
            case ADD:
                return "ADD_" + dtypeToQuad(type);
            case SUB:
				return "SUB_" + dtypeToQuad(type);
            case MUL:
                return "MUL_" + dtypeToQuad(type);
            case DIV:
                return "DIV_" + dtypeToQuad(type);
            case MOD:
                return "MOD_" + dtypeToQuad(type);
            case AND:
			case LOGICAL_AND:
                return "AND_" + dtypeToQuad(type);
            case OR:
			case LOGICAL_OR:
                return "OR_" + dtypeToQuad(type);
            case XOR:
                return "XOR_" + dtypeToQuad(type);
            case NOT:
			case LOGICAL_NOT:
                return "NOT_" + dtypeToQuad(type);
            case GT:
                return "GT_" + dtypeToQuad(type);
            case GTE:
                return "GTE_" + dtypeToQuad(type);
            case LT:
                return "LT_" + dtypeToQuad(type);
            case LTE:
                return "LTE_" + dtypeToQuad(type);
            case EQ:
                return "EQU_" + dtypeToQuad(type);
            case NEQ:
                return "NEQ_" + dtypeToQuad(type);
			case U_MINUS:
                return "NEG_" + dtypeToQuad(type);
			case PUSH:
				return "PUSH_" + dtypeToQuad(type);
			case POP:
				return "POP_" + dtypeToQuad(type);
			case JMP:
				return "JMP";
            case JNZ:
				return "JNZ_" + dtypeToQuad(type);
			case JZ:
				return "JZ_" + dtypeToQuad(type);
        }

        return "#";
    }

   
    static bool isIntegerType(dataTypes type) {
        return (type == DTYPE_BOOL || type == DTYPE_CHAR || type == DTYPE_INT);
    }

    /**
     * Converts the given data type into its corresponding token string.
     *
     * @param type the type to convert.
     *
     * @return the corresponding token string.
     */
    static string dtypeToStr(DataType type) {
        switch (type) {
            case DTYPE_VOID:
                return "void";
            case DTYPE_BOOL:
                return "bool";
            case DTYPE_CHAR:
                return "char";
            case DTYPE_INT:
                return "int";
            case DTYPE_FLOAT:
                return "float";
            case DTYPE_FUNC_PTR:
                return "pointer to function";
            case DTYPE_ERROR:
                return "type error";
        }

        return "unknown";
    }

    /**
     * Converts the given data type into its corresponding quadruple string.
     *
     * @param type the type to convert.
     *
     * @return the corresponding quadruple string.
     */
    static string dtypeToQuad(DataType type) {
        switch (type) {
            case DTYPE_VOID:
                return "VOID";
            case DTYPE_BOOL:
                return "BOOL";
            case DTYPE_CHAR:
                return "CHR";
            case DTYPE_INT:
                return "INT";
            case DTYPE_FLOAT:
                return "FLOAT";
            case DTYPE_FUNC_PTR:
                return "FNCPTR";
            case DTYPE_ERROR:
                return "TYPERR";
        }

        return "unknown";
    }

    /**
     * Convert data type from t1 into t2.
     *
     * @param t1 the type to convert from.
     * @param t2 the type to convert to.
     *
     * @return the corresponding quadruple string.
     */
    static string dtypeConvQuad(DataType t1, DataType t2) {
        return (t1 != t2 ? dtypeToQuad(t1) + "_TO_" + dtypeToQuad(t2) + "\n" : "");
    }
};
#endif