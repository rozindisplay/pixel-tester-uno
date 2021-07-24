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
    int cmdInit();
    int cmdHome();
    int cmdClearError();
    int cmdLimit();
    int cmdSetSteps();
    int cmdAddSteps();
    int cmdSetAngle();
    int cmdAddAngle();
    int cmdPing();
    int cmdError();
    int cmdMoving();
    int cmdStatus();
    int cmdHelp();

    void printCmd(const char* cmd, const char* args[], int size, int spaces, const char* description);
};

#endif
