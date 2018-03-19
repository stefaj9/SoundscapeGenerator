# Soundscape Generator

## When adding SoundscapeGenerator to a Visual Studio for the first time.

[Download and Install](https://www.openal.org/downloads/) - OpenAL 1.1 Core SDK (zip)

### Add this to C/C++ -> General -> Additional Include Directories
```
C:\Program Files (x86)\OpenAL 1.1 SDK\include 
```

### Add  this to Linker -> General -> Additional Library Directories
```
C:\Program Files (x86)\OpenAL 1.1 SDK\libs\Win32
```

### Add  this at the end  to Linker -> Input -> Additional Dependencies 
```
OpenAL32.lib 
```
### Add this at the end to C/C++ -> Preprocessor -> Preprocessor Definitions
```
_CRT_SECURE_NO_WARNINGS
```

### Change solution platform from x64 to x86


