# HooliGame
Assignment for C++ course in Athens University of Economics and Business

Two greek football hooligans battle it out to the end!!

## Windows (Visual Studio)

Visual Studio 2017/2019 is required

To create the projects run:

```bash
vendor/premake5.exe vs2017
```

This generates the solution file for Visual Studio. You can build it using Visual Studio.

## Mac


To create GNU make files run:
```bash
vendor/premake5_mac_x64 gmake2
```

After the make files are created, run 
```bash
make
```
to build the project.

In order to build the optimized version run
```bash
make config=release
```

### Executable directory

The executable is in bin/{config}-{os}/
