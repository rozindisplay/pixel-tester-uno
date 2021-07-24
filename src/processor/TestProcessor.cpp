#include "Arduino.h"
#include <processor/TestProcessor.h>
#include <config/Config.h>

int TestProcessor::onInit(int i2cAddress, const Limit& limitP1, const Limit& limitP2, const Limit& limitP3, const Limit& limitP4) {
    logInit(i2cAddress, limitP1, limitP2, limitP3, limitP4);
    return PIXEL_WRITER.init(i2cAddress, limitP1, limitP2, limitP3, limitP4);
}

int TestProcessor::onHome(int i2cAddress) {
    logHome(i2cAddress);
    return PIXEL_WRITER.home(i2cAddress);
}

int TestProcessor::onClearError(int i2cAddress) {
    logClearError(i2cAddress);
    return PIXEL_WRITER.clearErrorCode(i2cAddress);
}

int TestProcessor::onSetLimit(int i2cAddress, char pixle, const Limit& limit) {
    logSetLimit(i2cAddress, pixle, limit);
    return PIXEL_WRITER.setLimit(i2cAddress, pixle, limit);
}

int TestProcessor::onSetSteps(int i2cAddress, char pixle, int steps) {
    logSetSteps(i2cAddress, pixle, steps);
    return PIXEL_WRITER.setSteps(i2cAddress, pixle, steps);
}

int TestProcessor::onAddSteps(int i2cAddress, char pixle, int steps) {
    logAddSteps(i2cAddress, pixle, steps);
    return PIXEL_WRITER.addSteps(i2cAddress, pixle, steps);
}

int TestProcessor::onSetAngle(int i2cAddress, char pixle, double angle) {
    logSetAngle(i2cAddress, pixle, angle);
    return PIXEL_WRITER.setAngle(i2cAddress, pixle, angle);
}

int TestProcessor::onAddAngle(int i2cAddress, char pixle, double angle) {
    logAddAngle(i2cAddress, pixle, angle);
    return PIXEL_WRITER.addAngle(i2cAddress, pixle, angle);
}

int TestProcessor::onPing(int i2cAddress) {
    logPing(i2cAddress);

    int err = PIXEL_WRITER.requestPing(i2cAddress);
    if(err==0) {
        Serial.println(" > good");
    } else {
        Serial.println(" > failed");
    }

    return err;
}

int TestProcessor::onError(int i2cAddress) {
    logError(i2cAddress);

    int code;
    int err = PIXEL_WRITER.requestErrorCode(i2cAddress, code);

    Serial.print(" > ");
    Serial.println(code);

    return err;
}

int TestProcessor::onMoving(int i2cAddress) {
    logMoving(i2cAddress);
    
    unsigned char count;
    int err = PIXEL_WRITER.requestMovingCount(i2cAddress, count);

    Serial.print(" > ");
    Serial.println(count);

    return err;
}

int TestProcessor::onStatus(int i2cAddress) {
    
    logStatus(i2cAddress);
    
    NodeStatus statusSet;
    int err = PIXEL_WRITER.requestStatus(i2cAddress, statusSet);
    
    Serial.print(" > ");
    Serial.print("status");
    Serial.println(':');
    Serial.print(' ');
    Serial.print(' ');
    Serial.print("error");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(statusSet.error);

    int size = statusSet.size();
    for(int i=0; i<size; i++) {
        PixelStatus status = statusSet[i];

        Serial.print(' ');
        Serial.print(' ');
        Serial.print("pix");
        Serial.print("[");
        Serial.print(i);
        Serial.print("].");
        Serial.print("moving: ");
        Serial.println(status.moving);
        
        Serial.print(' ');
        Serial.print(' ');
        Serial.print("pix");
        Serial.print("[");
        Serial.print(i);
        Serial.print("].");
        Serial.print("target: ");
        Serial.println(status.target);

        Serial.print(' ');
        Serial.print(' ');
        Serial.print("pix");
        Serial.print("[");
        Serial.print(i);
        Serial.print("].");
        Serial.print("steps: ");
        Serial.println(status.steps);

        Serial.print(' ');
        Serial.print(' ');
        Serial.print("pix");
        Serial.print("[");
        Serial.print(i);
        Serial.print("].");
        Serial.print("angle: ");
        Serial.println(status.angle);

        Serial.print(' ');
        Serial.print(' ');
        Serial.print("pix");
        Serial.print("[");
        Serial.print(i);
        Serial.print("].");
        Serial.print("limit: ");
        Serial.print(status.limit.lower);
        Serial.print(':');
        Serial.println(status.limit.upper);
    }

    return err;
}

void TestProcessor::logInit(int i2cAddress, const Limit& limitP1, const Limit& limitP2, const Limit& limitP3, const Limit& limitP4) {
    Serial.print("init");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print(limitP1.lower);
    Serial.print(':');
    Serial.print(limitP1.upper);
    Serial.print(' ');
    Serial.print(limitP2.lower);
    Serial.print(':');
    Serial.print(limitP2.upper);
    Serial.print(' ');
    Serial.print(limitP3.lower);
    Serial.print(':');
    Serial.print(limitP3.upper);
    Serial.print(' ');
    Serial.print(limitP4.lower);
    Serial.print(':');
    Serial.print(limitP4.upper);
    Serial.println();
}

void TestProcessor::logHome(int i2cAddress) {
    Serial.print("home");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.println();
}

void TestProcessor::logClearError(int i2cAddress) {
    Serial.print("clear-error");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.println();
}

void TestProcessor::logSetLimit(int i2cAddress, char pixle, const Limit& limit) {
    Serial.print("limit");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixle);
    Serial.print(' ');
    Serial.print(limit.lower);
    Serial.print(':');
    Serial.print(limit.upper);
    Serial.println();
}

void TestProcessor::logSetSteps(int i2cAddress, char pixle, int steps) {
    Serial.println("set-steps");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixle);
    Serial.print(' ');
    Serial.print(steps);
    Serial.println();
}

void TestProcessor::logAddSteps(int i2cAddress, char pixle, int steps) {
    Serial.println("add-steps");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixle);
    Serial.print(' ');
    Serial.print(steps);
    Serial.println();
}

void TestProcessor::logSetAngle(int i2cAddress, char pixle, double angle) {
    Serial.println("set-angle");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixle);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println();
}

void TestProcessor::logAddAngle(int i2cAddress, char pixle, double angle) {
    Serial.println("add-angle");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixle);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println();
}

void TestProcessor::logPing(int i2cAddress) {
    Serial.print("ping");
    Serial.print(':');
    Serial.print(' ');
    Serial.println(i2cAddress);
}

void TestProcessor::logError(int i2cAddress) {
    Serial.print("error");
    Serial.print(':');
    Serial.print(' ');
    Serial.println(i2cAddress);
}

void TestProcessor::logMoving(int i2cAddress) {
    Serial.print("moving");
    Serial.print(':');
    Serial.print(' ');
    Serial.println(i2cAddress);
}

void TestProcessor::logStatus(int i2cAddress) {
    Serial.print("status");
    Serial.print(':');
    Serial.print(' ');
    Serial.println(i2cAddress);
}
