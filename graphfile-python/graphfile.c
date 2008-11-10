/* 0.9.7 on Mon Nov 10 17:17:09 2008 */

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "structmember.h"
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#if PY_VERSION_HEX < 0x02050000
  typedef int Py_ssize_t;
  #define PY_SSIZE_T_MAX INT_MAX
  #define PY_SSIZE_T_MIN INT_MIN
  #define PyInt_FromSsize_t(z) PyInt_FromLong(z)
  #define PyInt_AsSsize_t(o)	PyInt_AsLong(o)
#endif
#ifndef WIN32
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
#endif
#ifdef __cplusplus
#define __PYX_EXTERN_C extern "C"
#else
#define __PYX_EXTERN_C extern
#endif
#include <math.h>
#include "graphfile.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "sys/types.h"
#include "stdio.h"
#include "unistd.h"


typedef struct {PyObject **p; char *s;} __Pyx_InternTabEntry; /*proto*/
typedef struct {PyObject **p; char *s; long n;} __Pyx_StringTabEntry; /*proto*/

static PyObject *__pyx_m;
static PyObject *__pyx_b;
static int __pyx_lineno;
static char *__pyx_filename;
static char **__pyx_f;

static int __Pyx_ArgTypeTest(PyObject *obj, PyTypeObject *type, int none_allowed, char *name); /*proto*/

static PyObject *__Pyx_CreateClass(PyObject *bases, PyObject *dict, PyObject *name, char *modname); /*proto*/

static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb); /*proto*/

static PyObject *__Pyx_GetName(PyObject *dict, PyObject *name); /*proto*/

static PyObject *__Pyx_UnpackItem(PyObject *); /*proto*/
static int __Pyx_EndUnpack(PyObject *); /*proto*/

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t); /*proto*/

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t); /*proto*/

static void __Pyx_AddTraceback(char *funcname); /*proto*/

/* Declarations from posix */


/* Declarations from graphfile */

struct __pyx_obj_9graphfile__Linkable {
  PyObject_HEAD
  graphfile_linkable_t linkable;
};

struct __pyx_obj_9graphfile_Writer {
  PyObject_HEAD
  graphfile_writer_t writer;
  PyObject *fileobj;
};

struct __pyx_obj_9graphfile_Reader {
  PyObject_HEAD
  graphfile_reader_t reader;
  struct __pyx_obj_9graphfile__Linkable *root;
  PyObject *fileobj;
};




static PyTypeObject *__pyx_ptype_9graphfile__Linkable = 0;
static PyTypeObject *__pyx_ptype_9graphfile_Writer = 0;
static PyTypeObject *__pyx_ptype_9graphfile_Reader = 0;
static void *__pyx_f_9graphfile_allocate(size_t); /*proto*/
static int __pyx_f_9graphfile_reallocate(void **,size_t); /*proto*/
static FILE *__pyx_f_9graphfile_file_from_obj(PyObject *); /*proto*/


/* Implementation of graphfile */


static PyObject *__pyx_n_Error;

static void *__pyx_f_9graphfile_allocate(size_t __pyx_v_size) {
  void *__pyx_v_ptr;
  void *__pyx_r;
  int __pyx_1;

  /* "pyrex-lib/memory.pyx":32 */
  __pyx_v_ptr = malloc(__pyx_v_size);

  /* "pyrex-lib/memory.pyx":33 */
  __pyx_1 = (__pyx_v_ptr == NULL);
  if (__pyx_1) {
    __Pyx_Raise(PyExc_MemoryError, 0, 0);
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 34; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "pyrex-lib/memory.pyx":35 */
  __pyx_r = __pyx_v_ptr;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("graphfile.allocate");
  __pyx_r = NULL;
  __pyx_L0:;
  return __pyx_r;
}

static int __pyx_f_9graphfile_reallocate(void **__pyx_v_ptr,size_t __pyx_v_size) {
  void *__pyx_v_new_ptr;
  int __pyx_r;
  int __pyx_1;

  /* "pyrex-lib/memory.pyx":39 */
  __pyx_1 = (__pyx_v_size == 0);
  if (__pyx_1) {

    /* "pyrex-lib/memory.pyx":40 */
    free((__pyx_v_ptr[0]));

    /* "pyrex-lib/memory.pyx":41 */
    (__pyx_v_ptr[0]) = NULL;

    /* "pyrex-lib/memory.pyx":42 */
    __pyx_r = 0;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "pyrex-lib/memory.pyx":43 */
  __pyx_v_new_ptr = realloc((__pyx_v_ptr[0]),__pyx_v_size);

  /* "pyrex-lib/memory.pyx":44 */
  __pyx_1 = (__pyx_v_new_ptr == NULL);
  if (__pyx_1) {
    __Pyx_Raise(PyExc_MemoryError, 0, 0);
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 45; goto __pyx_L1;}
    goto __pyx_L3;
  }
  __pyx_L3:;

  /* "pyrex-lib/memory.pyx":46 */
  (__pyx_v_ptr[0]) = __pyx_v_new_ptr;

  /* "pyrex-lib/memory.pyx":47 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("graphfile.reallocate");
  __pyx_r = (-1);
  __pyx_L0:;
  return __pyx_r;
}

static PyObject *__pyx_k2p;

static char __pyx_k2[] = "Invalid fileobj";

static FILE *__pyx_f_9graphfile_file_from_obj(PyObject *__pyx_v_fileobj) {
  FILE *__pyx_v_file;
  FILE *__pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  Py_INCREF(__pyx_v_fileobj);

  /* "pyrex-lib/python.pyx":40 */
  __pyx_v_file = PyFile_AsFile(__pyx_v_fileobj);

  /* "pyrex-lib/python.pyx":41 */
  __pyx_1 = (NULL == __pyx_v_file);
  if (__pyx_1) {
    __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_2) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 42; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 42; goto __pyx_L1;}
    Py_INCREF(__pyx_k2p);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_k2p);
    __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 42; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_4, 0, 0);
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    {__pyx_filename = __pyx_f[1]; __pyx_lineno = 42; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "pyrex-lib/python.pyx":43 */
  __pyx_r = __pyx_v_file;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("graphfile.file_from_obj");
  __pyx_r = NULL;
  __pyx_L0:;
  Py_DECREF(__pyx_v_fileobj);
  return __pyx_r;
}

static PyObject *__pyx_n_graphfile_writer_init;


