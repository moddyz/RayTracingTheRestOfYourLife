# RayTracingTheRestOfYourLife

An implementation of the book [Ray Tracing: The Rest of Your Life](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html).  

## Table of Contents

- [Prequel](#prequel)
- [Programs](#programs)
  * [0. A Simple Monte Carlo Program](#0-a-simple-monte-carlo-program)
- [Library](#library)
- [Documentation](#documentation)
- [Building](#building)
- [Build Status](#build-status)

## Prequel

The implementation(s) to the prequels are available:  
- [RayTracingInOneWeekend](https://github.com/moddyz/RayTracingInOneWeekend).
- [RayTracingTheNextWeek](https://github.com/moddyz/RayTracingTheNextWeek).

## Programs

### 0. A Simple Monte Carlo Program

Using random sampling techniques to approximate _pi_.

[Source code](./src/0_aSimpleMonteCarloProgram/main.cpp)

[Link to Chapter 2](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html#asimplemontecarloprogram)

## Library

Common functions and classes are refactored into the [raytrace library](./src/raytrace) and the [GraphicsMath](https://github.com/moddyz/GraphicsMath) project.

## Documentation

Doxygen documentation based on the latest state of master, [hosted by GitHub Pages](https://moddyz.github.io/RayTracingTheRestOfYourLife/).

## Building

A convenience build script is provided, for building all targets, and optionally installing to a location:
```
./build.sh <OPTIONAL_INSTALL_LOCATION>
```

### Requirements

- `>= CMake-3.17`
- `C++17`
- `doxygen` and `graphviz` (optional for documentation)

## Build Status

|       | master | 
| ----- | ------ | 
| macOS-10.14 | [![Build Status](https://travis-ci.com/moddyz/RayTracingTheRestOfYourLife.svg?branch=master)](https://travis-ci.com/moddyz/RayTracingTheRestOfYourLife) |
