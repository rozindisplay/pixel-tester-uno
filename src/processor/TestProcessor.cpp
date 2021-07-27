#include "Arduino.h"
#include <processor/TestProcessor.h>
#include <config/Config.h>

int TestProcessor::onGetPixels(int i2cAddress) {
    logGetPixels(i2cAddress);

    unsigned char count;
    int err = PIXEL_WRITER.requestPixel(i2cAddress, count);
    if(err==0) {
        Serial.print(" > ");
        Serial.println(count);
    } else {
        Serial.print(" > ");
        Serial.println("failed");
    }

    return err;
}

int TestProcessor::onHome(int i2cAddress) {
    logHome(i2cAddress);
    return PIXEL_WRITER.home(i2cAddress);
}

int TestProcessor::onHome(int i2cAddress, char pixel) {
    logHome(i2cAddress, pixel);
    return PIXEL_WRITER.home(i2cAddress, pixel);
}

int TestProcessor::onGetLimit(int i2cAddress, char pixel) {
    logGetLimit(i2cAddress, pixel);
    
    PixLimit limit;
    int err = PIXEL_WRITER.requestLimit(i2cAddress, pixel, limit);
    if(err==0) {
        Serial.print(" > ");
        Serial.print(limit.lower);
        Serial.print(':');
        Serial.print(limit.upper);
        Serial.println();
    } else {
        Serial.print(" > ");
        Serial.println("failed");
    }

    return err;
}

int TestProcessor::onSetLimit(int i2cAddress, char pixel, const PixLimit& limit) {
    logSetLimit(i2cAddress, pixel, limit);
    return PIXEL_WRITER.setLimit(i2cAddress, pixel, limit);
}

int TestProcessor::onGetSteps(int i2cAddress, char pixel) {
    logGetSteps(i2cAddress, pixel);

    int steps;
    int err = PIXEL_WRITER.requestSteps(i2cAddress, pixel, steps);
    if(err==0) {
        Serial.print(" > ");
        Serial.println(steps);
    } else {
        Serial.println(" > ");
        Serial.println("failed");
    }

    return err;
}

int TestProcessor::onGetStepsTarget(int i2cAddress, char pixel) {
    logGetStepsTarget(i2cAddress, pixel);

    int steps;
    int err = PIXEL_WRITER.requestTargetSteps(i2cAddress, pixel, steps);
    if(err==0) {
        Serial.print(" > ");
        Serial.println(steps);
    } else {
        Serial.println(" > ");
        Serial.println("failed");
    }

    return err;
}


int TestProcessor::onSetSteps(int i2cAddress, char pixel, int steps) {
    logSetSteps(i2cAddress, pixel, steps);
    return PIXEL_WRITER.setSteps(i2cAddress, pixel, steps);
}

int TestProcessor::onAddSteps(int i2cAddress, char pixel, int steps) {
    logAddSteps(i2cAddress, pixel, steps);
    return PIXEL_WRITER.addSteps(i2cAddress, pixel, steps);
}

int TestProcessor::onGetAngle(int i2cAddress, char pixel) {
    logGetAngle(i2cAddress, pixel);

    double angle;
    int err = PIXEL_WRITER.requestAngle(i2cAddress, pixel, angle);
    if(err==0) {
        Serial.print(" > ");
        Serial.println(angle);
    } else {
        Serial.println(" > ");
        Serial.println("failed");
    }

    return err;
}

int TestProcessor::onGetAngleTarget(int i2cAddress, char pixel) {
    logGetAngleTarget(i2cAddress, pixel);

    double angle;
    int err = PIXEL_WRITER.requestTargetAngle(i2cAddress, pixel, angle);
    if(err==0) {
        Serial.print(" > ");
        Serial.println(angle);
    } else {
        Serial.println(" > ");
        Serial.println("failed");
    }

    return err;
}

int TestProcessor::onSetAngle(int i2cAddress, char pixel, double angle) {
    logSetAngle(i2cAddress, pixel, angle);
    return PIXEL_WRITER.setAngle(i2cAddress, pixel, angle);
}

int TestProcessor::onAddAngle(int i2cAddress, char pixel, double angle) {
    logAddAngle(i2cAddress, pixel, angle);
    return PIXEL_WRITER.addAngle(i2cAddress, pixel, angle);
}

int TestProcessor::onMoving(int i2cAddress) {
    logMoving(i2cAddress);
    
    unsigned char count;
    int err = PIXEL_WRITER.requestMoving(i2cAddress, count);
    if(err==0) {
        Serial.print(" > ");
        Serial.println(count);
    } else {
        Serial.println(" > ");
        Serial.println("failed");
    }

    return err;
}

int TestProcessor::onMoving(int i2cAddress, char pixel) {
    logMoving(i2cAddress, pixel);
    
    bool isMoving;
    int err = PIXEL_WRITER.requestIsMoving(i2cAddress, pixel, isMoving);
    if(err==0) {
        Serial.print(" > ");
        Serial.println(isMoving);
    } else {
        Serial.println(" > ");
        Serial.println("failed");
    }

    return err;
}

