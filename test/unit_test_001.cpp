//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-02
// PURPOSE: unit tests for the MT8870
//          https://github.com/RobTillaart/MT8870
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>

#define assertEqualFloat(arg1, arg2, arg3)  assertOp("assertEqualFloat", "expected", fabs(arg1 - arg2), compareLessOrEqual, "<=", "actual", arg3)
// #define assertEqualINF(arg)  assertOp("assertEqualINF", "expected", INFINITY, compareEqual, "==", "actual", arg)
// #define assertEqualNAN(arg)  assertOp("assertEqualNAN", "expected", true, compareEqual, "==", "actual", isnan(arg))


#include "Arduino.h"
#include "MT8870.h"



unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", MT8870_LIB_VERSION);

  uint8_t STQ = 4, Q1 = 5, Q2 = 6, Q3 = 7, Q4 = 8;
  MT8870 DTMF;

  DTMF.begin(STQ, Q1, Q2, Q3, Q4);

  assertFalse(DTMF.available());
}


unittest(test_read)
{
  GodmodeState* state = GODMODE();
  state->reset();
  
  uint8_t STQ = 4, Q1 = 5, Q2 = 6, Q3 = 7, Q4 = 8;
  MT8870 DTMF;

  DTMF.begin(STQ, Q1, Q2, Q3, Q4);
  assertFalse(DTMF.available());
  state->digitalPin[STQ] = 1;
  assertTrue(DTMF.available());

  state->digitalPin[Q1] = 1;
  state->digitalPin[Q2] = 0;
  state->digitalPin[Q3] = 0;
  state->digitalPin[Q4] = 1;

  assertEqual('9', DTMF.read());

  state->digitalPin[Q1] = 1;
  state->digitalPin[Q2] = 0;
  state->digitalPin[Q3] = 1;
  state->digitalPin[Q4] = 1;
  assertEqual(11, DTMF.readRaw());
  assertEqual(11, DTMF.lastRaw());
}

unittest_main()

// --------
