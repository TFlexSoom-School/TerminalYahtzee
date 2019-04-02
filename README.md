# Terminal Yahtzee
Simple NCurses Game that uses arrow keys and enter key for control. 
Simply press backspace twice to quit early. The project requires further 
testing and ui fine tuning, but the game is playable.

## Notes
This was before I had access to a decent style guide or design architectures.
Much of the code is made in poor design in functional and architectural standards.
I would recommend looking for a better design in gameplay rather than this spaghetti
code.

# How to Use
The code is a C++ project made for linux systems. Make sure you have the nCurses library
along with a flavor of C++ compiler to use. I have a makefile which hosts the compiler
under variable `CC`. _Note_ the makefile is also under revision. Feel free to pull
request a much cleaner script.

# How to add
The poorly designed architecutre has a huge coupling with the UI, but I would
gladly accept any pull resquests made to any functionality. Improving this project
is good practice of C++. Although this does require linux distro I will comment
if linux only functions are used in this project. Developers should stick to
C runtime and NCurses only when programming, including the STL library.

# Is this hosted?
No it is not.

# Purpose of this project
A simple practice of C++ programming with the NCurses Environment. I highly recommend
individuals check out my ESCAPE CS 162 repository.

# How to include this project
All files under src are valid to use across other projects except TerminalYahtzee.cpp
which defines a main. There is no plans for the project to become a subsystem or
dynamically linked/shared library. If such is desired file an issue.
