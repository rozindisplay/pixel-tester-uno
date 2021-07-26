#ifndef PIXEL_TESTER_TEST_PROCESSOR
#define PIXEL_TESTER_TEST_PROCESSOR

#include <pix/PixModel.h>

class TestProcessor {
public:
    int onGetPixels(int i2cAddress);
    int onHome(int i2cAddress);
    int onHome(int i2cAddress, char pixle);
    int onGetLimit(int i2cAddress, char pixle);
    int onSetLimit(int i2cAddress, char pixle, const PixLimit& limit);
    int onGetSteps(int i2cAddress, char pixle);
    int onGetStepsTarget(int i2cAddress, char pixle);
    int onSetSteps(int i2cAddress, char pixle, int steps);
    int onAddSteps(int i2cAddress, char pixle, int steps);
    int onGetAngle(int i2cAddress, char pixle);
    int onGetAngleTarget(int i2cAddress, char pixle);
    int onSetAngle(int i2cAddress, char pixle, double angle);
    int onAddAngle(int i2cAddress, char pixle, double angle);
    int onMoving(int i2cAddress);
    int onMoving(int i2cAddress, char pixle);
    int onError(int i2cAddress);
    int onClearError(int i2cAddress);
    int onStatus(int i2cAddress, char pixle);
    int onPing(int i2cAddress);
private:
    void logGetPixels(int i2cAddress);
    void logHome(int i2cAddress);
    void logHome(int i2cAddress, char pixle);
    void logGetLimit(int i2cAddress, char pixle);
    void logSetLimit(int i2cAddress, char pixle, const PixLimit& limit);
    void logGetSteps(int i2cAddress, char pixle);
    void logGetStepsTarget(int i2cAddress, char pixle);
    void logSetSteps(int i2cAddress, char pixle, int steps);
    void logAddSteps(int i2cAddress, char pixle, int steps);
    void logGetAngle(int i2cAddress, char pixle);
    void logGetAngleTarget(int i2cAddress, char pixle);
    void logSetAngle(int i2cAddress, char pixle, double angle);
    void logAddAngle(int i2cAddress, char pixle, double angle);
    void logMoving(int i2cAddress);
    void logMoving(int i2cAddress, char pixle);
    void logError(int i2cAddress);
    void logClearError(int i2cAddress);
    void logStatus(int i2cAddress, char pixle);
    void logPing(int i2cAddress);
};

#endif
