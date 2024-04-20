# Structure Search

This piece of software will search levels for a given structure.

# Usage

There are 3 files to be mindful of

- levels.txt
  - Contains a list of paths to files. These paths will be the level data analysed
- structure.txt
  - This will be the level string of structures. It supports multiple structures
- settings.csv
  - The settings for the software

| Setting          | Description                                                                                             | Values                      |
| :--------------- | :------------------------------------------------------------------------------------------------------ | :-------------------------- |
| VERSION_CHECK    | Whether the program should check for signs of update 1.6                                                | `true` or `false`           |
| GRID_SQUARES     | A multiplier for how many grid squares should be considered in the analysis                             | Any Positive Decimal Number |
| CHECK_90         | Whether to check if object rotations are all disvisible by 90. only active if `VERSION_CHECK` is `true` | `true` or `false`           |
| SCORE_THRESHOLD  | How high the similarity score has to be before it shows on logs                                         | `0.0-1.0`                   |
| STRUCTURE_INDEX  | Which structure should be used in order of X Position. Index is **0-Based**                             | Any Positive number         |
| USE_LEVEL_FOLDER | If the `levels/` folder should be scanned rather than using `levels.txt`                                | `true` or `false`           |
| THREADS          | The number of threads to use in the program                                                             | Any Positive number         |

# Building

> This project can be built using CMake and C++ 17. To start recursively clone the repository

```sh
git clone https://github.com/Wyliemaster/Geometry-Dash-Structure-Search.git --recursive
``` 
# Windows

> *Before you can compile this on windows, you need to have a library for Zlib available. so to start off compile zlib and place the `zlibstatic.lib` inside the `lib/` directory*

Once `zlibstatic.lib` has been placed in the directory, you can configure cmake from the project root using

```sh
cmake -B build
```

and then you can build it in release mode

```sh
cmake --build build --config release
```

# Linux

> You will need zlib installed to build this project. You can do it with these commands
> ```sh
> sudo apt install zlib1g
> ```

From the root of the project enter the following command to configure cmake

```sh
 cmake -B build -DCMAKE_BUILD_TYPE=Release
 ```

 and then to build, run

```sh
  cmake --build build
```

# Credits
- [SMJS](https://github.com/SMJSGaming) for Zlib and Base64 assistance