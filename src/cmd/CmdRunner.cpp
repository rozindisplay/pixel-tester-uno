#include "Arduino.h"
#include <cmd/CmdRunner.h>

#include <config/Config.h>
#include <PixelClientConsts.h>

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
    } else if (strcmp("ping", token)==0) {
        cmdPing();
    } else if (strcmp("error", token)==0) {
        cmdError();
    } else if (strcmp("help", token)==0) {
        cmdHelp();
    } else {
        Serial.print("ERR CMD: ");
        Serial.println(token);
        cmdHelp();
    }
}

void CmdRunner::printHelp() {
    Serial.println("Pixel-Tester");
    Serial.println();
    Serial.println("Commands:");
    Serial.println(" home <adrs>                                 - runs the home process");
    Serial.println(" home <adrs> <l>:<h> <l>:<h> <l>:<h> <l>:<h> - sets the limits for all pixles and runs the home process");
    Serial.println(" limit <adrs> <pixle> <lo>:<hi>              - sets the limits for the given pixle");
    Serial.println(" set-steps <adrs> <pixle> <steps>            - sets the position to the given steps");
    Serial.println(" add-steps <adrs> <pixle> <steps>            - adds the given steps to the current position");
    Serial.println(" set-angle <adrs> <pixle> <angle>            - sets the position to the given angle");
    Serial.println(" add-angle <adrs> <pixle> <angle>            - adds the given angle to the current position");
    Serial.println(" ping <adrs>                                 - makes a ping request");
    Serial.println(" error <adrs>                                - makes a request for an error code");
    Serial.println(" help                                        - print this menu");
}

void CmdRunner::cmdHome() {
    if(ARGUMENTS.getCount()==2) {
        int adrs;
        if(!ARGUMENTS.getInt(1, adrs)) {
            return;
        }

        processor->onHome(adrs);
        return;
    } else if(ARGUMENTS.getCount()==6) {
        int adrs;
        if(!ARGUMENTS.getInt(1, adrs)) {
            return;
        }
        
        int lo = 0;
        int hi = 0;
        if(!ARGUMENTS.getLimits(2, lo, hi)) {
            return;
        }
        PixelClientLimit l1(lo, hi);

        if(!ARGUMENTS.getLimits(3, lo, hi)) {
            return;
        }
        PixelClientLimit l2(lo, hi);

        if(!ARGUMENTS.getLimits(4, lo, hi)) {
            return;
        }
        PixelClientLimit l3(lo, hi);

        if(!ARGUMENTS.getLimits(5, lo, hi)) {
            return;
        }
        PixelClientLimit l4(lo, hi);

        processor->onSetLimitsAndHome(adrs, l1, l2, l3, l4);
    } else {
        // TODO error
    }
}

void CmdRunner::cmdLimit() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return;
    }
    
    int pixle;
    if(!ARGUMENTS.getInt(2, pixle)) {
        return;
    }

    int lo;
    int hi;
    if(!ARGUMENTS.getLimits(3, lo, hi)) {
        return;
    }

    PixelClientLimit limit(lo, hi);
    processor->onSetLimit(adrs, pixle, limit);
}

void CmdRunner::cmdSetSteps() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return;
    }
    
    int pixle;
    if(!ARGUMENTS.getInt(2, pixle)) {
        return;
    }

    int steps;
    if(!ARGUMENTS.getInt(3, steps)) {
        return;
    }

    processor->onSetSteps(adrs, pixle, steps);
}

void CmdRunner::cmdAddSteps() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return;
    }


    int pixle;
    if(!ARGUMENTS.getInt(2, pixle)) {
        return;
    }

    int steps;
    if(!ARGUMENTS.getInt(3, steps)) {
        return;
    }

    processor->onAddSteps(adrs, pixle, steps);
}

void CmdRunner::cmdSetAngle() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return;
    }
    
    int pixle;
    if(!ARGUMENTS.getInt(2, pixle)) {
        return;
    }

    double angle;
    if(!ARGUMENTS.getDouble(3, angle)) {
        return;
    }

    processor->onSetAngle(adrs, pixle, angle);
}

void CmdRunner::cmdAddAngle() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return;
    }

    int pixle;
    if(!ARGUMENTS.getInt(2, pixle)) {
        return;
    }

    double angle;
    if(!ARGUMENTS.getDouble(3, angle)) {
        return;
    }

    processor->onAddAngle(adrs, pixle, angle);
}

void CmdRunner::cmdPing() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return;
    }

    processor->onPing(adrs);
}

void CmdRunner::cmdError() {
    int adrs;
    if(!ARGUMENTS.getInt(1, adrs)) {
        return;
    }

    processor->onError(adrs);
}


void CmdRunner::cmdHelp() {
    printHelp();
}
