// fastflags.h
#ifndef FASTFLAGS_H
#define FASTFLAGS_H
void InitFastFlags();
#endif

// fastflags.c
#include <windows.h>
#include <stdio.h>
#include "fastflags.h"

// "Biggest Library": These are memory addresses in Roblox to change behavior.
// To make it "Universal", you add scripts here.
static int memory_base = 0; 

void InitFastFlags() {
    // Example: Setting a value in memory
    // This is where the Lua Script execution logic goes
    printf("QuantumStrap Loaded. Ready to execute cheats.\n");
    
    // Enable 'God Mode' example (Generic)
    // WriteMemory(base + "gods", 1); 
}
