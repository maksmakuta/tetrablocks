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

### How to build/play?

 1. Clone this repository  
 ```shell
  git clone --depth=1 https://github.com/maksmakuta/tetrablocks.git && cd tetrablocks 
  ```

 2. Make temporary dir for building   
 ```shell
 mkdir build && cd build
 ```  
 
 3. Use CMake to generate build script     
 ```shell
 cmake .. 
 ```  
 
 4. Run build script 
 ```shell
  make 
  ```  
 5. Run executable     
 ```shell
  ./tetrablocks 
 ```
    
### Current screenshot

![](/screenshots/img.png)

Rendering font texture atlas generated in runtime

### Author and Licenses
 Maks Makuta (c) 2025  
 MIT Licence