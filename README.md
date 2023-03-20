# PDP-11 Emulator
---
The PDP-11 is a series of 16-bit minicomputers sold by DEC from 1970 into the 1990s.

My project is a PDP-11 emulator. Due to the limited time for development, we have implemented only a part of the functions.

# What can the emulator do? What features are implemented?
---
My emulator has a program loading function, which may include the following commands:

~~~
add      Addition
mov      Assignment
cmp      Comparing two words without changes
sob      Summation of an array of integers

clr      Clear register
tst      Test command to set flags N and Z, and V, C to 0
tstb     Test command to set flags N and Z, and V, C to 0

ccc      Set all flags to 0
cln      Set flag N to 0
clz      Set the Z flag to 0
clv      Set flag V to 0
clc      Set flag C to 0

scc      Set all flags to 1
sen      Set flag N to 1
sez      Set the Z flag to 1
sev      Set V flag to 1
sec      Set flag C to 1

br       Br (Branching)
beq      Br if Z = 0
bpl      Br if N = 0

halt     Stop the program
nop      No operation

~~~
# How to run emulator?
---
Once you have downloaded all the source code for the emulator, you will need to run it. To do this, you can use the Ubuntu command line:

1. Launch the Ubuntu command line;
2. Go to the directory with the `pdp11.exe` file;
3. Run `Makefile` with the `make` command;
4. After compilation, run the emulator with the command `./pdp11.exe`;

