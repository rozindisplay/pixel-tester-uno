#include "Arguments.h"

#define ARGUMENTS_LINE_DELIMITER '\n'
#define ARGUMENTS_LIMIT_MAX 16

bool Arguments::next() {
    if(Serial.available()==0) {
        Serial.println("ERROR: user input not found");
        return false;
    }

    // clean buffer
    for(int i=0; i<ARGUMENTS_BUFFER_SIZE; i++) {
        buffer[i] = '\0';
    }

    // read line into buffer
    Serial.readBytesUntil(ARGUMENTS_LINE_DELIMITER, buffer, ARGUMENTS_BUFFER_SIZE-1);
    
    // find arguments and convert arg delimiters into null chars
    int argCount = 0;
    bool argFound = false;
    for(int i=0; i<ARGUMENTS_BUFFER_SIZE; i++) {
        char ch = buffer[i];
        if('\0' == ch) {
            // found the end of the string
            count = argCount;
            return true;
        }

        if(isWhitespace(ch)) {
            buffer[i] = '\0';
            argFound = false;
        } else if(!argFound) {
            if(argCount+1 == ARGUMENTS_MAX_COUNT) {
                Serial.println("ERROR: too many arguments given");
                return false;
            }

            args[argCount++] = &buffer[i];
            argFound = true;
        } else {
            // all chars will be converted to lowercase
            buffer[i] = lowercase(ch);
        }
    }

    Serial.println("ERROR: reached end of buffer and did not find null terminator");
    return false;
}

size_t Arguments::getCount() {
    return count;
}

bool Arguments::getString(size_t index, char*& value) {
    if(index>=count) {
        Serial.println("index out of bounds");
        return false;
    }

    value = args[index];
    return true;
}

bool Arguments::getInt(size_t index, int& value) {
    if(index>=count) {
        Serial.println("index out of bounds");
        return false;
    }

    char* num = args[index];
    return parseInt(num, value);
}

bool Arguments::getDouble(size_t index, double& value) {
    if(index>=count) {
        Serial.println("index out of bounds");
        return false;
    }

    char* num = args[index];
    char* end;

    // parse the value
    double fvalue = strtod(num, &end);
    if (end == num) {
        // failed to parse
        Serial.println("failed to parse number");
        return false;
    }
    
    value = fvalue;
    return true;
}

bool Arguments::getLimits(size_t index, int& lower, int& upper) {
    if(index>=count) {
        Serial.println("index out of bounds");
        return false;
    }

    char* limits = args[index];
    size_t size = strlen(limits);
    if(ARGUMENTS_LIMIT_MAX <= size) {
        Serial.println("size of defined limit is too long");
        return false;
    }

    size_t sizeWithNull = size+1;
    char buffer[sizeWithNull];
    for(size_t i=0; i<sizeWithNull; i++) {
        buffer[i] = '\0';
    }
    memcpy(buffer, limits, size);

    char* lowerStr = buffer;
    char* upperStr;

    for(size_t i=0; i<size; i++) {
        char ch = buffer[i];
        if(':' == ch) {
            buffer[i] = '\0';
            upperStr = &buffer[i] + 1;
            break;
        }
    }

    if(!parseInt(lowerStr, lower)) {
        return false;
    }
    if(!parseInt(upperStr, upper)) {
        return false;
    }

    return true;
}

bool Arguments::isWhitespace(char ch) {
    return ch==' ' || ch=='\t' || ch=='\r' || ch=='\n' || ch=='\v' || ch=='\f';
}

bool Arguments::isUpperCase(char ch) {
    return ch >= 'A' && ch <='Z';
}

char Arguments::lowercase(char ch) {
    if(!isUpperCase(ch)) {
        return ch;
    }
    ch += ('a' - 'A');
    return ch;
}

bool Arguments::parseInt(char* num, int& value) {
    char* end;

    // parse the value
    long lvalue = strtol(num, &end, 10);
    
    if (end == num) {
        // failed to parse
        Serial.println("failed to parse number");
        return false;
    }
    if (lvalue > INT16_MAX || lvalue < INT16_MIN) {
        // out of range
        Serial.println("parsed number out of range");
        return false;
    }

    value = (int)lvalue;
    return true;
}
