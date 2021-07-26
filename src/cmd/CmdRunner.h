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
    int cmdGetPixels();
    int cmdHome();
    int cmdGetLimit();
    int cmdSetLimit();
    int cmdGetSteps();
    int cmdGetStepsTarget();
    int cmdSetSteps();
    int cmdAddSteps();
    int cmdGetAngle();
    int cmdGetAngleTarget();
    int cmdSetAngle();
    int cmdAddAngle();
    int cmdMoving();
    int cmdError();
    int cmdClearError();
    int cmdStatus();
    int cmdPing();
    int cmdHelp();

    void printCmd(const char* cmd, const char* args[], int size, int spaces, const char* description);
};

#endif
