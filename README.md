# OptiPNG-GUI
An application that allows you to losslessly optimize the filesize of PNG images.
## Key features
**Graphical!** Select a whole folder of images and optimize them in a few clicks! 

**Multithreaded!** Queue up images all at once or as they optimize and this program will optimize them all on separate threads!
## Prerequisites
- [optipng](https://optipng.sourceforge.net/)
- glibc
- libQT5Core/GUI/Widgets 
## Compiling
Compile using QtCreator or CMake.
```
cmake CMakeLists.txt && make
```
