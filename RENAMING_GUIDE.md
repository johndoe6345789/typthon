# Typthon Renaming Guide

This document tracks the ongoing effort to rename Python/Py* prefixes to Typthon/Ty* throughout the codebase.

## Overview

Typthon is a fork of Python that aims to become a strictly typed language. As part of this transformation, we're systematically renaming all Python-related prefixes to Typthon equivalents.

## Completed Renamings

### Phase 1: Core API Functions (Completed in PR #21)
- Basic Py* → Ty* renames for most of the codebase
- Core Python API functions
- Type system functions
- Object management functions

### Phase 2: Build System Fixes (This PR)

#### Python/crossinterp.c
- ✅ `PyMem_RawCalloc` → `TyMem_RawCalloc` (7 occurrences)
- ✅ `PyMem_RawMalloc` → `TyMem_RawMalloc` (2 occurrences)
- ✅ `PyThreadState_Get` → `TyThreadState_Get` (5 occurrences)
- ✅ `PyThreadState_Swap` → `TyThreadState_Swap` (8 occurrences)
- ✅ `PyThreadState_Clear` → `TyThreadState_Clear` (2 occurrences)
- ✅ `PyThreadState_Delete` → `TyThreadState_Delete` (2 occurrences)
- ✅ `PyThreadState_GET` → `TyThreadState_GET` (1 occurrence)
- ✅ `PyThreadState_GetInterpreter` → `TyThreadState_GetInterpreter` (4 occurrences)
- ✅ `PyInterpreterState_Get` → `TyInterpreterState_Get` (5 occurrences)
- ✅ `PyInterpreterState_GetID` → `TyInterpreterState_GetID` (3 occurrences)
- ✅ `PyInterpreterState_GetDict` → `TyInterpreterState_GetDict` (1 occurrence)
- ✅ `PyInterpreterState_Delete` → `TyInterpreterState_Delete` (1 occurrence)
- ✅ `PyMarshal_ReadObjectFromString` → `TyMarshal_ReadObjectFromString` (1 occurrence)
- ✅ `PyMarshal_WriteObjectToString` → `TyMarshal_WriteObjectToString` (1 occurrence)

#### Python/specialize.c
- ✅ `_Py_OPCODE` → `_Ty_OPCODE` (2 occurrences)

#### Modules/atexitmodule.c
- ✅ `Py_BEGIN_CRITICAL_SECTION` → `Ty_BEGIN_CRITICAL_SECTION` (1 occurrence)
- ✅ `Py_END_CRITICAL_SECTION` → `Ty_END_CRITICAL_SECTION` (1 occurrence)

## Remaining Work

### Missing Function Implementations

The following functions are referenced but not yet implemented or need to be found in the codebase:

1. `_Ty_bswap32` - Byte swap function (referenced in unicodeobject.c)
2. `Ty_off_t_converter` - File offset converter (referenced in posixmodule.c)
3. Various `_Ty_Specialize_*` functions:
   - `_Ty_Specialize_BinaryOp`
   - `_Ty_Specialize_Call`
   - `_Ty_Specialize_CallKw`
   - `_Ty_Specialize_CompareOp`
   - `_Ty_Specialize_ContainsOp`
   - `_Ty_Specialize_ForIter`
   - `_Ty_Specialize_LoadAttr`
   - `_Ty_Specialize_LoadGlobal`
   - `_Ty_Specialize_LoadSuperAttr`
   - `_Ty_Specialize_Send`
   - `_Ty_Specialize_StoreAttr`
   - `_Ty_Specialize_StoreSubscr`
   - `_Ty_Specialize_ToBool`
   - `_Ty_Specialize_UnpackSequence`
4. `_Ty_InitCleanup` - Cleanup initialization function

### Directory Structure

Per the requirement to rename the Python folder to Typthon, we still need to:
- [ ] Rename `Python/` directory to `Typthon/`
- [ ] Update all references in `CMakeLists.txt`
- [ ] Update all #include paths
- [ ] Update documentation

## Impact on Strict Typing Goals

The renaming work is a prerequisite for implementing strict typing in Typthon because:

1. **Clear Identity**: Establishes Typthon as distinct from Python
2. **Clean Foundation**: Ensures all APIs use consistent naming
3. **Future Extensibility**: Makes it easier to add new typed features without confusion
4. **Documentation**: Makes it clear what belongs to Typthon vs. Python compatibility layers

## Testing

After each batch of renames, we verify:
- ✅ Code compiles without syntax errors
- 🔄 Linker errors are being resolved progressively
- ⏳ Test suite passes (pending full build)
- ⏳ Version output works: `typthon --version`
- ⏳ Help works: `typthon --help`

## Notes

- Some references to "Py" in comments are intentionally left unchanged when they refer to the Python compatibility or origin
- Build is progressing - most Py→Ty renames in core files are complete
- Next phase will focus on finding/implementing missing specialized functions
