//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
//      Copyright (C) 2015 Peter Walsh, Milford, NH 03055
//      All Rights Reserved under the MIT license as outlined below.
//
//  FILE
//      Dump.c
//
//  DESCRIPTION
//
//      Memory dump modules
//
//  VERSION:    2015.03.04
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

#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "Dump.h"
#include "Serial.h"

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
// DumpSpaces - Print out spaces for a block memory dump
//
// Inputs:      Address to start dumping
//              # of bytes per line to dump
//
// Outputs:     None.
//
static void DumpSpaces(uint8_t *Addr,uint8_t NumData) {
    uint8_t Spaces = (((uint16_t) Addr) & (NumData-1));

    //
    // Print out spaces so that corresponding bytes will match first line
    //
    if( Spaces != 0 ) {
        PrintH(((uint16_t) Addr) >> 8);
        PrintH(((uint16_t) Addr) & 0xFF);
        PrintStringP(PSTR(": "));
        while( Spaces-- )
            PrintStringP(PSTR("   "));
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
// DumpMem - Dump out a block of memory
//
// Inputs:      Address to start dumping
//              # of bytes to dump
//
// Outputs:     None.
//
void DumpMem(uint8_t *Addr,uint16_t Len) {

    DumpSpaces(Addr,16);

    while( Len-- ) {
        //
        // Every 16 bytes print out a CR and current address
        //
        if( (((uint16_t) Addr) & 0x0F) == 0 ) {
            PrintCRLF();
            PrintH(((uint16_t) Addr) >> 8);
            PrintH(((uint16_t) Addr) & 0xFF);
            PrintStringP(PSTR(": "));
            }
        PrintH(*Addr++);
        PrintChar(' ');
        }

    PrintCRLF();
    }

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//
// DumpEEPROM - Dump out a block of EEPROM
//
// Inputs:      Address to start dumping
//              # of bytes to dump
//
// Outputs:     None.
//
void DumpEEPROM(uint8_t *Addr,uint16_t Len) {

    DumpSpaces(Addr,16);

    while( Len-- ) {
        //
        // Every 16 bytes print out a CR and current address
        //
        if( (((uint16_t) Addr) & 0x0F) == 0 ) {
            PrintCRLF();
            PrintH(((uint16_t) Addr) >> 8);
            PrintH(((uint16_t) Addr) & 0xFF);
            PrintStringP(PSTR(": "));
            }
        PrintH(eeprom_read_byte(Addr++));
        PrintChar(' ');
        }

    PrintCRLF();
    }
