#include "Arduino.h"
#include <processor/TestProcessor.h>

void TestProcessor::onHome(char opcode) {
    logHome(opcode);
}

void TestProcessor::onSetLimitsAndHome(char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) {
    logSetLimitsAndHome(opcode, limitP1, limitP2, limitP3, limitP4);
}

void TestProcessor::onSetLimit(char opcode, char pixle, const PixelClientLimit& limit) {
    logSetLimit(opcode, pixle, limit);
}

void TestProcessor::onSetSteps(char opcode, char pixle, int steps) {
    logSetSteps(opcode, pixle, steps);
}

void TestProcessor::onAddSteps(char opcode, char pixle, int steps) {
    logAddSteps(opcode, pixle, steps);
}

void TestProcessor::onSetAngle(char opcode, char pixle, double angle) {
    logSetAngle(opcode, pixle, angle);
}

void TestProcessor::onAddAngle(char opcode, char pixle, double angle) {
    logAddAngle(opcode, pixle, angle);
}

void TestProcessor::logHome(char opcode) {
    Serial.println("CMD=HOME;");
}

void TestProcessor::logSetLimitsAndHome(char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) {
    char buf[256];
    const char format[] = "CMD=SET_LIMITS_AND_HOME; L1_LO=%i; L1_HI=%i; L2_LO=%i; L2_HI=%i; L3_LO=%i; L3_HI=%i; L4_LO=%i; L4_HI=%i;";
    snprintf(buf, 256, format, limitP1.lower, limitP1.upper, limitP2.lower, limitP2.upper, limitP3.lower, limitP3.upper, limitP4.lower, limitP4.upper);
    Serial.println(buf);
}

void TestProcessor::logSetLimit(char opcode, char pixle, const PixelClientLimit& limit) {
    char buf[256];
    const char format[] = "CMD=SET_LIMIT; PIXLE=%i; L_LO=%i; L_HI=%i;";
    snprintf(buf, 256, format, pixle, limit.lower, limit.upper);
    Serial.println(buf);
}

void TestProcessor::logSetSteps(char opcode, char pixle, int steps) {
    char buf[256];
    const char format[] = "CMD=SET_STEPS; PIXLE=%i; STEPS=%i;";
    snprintf(buf, 256, format, pixle, steps);
    Serial.println(buf);
}

void TestProcessor::logAddSteps(char opcode, char pixle, int steps) {
    char buf[256];
    const char format[] = "CMD=ADD_STEPS; PIXLE=%i; STEPS=%i;";
    snprintf(buf, 256, format, pixle, steps);
    Serial.println(buf);
}

void TestProcessor::logSetAngle(char opcode, char pixle, double angle) {
    char buf[256];
    const char format[] = "CMD=SET_ANGLE; PIXLE=%i; ANGLE=";
    snprintf(buf, 256, format, pixle);
    Serial.println(buf);
    Serial.println(angle);
}

void TestProcessor::logAddAngle(char opcode, char pixle, double angle) {
    char buf[256];
    const char format[] = "CMD=ADD_ANGLE; PIXLE=%i; ANGLE=";
    snprintf(buf, 256, format, pixle);
    Serial.print(buf);
    Serial.println(angle);
}
