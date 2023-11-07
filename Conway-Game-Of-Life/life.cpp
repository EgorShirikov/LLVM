#include "sim.h"

extern "C" unsigned int calcNeighbours(const unsigned int *prevGen, unsigned int y, unsigned int x) {
    unsigned aliveNeighbours = 0;
    for (unsigned newY = y - 1; newY <= y + 1; newY++) {
        for (unsigned newX = x - 1; newX <= x + 1; newX++) {
            if (newX != 4294967295 && newX < SIM_X_SIZE
                && newY != 4294967295 && newY < SIM_Y_SIZE
                && !(newX == x && newY == y)) {
                aliveNeighbours += prevGen[newY * SIM_X_SIZE + newX];
            }
        }
    }
    return aliveNeighbours;
}

extern "C" void calcGen(const unsigned *prevGen, unsigned *nextGen) {
    for (unsigned y = 0; y < SIM_Y_SIZE; y++) {
        for (unsigned x = 0; x < SIM_X_SIZE; x++) {
            unsigned int aliveNeighbours = calcNeighbours(prevGen, y, x);
            if (prevGen[y * SIM_X_SIZE + x] == 0) {
                nextGen[y * SIM_X_SIZE + x] = (aliveNeighbours == 3);
            } else {
                nextGen[y * SIM_X_SIZE + x] = (aliveNeighbours == 2 || aliveNeighbours == 3);
            }
        }
    }
}

extern "C" void drawGen(const unsigned *gen) {
    for (unsigned y = 0; y < SIM_Y_SIZE; y++) {
        for (unsigned x = 0; x < SIM_X_SIZE; x++) {
            simSetPixel(x, y, 0xFF000000 + 0xFF00 * gen[y * SIM_X_SIZE + x]);
        }
    }
    simFlush();
}

extern "C" void initGen(unsigned *gen) {
    for (unsigned y = 0; y < SIM_Y_SIZE; y++) {
        for (unsigned x = 0; x < SIM_X_SIZE; x++) {
            gen[y * SIM_X_SIZE + x] = simRand();
        }
    }
}

int main() {
    unsigned gen1[SIM_DATA_ADR];
    unsigned gen2[SIM_DATA_ADR];
    unsigned *nextGen = gen1;
    unsigned *prevGen = gen2;

    simInit();
    initGen(prevGen);

    while (simEvent()) {
        calcGen(prevGen, nextGen);
        drawGen(prevGen);
        unsigned *tmp = prevGen;
        prevGen = nextGen;
        nextGen = tmp;
    }

    simExit();
    return 0;
}

