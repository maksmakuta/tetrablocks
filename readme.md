# TetraBlocks

 Simple block placing game inspired by tetris.  
 Player can place shapes in any available place on grid (9x9 blocks).  
 If horizontal or vertical line is filled - it's disappears and player gain points.
 
### Used technologies

 - C++20
 - OpenGL 3.3 Core profile
 - GLM - linear algebra library
 - Freetype - text rendering library
 - GLFW - window management
 - libPNG - image loading library

### How to play?

 1. Clone this repository  
 ``` git clone --depth=1 https://github.com/maksmakuta/tetrablocks.git && cd tetrablocks ```
 2. Make temporary dir for building  
 ``` mkdir build && cd build```
 3. Use CMake to generate build script  
 ``` cmake .. ```
 4. Run build script  
 ``` make ```
 5. Run executable  
 ``` ./tetrablocks ```
    
### Author and Licenses
 Maks Makuta (c) 2025  
 MIT Licence