# Routing Algo Solver

A simple visual tool to explore and understand graph routing algorithms like Dijkstra and Bellman-Ford.

## Introduction
This project is a software application that gives a simple and practical UI to two of the most basic and important routing algorithms, Dijkstra and Bellman-Ford.

* The backend of the project is a set of classes designed to handle graph structures and execute routing algorithms on them. It is built to be reusable and efficient.

* The UI is based on raylib. All input/output classes in the frontend folder are built from scratch and kept intentionally simple.

* This is a school project.

## Example
Fill directly on github

## Compilation Instructions
### Requirements
- CMake
- A C++ compiler

The project is built with CMake.
On Windows, you can use Ninja instead of Make.

1. Raylib is automatically included via FetchContent in CMake if it is not installed locally.
2. `mkdir build && cd build`
3. `cmake ..`
4. `make`
5. Run the generated executable.

## Commands

- **N**: Place nodes
- **Left Click**: Select or create an edge  
- **Backspace**: Delete a node or an edge (when hovering)
- **C**: Clear all

## Project Structure

```
├── 📁 src
│   ├── 📁 app
│   │   ├── ⚡ Application.cpp
│   │   ├── ⚡ Application.h
│   │   ├── ⚡ Renderer.cpp
│   │   ├── ⚡ Renderer.h
│   │   ├── ⚡ globals.h
│   │   └── ⚡ main.cpp
│   └── 📁 core
│       ├── 📁 backend
│       │   ├── ⚡ Edge.cpp
│       │   ├── ⚡ Edge.h
│       │   ├── ⚡ EdgeHelper.cpp
│       │   ├── ⚡ EdgeHelper.h
│       │   ├── ⚡ Graph.cpp
│       │   ├── ⚡ Graph.h
│       │   ├── ⚡ Node.cpp
│       │   ├── ⚡ Node.h
│       │   ├── ⚡ NodeHelper.cpp
│       │   ├── ⚡ NodeHelper.h
│       │   ├── ⚡ graphHandling.h
│       │   ├── ⚡ routingAlgos.cpp
│       │   └── ⚡ vecMath.h
│       └── 📁 frontend
│           ├── ⚡ Button.cpp
│           ├── ⚡ Button.h
│           ├── ⚡ Checkbox.cpp
│           ├── ⚡ Checkbox.h
│           ├── ⚡ OutputWindow.cpp
│           ├── ⚡ OutputWindow.h
│           ├── ⚡ TextCase.cpp
│           ├── ⚡ TextCase.h
│           ├── ⚡ Window.cpp
│           ├── ⚡ Window.h
│           └── ⚡ ui.h
├── ⚙️ .gitignore
├── 📄 CMakeLists.txt
└── 📝 README.md
```