static int __pyx_f_9graphfile_6Writer___cinit__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_9graphfile_6Writer___cinit__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_fileobj = 0;
  int __pyx_r;
  FILE *__pyx_1;
  int __pyx_2;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  static char *__pyx_argnames[] = {"fileobj",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_fileobj)) return -1;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_fileobj);

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":30 */
  __pyx_1 = __pyx_f_9graphfile_file_from_obj(__pyx_v_fileobj); if (__pyx_1 == NULL) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 30; goto __pyx_L1;}
  __pyx_2 = (0 != graphfile_writer_init((&((struct __pyx_obj_9graphfile_Writer *)__pyx_v_self)->writer),__pyx_1));
  if (__pyx_2) {
    __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_3) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 31; goto __pyx_L1;}
    __pyx_4 = PyTuple_New(1); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 31; goto __pyx_L1;}
    Py_INCREF(__pyx_n_graphfile_writer_init);
    PyTuple_SET_ITEM(__pyx_4, 0, __pyx_n_graphfile_writer_init);
    __pyx_5 = PyObject_CallObject(__pyx_3, __pyx_4); if (!__pyx_5) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 31; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __Pyx_Raise(__pyx_5, 0, 0);
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    {__pyx_filename = __pyx_f[2]; __pyx_lineno = 31; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":32 */
  Py_INCREF(__pyx_v_fileobj);
  Py_DECREF(((struct __pyx_obj_9graphfile_Writer *)__pyx_v_self)->fileobj);
  ((struct __pyx_obj_9graphfile_Writer *)__pyx_v_self)->fileobj = __pyx_v_fileobj;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("graphfile.Writer.__cinit__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_fileobj);
  return __pyx_r;
}

static void __pyx_f_9graphfile_6Writer___dealloc__(PyObject *__pyx_v_self); /*proto*/
static void __pyx_f_9graphfile_6Writer___dealloc__(PyObject *__pyx_v_self) {
  Py_INCREF(__pyx_v_self);
  graphfile_writer_fini((&((struct __pyx_obj_9graphfile_Writer *)__pyx_v_self)->writer));

  Py_DECREF(__pyx_v_self);
}

static PyObject *__pyx_n_graphfile_writer_set_root;


static PyObject *__pyx_f_9graphfile_6Writer_set_root(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_9graphfile_6Writer_set_root(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  struct __pyx_obj_9graphfile__Linkable *__pyx_v_root = 0;
  PyObject *__pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  static char *__pyx_argnames[] = {"root",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_root)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_root);
  if (!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_root), __pyx_ptype_9graphfile__Linkable, 1, "root")) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 36; goto __pyx_L1;}
  __pyx_1 = (0 != graphfile_writer_set_root((&((struct __pyx_obj_9graphfile_Writer *)__pyx_v_self)->writer),(&__pyx_v_root->linkable)));
  if (__pyx_1) {
    __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_2) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 38; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 38; goto __pyx_L1;}
    Py_INCREF(__pyx_n_graphfile_writer_set_root);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_n_graphfile_writer_set_root);
    __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 38; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_4, 0, 0);
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    {__pyx_filename = __pyx_f[2]; __pyx_lineno = 38; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("graphfile.Writer.set_root");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_root);
  return __pyx_r;
}

static PyObject *__pyx_n_graphfile_writer_write;


