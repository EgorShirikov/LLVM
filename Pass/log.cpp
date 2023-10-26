#include <cstdio>

extern "C" void routeLogger(char *callerInstruction, char *calleeInstruction) {
    printf("%s <- %s\n", callerInstruction, calleeInstruction);
}

