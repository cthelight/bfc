# bfc
BrainFuck compiler written in c, using gcc
## Compilation
Simply use the provided Make file to compile to binary.

## Flags
-o <name> The BrainFuck program will compile to binary named <name>
-k Keeps the intermediate C source code
-m <number> Sets the size of the BrainFuck memory to <number> of cells
-D Do not compile to binary, just transcode to C (C file will only be kept if used with -k option)
