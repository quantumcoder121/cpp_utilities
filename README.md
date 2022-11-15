# C++ Utilities for Machine Learning

# Usage

## Header Files

These are present in the ```include/``` directory and the implementations are present in the ```src/``` directory.

### numcpp.h

C++ version of NumPy. Useful for building neural networks and statistical analyses. ```numcpp.h``` is the header file.
### math.h

Includes several math functions in C++. ```math.h``` is the header file.

### cppdl.h

Preliminary version of a C++ deep learning library. ```cppdl.h``` is the header file. Work under progress.

### mllib.h

Basic ML library. ```mllib.h``` is the header file. Work under progress.

## Library

A dynamically linked library (DLL) named ```libml.so``` is present in the ```lib/``` directory. The definitions of all the relevant functions are present in this library and are loaded by the executable at runtime.

## Compilation

The ```g++``` flags used to create the executable are

    -O3 -Wall -Wextra -Wpedantic -I/path/to/include -L/path/to/lib -lml -fopenmp -Wl,-rpath=/path/to/lib

The ```-O3, -Wall, -Wextra, -Wpedantic``` flags are optional
While building the library, if you have done ```sudo make install```, all the flags except ```-fopenmp``` and ```-lml``` become optional.

You can also use ```make main=your_file.cpp target``` to build the executable.

To make the library again, the command is:

    make all

To install it in the standard library and include directories, you can optionally enter ```sudo make install``` after doing this.

## Sidenote

Guys I really want to build this library much more and right now it's still in a very primary stage. If you happen to look at this repository, please please please contribute whatever you like. Even one PR would mean a lot to me. Let's make this world nicer by creating more and more open source stuff.