static PyObject *__pyx_f_9graphfile_6Writer_write(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_9graphfile_6Writer_write(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_data = 0;
  PyObject *__pyx_v_linkables = 0;
  struct __pyx_obj_9graphfile__Linkable *__pyx_v_result_linkable;
  char *__pyx_v_buffer;
  Py_ssize_t __pyx_v_buffer_length;
  graphfile_linkable_t *__pyx_v_c_linkables;
  graphfile_size_t __pyx_v_i;
  int __pyx_v_result;
  PyObject *__pyx_v_linkable;
  PyObject *__pyx_r;
  int __pyx_1;
  Py_ssize_t __pyx_2;
  void *__pyx_3;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  PyObject *__pyx_6 = 0;
  graphfile_size_t __pyx_7;
  static char *__pyx_argnames[] = {"data","linkables",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "OO", __pyx_argnames, &__pyx_v_data, &__pyx_v_linkables)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_data);
  Py_INCREF(__pyx_v_linkables);
  __pyx_v_result_linkable = ((struct __pyx_obj_9graphfile__Linkable *)Py_None); Py_INCREF(Py_None);
  __pyx_v_linkable = Py_None; Py_INCREF(Py_None);

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":48 */
  __pyx_1 = PyString_AsStringAndSize(__pyx_v_data,(&__pyx_v_buffer),(&__pyx_v_buffer_length)); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 48; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":49 */
  __pyx_2 = PyObject_Length(__pyx_v_linkables); if (__pyx_2 == -1) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 49; goto __pyx_L1;}
  __pyx_3 = __pyx_f_9graphfile_allocate(((sizeof(graphfile_linkable_t)) * __pyx_2)); if (__pyx_3 == NULL) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 49; goto __pyx_L1;}
  __pyx_v_c_linkables = ((graphfile_linkable_t *)__pyx_3);

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":50 */
  /*try:*/ {

    /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":51 */
    __pyx_4 = PyTuple_New(1); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 51; goto __pyx_L3;}
    Py_INCREF(__pyx_v_linkables);
    PyTuple_SET_ITEM(__pyx_4, 0, __pyx_v_linkables);
    __pyx_5 = PyObject_CallObject(((PyObject *)(&PyEnum_Type)), __pyx_4); if (!__pyx_5) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 51; goto __pyx_L3;}
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __pyx_4 = PyObject_GetIter(__pyx_5); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 51; goto __pyx_L3;}
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    for (;;) {
      __pyx_5 = PyIter_Next(__pyx_4);
      if (!__pyx_5) {
        if (PyErr_Occurred()) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 51; goto __pyx_L3;}
        break;
      }
      __pyx_6 = PyObject_GetIter(__pyx_5); if (!__pyx_6) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 51; goto __pyx_L3;}
      Py_DECREF(__pyx_5); __pyx_5 = 0;
      __pyx_5 = __Pyx_UnpackItem(__pyx_6); if (!__pyx_5) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 51; goto __pyx_L3;}
      __pyx_7 = PyInt_AsUnsignedLongLongMask(__pyx_5); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 51; goto __pyx_L3;}
      Py_DECREF(__pyx_5); __pyx_5 = 0;
      __pyx_v_i = __pyx_7;
      __pyx_5 = __Pyx_UnpackItem(__pyx_6); if (!__pyx_5) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 51; goto __pyx_L3;}
      Py_DECREF(__pyx_v_linkable);
      __pyx_v_linkable = __pyx_5;
      __pyx_5 = 0;
      if (__Pyx_EndUnpack(__pyx_6) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 51; goto __pyx_L3;}
      Py_DECREF(__pyx_6); __pyx_6 = 0;
      (__pyx_v_c_linkables[__pyx_v_i]) = ((struct __pyx_obj_9graphfile__Linkable *)__pyx_v_linkable)->linkable;
    }
    Py_DECREF(__pyx_4); __pyx_4 = 0;

    /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":53 */
    __pyx_5 = PyObject_CallObject(((PyObject *)__pyx_ptype_9graphfile__Linkable), 0); if (!__pyx_5) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 53; goto __pyx_L3;}
    Py_DECREF(((PyObject *)__pyx_v_result_linkable));
    __pyx_v_result_linkable = ((struct __pyx_obj_9graphfile__Linkable *)__pyx_5);
    __pyx_5 = 0;

    /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":54 */
    __pyx_2 = PyObject_Length(__pyx_v_linkables); if (__pyx_2 == -1) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 55; goto __pyx_L3;}
    __pyx_v_result = graphfile_writer_write((&((struct __pyx_obj_9graphfile_Writer *)__pyx_v_self)->writer),__pyx_v_buffer,__pyx_v_buffer_length,__pyx_v_c_linkables,__pyx_2,(&__pyx_v_result_linkable->linkable));

    /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":57 */
    __pyx_1 = (__pyx_v_result != 0);
    if (__pyx_1) {
      __pyx_6 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_6) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 58; goto __pyx_L3;}
      __pyx_4 = PyTuple_New(1); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 58; goto __pyx_L3;}
      Py_INCREF(__pyx_n_graphfile_writer_write);
      PyTuple_SET_ITEM(__pyx_4, 0, __pyx_n_graphfile_writer_write);
      __pyx_5 = PyObject_CallObject(__pyx_6, __pyx_4); if (!__pyx_5) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 58; goto __pyx_L3;}
      Py_DECREF(__pyx_6); __pyx_6 = 0;
      Py_DECREF(__pyx_4); __pyx_4 = 0;
      __Pyx_Raise(__pyx_5, 0, 0);
      Py_DECREF(__pyx_5); __pyx_5 = 0;
      {__pyx_filename = __pyx_f[2]; __pyx_lineno = 58; goto __pyx_L3;}
      goto __pyx_L7;
    }
    __pyx_L7:;

    /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":59 */
    Py_INCREF(((PyObject *)__pyx_v_result_linkable));
    __pyx_r = ((PyObject *)__pyx_v_result_linkable);
    goto __pyx_L2;
  }
  /*finally:*/ {
    int __pyx_why;
    PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
    int __pyx_exc_lineno;
    __pyx_why = 0; goto __pyx_L4;
    __pyx_L2: __pyx_why = 3; goto __pyx_L4;
    __pyx_L3: {
      __pyx_why = 4;
      Py_XDECREF(__pyx_6); __pyx_6 = 0;
      Py_XDECREF(__pyx_4); __pyx_4 = 0;
      Py_XDECREF(__pyx_5); __pyx_5 = 0;
      PyErr_Fetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
      __pyx_exc_lineno = __pyx_lineno;
      goto __pyx_L4;
    }
    __pyx_L4:;
    free(__pyx_v_c_linkables);
    switch (__pyx_why) {
      case 3: goto __pyx_L0;
      case 4: {
        PyErr_Restore(__pyx_exc_type, __pyx_exc_value, __pyx_exc_tb);
        __pyx_lineno = __pyx_exc_lineno;
        __pyx_exc_type = 0;
        __pyx_exc_value = 0;
        __pyx_exc_tb = 0;
        goto __pyx_L1;
      }
    }
  }

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  Py_XDECREF(__pyx_6);
  __Pyx_AddTraceback("graphfile.Writer.write");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_result_linkable);
  Py_DECREF(__pyx_v_linkable);
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_data);
  Py_DECREF(__pyx_v_linkables);
  return __pyx_r;
}

static PyObject *__pyx_n_graphfile_reader_init;


