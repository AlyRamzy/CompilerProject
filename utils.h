#ifndef __UTILS_H_
#define __UTILS_H_

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
#endif