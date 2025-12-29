#ifndef Ty_INTERNAL_FUNCTION_H
#define Ty_INTERNAL_FUNCTION_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef Ty_BUILD_CORE
#  error "this header requires Ty_BUILD_CORE define"
#endif

extern TyObject* _PyFunction_Vectorcall(
    TyObject *func,
    TyObject *const *stack,
    size_t nargsf,
    TyObject *kwnames);


#define FUNC_VERSION_UNSET 0
#define FUNC_VERSION_CLEARED 1
#define FUNC_VERSION_FIRST_VALID 2

extern PyFunctionObject* _PyFunction_FromConstructor(PyFrameConstructor *constr);

static inline int
_PyFunction_IsVersionValid(uint32_t version)
{
    return version >= FUNC_VERSION_FIRST_VALID;
}

extern uint32_t _PyFunction_GetVersionForCurrentState(PyFunctionObject *func);
PyAPI_FUNC(void) _PyFunction_SetVersion(PyFunctionObject *func, uint32_t version);
void _PyFunction_ClearCodeByVersion(uint32_t version);
PyFunctionObject *_PyFunction_LookupByVersion(uint32_t version, TyObject **p_code);

extern TyObject *_Ty_set_function_type_params(
    TyThreadState* unused, TyObject *func, TyObject *type_params);


/* See pycore_code.h for explanation about what "stateless" means. */

PyAPI_FUNC(int)
_PyFunction_VerifyStateless(TyThreadState *, TyObject *);

static inline TyObject* _PyFunction_GET_BUILTINS(TyObject *func) {
    return _PyFunction_CAST(func)->func_builtins;
}
#define _PyFunction_GET_BUILTINS(func) _PyFunction_GET_BUILTINS(_TyObject_CAST(func))


#ifdef __cplusplus
}
#endif
#endif /* !Ty_INTERNAL_FUNCTION_H */
