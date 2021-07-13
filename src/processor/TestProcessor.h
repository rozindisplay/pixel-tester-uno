#ifndef PIXEL_TESTER_TEST_PROCESSOR
#define PIXEL_TESTER_TEST_PROCESSOR

#include "PixelClientProcessor.h"

class TestProcessor {
public:
    void onHome(int i2cAddress, char opcode);
    void onSetLimitsAndHome(int i2cAddress, char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4);
    void onSetLimit(int i2cAddress, char opcode, char pixle, const PixelClientLimit& limit);
    void onSetSteps(int i2cAddress, char opcode, char pixle, int steps);
    void onAddSteps(int i2cAddress, char opcode, char pixle, int steps);
    void onSetAngle(int i2cAddress, char opcode, char pixle, double angle);
    void onAddAngle(int i2cAddress, char opcode, char pixle, double angle);
private:
    void logHome(int i2cAddress, char opcode);
    void logSetLimitsAndHome(int i2cAddress, char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4);
    void logSetLimit(int i2cAddress, char opcode, char pixle, const PixelClientLimit& limit);
    void logSetSteps(int i2cAddress, char opcode, char pixle, int steps);
    void logAddSteps(int i2cAddress, char opcode, char pixle, int steps);
    void logSetAngle(int i2cAddress, char opcode, char pixle, double angle);
    void logAddAngle(int i2cAddress, char opcode, char pixle, double angle);
};

#endif
