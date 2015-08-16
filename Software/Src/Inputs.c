//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
//      Copyright (C) 2015 Peter Walsh, Milford, NH 03055
//      All Rights Reserved under the MIT license as outlined below.
//
//  FILE
//      Inputs.c
//
//  DESCRIPTION
//
//      Input processing
//
//      See Inputs.h for an in-depth description
//
//  VERSION:    2010.12.19
//
//////////////////////////////////////////////////////////////////////////////////////////
//
//  MIT LICENSE
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//    this software and associated documentation files (the "Software"), to deal in
//    the Software without restriction, including without limitation the rights to
//    use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
//    of the Software, and to permit persons to whom the Software is furnished to do
//    so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//    all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//    INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//    PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

#include <PortMacros.h>

#include "Inputs.h"

#include "Debug.h"

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
// Data declarations
//
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

bool Input1Changed  NOINIT;
bool Input2Changed  NOINIT;

bool Input1On       NOINIT;
bool Input2On       NOINIT;

static uint8_t  Input1Debounce NOINIT;
static uint8_t  Input2Debounce NOINIT;

#define INPUT1_PIN  (_BIT_ON(_PIN(INPUT_I1_PORT),INPUT_I1_BIT) == 0)
#define INPUT2_PIN  (_BIT_ON(_PIN(INPUT_I2_PORT),INPUT_I2_BIT) == 0)

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
// InputsInit - Initialize inputs
//
// Inputs:      None.
//
// Outputs:     None.
//
void InputsInit(void) {

    _SET_BIT(PCMSK_I1,PCINT_I1);
    _SET_BIT(PCMSK_I2,PCINT_I2);

    _CLR_BIT( _DDR(INPUT_I1_PORT),INPUT_I1_BIT);    // Inputs are inputs
    _SET_BIT(_PORT(INPUT_I1_PORT),INPUT_I1_BIT);    // With internal pullup

    _CLR_BIT( _DDR(INPUT_I2_PORT),INPUT_I2_BIT);    // Inputs are inputs
    _SET_BIT(_PORT(INPUT_I2_PORT),INPUT_I2_BIT);    // With internal pullup

    Input1Changed = false;
    Input2Changed = false;

    Input1On      = INPUT1_PIN;
    Input2On      = INPUT2_PIN;

    Input1Debounce = 0;
    Input2Debounce = 0;
    }


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
// Input1Update - Update input1 for debounce
//
// Inputs:      None.
//
// Outputs:     None.
//
static void Input1Update(void) {

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Whenever the buttons are different from the mirror value, reset the
    //   debounce clock
    //
    if( Input1On != INPUT1_PIN ) {
        Input1Debounce = INPUT_I1_DEBOUNCE;
        Input1On       = INPUT1_PIN;
        return;
        }

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //
    // IDLE - No button changes, nothing going on
    //
    if( Input1Debounce == 0 )
        return;

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //
    // DEBOUNCE - If timer hasn't expired, keep waiting.
    //
    Input1Debounce--;

    if( Input1Debounce > 0 ) 
        return;

    ProcessInput1(Input1On);
    }


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
// Input2Update - Update input2 for debounce
//
// Inputs:      None.
//
// Outputs:     None.
//
static void Input2Update(void) {

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Whenever the buttons are different from the mirror value, reset the
    //   debounce clock
    //
    if( Input2On != INPUT2_PIN ) {
        Input2Debounce = INPUT_I2_DEBOUNCE;
        Input2On       = INPUT2_PIN;
        return;
        }

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //
    // IDLE - No button changes, nothing going on
    //
    if( Input2Debounce == 0 )
        return;

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //
    // DEBOUNCE - If timer hasn't expired, keep waiting.
    //
    Input2Debounce--;

    if( Input2Debounce > 0 ) 
        return;

    ProcessInput2(Input2On);
    }


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
// InputsUpdate - Update inputs for debounce
//
// Inputs:      None.
//
// Outputs:     None.
//
void InputsUpdate(void) {

    Input1Update();
    Input2Update();

Debug1 = INPUT1_PIN;
Debug2 = Input2On ? 1 : 0;
    }

