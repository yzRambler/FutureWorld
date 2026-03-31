# FutureWorld

FutureWorld have achieved two running way: .exe for Windows and .wasm for Browser.  Here, I supply .exe file in Windows merely. The .wasm object is compiled by same 
source codes as well (just little modifying).
The demoe running in Internet can be found in my website: www.spaceyz.org. (www.spaceyz.org/horseAni.html) You can check the loading flow of all assets by Browser's control. 

At present, FutureWorld be at test phase which use to check out various considering. FutureWorld is 3D engine for Internet mainly and base on Webassembly technology 
which is compiled from source code into .wasm object file by Emscripten compiler. What problems will present in this procedure and latent trouble will be met as .wasm 
file running at browser, all of these must be test one by one. I have checked out the part functions of Emscripten support OpenglES2.0/3.0. These examine is very 
important for next development mission.   


The startup is in Aug. 2020. First demo (Version 0.0.0 Alpha) basically is used to verify the rendering OpenGLES effect in Web environment and the possible of compiling 
C++ codes into .wasm file which support OpenGLES interface. It had achieved that parse and render .obj modle / .bmp picture.    


Second edition (Version 0.1.0 Alpha) mostly examine skeleton animation function at WEB circumstance and multi-projectes support from Emscripten. In this edition, all codes
are splited some different pojectes with its' functionality. Some new functions had been completed:
1. Parse .png file.
2. Define .fwd file. (include mesh and material information and skeleton animation data)
3. Optimize skeleton animation algorithm for Browser. (Obtain 4 times prime animtion fps.  hahahaha~~~~).
4. It is enable to load outside resources with specific option by CAspect class and it's sub-class objects. This function had been accomplished in Version 0.0.0 Alpha.
   In here, it had been improved.
5. Parse scene file (.sce).
6. Switch from one scene to another.


Now, third edition (Version 0.2.0 Alpha) primarily be used to test the result of which the compiled codes by Emscripten run for FrameBuffer of OpenGLES. To render UI, base on 
this. UI can be considered a appliction on FutureWold Engine functions. All UI objects can be created from outside config file (.fui).
This edition has improved the render procedure as well and defined the "Space-Time" conception.(i.e. all rendered objects are in specific "Space-Time").


Presently, Version 0.2.0 just offer part source codes.  In next step, I will redesign the architecture and reconstruct all codes throughly. The mulity-thread process and new 
class relationship will be adopted, the PBR shader will be accomplished. After these functions are accomplished, I will publish completed Version 0.2.0 Alpha codes. 
