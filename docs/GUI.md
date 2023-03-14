# Installing Qt 6
Follow the instructions from this [link](https://youtu.be/nscgFv4l53w) to install Qt 6 on Linux, Mac or Windows.

# Build
This project is currently built using CMake. Thus Cmake along with Qt must be installed to build the project. For linux distros, may need to install OpenGL as well.

Use the following command to build:
```
    cd ivu3k
    mkdir build
    cd build
    cmake -DCMAKE_PREFIX_PATH="path_to_qt/Qt/6.4.2/gcc_64/lib/cmake" ..
    make
```
Run
```
    ./ivu3k
```
