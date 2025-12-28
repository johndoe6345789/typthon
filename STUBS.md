# Typthon Build System Stubs Documentation

This document lists all stub implementations created to resolve linking issues in the Typthon CMake build system.

## Stub File Location

All stubs are implemented in: `Python/frozen_stubs.c`

## Stubbed Components

### 1. Frozen Modules

**Purpose**: CPython's frozen modules system allows embedding Python code as C arrays. These are normally generated during the build process.

**Stubs Created**:
- `_PyImport_FrozenBootstrap` - Bootstrap frozen modules
- `_PyImport_FrozenStdlib` - Standard library frozen modules  
- `_PyImport_FrozenTest` - Test frozen modules
- `PyImport_FrozenModules` - Main frozen modules array
- `_PyImport_FrozenAliases` - Frozen module aliases

**Implementation**: Empty arrays/NULL pointers that satisfy linker requirements but provide no actual frozen modules.

### 2. Import System

**Purpose**: Module initialization table for built-in modules.

**Stubs Created**:
- `_PyImport_Inittab` - Empty module initialization table

**Implementation**: Empty array that prevents initialization of additional built-in modules beyond those explicitly linked.

### 3. Build Information

**Purpose**: Provide version and build metadata to the interpreter.

**Stubs Created**:
- `Py_GetBuildInfo()` - Returns build date/time string
- `_Py_gitidentifier()` - Returns git branch identifier ("default")
- `_Py_gitversion()` - Returns version string ("Typthon 3.14.0")

**Implementation**: Simple string returns with minimal metadata.

### 4. Dynamic Loading

**Purpose**: Configuration for dynamic library loading.

**Stubs Created**:
- `_PyImport_GetDLOpenFlags()` - Returns dlopen flags

**Implementation**: Returns `RTLD_NOW | RTLD_GLOBAL` (0x102) for immediate symbol resolution.

### 5. Path Configuration

**Purpose**: Initialize Python module search paths.

**Stubs Created**:
- `_PyConfig_InitPathConfig()` - Initializes path configuration

**Implementation**: Returns `PyStatus_Ok()` without actually configuring paths. The interpreter will use defaults.

### 6. Fault Handler

**Purpose**: Signal handling and crash reporting module.

**Stubs Created**:
- `_PyFaulthandler_Init()` - Initialize fault handler
- `_PyFaulthandler_Fini()` - Finalize fault handler

**Implementation**: No-op functions that return success. Fault handler module excluded from build due to compilation issues.

**Note**: The faulthandler module was excluded from compilation (`Modules/faulthandler.c`) due to constant initialization errors with `Py_ARRAY_LENGTH` macro.

### 7. POSIX Functions

**Purpose**: Platform-specific system call that's not universally available.

**Stubs Created**:
- `plock()` - Process memory locking (Solaris-specific)

**Implementation**: Returns -1 with errno set to `ENOSYS` (not implemented). Also removed `HAVE_PLOCK` from pyconfig.h.

**Note**: `plock()` is a legacy Solaris function not available on modern Linux systems.

## Configuration Changes

### pyconfig.h Modifications

The following configuration define was commented out:

```c
/* plock is not available on modern Linux systems */
/* #define HAVE_PLOCK 1 */
```

This prevents the code from attempting to call the non-existent `plock()` function, instead using our stub implementation.

## Module Exclusions

The following module was excluded from the build:

- **faulthandler** (`Modules/faulthandler.c`) - Excluded due to compilation errors with non-constant array initialization

## Impact on Functionality

These stubs mean the following features are not available in this build:

1. **No frozen modules**: Cannot embed Python code as frozen C arrays
2. **No fault handler**: No signal handling for crashes/segfaults
3. **No plock**: No Solaris-style process memory locking
4. **Minimal build info**: Git metadata is stubbed with placeholder values
5. **No custom built-in modules**: Only modules explicitly linked are available

## Future Improvements

To get a fully-functional Python interpreter, the following would be needed:

1. Generate actual frozen modules using `Tools/build/freeze_modules.py`
2. Re-enable and fix the faulthandler module compilation
3. Implement proper path configuration in `_PyConfig_InitPathConfig()`
4. Generate real build information with git metadata
5. Add more built-in modules to the `_PyImport_Inittab` table

## Testing

The interpreter successfully:
- ✅ Starts and shows version: `typthon --version`
- ✅ Displays help: `typthon --help`
- ✅ Links all core libraries without errors
- ✅ Builds with Ninja in under 2 minutes on modern hardware

## Build Statistics

- **Total source files compiled**: 177
- **Core library size**: libpython_core.a
- **Executable**: typthon
- **Build tool**: Ninja (recommended) or Unix Makefiles
- **Build time**: ~90 seconds with parallel compilation (`-j4`)
