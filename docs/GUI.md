# Overview
The GUI contains Code panel, Registers panel, DRAM panel and L1 Cache panel.

An assembly file can be loaded whithin the Code panel. The assembly code would be converted to binary by default. The assembly, binary, together with the address of each instruction would be displayed in the code panel after loading.

The Registers panel records the register name and the data contained in each register.

*The DRAM panel records data in each memory address. One can load/store a memory file to/from the panel from/to a local file.

*The Cache panel records data stored in cache. For every line stored in the panel, it will record tag, index, dirty bit, valid bit and the actual data. (May want to separate the data column to several columns for different offsets.) One can load/store a cache file to/from the panel from/to a local file. Also one can reset the cache before each run.

Items to be implemented are marked with *.

# Implementatation Logs
## 3/15/2023
- Added DRAM and Cache panels together with buttons to load/store memory/cache files in the future.
- Made the Code panel be able to be toggled between binary view and hex view of the instruction data by clicking the header of the column.
- Added `Quick Load` button to the code panel.

## 3/14/2023
Currently the assembler could be run using GUI. An assembly file can be loaded. While loading, the assembly will be complied to instructions in hex. Both assembly and hex instructions will appear in the code panel. Will add the addresses of the instructions later.

Added a basic register panel, which records the value each register currently holds.

# Install Qt 6
Follow the instructions from this [link](https://youtu.be/nscgFv4l53w) to install Qt 6 on Linux, Mac or Windows.

# Build and Run
This project can definitely be built and run using `Qt Creator`.

One can also build the project using command line. This project is currently built using `CMake`. Thus `Cmake` along with `Qt` must be installed to build the project. For linux distros, may need to install `OpenGL` as well.

## Linux 

### Build
```
# in i-love-you-r3000 root directory
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH="path_to_qt/Qt/6.4.2/gcc_64/lib/cmake" ..
make
```
Note: `path_to_qt` is the path to your Qt installation directory.

### Run
```
./ivu3k
```

## Windows
To build on Windows, we may need some CMake generator. I am using `Visual Studio 16 2019`, one may use other CMake generators, e.g. `Ninja`, etc.

### Build
The `MSVC 2019` component of Qt needs to be added in order to build using VS2019. Use the following commands to generate `.sln` file.
```
# in i-love-you-r3000 root directory
mkdir build
cd build
cmake -S .. -B . -DCMAKE_PREFIX_PATH="path_to_qt\Qt\6.4.2\msvc2019_64"
```
Now build with `MSBuild`:
```
MSBuild.exe .\ivu3k.sln
```
### Run
The executable should be in the `build/Debug` folder:
```
cd Debug
.\ivu3k.exe
```
### Note
One may add the path of `MSBuild` and `"path_to_qt\Qt\6.4.2\msvc2019_64\bin"` to the system environment variables.

### Reference
[Qt documentation](https://doc.qt.io/qt-6/cmake-build-on-cmdline.html)

[A Youtube video](https://www.youtube.com/watch?v=HRGZDnNMc5U&t=360s)
