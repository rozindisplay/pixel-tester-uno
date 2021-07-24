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

    if(strcmp("init", token)==0) {
        err = cmdInit();
    } else if(strcmp("home", token)==0) {
        err = cmdHome();
    } else if (strcmp("clear-error", token)==0) {
        err = cmdClearError();
    } else if (strcmp("limit", token)==0) {
        err = cmdLimit();
    } else if (strcmp("set-steps", token)==0) {
        err = cmdSetSteps();
    } else if (strcmp("add-steps", token)==0) {
        err = cmdAddSteps();
    } else if (strcmp("set-angle", token)==0) {
        err = cmdSetAngle();
    } else if (strcmp("add-angle", token)==0) {
        err = cmdAddAngle();
    } else if (strcmp("ping", token)==0) {
        err = cmdPing();
    } else if (strcmp("error", token)==0) {
        err = cmdError();
    } else if (strcmp("moving", token)==0) {
        err = cmdMoving();
    } else if (strcmp("status", token)==0) {
        err = cmdStatus();
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
    Serial.println("Commands:");
    
    // init <adrs> <l>:<h> <l>:<h> <l>:<h> <l>:<h> - sets the limits for all pixels and runs the home process
    // home <adrs>                                 - runs the home process
    // clear-error <adrs>                          - clears and resets the error code
    // limit <adrs> <pixel> <l>:<h>                - sets the limits for the given pixel
    // set-steps <adrs> <pixel> <steps>            - sets the position to the given steps
    // set-angle <adrs> <pixel> <angle>            - sets the position to the given angle
    // ping <adrs>                                 - makes a ping request
    // error <adrs>                                - makes a request for an error code
    // moving <adrs>                               - makes a request for the number of pixels currently moving
    // status <adrs>                               - makes a request for the current status
    // help                                        - print this menu

    // init
    const char* initArgs[] = {"<adrs>", "<l>:<h>", "<l>:<h>", "<l>:<h>", "<l>:<h>"};
    printCmd("init", initArgs, 5, 1, "sets the limits for all pixels and runs the home process");

    // home
    const char* adrsArgs[] = {"<adrs>"};
    printCmd("home", adrsArgs, 1, 33, "runs the home process");

    // clear errors
    printCmd("clear-error", adrsArgs, 1, 26, "clears and resets the error code");

    // limit
    const char* limitArgs[] = {"<adrs>", "<pixel>", "<l>:<h>"};
    printCmd("limit", limitArgs, 3, 16, "clears and resets the error code");

    // set-steps
    const char* stepsArgs[] = {"<adrs>", "<pixel>", "<steps>"};
    printCmd("set-steps", stepsArgs, 3, 12, "sets the position to the given steps");

    // add-steps
    printCmd("add-steps", stepsArgs, 3, 12, "adds the given steps to the current position");

    // set-angle
    const char* angleArgs[] = {"<adrs>", "<pixel>", "<angle>"};
    printCmd("set-angle", angleArgs, 3, 12, "sets the position to the given angle");

    // add-angle
    printCmd("add-angle", angleArgs, 3, 12, "adds the given angle to the current position");

    // ping
    printCmd("ping", adrsArgs, 1, 33, "makes a ping request");

    // error
    printCmd("error", adrsArgs, 1, 32, "makes a request for an error code");

    // moving
    printCmd("moving", adrsArgs, 1, 31, "makes a request for the number of pixels currently moving");

    // status
    printCmd("status", adrsArgs, 1, 31, "makes a request for the current status");

    // help
    printCmd("help", adrsArgs, 0, 40, "print this menu");
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

int CmdRunner::cmdInit() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }
    
    int lo = 0;
    int hi = 0;
    if(!ARGUMENTS.getLimits(2, lo, hi)) {
        return ERROR_INVALID_INPUT;
    }
    PixLimit l1(lo, hi);

    if(!ARGUMENTS.getLimits(3, lo, hi)) {
        return ERROR_INVALID_INPUT;
    }
    PixLimit l2(lo, hi);

    if(!ARGUMENTS.getLimits(4, lo, hi)) {
        return ERROR_INVALID_INPUT;
    }
    PixLimit l3(lo, hi);

    if(!ARGUMENTS.getLimits(5, lo, hi)) {
        return ERROR_INVALID_INPUT;
    }
    PixLimit l4(lo, hi);

    return processor->onInit(adrs, l1, l2, l3, l4);
}

int CmdRunner::cmdHome() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        // todo
        return ERROR_INVALID_INPUT;
    }

    return processor->onHome(adrs);
}

int CmdRunner::cmdClearError() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onClearError(adrs);
}

int CmdRunner::cmdLimit() {
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

int CmdRunner::cmdPing() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onPing(adrs);
}

int CmdRunner::cmdError() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onError(adrs);
}

int CmdRunner::cmdMoving() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return ERROR_INVALID_INPUT;
    }

    return processor->onMoving(adrs);
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

int CmdRunner::cmdHelp() {
    printHelp();
    return 0;
}