int TestProcessor::onError(int i2cAddress) {
    logError(i2cAddress);

    int code;
    int err = PIXEL_WRITER.requestErrorCode(i2cAddress, code);
    if(err==0) {
        Serial.print(" > ");
        Serial.println(code);
    } else {
        Serial.println(" > ");
        Serial.println("failed");
    }

    return err;
}

int TestProcessor::onClearError(int i2cAddress) {
    logClearError(i2cAddress);
    return PIXEL_WRITER.clearErrorCode(i2cAddress);
}

int TestProcessor::onStatus(int i2cAddress, char pixel) {
    
    logStatus(i2cAddress, pixel);
    
    PixStatus status;
    int err = PIXEL_WRITER.requestStatus(i2cAddress, pixel, status);
    if(err!=0) {
        Serial.println(" > failed");
        return err;
    }

    Serial.print(" > ");
    Serial.print("moving = ");
    Serial.println(status.moving);
    
    Serial.print(" > ");
    Serial.print("target = ");
    Serial.println(status.target);

    Serial.print(" > ");
    Serial.print("steps = ");
    Serial.println(status.steps);

    Serial.print(" > ");
    Serial.print("angle = ");
    Serial.println(status.angle);

    Serial.print(" > ");
    Serial.print("limit = ");
    Serial.print(status.limit.lower);
    Serial.print(':');
    Serial.println(status.limit.upper);

    return err;
}

int TestProcessor::onPing(int i2cAddress) {
    logPing(i2cAddress);

    int err = PIXEL_WRITER.requestPing(i2cAddress);
    if(err==0) {
        Serial.print(" > ");
        Serial.println("success");
    } else {
        Serial.print(" > ");
        Serial.println("failed");
    }

    return err;
}

void TestProcessor::logGetPixels(int i2cAddress) {
    Serial.print("pixels");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.println();
}

void TestProcessor::logHome(int i2cAddress) {
    Serial.print("home");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.println();
}

void TestProcessor::logHome(int i2cAddress, char pixel) {
    Serial.print("home");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixel);
    Serial.println();
}

void TestProcessor::logGetLimit(int i2cAddress, char pixel) {
    Serial.print("limit");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixel);
    Serial.println();
}

void TestProcessor::logSetLimit(int i2cAddress, char pixel, const PixLimit& limit) {
    Serial.print("limit");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixel);
    Serial.print(' ');
    Serial.print(limit.lower);
    Serial.print(':');
    Serial.print(limit.upper);
    Serial.println();
}

void TestProcessor::logGetSteps(int i2cAddress, char pixel) {
    Serial.print("steps");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.println((int)pixel);
}

void TestProcessor::logGetStepsTarget(int i2cAddress, char pixel) {
    Serial.print("steps-target");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.println((int)pixel);
}

void TestProcessor::logSetSteps(int i2cAddress, char pixel, int steps) {
    Serial.print("set-steps");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixel);
    Serial.print(' ');
    Serial.print(steps);
    Serial.println();
}

void TestProcessor::logAddSteps(int i2cAddress, char pixel, int steps) {
    Serial.print("add-steps");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixel);
    Serial.print(' ');
    Serial.print(steps);
    Serial.println();
}

void TestProcessor::logGetAngle(int i2cAddress, char pixel) {
    Serial.print("angle");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.println((int)pixel);
}

void TestProcessor::logGetAngleTarget(int i2cAddress, char pixel) {
    Serial.print("angle-target");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.println((int)pixel);
}

void TestProcessor::logSetAngle(int i2cAddress, char pixel, double angle) {
    Serial.print("set-angle");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixel);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println();
}

void TestProcessor::logAddAngle(int i2cAddress, char pixel, double angle) {
    Serial.print("add-angle");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.print((int)pixel);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println();
}

void TestProcessor::logMoving(int i2cAddress) {
    Serial.print("moving");
    Serial.print(':');
    Serial.print(' ');
    Serial.println(i2cAddress);
}

void TestProcessor::logMoving(int i2cAddress, char pixel) {
    Serial.print("moving");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.println((int)pixel);
}

void TestProcessor::logError(int i2cAddress) {
    Serial.print("error");
    Serial.print(':');
    Serial.print(' ');
    Serial.println(i2cAddress);
}

void TestProcessor::logClearError(int i2cAddress) {
    Serial.print("clear-error");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.println();
}

void TestProcessor::logStatus(int i2cAddress, char pixel) {
    Serial.print("status");
    Serial.print(':');
    Serial.print(' ');
    Serial.print(i2cAddress);
    Serial.print(' ');
    Serial.println((int)pixel);
}

void TestProcessor::logPing(int i2cAddress) {
    Serial.print("ping");
    Serial.print(':');
    Serial.print(' ');
    Serial.println(i2cAddress);
}
