# Soundscape Generator

## When adding SoundscapeGenerator to Visual Studio for the first time.

[Download and Install](http://sol.gfxile.net/soloud/soloud_20160109.zip) - soloud_20160109.zip
Move the contents of the zip to C:\SoLoud

### Add this to C/C++ -> General -> Additional Include Directories
```
C:\SoLoud\include 
```

### Add  this to Linker -> General -> Additional Library Directories
```
C:\SoLoud\lib
```

### Add  this at the end  to Linker -> Input -> Additional Dependencies 
```
soloud_static_x86.lib
```

### Change solution platform from x64 to x86


