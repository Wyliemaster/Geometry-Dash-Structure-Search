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

This project can be built using CMake and C++ 17.

> **Important:** this project relies zlib. Please compile a static instance of it and place it into `lib` before trying to build

- On windows the lib is `zlibstatic.lib`
- On Unix the lib is `libz.so`

Firstly, create a build directory

```sh
mkdir build
```

And then navigate to it

```sh
cd build
```

now run the following command

```sh
cmake ..
```

## Windows

Open up the build folder and open the .sln file. from there go to the `search` project and build with visual studio

## Linux

enter the following

```sh
make
```

# Credits
- [SMJS](https://github.com/SMJSGaming) for Zlib and Base64 assistance