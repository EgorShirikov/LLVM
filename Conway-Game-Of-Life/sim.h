#define CELL_SIZE 10
#define WIDTH 800
#define HEIGHT 600

#define SIM_X_SIZE (WIDTH / CELL_SIZE)
#define SIM_Y_SIZE (HEIGHT / CELL_SIZE)
#define SIM_DATA_ADR (SIM_X_SIZE * SIM_Y_SIZE)


extern void simSetPixel(unsigned x, unsigned y, unsigned argb);
extern void simFlush();
extern int simRand();
extern void simInit();
extern bool simEvent();
extern void simExit();