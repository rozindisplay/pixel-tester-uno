#include "Arduino.h"
#include <processor/TestProcessor.h>
#include <config/Config.h>

void TestProcessor::onHome(int i2cAddress, char opcode) {
    logHome(i2cAddress, opcode);
    PIXEL_WRITER.home(i2cAddress);
}

void TestProcessor::onSetLimitsAndHome(int i2cAddress, char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) {
    logSetLimitsAndHome(i2cAddress, opcode, limitP1, limitP2, limitP3, limitP4);
    PIXEL_WRITER.setLimitsAndHome(i2cAddress, limitP1, limitP2, limitP3, limitP4);
}

void TestProcessor::onSetLimit(int i2cAddress, char opcode, char pixle, const PixelClientLimit& limit) {
    logSetLimit(i2cAddress, opcode, pixle, limit);
    PIXEL_WRITER.setLimit(i2cAddress, pixle, limit);
}

void TestProcessor::onSetSteps(int i2cAddress, char opcode, char pixle, int steps) {
    logSetSteps(i2cAddress, opcode, pixle, steps);
    PIXEL_WRITER.setSteps(i2cAddress, pixle, steps);
}

void TestProcessor::onAddSteps(int i2cAddress, char opcode, char pixle, int steps) {
    logAddSteps(i2cAddress, opcode, pixle, steps);
    PIXEL_WRITER.addSteps(i2cAddress, pixle, steps);
}

void TestProcessor::onSetAngle(int i2cAddress, char opcode, char pixle, double angle) {
    logSetAngle(i2cAddress, opcode, pixle, angle);
    PIXEL_WRITER.setAngle(i2cAddress, pixle, angle);
}

void TestProcessor::onAddAngle(int i2cAddress, char opcode, char pixle, double angle) {
    logAddAngle(i2cAddress, opcode, pixle, angle);
    PIXEL_WRITER.addAngle(i2cAddress, pixle, angle);
}

void TestProcessor::logHome(int i2cAddress, char opcode) {
    Serial.print("HOME: ");
    Serial.print(i2cAddress);
    Serial.println();
}

void TestProcessor::logSetLimitsAndHome(int i2cAddress, char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) {
    Serial.print("SET_LIMITS_AND_HOME: ");
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

void TestProcessor::logSetLimit(int i2cAddress, char opcode, char pixle, const PixelClientLimit& limit) {
    Serial.print("SET_LIMIT: ");
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixle);
    Serial.print(' ');
    Serial.print(limit.lower);
    Serial.print(':');
    Serial.print(limit.upper);
    Serial.println();
}

void TestProcessor::logSetSteps(int i2cAddress, char opcode, char pixle, int steps) {
    Serial.println("SET_STEPS: ");
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixle);
    Serial.print(' ');
    Serial.print(steps);
    Serial.println();
}

void TestProcessor::logAddSteps(int i2cAddress, char opcode, char pixle, int steps) {
    Serial.println("ADD_STEPS: ");
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixle);
    Serial.print(' ');
    Serial.print(steps);
    Serial.println();
}

void TestProcessor::logSetAngle(int i2cAddress, char opcode, char pixle, double angle) {
    Serial.println("SET_ANGLE: ");
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixle);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println();
}

void TestProcessor::logAddAngle(int i2cAddress, char opcode, char pixle, double angle) {
    Serial.println("ADD_ANGLE: ");
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixle);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println();
}
