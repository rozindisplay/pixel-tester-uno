#include "Arduino.h"
#include <cmd/CmdRunner.h>

#include <config/Config.h>
#include <PixelClientConsts.h>

CmdRunner::CmdRunner(PixelClientProcessor& processor): processor(&processor) {
}

void CmdRunner::run() {
    if(Serial.available()==0) {
        return;
    }
    
    if(!ARGUMENTS.next()) {
        return;
    }

    char* token;
    if(!ARGUMENTS.getString(0, token)) {
        return;
    }

    if(strcmp("home", token)==0) {
        cmdHome();
    } else if (strcmp("limit", token)==0) {
        cmdLimit();
    } else if (strcmp("set-steps", token)==0) {
        cmdSetSteps();
    } else if (strcmp("add-steps", token)==0) {
        cmdAddSteps();
    } else if (strcmp("set-angle", token)==0) {
        cmdSetAngle();
    } else if (strcmp("add-angle", token)==0) {
        cmdAddAngle();
    } else if (strcmp("help", token)==0) {
        cmdHelp();
    } else {
        Serial.print("ERROR: Unknown Command : ");
        Serial.println(token);
        cmdHelp();
    }
}

void CmdRunner::printHelp() {
    Serial.println("pixel-tester-uno");
    Serial.println();
    Serial.println("Commands:");
    Serial.println(" home                                         - runs the home process");
    Serial.println(" home <lo>:<hi> <lo>:<hi> <lo>:<hi> <lo>:<hi> - sets the limits for all pixles and runs the home process");
    Serial.println(" limit <pixle> <lo>:<hi>                      - sets the limits for the given pixle");
    Serial.println(" set-steps <pixle> <steps>                    - sets the position to the given steps");
    Serial.println(" add-steps <pixle> <steps>                    - adds the given steps to the current position");
    Serial.println(" set-angle <pixle> <angle>                    - sets the position to the given angle");
    Serial.println(" add-angle <pixle> <angle>                    - adds the given angle to the current position");
    Serial.println(" help                                         - print this menu");
}

void CmdRunner::cmdHome() {
    if(ARGUMENTS.getCount()==1) {
        processor->onHome(OP_HOME);
        return;
    } else if(ARGUMENTS.getCount()==5) {
        int lo = 0;
        int hi = 0;

        if(!ARGUMENTS.getLimits(1, lo, hi)) {
            return;
        }
        PixelClientLimit l1(lo, hi);

        if(!ARGUMENTS.getLimits(2, lo, hi)) {
            return;
        }
        PixelClientLimit l2(lo, hi);

        if(!ARGUMENTS.getLimits(3, lo, hi)) {
            return;
        }
        PixelClientLimit l3(lo, hi);

        if(!ARGUMENTS.getLimits(4, lo, hi)) {
            return;
        }
        PixelClientLimit l4(lo, hi);

        processor->onSetLimitsAndHome(OP_SET_LIMITS_AND_HOME, l1, l2, l3, l4);
    } else {
        // TODO error
    }
}

void CmdRunner::cmdLimit() {
    int pixle;
    if(!ARGUMENTS.getInt(1, pixle)) {
        return;
    }

    int lo;
    int hi;
    if(!ARGUMENTS.getLimits(2, lo, hi)) {
        return;
    }

    PixelClientLimit limit(lo, hi);
    processor->onSetLimit(OP_SET_LIMITS, pixle, limit);
}

void CmdRunner::cmdSetSteps() {
    int pixle;
    if(!ARGUMENTS.getInt(1, pixle)) {
        return;
    }

    int steps;
    if(!ARGUMENTS.getInt(2, steps)) {
        return;
    }

    processor->onSetSteps(OP_SET_STEPS, pixle, steps);
}

void CmdRunner::cmdAddSteps() {
    int pixle;
    if(!ARGUMENTS.getInt(1, pixle)) {
        return;
    }

    int steps;
    if(!ARGUMENTS.getInt(2, steps)) {
        return;
    }

    processor->onAddSteps(OP_ADD_STEPS, pixle, steps);
}

void CmdRunner::cmdSetAngle() {
    int pixle;
    if(!ARGUMENTS.getInt(1, pixle)) {
        return;
    }

    double angle;
    if(!ARGUMENTS.getDouble(2, angle)) {
        return;
    }

    processor->onSetAngle(OP_SET_ANGLE, pixle, angle);
}

void CmdRunner::cmdAddAngle() {
    int pixle;
    if(!ARGUMENTS.getInt(1, pixle)) {
        return;
    }

    double angle;
    if(!ARGUMENTS.getDouble(2, angle)) {
        return;
    }

    processor->onAddAngle(OP_ADD_ANGLE, pixle, angle);
}


void CmdRunner::cmdHelp() {
    printHelp();
}