static int __pyx_f_9graphfile_6Reader___cinit__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_9graphfile_6Reader___cinit__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_fileobj = 0;
  int __pyx_r;
  PyObject *__pyx_1 = 0;
  FILE *__pyx_2;
  int __pyx_3;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  static char *__pyx_argnames[] = {"fileobj",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_fileobj)) return -1;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_fileobj);

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":68 */
  __pyx_1 = PyObject_CallObject(((PyObject *)__pyx_ptype_9graphfile__Linkable), 0); if (!__pyx_1) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 68; goto __pyx_L1;}
  Py_DECREF(((PyObject *)((struct __pyx_obj_9graphfile_Reader *)__pyx_v_self)->root));
  ((struct __pyx_obj_9graphfile_Reader *)__pyx_v_self)->root = ((struct __pyx_obj_9graphfile__Linkable *)__pyx_1);
  __pyx_1 = 0;

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":69 */
  __pyx_2 = __pyx_f_9graphfile_file_from_obj(__pyx_v_fileobj); if (__pyx_2 == NULL) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 69; goto __pyx_L1;}
  __pyx_3 = (0 != graphfile_reader_init((&((struct __pyx_obj_9graphfile_Reader *)__pyx_v_self)->reader),__pyx_2,(&((struct __pyx_obj_9graphfile_Reader *)__pyx_v_self)->root->linkable)));
  if (__pyx_3) {
    __pyx_1 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_1) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 70; goto __pyx_L1;}
    __pyx_4 = PyTuple_New(1); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 70; goto __pyx_L1;}
    Py_INCREF(__pyx_n_graphfile_reader_init);
    PyTuple_SET_ITEM(__pyx_4, 0, __pyx_n_graphfile_reader_init);
    __pyx_5 = PyObject_CallObject(__pyx_1, __pyx_4); if (!__pyx_5) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 70; goto __pyx_L1;}
    Py_DECREF(__pyx_1); __pyx_1 = 0;
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __Pyx_Raise(__pyx_5, 0, 0);
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    {__pyx_filename = __pyx_f[2]; __pyx_lineno = 70; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":71 */
  Py_INCREF(__pyx_v_fileobj);
  Py_DECREF(((struct __pyx_obj_9graphfile_Reader *)__pyx_v_self)->fileobj);
  ((struct __pyx_obj_9graphfile_Reader *)__pyx_v_self)->fileobj = __pyx_v_fileobj;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("graphfile.Reader.__cinit__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_fileobj);
  return __pyx_r;
}

static void __pyx_f_9graphfile_6Reader___dealloc__(PyObject *__pyx_v_self); /*proto*/
static void __pyx_f_9graphfile_6Reader___dealloc__(PyObject *__pyx_v_self) {
  Py_INCREF(__pyx_v_self);
  graphfile_reader_fini((&((struct __pyx_obj_9graphfile_Reader *)__pyx_v_self)->reader));

  Py_DECREF(__pyx_v_self);
}

static PyObject *__pyx_n_graphfile_reader_read;
static PyObject *__pyx_n_append;

static PyObject *__pyx_k9p;

static char __pyx_k9[] = "File has changed within a single read";

static PyObject *__pyx_f_9graphfile_6Reader_read(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_9graphfile_6Reader_read(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  struct __pyx_obj_9graphfile__Linkable *__pyx_v_linkable = 0;
  graphfile_size_t __pyx_v_i;
  int __pyx_v_result;
  char *__pyx_v_result_buffer;
  graphfile_linkable_t *__pyx_v_result_linkables;
  graphfile_size_t __pyx_v_result_buffer_length;
  graphfile_size_t __pyx_v_new_result_buffer_length;
  graphfile_size_t __pyx_v_result_linkables_count;
  graphfile_size_t __pyx_v_new_result_linkables_count;
  PyObject *__pyx_v_data;
  PyObject *__pyx_v_linkables;
  PyObject *__pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  void *__pyx_5;
  static char *__pyx_argnames[] = {"linkable",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_linkable)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_linkable);
  __pyx_v_data = Py_None; Py_INCREF(Py_None);
  __pyx_v_linkables = Py_None; Py_INCREF(Py_None);
  if (!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_linkable), __pyx_ptype_9graphfile__Linkable, 1, "linkable")) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 74; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":83 */
  __pyx_v_result = graphfile_reader_read((&((struct __pyx_obj_9graphfile_Reader *)__pyx_v_self)->reader),(&__pyx_v_linkable->linkable),NULL,0,(&__pyx_v_result_buffer_length),NULL,0,(&__pyx_v_result_linkables_count));

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":92 */
  __pyx_1 = (__pyx_v_result != 0);
  if (__pyx_1) {
    __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_2) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 93; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 93; goto __pyx_L1;}
    Py_INCREF(__pyx_n_graphfile_reader_read);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_n_graphfile_reader_read);
    __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 93; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_4, 0, 0);
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    {__pyx_filename = __pyx_f[2]; __pyx_lineno = 93; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":95 */
  __pyx_5 = __pyx_f_9graphfile_allocate(__pyx_v_result_buffer_length); if (__pyx_5 == NULL) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 95; goto __pyx_L1;}
  __pyx_v_result_buffer = ((char *)__pyx_5);

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":96 */
  /*try:*/ {

    /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":97 */
    __pyx_5 = __pyx_f_9graphfile_allocate((__pyx_v_result_linkables_count * (sizeof(graphfile_linkable_t)))); if (__pyx_5 == NULL) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 97; goto __pyx_L4;}
    __pyx_v_result_linkables = ((graphfile_linkable_t *)__pyx_5);

    /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":98 */
    /*try:*/ {

      /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":99 */
      __pyx_v_result = graphfile_reader_read((&((struct __pyx_obj_9graphfile_Reader *)__pyx_v_self)->reader),(&__pyx_v_linkable->linkable),__pyx_v_result_buffer,__pyx_v_result_buffer_length,(&__pyx_v_new_result_buffer_length),__pyx_v_result_linkables,__pyx_v_result_linkables_count,(&__pyx_v_new_result_linkables_count));

      /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":108 */
      __pyx_1 = (__pyx_v_result != 0);
      if (__pyx_1) {
        __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_2) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 109; goto __pyx_L7;}
        __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 109; goto __pyx_L7;}
        Py_INCREF(__pyx_n_graphfile_reader_read);
        PyTuple_SET_ITEM(__pyx_3, 0, __pyx_n_graphfile_reader_read);
        __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 109; goto __pyx_L7;}
        Py_DECREF(__pyx_2); __pyx_2 = 0;
        Py_DECREF(__pyx_3); __pyx_3 = 0;
        __Pyx_Raise(__pyx_4, 0, 0);
        Py_DECREF(__pyx_4); __pyx_4 = 0;
        {__pyx_filename = __pyx_f[2]; __pyx_lineno = 109; goto __pyx_L7;}
        goto __pyx_L9;
      }
      __pyx_L9:;

      /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":110 */
      __pyx_1 = (__pyx_v_new_result_buffer_length != __pyx_v_result_buffer_length);
      if (!__pyx_1) {
        __pyx_1 = (__pyx_v_new_result_linkables_count != __pyx_v_result_linkables_count);
      }
      if (__pyx_1) {
        __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_2) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 112; goto __pyx_L7;}
        __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 112; goto __pyx_L7;}
        Py_INCREF(__pyx_k9p);
        PyTuple_SET_ITEM(__pyx_3, 0, __pyx_k9p);
        __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 112; goto __pyx_L7;}
        Py_DECREF(__pyx_2); __pyx_2 = 0;
        Py_DECREF(__pyx_3); __pyx_3 = 0;
        __Pyx_Raise(__pyx_4, 0, 0);
        Py_DECREF(__pyx_4); __pyx_4 = 0;
        {__pyx_filename = __pyx_f[2]; __pyx_lineno = 112; goto __pyx_L7;}
        goto __pyx_L10;
      }
      __pyx_L10:;

      /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":113 */
      __pyx_2 = PyString_FromStringAndSize(__pyx_v_result_buffer,__pyx_v_result_buffer_length); if (!__pyx_2) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 113; goto __pyx_L7;}
      Py_DECREF(__pyx_v_data);
      __pyx_v_data = __pyx_2;
      __pyx_2 = 0;

      /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":114 */
      __pyx_3 = PyList_New(0); if (!__pyx_3) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 114; goto __pyx_L7;}
      Py_DECREF(__pyx_v_linkables);
      __pyx_v_linkables = __pyx_3;
      __pyx_3 = 0;

      /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":115 */
      for (__pyx_v_i = 0; __pyx_v_i < __pyx_v_result_linkables_count; ++__pyx_v_i) {

        /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":117 */
        __pyx_4 = PyObject_CallObject(((PyObject *)__pyx_ptype_9graphfile__Linkable), 0); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 117; goto __pyx_L7;}
        Py_DECREF(((PyObject *)__pyx_v_linkable));
        __pyx_v_linkable = ((struct __pyx_obj_9graphfile__Linkable *)__pyx_4);
        __pyx_4 = 0;

        /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":118 */
        __pyx_v_linkable->linkable = (__pyx_v_result_linkables[__pyx_v_i]);

        /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":119 */
        __pyx_2 = PyObject_GetAttr(__pyx_v_linkables, __pyx_n_append); if (!__pyx_2) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 119; goto __pyx_L7;}
        __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 119; goto __pyx_L7;}
        Py_INCREF(((PyObject *)__pyx_v_linkable));
        PyTuple_SET_ITEM(__pyx_3, 0, ((PyObject *)__pyx_v_linkable));
        __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 119; goto __pyx_L7;}
        Py_DECREF(__pyx_2); __pyx_2 = 0;
        Py_DECREF(__pyx_3); __pyx_3 = 0;
        Py_DECREF(__pyx_4); __pyx_4 = 0;
      }

      /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":120 */
      __pyx_2 = PyTuple_New(2); if (!__pyx_2) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 120; goto __pyx_L7;}
      Py_INCREF(__pyx_v_data);
      PyTuple_SET_ITEM(__pyx_2, 0, __pyx_v_data);
      Py_INCREF(__pyx_v_linkables);
      PyTuple_SET_ITEM(__pyx_2, 1, __pyx_v_linkables);
      __pyx_r = __pyx_2;
      __pyx_2 = 0;
      goto __pyx_L6;
    }
    /*finally:*/ {
      int __pyx_why;
      PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
      int __pyx_exc_lineno;
      __pyx_why = 0; goto __pyx_L8;
      __pyx_L6: __pyx_why = 3; goto __pyx_L8;
      __pyx_L7: {
        __pyx_why = 4;
        Py_XDECREF(__pyx_3); __pyx_3 = 0;
        Py_XDECREF(__pyx_4); __pyx_4 = 0;
        Py_XDECREF(__pyx_2); __pyx_2 = 0;
        PyErr_Fetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
        __pyx_exc_lineno = __pyx_lineno;
        goto __pyx_L8;
      }
      __pyx_L8:;
      free(__pyx_v_result_linkables);
      switch (__pyx_why) {
        case 3: goto __pyx_L3;
        case 4: {
          PyErr_Restore(__pyx_exc_type, __pyx_exc_value, __pyx_exc_tb);
          __pyx_lineno = __pyx_exc_lineno;
          __pyx_exc_type = 0;
          __pyx_exc_value = 0;
          __pyx_exc_tb = 0;
          goto __pyx_L4;
        }
      }
    }
  }
  /*finally:*/ {
    int __pyx_why;
    PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
    int __pyx_exc_lineno;
    __pyx_why = 0; goto __pyx_L5;
    __pyx_L3: __pyx_why = 3; goto __pyx_L5;
    __pyx_L4: {
      __pyx_why = 4;
      Py_XDECREF(__pyx_3); __pyx_3 = 0;
      Py_XDECREF(__pyx_4); __pyx_4 = 0;
      Py_XDECREF(__pyx_2); __pyx_2 = 0;
      PyErr_Fetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
      __pyx_exc_lineno = __pyx_lineno;
      goto __pyx_L5;
    }
    __pyx_L5:;
    free(__pyx_v_result_buffer);
    switch (__pyx_why) {
      case 3: goto __pyx_L0;
      case 4: {
        PyErr_Restore(__pyx_exc_type, __pyx_exc_value, __pyx_exc_tb);
        __pyx_lineno = __pyx_exc_lineno;
        __pyx_exc_type = 0;
        __pyx_exc_value = 0;
        __pyx_exc_tb = 0;
        goto __pyx_L1;
      }
    }
  }

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("graphfile.Reader.read");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_data);
  Py_DECREF(__pyx_v_linkables);
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_linkable);
  return __pyx_r;
}

