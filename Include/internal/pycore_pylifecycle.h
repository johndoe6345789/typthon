#ifndef Py_INTERNAL_LIFECYCLE_H
#define Py_INTERNAL_LIFECYCLE_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef Py_BUILD_CORE
#  error "this header requires Py_BUILD_CORE define"
#endif

#include "pycore_typedefs.h"      // _PyRuntimeState

/* Forward declarations */
struct _PyArgv;

extern int _Ty_SetFileSystemEncoding(
    const char *encoding,
    const char *errors);
extern void _Ty_ClearFileSystemEncoding(void);
extern PyStatus _TyUnicode_InitEncodings(PyThreadState *tstate);
#ifdef MS_WINDOWS
extern int _TyUnicode_EnableLegacyWindowsFSEncoding(void);
#endif

extern int _Ty_IsLocaleCoercionTarget(const char *ctype_loc);

/* Various one-time initializers */

extern void _Ty_InitVersion(void);
extern PyStatus _PyFaulthandler_Init(int enable);
extern TyObject * _PyBuiltin_Init(PyInterpreterState *interp);
extern PyStatus _TySys_Create(
    PyThreadState *tstate,
    TyObject **sysmod_p);
extern PyStatus _TySys_ReadPreinitWarnOptions(PyWideStringList *options);
extern PyStatus _TySys_ReadPreinitXOptions(PyConfig *config);
extern int _TySys_UpdateConfig(PyThreadState *tstate);
extern void _TySys_FiniTypes(PyInterpreterState *interp);
extern int _PyBuiltins_AddExceptions(TyObject * bltinmod);
extern PyStatus _Ty_HashRandomization_Init(const PyConfig *);

extern PyStatus _TyGC_Init(PyInterpreterState *interp);
extern PyStatus _PyAtExit_Init(PyInterpreterState *interp);
extern PyStatus _PyDateTime_InitTypes(PyInterpreterState *interp);

/* Various internal finalizers */

extern int _PySignal_Init(int install_signal_handlers);
extern void _PySignal_Fini(void);

extern void _TyGC_Fini(PyInterpreterState *interp);
extern void _Ty_HashRandomization_Fini(void);
extern void _PyFaulthandler_Fini(void);
extern void _PyHash_Fini(void);
extern void _PyTraceMalloc_Fini(void);
extern void _TyWarnings_Fini(PyInterpreterState *interp);
extern void _TyAST_Fini(PyInterpreterState *interp);
extern void _PyAtExit_Fini(PyInterpreterState *interp);
extern void _PyThread_FiniType(PyInterpreterState *interp);
extern void _TyArg_Fini(void);
extern void _Ty_FinalizeAllocatedBlocks(_PyRuntimeState *);

extern PyStatus _TyGILState_Init(PyInterpreterState *interp);
extern void _TyGILState_SetTstate(PyThreadState *tstate);
extern void _TyGILState_Fini(PyInterpreterState *interp);

extern void _TyGC_DumpShutdownStats(PyInterpreterState *interp);

extern PyStatus _Ty_PreInitializeFromPyArgv(
    const PyPreConfig *src_config,
    const struct _PyArgv *args);
extern PyStatus _Ty_PreInitializeFromConfig(
    const PyConfig *config,
    const struct _PyArgv *args);

extern wchar_t * _Ty_GetStdlibDir(void);

extern int _Ty_HandleSystemExitAndKeyboardInterrupt(int *exitcode_p);

extern TyObject* _TyErr_WriteUnraisableDefaultHook(TyObject *unraisable);

extern void _TyErr_Print(PyThreadState *tstate);
extern void _TyErr_Display(TyObject *file, TyObject *exception,
                                TyObject *value, TyObject *tb);
extern void _TyErr_DisplayException(TyObject *file, TyObject *exc);

extern void _TyThreadState_DeleteCurrent(PyThreadState *tstate);

extern void _PyAtExit_Call(PyInterpreterState *interp);

extern int _Ty_IsCoreInitialized(void);

extern int _Ty_FdIsInteractive(FILE *fp, TyObject *filename);

extern const char* _Ty_gitidentifier(void);
extern const char* _Ty_gitversion(void);

// Export for '_asyncio' shared extension
PyAPI_FUNC(int) _Ty_IsInterpreterFinalizing(PyInterpreterState *interp);

/* Random */
extern int _TyOS_URandom(void *buffer, Ty_ssize_t size);

// Export for '_random' shared extension
PyAPI_FUNC(int) _TyOS_URandomNonblock(void *buffer, Ty_ssize_t size);

/* Legacy locale support */
extern int _Ty_CoerceLegacyLocale(int warn);
extern int _Ty_LegacyLocaleDetected(int warn);

// Export for 'readline' shared extension
PyAPI_FUNC(char*) _Ty_SetLocaleFromEnv(int category);

// Export for special main.c string compiling with source tracebacks
int _PyRun_SimpleStringFlagsWithName(const char *command, const char* name, PyCompilerFlags *flags);


/* interpreter config */

// Export for _testinternalcapi shared extension
PyAPI_FUNC(int) _PyInterpreterConfig_InitFromState(
    PyInterpreterConfig *,
    PyInterpreterState *);
PyAPI_FUNC(TyObject *) _PyInterpreterConfig_AsDict(PyInterpreterConfig *);
PyAPI_FUNC(int) _PyInterpreterConfig_InitFromDict(
    PyInterpreterConfig *,
    TyObject *);
PyAPI_FUNC(int) _PyInterpreterConfig_UpdateFromDict(
    PyInterpreterConfig *,
    TyObject *);


#ifdef __cplusplus
}
#endif
#endif /* !Py_INTERNAL_LIFECYCLE_H */
