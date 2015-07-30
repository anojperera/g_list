#!/bin/bash

# Creates a shared object
gcc -g -Wall -O0 -fPIC -c *.c

# Remove main object
rm main.o

# Move objects to bin
mv *.o ../bin/

# Create shared object
gcc -shared -Wl,-soname,libalist.so.1 -o ../bin/libalist.so.1.0.1 ../bin/*.o

# Clean objects
rm ../bin/*.o

# Create static archive
gcc -g -Wall -O0 -c *.c
rm main.o
mv *.o ../bin/
ar rcs ../bin/libalist.a ../bin/*.o
rm ../bin/*.o
exit 0
