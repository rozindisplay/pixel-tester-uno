#ifndef PIXEL_TESTER_TEST_PROCESSOR
#define PIXEL_TESTER_TEST_PROCESSOR

#include <pix/PixModel.h>

class TestProcessor {
public:
    int onInit(int i2cAddress, const PixLimit& limitP1, const PixLimit& limitP2, const PixLimit& limitP3, const PixLimit& limitP4);
    int onHome(int i2cAddress);
    int onClearError(int i2cAddress);
    int onSetLimit(int i2cAddress, char pixle, const PixLimit& limit);
    int onSetSteps(int i2cAddress, char pixle, int steps);
    int onAddSteps(int i2cAddress, char pixle, int steps);
    int onSetAngle(int i2cAddress, char pixle, double angle);
    int onAddAngle(int i2cAddress, char pixle, double angle);
    int onPing(int i2cAddress);
    int onError(int i2cAddress);
    int onMoving(int i2cAddress);
    int onStatus(int i2cAddress, char pixle);
private:
    void logInit(int i2cAddress, const PixLimit& limitP1, const PixLimit& limitP2, const PixLimit& limitP3, const PixLimit& limitP4);
    void logHome(int i2cAddress);
    void logClearError(int i2cAddress);
    void logSetLimit(int i2cAddress, char pixle, const PixLimit& limit);
    void logSetSteps(int i2cAddress, char pixle, int steps);
    void logAddSteps(int i2cAddress, char pixle, int steps);
    void logSetAngle(int i2cAddress, char pixle, double angle);
    void logAddAngle(int i2cAddress, char pixle, double angle);
    void logPing(int i2cAddress);
    void logError(int i2cAddress);
    void logMoving(int i2cAddress);
    void logStatus(int i2cAddress, char pixle);
};

#endif
