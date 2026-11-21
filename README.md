# FutureWorld
A lightweight, cross-platform 3D engine written in C++ and compiled to
WebAssembly via Emscripten. Runs natively on Windows and in the browser
(desktop and mobile) from a single source tree.

**Live demo:** 

https://www.spaceyz.org/horseAni.html   (in the browser)

https://github.com/yzRambler/FutureWorld/releases/tag/FutureWorld   (on Windows)


**Engine viewer:** 
https://www.spaceyz.org

---

## Why this project
Most browser 3D engines are ports of desktop engines. FutureWorld was designed
from the start for the browser: the rendering backend targets OpenGL ES 2.0/3.0,
the asset pipeline emits a compact custom binary format, and the entire engine
builds to both `.exe` and `.wasm` without a separate code path. The performance is 
n times that of common JavaScript 3D web engine after adopting WebAssembly 
technology. 
The goal was to find out how far a hand-written C++ engine can be pushed inside
a browser sandbox — and what breaks when it gets there.

---

## At a glance

| Language | C++ |

| Build | MSVC (Windows) / Emscripten (WebAssembly) |

| Graphics API | OpenGL ES 2.0 / 3.0 |

| Platforms | Windows, Desktop Browsers, Mobile Browsers |

| Started from scratch | August 2020 |

| First release  | March 2025 |


## Architecture
The engine is split into independent modules with a one-way dependency flow:

- FWEditor Tooling / scene authoring
|
- FWUI Retained-mode UI widgets
|
- FWEngineSceneManager Scene graph and node lifecycle
|
- FWEngineRenderManager Render graph, material and pass management
|
- FWEnginePrimatterManager Asset(material, picture, model file, font library etc. )  management
|
- FWEngineCore / FWEngineBase The core objects of this engine.
|
- FWFileManager / FWIOSystem Virtual filesystem and IO manager
|
- FWMathLibrary Vectors, matrices, quaternions, projections


Implemented
-
**Resource management**
-
- Support common file (FBX / PNG /OBJ  model file) and 
   **custom file** (FWD contain model mesh, joint hierarchy, skinning weights, 
    keyframe tracks) 

- Custom **resource package format(PAK)** with an internal index, so a whole
  scene ships as a single file

- Reference-counted asset lifetime; shared resource is uploaded to the memory once

-Skeletal animation acceleration algorithm
  


**Render management (in progress)**
-
- **Transparency sorting via merge sort.** Transparent geometry must be drawn
  back-to-front every frame. Merge sort was chosen deliberately: it is stable,
  guarantees O(n log n), and runs in O(n) on nearly-sorted input — which is
  exactly the case between consecutive frames, since camera motion is small.
  The cost is allocation, so the sort operates on a pre-allocated index buffer.

- Material and pass separation; per-draw uniform caching


**UI system (initial)**
-
- Retained-mode widget tree with layout, hit testing and input routing

-Custom font library

**Math library**
-
- Self-contained vector / matrix / quaternion implementation, written to
  control the exact memory layout the renderer expects rather than adapting
  to a third-party convention


Next
-
- Scene management (BSP/Quadtree/Octree for acceleration culling algoritm are the next milestone)

- PBR rendering

-Multi-threaded pool


Build
-
- Windows

Install Visual Studio 2019 or later with the C++ desktop workload

- WebAssembly

Install and activate emsdk (emsdk install latest && emsdk activate latest)

