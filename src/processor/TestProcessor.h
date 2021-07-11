#ifndef PIXEL_TESTER_TEST_PROCESSOR
#define PIXEL_TESTER_TEST_PROCESSOR

#include "PixelClientProcessor.h"

class TestProcessor: public PixelClientProcessor  {
public:
    void onHome(char opcode);
    void onSetLimitsAndHome(char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4);
    void onSetLimit(char opcode, char pixle, const PixelClientLimit& limit);
    void onSetSteps(char opcode, char pixle, int steps);
    void onAddSteps(char opcode, char pixle, int steps);
    void onSetAngle(char opcode, char pixle, double angle);
    void onAddAngle(char opcode, char pixle, double angle);
private:
    void logHome(char opcode);
    void logSetLimitsAndHome(char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4);
    void logSetLimit(char opcode, char pixle, const PixelClientLimit& limit);
    void logSetSteps(char opcode, char pixle, int steps);
    void logAddSteps(char opcode, char pixle, int steps);
    void logSetAngle(char opcode, char pixle, double angle);
    void logAddAngle(char opcode, char pixle, double angle);
};

#endif
