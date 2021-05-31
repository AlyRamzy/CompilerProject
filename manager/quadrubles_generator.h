#ifndef __QUADRUBLES_GENERATOR_H_
#define __QUADRUBLES_GENERATOR_H_

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class quadrublesGenerator {
public:
    stack<int> breakLabels, continueLabels;
    int labelCounter;
	bool declareFuncParams;

    quadrublesGenerator() {
        labelCounter = 1;
		declareFuncParams = false;
    }
};

#endif