static __Pyx_InternTabEntry __pyx_intern_tab[] = {
  {&__pyx_n_Error, "Error"},
  {&__pyx_n_append, "append"},
  {&__pyx_n_graphfile_reader_init, "graphfile_reader_init"},
  {&__pyx_n_graphfile_reader_read, "graphfile_reader_read"},
  {&__pyx_n_graphfile_writer_init, "graphfile_writer_init"},
  {&__pyx_n_graphfile_writer_set_root, "graphfile_writer_set_root"},
  {&__pyx_n_graphfile_writer_write, "graphfile_writer_write"},
  {0, 0}
};

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_k2p, __pyx_k2, sizeof(__pyx_k2)},
  {&__pyx_k9p, __pyx_k9, sizeof(__pyx_k9)},
  {0, 0, 0}
};

static PyObject *__pyx_tp_new_9graphfile__Linkable(PyTypeObject *t, PyObject *a, PyObject *k) {
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  return o;
}

static void __pyx_tp_dealloc_9graphfile__Linkable(PyObject *o) {
  (*o->ob_type->tp_free)(o);
}

static struct PyMethodDef __pyx_methods_9graphfile__Linkable[] = {
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number__Linkable = {
  0, /*nb_add*/
  0, /*nb_subtract*/
  0, /*nb_multiply*/
  0, /*nb_divide*/
  0, /*nb_remainder*/
  0, /*nb_divmod*/
  0, /*nb_power*/
  0, /*nb_negative*/
  0, /*nb_positive*/
  0, /*nb_absolute*/
  0, /*nb_nonzero*/
  0, /*nb_invert*/
  0, /*nb_lshift*/
  0, /*nb_rshift*/
  0, /*nb_and*/
  0, /*nb_xor*/
  0, /*nb_or*/
  0, /*nb_coerce*/
  0, /*nb_int*/
  0, /*nb_long*/
  0, /*nb_float*/
  0, /*nb_oct*/
  0, /*nb_hex*/
  0, /*nb_inplace_add*/
  0, /*nb_inplace_subtract*/
  0, /*nb_inplace_multiply*/
  0, /*nb_inplace_divide*/
  0, /*nb_inplace_remainder*/
  0, /*nb_inplace_power*/
  0, /*nb_inplace_lshift*/
  0, /*nb_inplace_rshift*/
  0, /*nb_inplace_and*/
  0, /*nb_inplace_xor*/
  0, /*nb_inplace_or*/
  0, /*nb_floor_divide*/
  0, /*nb_true_divide*/
  0, /*nb_inplace_floor_divide*/
  0, /*nb_inplace_true_divide*/
  #if Py_TPFLAGS_DEFAULT & Py_TPFLAGS_HAVE_INDEX
  0, /*nb_index*/
  #endif
};

static PySequenceMethods __pyx_tp_as_sequence__Linkable = {
  0, /*sq_length*/
  0, /*sq_concat*/
  0, /*sq_repeat*/
  0, /*sq_item*/
  0, /*sq_slice*/
  0, /*sq_ass_item*/
  0, /*sq_ass_slice*/
  0, /*sq_contains*/
  0, /*sq_inplace_concat*/
  0, /*sq_inplace_repeat*/
};

static PyMappingMethods __pyx_tp_as_mapping__Linkable = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer__Linkable = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_9graphfile__Linkable = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "graphfile._Linkable", /*tp_name*/
  sizeof(struct __pyx_obj_9graphfile__Linkable), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_9graphfile__Linkable, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number__Linkable, /*tp_as_number*/
  &__pyx_tp_as_sequence__Linkable, /*tp_as_sequence*/
  &__pyx_tp_as_mapping__Linkable, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer__Linkable, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE, /*tp_flags*/
  0, /*tp_doc*/
  0, /*tp_traverse*/
  0, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_9graphfile__Linkable, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  0, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_9graphfile__Linkable, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};

