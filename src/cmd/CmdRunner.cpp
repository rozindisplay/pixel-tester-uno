#include "Arduino.h"
#include <cmd/CmdRunner.h>

#include <config/Config.h>
#include <pix/PixConsts.h>

#define ERROR_INVALID_INPUT 1101

CmdRunner::CmdRunner(TestProcessor& processor): processor(&processor) {
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

    int err;

    if(strcmp("pixels", token)==0) {
        err = cmdGetPixels();
    } else if(strcmp("home", token)==0) {
        err = cmdHome();
    } else if (strcmp("limit", token)==0) {
        err = cmdGetLimit();
    } else if (strcmp("set-limit", token)==0) {
        err = cmdSetLimit();
    } else if (strcmp("steps", token)==0) {
        err = cmdGetSteps();
    } else if (strcmp("steps-target", token)==0) {
        err = cmdGetStepsTarget();
    } else if (strcmp("set-steps", token)==0) {
        err = cmdSetSteps();
    } else if (strcmp("add-steps", token)==0) {
        err = cmdAddSteps();
    } else if (strcmp("angle", token)==0) {
        err = cmdGetAngle();
    } else if (strcmp("angle-target", token)==0) {
        err = cmdGetAngleTarget();
    } else if (strcmp("set-angle", token)==0) {
        err = cmdSetAngle();
    } else if (strcmp("add-angle", token)==0) {
        err = cmdAddAngle();
    } else if (strcmp("moving", token)==0) {
        err = cmdMoving();
    } else if (strcmp("error", token)==0) {
        err = cmdError();
    } else if (strcmp("clear-error", token)==0) {
        err = cmdClearError();
    } else if (strcmp("status", token)==0) {
        err = cmdStatus();
    } else if (strcmp("ping", token)==0) {
        err = cmdPing();
    } else if (strcmp("help", token)==0) {
        err = cmdHelp();
    } else {
        Serial.print("ERR CMD: ");
        Serial.println(token);
        cmdHelp();
    }

    if(err!=0) {
        Serial.print("Err: ");
        Serial.println(err);
    }
}

void CmdRunner::printHelp() {
    Serial.println("Pixel-Tester");
    Serial.println();
    Serial.println("Commands: <arg> => arg is required; [arg] => arg is optional");
    
    // pixels <adrs>                          - requests the number of pixels on the node
    // home <adrs> [pixel]                    - runs the home process for the node or pixel
    // limit <adrs> <pixel>                   - requests the pixel's limits
    // set-limit <adrs> <pixel> <l>:<h>       - sets the limits for a pixel
    // steps <adrs> <pixel>                   - requests the pixel's current position in steps from zero
    // steps-target <adrs> <pixel>            - requests the pixel's target position in steps
    // set-steps <adrs> <pixel> <steps>       - sets the position to the given steps
    // add-steps <adrs> <pixel> <steps>       - adds the given steps to the current position
    // angle <adrs> <pixel>                   - requests the pixel's current position in degrees from zero
    // angle-target <adrs> <pixel>            - requests the pixel's target position in degrees from zero
    // set-angle <adrs> <pixel> <angle>       - sets the position to the given angle
    // add-angle <adrs> <pixel> <angle>       - adds the given angle to the current position
    // moving <adrs> [pixel]                  - requests the number pixels currently moving
    // error <adrs>                           - requests the nodes last error code
    // clear-error <adrs>                     - clears the error code
    // status <adrs>                          - makes a request for the current status
    // ping <adrs>                            - makes a ping request
    // help                                   - print this menu


    const char* argsAdrs[] = {"<adrs>"};
    const char* argsAdrsPix[] = {"<adrs>", "<pixel>"};
    const char* argsAdrsOpPix[] = {"<adrs>", "[pixel]"};
    const char* argsAdrsPixLim[] = {"<adrs>", "<pixel>", "<l>:<h>"};
    const char* argsAdrsPixSteps[] = {"<adrs>", "<pixel>", "<steps>"};
    const char* argsAdrsPixAngle[] = {"<adrs>", "<pixel>", "<angle>"};

    // pixels
    printCmd("pixels", argsAdrs, 1, 26, "requests the number of pixels on the node");

    // home
    printCmd("home", argsAdrsOpPix, 2, 20, "runs the home process for the node or pixel");

    // limit
    printCmd("limit", argsAdrsPix, 2, 19, "requests the pixel's limits");

    // set-limit
    printCmd("set-limit", argsAdrsPixLim, 3, 7, "sets the limits for a pixel");

    // steps
    printCmd("steps", argsAdrsPix, 2, 19, "requests the pixel's current position in steps from zero");

    // steps-target
    printCmd("steps-target", argsAdrsPix, 2, 12, "requests the pixel's target position in steps");

    // set-steps
    printCmd("set-steps", argsAdrsPixSteps, 3, 7, "sets the position to the given steps");

    // add-steps
    printCmd("add-steps", argsAdrsPixSteps, 3, 7, "adds the given steps to the current position");

    // angle
    printCmd("angle", argsAdrsPix, 2, 19, "requests the pixel's current position in degrees from zero");

    // angle-target
    printCmd("angle-target", argsAdrsPix, 2, 12, "requests the pixel's target position in degrees from zero");

    // set-angle
    printCmd("set-angle", argsAdrsPixAngle, 3, 7, "sets the position to the given angle");

    // add-angle
    printCmd("add-angle", argsAdrsPixAngle, 3, 7, "adds the given angle to the current position");

    // moving
    printCmd("moving", argsAdrsOpPix, 2, 18, "requests the number pixels currently moving");

    // error
    printCmd("error", argsAdrs, 1, 27, "requests the nodes last error code");

    // clear-error
    printCmd("clear-error", argsAdrs, 1, 21, "clears the error code");

    // status
    printCmd("status", argsAdrs, 1, 26, "makes a request for the status of a pixel");

    // ping
    printCmd("ping", argsAdrs, 1, 28, "makes a ping request");

    // help
    printCmd("help", argsAdrs, 0, 35, "print this menu");
}

