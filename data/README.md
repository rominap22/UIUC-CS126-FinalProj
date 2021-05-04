#Garbage Card Game - CS 126 Final Project
This project is for my final project of CS 126 at the University of Illinois at Urbana-Champaign for Spring 2021.

![License: MIT](https://img.shields.io/badge/License-MIT-greenyellow.svg)
##About
The card game [Garbage](https://bicyclecards.com/how-to-play/trash/), alternatively called Trash, is what I recreated 
with this project in CLion, using C++ to program the game logic and displaying the graphics using Cinder. The below 
contents outline instructions assuming execution on Windows OS, but setup instructions work for both MacOS and 
Windows OS.

##Dependencies
* [Clion](https://www.jetbrains.com/clion/)
* [Cinder](https://libcinder.org/)
* [Cinder + Git](https://libcinder.org/docs/guides/git/index.html)  
* [Clang](https://clang.llvm.org/)
* [Catch2](https://github.com/catchorg/Catch2)
* [CMake](https://cmake.org/)
* [Visual Studio Community 2015 with Update 3](https://my.visualstudio.com/Downloads?q=visual%20studio%202015&wt.mc_id=o~msft~vscom~older-downloads)

##Setting up Cinder and IDE
1. Please visit [this page](https://courses.grainger.illinois.edu/cs126/sp2021/notes/cpp-build/) of the  CS 126 website 
for instructions on how to set up the C++ and for configuring the build.
2. For instructions on installing and setting up Cinder, please see 
[this page](https://courses.grainger.illinois.edu/cs126/sp2021/notes/cinder-installation-notes/) of the course website.
3. Clone this repository to your local machine using git clone.
4. Set target and executable to be garbage-cinder for Cinder graphic version of the game.

##Game Controls
Event | Action
------------ | -------------
`Mouse pressed` | Card drawn from stock pile and either replaces corresponding face down card or is unplayable and goes to discard (b/c player either won or card is face up)
`1` | Represents rank 1 (Ace) when user input is requested for which position/rank to replace when a Jack is drawn
`2` | Represents rank 2 when user input is requested for which position/rank to replace when a Jack is drawn
`3` | Represents rank 3 when user input is requested for which position/rank to replace when a Jack is drawn
`4` | Represents rank 4 when user input is requested for which position/rank to replace when a Jack is drawn
`5` | Represents rank 5 when user input is requested for which position/rank to replace when a Jack is drawn
`6` | Represents rank 6 when user input is requested for which position/rank to replace when a Jack is drawn
`7` | Represents rank 7 when user input is requested for which position/rank to replace when a Jack is drawn
`8` | Represents rank 8 when user input is requested for which position/rank to replace when a Jack is drawn
`9` | Represents rank 9 when user input is requested for which position/rank to replace when a Jack is drawn
`0` | Represents rank 10 when user input is requested for which position/rank to replace when a Jack is drawn

**Author**: Romina Parimi - [rparimi2@illinois.edu](rparimi2@illinois.edu)