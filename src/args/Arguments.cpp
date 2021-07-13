#include "Arguments.h"

#define ARGUMENTS_LINE_DELIMITER '\n'
#define ARGUMENTS_LIMIT_MAX 16
#define ARGUMENTS_NULL_CHAR '\0'
#define ARGUMENTS_ERROR_INDEX_OUT_OF_BOUNDS "ERR: idx out of bounds"

bool Arguments::next() {
    if(Serial.available()==0) {
        Serial.println("ERR: no input");
        return false;
    }

    // clean buffer
    for(int i=0; i<ARGUMENTS_BUFFER_SIZE; i++) {
        buffer[i] = ARGUMENTS_NULL_CHAR;
    }

    // read line into buffer
    Serial.readBytesUntil(ARGUMENTS_LINE_DELIMITER, buffer, ARGUMENTS_BUFFER_SIZE-1);
    
    // find arguments and convert arg delimiters into null chars
    int argCount = 0;
    bool argFound = false;
    for(int i=0; i<ARGUMENTS_BUFFER_SIZE; i++) {
        char ch = buffer[i];
        if(ARGUMENTS_NULL_CHAR == ch) {
            // Found the end of the string.
            count = argCount;
            return true;
        }

        if(isWhitespace(ch)) {
            // Whitespace delimits our arguments.
            // We convert whitespace to the null terminating chars of the args
            buffer[i] = ARGUMENTS_NULL_CHAR;

            // We are no longer looking at an argument.
            argFound = false;
        } else if(!argFound) {
            // start of next argument found
            if(argCount == ARGUMENTS_MAX_COUNT) {
                // we have a predetermined number of pointers
                Serial.println("ERR: too many args");
                return false;
            }

            // all chars will be converted to lowercase
            buffer[i] = lowercase(ch);

            // We found the arg. Keep the arg's location from the buffer
            args[argCount++] = &buffer[i];
            
            // We are looking at an argument.
            argFound = true;
        } else {
            // we're in the middle of reading in an arg
            // all chars will be converted to lowercase
            buffer[i] = lowercase(ch);
        }
    }

    Serial.println("ERR: EOF found");
    return false;
}

size_t Arguments::getCount() {
    return count;
}

bool Arguments::getString(size_t index, char*& value) {
    if(index>=count) {
        Serial.println(ARGUMENTS_ERROR_INDEX_OUT_OF_BOUNDS);
        return false;
    }

    value = args[index];
    return true;
}

bool Arguments::getInt(size_t index, int& value) {
    if(index>=count) {
        Serial.println(ARGUMENTS_ERROR_INDEX_OUT_OF_BOUNDS);
        return false;
    }

    char* num = args[index];
    return parseInt(num, value);
}

bool Arguments::getDouble(size_t index, double& value) {
    if(index>=count) {
        Serial.println(ARGUMENTS_ERROR_INDEX_OUT_OF_BOUNDS);
        return false;
    }

    // parse the value
    value = atof(args[index]);
    return true;
}

bool Arguments::getLimits(size_t index, int& lower, int& upper) {
    if(index>=count) {
        Serial.println(ARGUMENTS_ERROR_INDEX_OUT_OF_BOUNDS);
        return false;
    }

    char* limits = args[index];
    size_t size = strlen(limits);
    if(ARGUMENTS_LIMIT_MAX <= size) {
        Serial.println("ERR: limit too long");
        return false;
    }

    size_t sizeWithNull = size+1;
    char buffer[sizeWithNull];
    for(size_t i=0; i<sizeWithNull; i++) {
        buffer[i] = ARGUMENTS_NULL_CHAR;
    }
    memcpy(buffer, limits, size);

    char* lowerStr = buffer;
    char* upperStr;

    for(size_t i=0; i<size; i++) {
        char ch = buffer[i];
        if(':' == ch) {
            buffer[i] = ARGUMENTS_NULL_CHAR;
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
    value = atoi(num);
    return true;
}
