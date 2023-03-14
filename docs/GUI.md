# Installing Qt 6
Follow the instructions from this [link](https://youtu.be/nscgFv4l53w) to install Qt 6 on Linux, Mac or Windows.

# Build and Run
This project is currently built using CMake. Thus Cmake along with Qt must be installed to build the project. For linux distros, may need to install OpenGL as well.

## Linux 

### Build
```
cd ivu3k
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
To build on Windows, we may need some CMake generator. I am using Visual Studio 16 2019, one may use other CMAKE generators, e.g. Ninja, etc.

### Build
The `MSVC 2019` component of Qt needs to be added in order to build using VS2019. Use the following commands to generate `.sln` file.
```
cd ivu3k
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


