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

In order to install the required libraries run
```bash
brew bundle install
```
Make sure you already have [Homebrew](https://github.com/Homebrew/brew) and [Bundle](https://github.com/Homebrew/homebrew-bundle)

To create GNU Makefiles run
```bash
vendor/premake5_mac_x64 gmake2
```

After the Makefiles are created, run
```bash
make
```
to build the project
 
For the optimized version, run
```bash
make config=release
```

### Executable directory

The executable is in bin/{config}-{os}/