void CmdRunner::printCmd(const char* cmd, const char* args[], int argsize, int spaces, const char* description) {
    Serial.print(" ");
    Serial.print(cmd);
    for(int i=0; i<argsize; i++) {
        Serial.print(" ");
        Serial.print(args[i]);
    }

    for(int i=0; i<spaces; i++) {
        Serial.print(" ");
    }
    Serial.print("-");
    Serial.print(" ");
    Serial.println(description);
}

int CmdRunner::cmdGetPixels() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onGetPixels(adrs);
}

int CmdRunner::cmdHome() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    if(ARGUMENTS.getCount()==2) {
        // pixel defined
        int pixel;
        if(!ARGUMENTS.getInt(2, pixel)) {
            return ERROR_INVALID_INPUT;
        }
        return processor->onHome(adrs, pixel);
    } else {
        // pixel not defined
        return processor->onHome(adrs);
    }
}

int CmdRunner::cmdGetLimit() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }
    
    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onGetLimit(adrs, pixel);
}

int CmdRunner::cmdSetLimit() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }
    
    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    int lo;
    int hi;
    if(!ARGUMENTS.getLimits(3, lo, hi)) {
        return ERROR_INVALID_INPUT;
    }

    PixLimit limit(lo, hi);
    return processor->onSetLimit(adrs, pixel, limit);
}

int CmdRunner::cmdGetSteps() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }
    
    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onGetSteps(adrs, pixel);
}

int CmdRunner::cmdGetStepsTarget() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }
    
    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onGetStepsTarget(adrs, pixel);
}

int CmdRunner::cmdSetSteps() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }
    
    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    int steps;
    if(!ARGUMENTS.getInt(3, steps)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onSetSteps(adrs, pixel, steps);
}

int CmdRunner::cmdAddSteps() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }


    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    int steps;
    if(!ARGUMENTS.getInt(3, steps)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onAddSteps(adrs, pixel, steps);
}

int CmdRunner::cmdGetAngle() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }
    
    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onGetAngle(adrs, pixel);
}

int CmdRunner::cmdGetAngleTarget() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }
    
    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onGetAngleTarget(adrs, pixel);
}

int CmdRunner::cmdSetAngle() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }
    
    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    double angle;
    if(!ARGUMENTS.getDouble(3, angle)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onSetAngle(adrs, pixel, angle);
}

int CmdRunner::cmdAddAngle() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    double angle;
    if(!ARGUMENTS.getDouble(3, angle)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onAddAngle(adrs, pixel, angle);
}

int CmdRunner::cmdMoving() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    if(ARGUMENTS.getCount()>2) {
        // pixel given
        int pixel;
        if(!ARGUMENTS.getInt(2, pixel)) {
            return ERROR_INVALID_INPUT;
        }

        return processor->onMoving(adrs, pixel);
    } else {
        // pixel not given
        return processor->onMoving(adrs);
    }
}

int CmdRunner::cmdError() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onError(adrs);
}

int CmdRunner::cmdClearError() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onClearError(adrs);
}

int CmdRunner::cmdStatus() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    int pixel;
    if(!ARGUMENTS.getInt(2, pixel)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onStatus(adrs, pixel);
}

int CmdRunner::cmdPing() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onPing(adrs);
}

int CmdRunner::cmdHelp() {
    printHelp();
    return 0;
}
