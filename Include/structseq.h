
/* Named tuple object interface */

#ifndef Ty_STRUCTSEQ_H
#define Ty_STRUCTSEQ_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct PyStructSequence_Field {
    const char *name;
    const char *doc;
} PyStructSequence_Field;

typedef struct PyStructSequence_Desc {
    const char *name;
    const char *doc;
    PyStructSequence_Field *fields;
    int n_in_sequence;
} PyStructSequence_Desc;

PyAPI_DATA(const char * const) PyStructSequence_UnnamedField;

#ifndef Ty_LIMITED_API
PyAPI_FUNC(void) PyStructSequence_InitType(TyTypeObject *type,
                                           PyStructSequence_Desc *desc);
PyAPI_FUNC(int) PyStructSequence_InitType2(TyTypeObject *type,
                                           PyStructSequence_Desc *desc);
#endif
PyAPI_FUNC(TyTypeObject*) PyStructSequence_NewType(PyStructSequence_Desc *desc);

PyAPI_FUNC(TyObject *) PyStructSequence_New(TyTypeObject* type);

PyAPI_FUNC(void) PyStructSequence_SetItem(TyObject*, Ty_ssize_t, TyObject*);
PyAPI_FUNC(TyObject*) PyStructSequence_GetItem(TyObject*, Ty_ssize_t);

#ifndef Ty_LIMITED_API
typedef PyTupleObject PyStructSequence;
#define PyStructSequence_SET_ITEM PyStructSequence_SetItem
#define PyStructSequence_GET_ITEM PyStructSequence_GetItem
#endif

#ifdef __cplusplus
}
#endif
#endif /* !Ty_STRUCTSEQ_H */
