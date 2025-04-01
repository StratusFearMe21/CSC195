# Note to teacher

Because I'm on Linux, this project uses [`meson`](https://github.com/mesonbuild/meson) as it's main build system instead of Visual Studio. *However*, it is still possible to build this project under Visual Studio with a few simple steps

1. Install `meson` via the command line
```sh
winget install mesonbuild.meson
```

2. Use `meson` to set up the build directory
```sh
cd CSC195
meson setup vsbuild --backend=vs
```

3. Open the generated solution under the new `vsbuild` folder

If at any point I need to turn in an assignment as a ZIP file, I'll make sure to bundle a working solution with it. 
