#ifndef PIXEL_TESTER_CONFIG
#define PIXEL_TESTER_CONFIG

#include <pix/PixWriter.h>

#include <cmd/CmdRunner.h>
#include <args/Arguments.h>
#include <processor/TestProcessor.h>

#define OPCODE_HOME "HOME"
#define OPCODE_SET_LIMITS_AND_HOME "SET_LIMITS_AND_HOME"
#define OPCODE_SET_LIMITS "SET_LIMITS"
#define OPCODE_SET_STEPS "SET_STEPS"
#define OPCODE_ADD_STEPS "ADD_STEPS"
#define OPCODE_SET_ANGLE "SET_ANDLE"
#define OPCODE_ADD_ANGLE "ADD_ANDLE"

extern PixWriter PIXEL_WRITER;

extern TestProcessor PROCESSOR;
extern Arguments ARGUMENTS;
extern CmdRunner CMD_RUNNER;

#endif