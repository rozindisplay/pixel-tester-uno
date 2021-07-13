#ifndef PIXEL_TESTER_ARGUMENTS
#define PIXEL_TESTER_ARGUMENTS

#define ARGUMENTS_BUFFER_SIZE 80
#define ARGUMENTS_MAX_COUNT 6

#include "Arduino.h"

/**
 * This class is used to read the user arguments. It reads a line from the Serial port and parses them.
 */
class Arguments {
public:
    /**
     * Reads the next line of aarrguments and sets it as the current line
     * @returns true if the operation was successful
     */
    bool next();

    /**
     * Returns the number of arrguments found on the current line
     * @returns the number of arrguments found on the current line
     */
    size_t getCount();

    /**
     * Returns the argument at the given index as a string
     * @param index the argument index
     * @param value a variable used to return the result
     * @returns true if the operation was successful
     */
    bool getString(size_t index, char*& value);
    
    /**
     * Returns the argument at the given index as an int
     * @param index the argument index
     * @param value a variable used to return the result
     * @returns true if the operation was successful
     */
    bool getInt(size_t index, int& value);

    /**
     * Returns the argument at the given index as a double
     * @param index the argument index
     * @param value a variable used to return the result
     * @returns true if the operation was successful
     */
    bool getDouble(size_t index, double& value);

    /**
     * Returns the argument as a pair of lower and upper limits
     * @param index the argument index
     * @param lower a variable used to return the lower limit
     * @param lower a variable used to return the upper limit
     * @returns true if the operation was successful
     */
    bool getLimits(size_t index, int& lower, int& upper);

private:
    /** the argument buffer */
    char buffer[ARGUMENTS_BUFFER_SIZE];

    /** an array of pointers, pointing to the start of each arg */
    char* args[ARGUMENTS_MAX_COUNT];

    size_t count = 0;

    bool isWhitespace(char);
    bool isUpperCase(char);
    /**
     * converts uppercase to lowercase
     * @returns the lower case char
     */
    char lowercase(char);

    bool parseInt(char*, int& value);
};

#endif