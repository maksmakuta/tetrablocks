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

  Clone this repository  
 ```shell git clone --depth=1 https://github.com/maksmakuta/tetrablocks.git && cd tetrablocks ```
 Make temporary dir for building   
 ```shell mkdir build && cd build```  
 Use CMake to generate build script     
 ```shell cmake .. ```  
 Run build script     
 ```shell make ```  
 Run executable     
 ```shell ./tetrablocks   ```
    
### Author and Licenses
 Maks Makuta (c) 2025  
 MIT Licence