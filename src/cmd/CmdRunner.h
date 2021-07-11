#ifndef PIXEL_TESTER_CMD_RUNNER
#define PIXEL_TESTER_CMD_RUNNER

#include "PixelClientProcessor.h"

class CmdRunner {
public:
    CmdRunner(PixelClientProcessor& processor);
    void run();
    void printHelp();
private:
    PixelClientProcessor* processor;
    void cmdHome();
    void cmdLimit();
    void cmdSetSteps();
    void cmdAddSteps();
    void cmdSetAngle();
    void cmdAddAngle();
    void cmdHelp();
};

#endif
