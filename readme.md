# TetraBlocks

 Simple block placing game inspired by tetris and some popular games for mobile devices.  
 Player can place shapes (tetrominoes) in any available place on grid (9x9 blocks).  
 If horizontal and/or vertical line is filled - it's disappears and player gain points.
 If any shape can't fit board - game ends.
 
### Used technologies

 - C++20
 - CMake 3.30+
 - OpenGL 3.3 Core profile
 - GLM - linear algebra library
 - Freetype - text rendering library
 - GLFW - window management
 - libspng - loading library for PNG images

### Features

 - [X] Rendering
   - [X] Text 
   - [X] Vector shapes
   - [X] Images
   - [ ] UI 
     - [X] Main Menu
     - [ ] Pause Menu
     - [ ] Game Over Menu
     - [ ] Game
 - [ ] Game logic
   - [ ] Shapes generation
   - [ ] Drag&Drop mechanism for shapes
   - [ ] Check if board have space for shapes
   - [ ] Score system

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

### Author and Licenses

 Maks Makuta (c) 2025   

 | Item                                                     | License           |  
 |----------------------------------------------------------|-------------------|  
 | Code                                                     | MIT               |
 | [Font](https://www.fontspace.com/timeburner-font-f15111) | Freeware          |
 | [UI Icons](https://kenney.nl/assets/game-icons)          | CC0 1.0 Universal |       