static PyObject *__pyx_tp_new_9graphfile_Writer(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_9graphfile_Writer *p;
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  p = ((struct __pyx_obj_9graphfile_Writer *)o);
  p->fileobj = Py_None; Py_INCREF(Py_None);
  if (__pyx_f_9graphfile_6Writer___cinit__(o, a, k) < 0) {
    Py_DECREF(o); o = 0;
  }
  return o;
}

static void __pyx_tp_dealloc_9graphfile_Writer(PyObject *o) {
  struct __pyx_obj_9graphfile_Writer *p = (struct __pyx_obj_9graphfile_Writer *)o;
  {
    PyObject *etype, *eval, *etb;
    PyErr_Fetch(&etype, &eval, &etb);
    ++o->ob_refcnt;
    __pyx_f_9graphfile_6Writer___dealloc__(o);
    if (PyErr_Occurred()) PyErr_WriteUnraisable(o);
    --o->ob_refcnt;
    PyErr_Restore(etype, eval, etb);
  }
  Py_XDECREF(p->fileobj);
  (*o->ob_type->tp_free)(o);
}

static int __pyx_tp_traverse_9graphfile_Writer(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_9graphfile_Writer *p = (struct __pyx_obj_9graphfile_Writer *)o;
  if (p->fileobj) {
    e = (*v)(p->fileobj, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_9graphfile_Writer(PyObject *o) {
  struct __pyx_obj_9graphfile_Writer *p = (struct __pyx_obj_9graphfile_Writer *)o;
  PyObject *t;
  t = p->fileobj; 
  p->fileobj = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  return 0;
}

static struct PyMethodDef __pyx_methods_9graphfile_Writer[] = {
  {"set_root", (PyCFunction)__pyx_f_9graphfile_6Writer_set_root, METH_VARARGS|METH_KEYWORDS, 0},
  {"write", (PyCFunction)__pyx_f_9graphfile_6Writer_write, METH_VARARGS|METH_KEYWORDS, 0},
  {0, 0, 0, 0}
};

static struct PyMemberDef __pyx_members_9graphfile_Writer[] = {
  {"fileobj", T_OBJECT, offsetof(struct __pyx_obj_9graphfile_Writer, fileobj), READONLY, 0},
  {0, 0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_Writer = {
  0, /*nb_add*/
  0, /*nb_subtract*/
  0, /*nb_multiply*/
  0, /*nb_divide*/
  0, /*nb_remainder*/
  0, /*nb_divmod*/
  0, /*nb_power*/
  0, /*nb_negative*/
  0, /*nb_positive*/
  0, /*nb_absolute*/
  0, /*nb_nonzero*/
  0, /*nb_invert*/
  0, /*nb_lshift*/
  0, /*nb_rshift*/
  0, /*nb_and*/
  0, /*nb_xor*/
  0, /*nb_or*/
  0, /*nb_coerce*/
  0, /*nb_int*/
  0, /*nb_long*/
  0, /*nb_float*/
  0, /*nb_oct*/
  0, /*nb_hex*/
  0, /*nb_inplace_add*/
  0, /*nb_inplace_subtract*/
  0, /*nb_inplace_multiply*/
  0, /*nb_inplace_divide*/
  0, /*nb_inplace_remainder*/
  0, /*nb_inplace_power*/
  0, /*nb_inplace_lshift*/
  0, /*nb_inplace_rshift*/
  0, /*nb_inplace_and*/
  0, /*nb_inplace_xor*/
  0, /*nb_inplace_or*/
  0, /*nb_floor_divide*/
  0, /*nb_true_divide*/
  0, /*nb_inplace_floor_divide*/
  0, /*nb_inplace_true_divide*/
  #if Py_TPFLAGS_DEFAULT & Py_TPFLAGS_HAVE_INDEX
  0, /*nb_index*/
  #endif
};

static PySequenceMethods __pyx_tp_as_sequence_Writer = {
  0, /*sq_length*/
  0, /*sq_concat*/
  0, /*sq_repeat*/
  0, /*sq_item*/
  0, /*sq_slice*/
  0, /*sq_ass_item*/
  0, /*sq_ass_slice*/
  0, /*sq_contains*/
  0, /*sq_inplace_concat*/
  0, /*sq_inplace_repeat*/
};

static PyMappingMethods __pyx_tp_as_mapping_Writer = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_Writer = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_9graphfile_Writer = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "graphfile.Writer", /*tp_name*/
  sizeof(struct __pyx_obj_9graphfile_Writer), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_9graphfile_Writer, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_Writer, /*tp_as_number*/
  &__pyx_tp_as_sequence_Writer, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_Writer, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_Writer, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  0, /*tp_doc*/
  __pyx_tp_traverse_9graphfile_Writer, /*tp_traverse*/
  __pyx_tp_clear_9graphfile_Writer, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_9graphfile_Writer, /*tp_methods*/
  __pyx_members_9graphfile_Writer, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  0, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_9graphfile_Writer, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};

static PyObject *__pyx_tp_new_9graphfile_Reader(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_9graphfile_Reader *p;
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  p = ((struct __pyx_obj_9graphfile_Reader *)o);
  p->root = ((struct __pyx_obj_9graphfile__Linkable *)Py_None); Py_INCREF(Py_None);
  p->fileobj = Py_None; Py_INCREF(Py_None);
  if (__pyx_f_9graphfile_6Reader___cinit__(o, a, k) < 0) {
    Py_DECREF(o); o = 0;
  }
  return o;
}

static void __pyx_tp_dealloc_9graphfile_Reader(PyObject *o) {
  struct __pyx_obj_9graphfile_Reader *p = (struct __pyx_obj_9graphfile_Reader *)o;
  {
    PyObject *etype, *eval, *etb;
    PyErr_Fetch(&etype, &eval, &etb);
    ++o->ob_refcnt;
    __pyx_f_9graphfile_6Reader___dealloc__(o);
    if (PyErr_Occurred()) PyErr_WriteUnraisable(o);
    --o->ob_refcnt;
    PyErr_Restore(etype, eval, etb);
  }
  Py_XDECREF(((PyObject *)p->root));
  Py_XDECREF(p->fileobj);
  (*o->ob_type->tp_free)(o);
}

static int __pyx_tp_traverse_9graphfile_Reader(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_9graphfile_Reader *p = (struct __pyx_obj_9graphfile_Reader *)o;
  if (p->root) {
    e = (*v)(((PyObject*)p->root), a); if (e) return e;
  }
  if (p->fileobj) {
    e = (*v)(p->fileobj, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_9graphfile_Reader(PyObject *o) {
  struct __pyx_obj_9graphfile_Reader *p = (struct __pyx_obj_9graphfile_Reader *)o;
  PyObject *t;
  t = ((PyObject *)p->root); 
  p->root = ((struct __pyx_obj_9graphfile__Linkable *)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->fileobj; 
  p->fileobj = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  return 0;
}

static struct PyMethodDef __pyx_methods_9graphfile_Reader[] = {
  {"read", (PyCFunction)__pyx_f_9graphfile_6Reader_read, METH_VARARGS|METH_KEYWORDS, 0},
  {0, 0, 0, 0}
};

static struct PyMemberDef __pyx_members_9graphfile_Reader[] = {
  {"root", T_OBJECT, offsetof(struct __pyx_obj_9graphfile_Reader, root), READONLY, 0},
  {"fileobj", T_OBJECT, offsetof(struct __pyx_obj_9graphfile_Reader, fileobj), READONLY, 0},
  {0, 0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_Reader = {
  0, /*nb_add*/
  0, /*nb_subtract*/
  0, /*nb_multiply*/
  0, /*nb_divide*/
  0, /*nb_remainder*/
  0, /*nb_divmod*/
  0, /*nb_power*/
  0, /*nb_negative*/
  0, /*nb_positive*/
  0, /*nb_absolute*/
  0, /*nb_nonzero*/
  0, /*nb_invert*/
  0, /*nb_lshift*/
  0, /*nb_rshift*/
  0, /*nb_and*/
  0, /*nb_xor*/
  0, /*nb_or*/
  0, /*nb_coerce*/
  0, /*nb_int*/
  0, /*nb_long*/
  0, /*nb_float*/
  0, /*nb_oct*/
  0, /*nb_hex*/
  0, /*nb_inplace_add*/
  0, /*nb_inplace_subtract*/
  0, /*nb_inplace_multiply*/
  0, /*nb_inplace_divide*/
  0, /*nb_inplace_remainder*/
  0, /*nb_inplace_power*/
  0, /*nb_inplace_lshift*/
  0, /*nb_inplace_rshift*/
  0, /*nb_inplace_and*/
  0, /*nb_inplace_xor*/
  0, /*nb_inplace_or*/
  0, /*nb_floor_divide*/
  0, /*nb_true_divide*/
  0, /*nb_inplace_floor_divide*/
  0, /*nb_inplace_true_divide*/
  #if Py_TPFLAGS_DEFAULT & Py_TPFLAGS_HAVE_INDEX
  0, /*nb_index*/
  #endif
};

static PySequenceMethods __pyx_tp_as_sequence_Reader = {
  0, /*sq_length*/
  0, /*sq_concat*/
  0, /*sq_repeat*/
  0, /*sq_item*/
  0, /*sq_slice*/
  0, /*sq_ass_item*/
  0, /*sq_ass_slice*/
  0, /*sq_contains*/
  0, /*sq_inplace_concat*/
  0, /*sq_inplace_repeat*/
};

static PyMappingMethods __pyx_tp_as_mapping_Reader = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_Reader = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_9graphfile_Reader = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "graphfile.Reader", /*tp_name*/
  sizeof(struct __pyx_obj_9graphfile_Reader), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_9graphfile_Reader, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_Reader, /*tp_as_number*/
  &__pyx_tp_as_sequence_Reader, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_Reader, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_Reader, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  0, /*tp_doc*/
  __pyx_tp_traverse_9graphfile_Reader, /*tp_traverse*/
  __pyx_tp_clear_9graphfile_Reader, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_9graphfile_Reader, /*tp_methods*/
  __pyx_members_9graphfile_Reader, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  0, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_9graphfile_Reader, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};

static struct PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

static void __pyx_init_filenames(void); /*proto*/

PyMODINIT_FUNC initgraphfile(void); /*proto*/
PyMODINIT_FUNC initgraphfile(void) {
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  __pyx_init_filenames();
  __pyx_m = Py_InitModule4("graphfile", __pyx_methods, 0, 0, PYTHON_API_VERSION);
  if (!__pyx_m) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 17; goto __pyx_L1;};
  Py_INCREF(__pyx_m);
  __pyx_b = PyImport_AddModule("__builtin__");
  if (!__pyx_b) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 17; goto __pyx_L1;};
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 17; goto __pyx_L1;};
  if (__Pyx_InternStrings(__pyx_intern_tab) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 17; goto __pyx_L1;};
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 17; goto __pyx_L1;};
  if (PyType_Ready(&__pyx_type_9graphfile__Linkable) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 22; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "_Linkable", (PyObject *)&__pyx_type_9graphfile__Linkable) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 22; goto __pyx_L1;}
  __pyx_ptype_9graphfile__Linkable = &__pyx_type_9graphfile__Linkable;
  __pyx_type_9graphfile_Writer.tp_free = _PyObject_GC_Del;
  if (PyType_Ready(&__pyx_type_9graphfile_Writer) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 25; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "Writer", (PyObject *)&__pyx_type_9graphfile_Writer) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 25; goto __pyx_L1;}
  __pyx_ptype_9graphfile_Writer = &__pyx_type_9graphfile_Writer;
  __pyx_type_9graphfile_Reader.tp_free = _PyObject_GC_Del;
  if (PyType_Ready(&__pyx_type_9graphfile_Reader) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 63; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "Reader", (PyObject *)&__pyx_type_9graphfile_Reader) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 63; goto __pyx_L1;}
  __pyx_ptype_9graphfile_Reader = &__pyx_type_9graphfile_Reader;

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":20 */
  __pyx_1 = PyDict_New(); if (!__pyx_1) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 20; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(1); if (!__pyx_2) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 20; goto __pyx_L1;}
  Py_INCREF(PyExc_Exception);
  PyTuple_SET_ITEM(__pyx_2, 0, PyExc_Exception);
  __pyx_3 = __Pyx_CreateClass(__pyx_2, __pyx_1, __pyx_n_Error, "graphfile"); if (!__pyx_3) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 20; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  if (PyObject_SetAttr(__pyx_m, __pyx_n_Error, __pyx_3) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 20; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/a/home/eyal/devel/pythontracer/graphfile-python/graphfile.pyx":74 */
  return;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("graphfile");
}

static char *__pyx_filenames[] = {
  "memory.pyx",
  "python.pyx",
  "graphfile.pyx",
};

/* Runtime support code */

static void __pyx_init_filenames(void) {
  __pyx_f = __pyx_filenames;
}

static int __Pyx_ArgTypeTest(PyObject *obj, PyTypeObject *type, int none_allowed, char *name) {
    if (!type) {
        PyErr_Format(PyExc_SystemError, "Missing type object");
        return 0;
    }
    if ((none_allowed && obj == Py_None) || PyObject_TypeCheck(obj, type))
        return 1;
    PyErr_Format(PyExc_TypeError,
        "Argument '%s' has incorrect type (expected %s, got %s)",
        name, type->tp_name, obj->ob_type->tp_name);
    return 0;
}

static PyObject *__Pyx_CreateClass(
    PyObject *bases, PyObject *dict, PyObject *name, char *modname)
{
    PyObject *py_modname;
    PyObject *result = 0;
    
    py_modname = PyString_FromString(modname);
    if (!py_modname)
        goto bad;
    if (PyDict_SetItemString(dict, "__module__", py_modname) < 0)
        goto bad;
    result = PyClass_New(bases, dict, name);
bad:
    Py_XDECREF(py_modname);
    return result;
}

static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb) {
    Py_XINCREF(type);
    Py_XINCREF(value);
    Py_XINCREF(tb);
    /* First, check the traceback argument, replacing None with NULL. */
    if (tb == Py_None) {
        Py_DECREF(tb);
        tb = 0;
    }
    else if (tb != NULL && !PyTraceBack_Check(tb)) {
        PyErr_SetString(PyExc_TypeError,
            "raise: arg 3 must be a traceback or None");
        goto raise_error;
    }
    /* Next, replace a missing value with None */
    if (value == NULL) {
        value = Py_None;
        Py_INCREF(value);
    }
    #if PY_VERSION_HEX < 0x02050000
    if (!PyClass_Check(type))
    #else
    if (!PyType_Check(type))
    #endif
    {
        /* Raising an instance.  The value should be a dummy. */
        if (value != Py_None) {
            PyErr_SetString(PyExc_TypeError,
                "instance exception may not have a separate value");
            goto raise_error;
        }
        /* Normalize to raise <class>, <instance> */
        Py_DECREF(value);
        value = type;
        #if PY_VERSION_HEX < 0x02050000
            if (PyInstance_Check(type)) {
                type = (PyObject*) ((PyInstanceObject*)type)->in_class;
                Py_INCREF(type);
            }
            else {
                PyErr_SetString(PyExc_TypeError,
                    "raise: exception must be an old-style class or instance");
                goto raise_error;
            }
        #else
            type = (PyObject*) type->ob_type;
            Py_INCREF(type);
            if (!PyType_IsSubtype((PyTypeObject *)type, (PyTypeObject *)PyExc_BaseException)) {
                PyErr_SetString(PyExc_TypeError,
                    "raise: exception class must be a subclass of BaseException");
                goto raise_error;
            }
        #endif
    }
    PyErr_Restore(type, value, tb);
    return;
raise_error:
    Py_XDECREF(value);
    Py_XDECREF(type);
    Py_XDECREF(tb);
    return;
}

static PyObject *__Pyx_GetName(PyObject *dict, PyObject *name) {
    PyObject *result;
    result = PyObject_GetAttr(dict, name);
    if (!result)
        PyErr_SetObject(PyExc_NameError, name);
    return result;
}

static void __Pyx_UnpackError(void) {
    PyErr_SetString(PyExc_ValueError, "unpack sequence of wrong size");
}

static PyObject *__Pyx_UnpackItem(PyObject *iter) {
    PyObject *item;
    if (!(item = PyIter_Next(iter))) {
        if (!PyErr_Occurred())
            __Pyx_UnpackError();
    }
    return item;
}

static int __Pyx_EndUnpack(PyObject *iter) {
    PyObject *item;
    if ((item = PyIter_Next(iter))) {
        Py_DECREF(item);
        __Pyx_UnpackError();
        return -1;
    }
    else if (!PyErr_Occurred())
        return 0;
    else
        return -1;
}

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t) {
    while (t->p) {
        *t->p = PyString_InternFromString(t->s);
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

#include "compile.h"
#include "frameobject.h"
#include "traceback.h"

static void __Pyx_AddTraceback(char *funcname) {
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    PyObject *py_globals = 0;
    PyObject *empty_tuple = 0;
    PyObject *empty_string = 0;
    PyCodeObject *py_code = 0;
    PyFrameObject *py_frame = 0;
    
    py_srcfile = PyString_FromString(__pyx_filename);
    if (!py_srcfile) goto bad;
    py_funcname = PyString_FromString(funcname);
    if (!py_funcname) goto bad;
    py_globals = PyModule_GetDict(__pyx_m);
    if (!py_globals) goto bad;
    empty_tuple = PyTuple_New(0);
    if (!empty_tuple) goto bad;
    empty_string = PyString_FromString("");
    if (!empty_string) goto bad;
    py_code = PyCode_New(
        0,            /*int argcount,*/
        0,            /*int nlocals,*/
        0,            /*int stacksize,*/
        0,            /*int flags,*/
        empty_string, /*PyObject *code,*/
        empty_tuple,  /*PyObject *consts,*/
        empty_tuple,  /*PyObject *names,*/
        empty_tuple,  /*PyObject *varnames,*/
        empty_tuple,  /*PyObject *freevars,*/
        empty_tuple,  /*PyObject *cellvars,*/
        py_srcfile,   /*PyObject *filename,*/
        py_funcname,  /*PyObject *name,*/
        __pyx_lineno,   /*int firstlineno,*/
        empty_string  /*PyObject *lnotab*/
    );
    if (!py_code) goto bad;
    py_frame = PyFrame_New(
        PyThreadState_Get(), /*PyThreadState *tstate,*/
        py_code,             /*PyCodeObject *code,*/
        py_globals,          /*PyObject *globals,*/
        0                    /*PyObject *locals*/
    );
    if (!py_frame) goto bad;
    py_frame->f_lineno = __pyx_lineno;
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    Py_XDECREF(empty_tuple);
    Py_XDECREF(empty_string);
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}
