#ifndef PIXEL_TESTER_CMD_RUNNER
#define PIXEL_TESTER_CMD_RUNNER

#include <processor/TestProcessor.h>

class CmdRunner {
public:
    CmdRunner(TestProcessor& processor);
    void run();
    void printHelp();
private:
    TestProcessor* processor;
    void cmdHome();
    void cmdLimit();
    void cmdSetSteps();
    void cmdAddSteps();
    void cmdSetAngle();
    void cmdAddAngle();
    void cmdPing();
    void cmdError();
    void cmdHelp();
};

#endif
