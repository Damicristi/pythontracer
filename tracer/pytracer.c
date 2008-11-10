/* 0.9.7 on Mon Nov 10 17:17:12 2008 */

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
#include "sys/time.h"
#include "time.h"
#include "sys/resource.h"
#include "sys/param.h"
#include "stdlib.h"
#include "string.h"
#include "graphfile.h"
#include "errno.h"
#include "sys/types.h"
#include "stdio.h"
#include "unistd.h"
#include "rotatingtree.h"


typedef struct {PyObject **p; char *s;} __Pyx_InternTabEntry; /*proto*/
typedef struct {PyObject **p; char *s; long n;} __Pyx_StringTabEntry; /*proto*/

static PyObject *__pyx_m;
static PyObject *__pyx_b;
static int __pyx_lineno;
static char *__pyx_filename;
static char **__pyx_f;

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list); /*proto*/

static PyObject *__Pyx_CreateClass(PyObject *bases, PyObject *dict, PyObject *name, char *modname); /*proto*/

static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb); /*proto*/

static PyObject *__Pyx_GetName(PyObject *dict, PyObject *name); /*proto*/

static void __Pyx_WriteUnraisable(char *name); /*proto*/

static PyObject *__Pyx_UnpackItem(PyObject *); /*proto*/
static int __Pyx_EndUnpack(PyObject *); /*proto*/

static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb); /*proto*/

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t); /*proto*/

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t); /*proto*/

static int __Pyx_SetVtable(PyObject *dict, void *vtable); /*proto*/

static void __Pyx_AddTraceback(char *funcname); /*proto*/

/* Declarations from posix */


/* Declarations from rotatingtree */


/* Declarations from pytracer */

typedef struct {
  void *array;
  size_t item_size;
  unsigned int used_count;
  unsigned int allocated_count;
} __pyx_t_8pytracer_darray;

typedef short __pyx_t_8pytracer_CodeIndex;

typedef struct {
  rotating_node_t header;
  __pyx_t_8pytracer_CodeIndex code_index;
} __pyx_t_8pytracer_CodeIndexEntry;

typedef struct {
  __pyx_t_8pytracer_CodeIndex index;
  int lineno;
  double user_time;
  double sys_time;
  double real_time;
} __pyx_t_8pytracer_InvocationData;

typedef struct {
  __pyx_t_8pytracer_InvocationData data;
  __pyx_t_8pytracer_darray children;
} __pyx_t_8pytracer_CallInvocation;

struct __pyx_obj_8pytracer__Linkable {
  PyObject_HEAD
  graphfile_linkable_t linkable;
};

struct __pyx_obj_8pytracer_Tracer {
  PyObject_HEAD
  struct __pyx_vtabstruct_8pytracer_Tracer *__pyx_vtab;
  PyObject *fileobj;
  PyObject *index_fileobj;
  rotating_node_t *written_indexes;
  FILE *index_file;
  graphfile_writer_t writer;
  __pyx_t_8pytracer_darray stack;
  pid_t tracer_pid;
  __pyx_t_8pytracer_CodeIndex next_code_index;
  PyObject *_prev_os_exit;
};



struct __pyx_vtabstruct_8pytracer_Tracer {
  int (*call_invocation_init)(struct __pyx_obj_8pytracer_Tracer *,__pyx_t_8pytracer_CallInvocation *,PyObject *,int,double,double,double);
  int (*_trace_event)(struct __pyx_obj_8pytracer_Tracer *,PyObject *,int,void *);
  int (*_push_call)(struct __pyx_obj_8pytracer_Tracer *,PyObject *,int,double,double,double);
  int (*_pop_call)(struct __pyx_obj_8pytracer_Tracer *,double,double,double);
  int (*_index_of_code)(struct __pyx_obj_8pytracer_Tracer *,PyObject *);
  int (*_write)(struct __pyx_obj_8pytracer_Tracer *,char *,unsigned int,__pyx_t_8pytracer_darray *,graphfile_linkable_t *);
  PyObject *(*_push_root)(struct __pyx_obj_8pytracer_Tracer *);
  PyObject *(*_pop_root)(struct __pyx_obj_8pytracer_Tracer *);
  PyObject *(*_pop_to_root)(struct __pyx_obj_8pytracer_Tracer *);
};
static struct __pyx_vtabstruct_8pytracer_Tracer *__pyx_vtabptr_8pytracer_Tracer;

static PyTypeObject *__pyx_ptype_8pytracer__Linkable = 0;
static PyTypeObject *__pyx_ptype_8pytracer_Tracer = 0;
static double __pyx_f_8pytracer_double_of_tv(struct timeval *); /*proto*/
static int __pyx_f_8pytracer_get_user_sys_times(double *,double *); /*proto*/
static int __pyx_f_8pytracer_get_real_time(double *); /*proto*/
static void *__pyx_f_8pytracer_allocate(size_t); /*proto*/
static int __pyx_f_8pytracer_reallocate(void **,size_t); /*proto*/
static FILE *__pyx_f_8pytracer_file_from_obj(PyObject *); /*proto*/
static int __pyx_f_8pytracer_darray_init(__pyx_t_8pytracer_darray *,size_t); /*proto*/
static void *__pyx_f_8pytracer_darray_add(__pyx_t_8pytracer_darray *); /*proto*/
static void *__pyx_f_8pytracer_darray_last(__pyx_t_8pytracer_darray *); /*proto*/
static void __pyx_f_8pytracer_darray_fini(__pyx_t_8pytracer_darray *); /*proto*/
static int __pyx_f_8pytracer_darray_fast_remove_last(__pyx_t_8pytracer_darray *); /*proto*/
static int __pyx_f_8pytracer_safe_fflush(FILE *); /*proto*/
static size_t __pyx_f_8pytracer_safe_fread(void *,size_t,FILE *); /*proto*/
static size_t __pyx_f_8pytracer_safe_fwrite(void *,size_t,FILE *); /*proto*/
static void __pyx_f_8pytracer_call_invocation_empty(__pyx_t_8pytracer_CallInvocation *); /*proto*/
static PyObject *__pyx_f_8pytracer_fwrite_string(PyObject *,FILE *); /*proto*/
static int __pyx_f_8pytracer_freeEntry(rotating_node_t *,void *); /*proto*/
static int __pyx_f_8pytracer_callback(struct __pyx_obj_8pytracer_Tracer *,PyObject *,int,void *); /*proto*/


/* Implementation of pytracer */


static PyObject *__pyx_n_os;
static PyObject *__pyx_n_sys;
static PyObject *__pyx_n_Error;

static double __pyx_f_8pytracer_double_of_tv(struct timeval *__pyx_v_tv) {
  double __pyx_r;
  __pyx_r = ((((double)1000000) * __pyx_v_tv->tv_sec) + ((double)__pyx_v_tv->tv_usec));
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}

static PyObject *__pyx_n_getrusage;


static int __pyx_f_8pytracer_get_user_sys_times(double *__pyx_v_user_time,double *__pyx_v_sys_time) {
  int __pyx_v_getrusage_return;
  struct rusage __pyx_v_getrusage_result;
  PyObject *__pyx_v_errno;
  int __pyx_r;
  PyObject *__pyx_1 = 0;
  int __pyx_2;
  PyObject *__pyx_3 = 0;
  __pyx_v_errno = Py_None; Py_INCREF(Py_None);

  /* "pyrex-lib/times.pyx":50 */
  __pyx_1 = PyInt_FromLong(0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 50; goto __pyx_L1;}
  Py_DECREF(__pyx_v_errno);
  __pyx_v_errno = __pyx_1;
  __pyx_1 = 0;

  /* "pyrex-lib/times.pyx":51 */
  __pyx_v_getrusage_return = getrusage(RUSAGE_SELF,(&__pyx_v_getrusage_result));

  /* "pyrex-lib/times.pyx":52 */
  __pyx_2 = (__pyx_v_getrusage_return == (-1));
  if (__pyx_2) {
    __pyx_1 = PyTuple_New(2); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    Py_INCREF(__pyx_v_errno);
    PyTuple_SET_ITEM(__pyx_1, 0, __pyx_v_errno);
    Py_INCREF(__pyx_n_getrusage);
    PyTuple_SET_ITEM(__pyx_1, 1, __pyx_n_getrusage);
    __pyx_3 = PyObject_CallObject(PyExc_OSError, __pyx_1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    Py_DECREF(__pyx_1); __pyx_1 = 0;
    __Pyx_Raise(__pyx_3, 0, 0);
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "pyrex-lib/times.pyx":54 */
  (__pyx_v_user_time[0]) = __pyx_f_8pytracer_double_of_tv((&__pyx_v_getrusage_result.ru_utime));

  /* "pyrex-lib/times.pyx":55 */
  (__pyx_v_sys_time[0]) = __pyx_f_8pytracer_double_of_tv((&__pyx_v_getrusage_result.ru_stime));

  /* "pyrex-lib/times.pyx":56 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("pytracer.get_user_sys_times");
  __pyx_r = (-1);
  __pyx_L0:;
  Py_DECREF(__pyx_v_errno);
  return __pyx_r;
}

static PyObject *__pyx_n_gettimeofday;


static int __pyx_f_8pytracer_get_real_time(double *__pyx_v_real_time) {
  struct timeval __pyx_v_tv;
  int __pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;

  /* "pyrex-lib/times.pyx":62 */
  __pyx_1 = (0 != gettimeofday((&__pyx_v_tv),NULL));
  if (__pyx_1) {
    __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 63; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 63; goto __pyx_L1;}
    Py_INCREF(__pyx_n_gettimeofday);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_n_gettimeofday);
    __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 63; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_4, 0, 0);
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 63; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "pyrex-lib/times.pyx":64 */
  (__pyx_v_real_time[0]) = __pyx_f_8pytracer_double_of_tv((&__pyx_v_tv));

  /* "pyrex-lib/times.pyx":65 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("pytracer.get_real_time");
  __pyx_r = (-1);
  __pyx_L0:;
  return __pyx_r;
}

static void *__pyx_f_8pytracer_allocate(size_t __pyx_v_size) {
  void *__pyx_v_ptr;
  void *__pyx_r;
  int __pyx_1;

  /* "pyrex-lib/memory.pyx":32 */
  __pyx_v_ptr = malloc(__pyx_v_size);

  /* "pyrex-lib/memory.pyx":33 */
  __pyx_1 = (__pyx_v_ptr == NULL);
  if (__pyx_1) {
    __Pyx_Raise(PyExc_MemoryError, 0, 0);
    {__pyx_filename = __pyx_f[1]; __pyx_lineno = 34; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "pyrex-lib/memory.pyx":35 */
  __pyx_r = __pyx_v_ptr;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("pytracer.allocate");
  __pyx_r = NULL;
  __pyx_L0:;
  return __pyx_r;
}

static int __pyx_f_8pytracer_reallocate(void **__pyx_v_ptr,size_t __pyx_v_size) {
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
    {__pyx_filename = __pyx_f[1]; __pyx_lineno = 45; goto __pyx_L1;}
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
  __Pyx_AddTraceback("pytracer.reallocate");
  __pyx_r = (-1);
  __pyx_L0:;
  return __pyx_r;
}

static PyObject *__pyx_k6p;

static char __pyx_k6[] = "Invalid fileobj";

static FILE *__pyx_f_8pytracer_file_from_obj(PyObject *__pyx_v_fileobj) {
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
    __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_2) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 42; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 42; goto __pyx_L1;}
    Py_INCREF(__pyx_k6p);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_k6p);
    __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 42; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_4, 0, 0);
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    {__pyx_filename = __pyx_f[2]; __pyx_lineno = 42; goto __pyx_L1;}
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
  __Pyx_AddTraceback("pytracer.file_from_obj");
  __pyx_r = NULL;
  __pyx_L0:;
  Py_DECREF(__pyx_v_fileobj);
  return __pyx_r;
}

static int __pyx_f_8pytracer_darray_init(__pyx_t_8pytracer_darray *__pyx_v_darray,size_t __pyx_v_item_size) {
  int __pyx_r;
  int __pyx_1;

  /* "pyrex-lib/darray.pyx":26 */
  __pyx_v_darray->array = NULL;

  /* "pyrex-lib/darray.pyx":27 */
  __pyx_v_darray->item_size = __pyx_v_item_size;

  /* "pyrex-lib/darray.pyx":28 */
  __pyx_v_darray->used_count = 0;

  /* "pyrex-lib/darray.pyx":29 */
  __pyx_v_darray->allocated_count = 8;

  /* "pyrex-lib/darray.pyx":30 */
  __pyx_1 = __pyx_f_8pytracer_reallocate((&__pyx_v_darray->array),(__pyx_v_darray->allocated_count * __pyx_v_darray->item_size)); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 30; goto __pyx_L1;}

  /* "pyrex-lib/darray.pyx":32 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("pytracer.darray_init");
  __pyx_r = (-1);
  __pyx_L0:;
  return __pyx_r;
}

static PyObject *__pyx_n_max;

static void *__pyx_f_8pytracer_darray_add(__pyx_t_8pytracer_darray *__pyx_v_darray) {
  void *__pyx_v_result;
  unsigned int __pyx_v_new_used_count;
  unsigned int __pyx_v_new_allocated_count;
  void *__pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  unsigned int __pyx_6;

  /* "pyrex-lib/darray.pyx":38 */
  __pyx_v_new_used_count = (__pyx_v_darray->used_count + 1);

  /* "pyrex-lib/darray.pyx":39 */
  __pyx_1 = (__pyx_v_new_used_count > __pyx_v_darray->allocated_count);
  if (__pyx_1) {

    /* "pyrex-lib/darray.pyx":40 */
    __pyx_2 = __Pyx_GetName(__pyx_b, __pyx_n_max); if (!__pyx_2) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 40; goto __pyx_L1;}
    __pyx_3 = PyInt_FromLong(1); if (!__pyx_3) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 40; goto __pyx_L1;}
    __pyx_4 = PyLong_FromUnsignedLong(__pyx_v_darray->allocated_count); if (!__pyx_4) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 40; goto __pyx_L1;}
    __pyx_5 = PyTuple_New(2); if (!__pyx_5) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 40; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_5, 0, __pyx_3);
    PyTuple_SET_ITEM(__pyx_5, 1, __pyx_4);
    __pyx_3 = 0;
    __pyx_4 = 0;
    __pyx_3 = PyObject_CallObject(__pyx_2, __pyx_5); if (!__pyx_3) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 40; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    __pyx_4 = PyInt_FromLong(2); if (!__pyx_4) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 40; goto __pyx_L1;}
    __pyx_2 = PyNumber_Multiply(__pyx_3, __pyx_4); if (!__pyx_2) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 40; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __pyx_6 = PyInt_AsUnsignedLongMask(__pyx_2); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 40; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    __pyx_v_new_allocated_count = __pyx_6;

    /* "pyrex-lib/darray.pyx":41 */
    #ifndef PYREX_WITHOUT_ASSERTIONS
    if (!(__pyx_v_new_allocated_count >= __pyx_v_new_used_count)) {
      PyErr_SetNone(PyExc_AssertionError);
      {__pyx_filename = __pyx_f[3]; __pyx_lineno = 41; goto __pyx_L1;}
    }
    #endif

    /* "pyrex-lib/darray.pyx":42 */
    __pyx_1 = __pyx_f_8pytracer_reallocate((&__pyx_v_darray->array),(__pyx_v_new_allocated_count * __pyx_v_darray->item_size)); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 42; goto __pyx_L1;}

    /* "pyrex-lib/darray.pyx":44 */
    __pyx_v_darray->allocated_count = __pyx_v_new_allocated_count;
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "pyrex-lib/darray.pyx":46 */
  __pyx_v_result = (&(((unsigned char *)__pyx_v_darray->array)[(__pyx_v_darray->used_count * __pyx_v_darray->item_size)]));

  /* "pyrex-lib/darray.pyx":47 */
  __pyx_v_darray->used_count = __pyx_v_new_used_count;

  /* "pyrex-lib/darray.pyx":48 */
  __pyx_r = __pyx_v_result;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("pytracer.darray_add");
  __pyx_r = NULL;
  __pyx_L0:;
  return __pyx_r;
}

static void *__pyx_f_8pytracer_darray_last(__pyx_t_8pytracer_darray *__pyx_v_darray) {
  void *__pyx_r;
  __pyx_r = (&(((unsigned char *)__pyx_v_darray->array)[((__pyx_v_darray->used_count - 1) * __pyx_v_darray->item_size)]));
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}

static void __pyx_f_8pytracer_darray_fini(__pyx_t_8pytracer_darray *__pyx_v_darray) {

  /* "pyrex-lib/darray.pyx":54 */
  free(__pyx_v_darray->array);

  /* "pyrex-lib/darray.pyx":55 */
  __pyx_v_darray->array = NULL;

  /* "pyrex-lib/darray.pyx":56 */
  __pyx_v_darray->used_count = (-1);

}

static int __pyx_f_8pytracer_darray_fast_remove_last(__pyx_t_8pytracer_darray *__pyx_v_darray) {
  unsigned int __pyx_v_new_used_count;
  int __pyx_r;

  /* "pyrex-lib/darray.pyx":62 */
  #ifndef PYREX_WITHOUT_ASSERTIONS
  if (!(__pyx_v_darray->used_count > 0)) {
    PyErr_SetNone(PyExc_AssertionError);
    {__pyx_filename = __pyx_f[3]; __pyx_lineno = 62; goto __pyx_L1;}
  }
  #endif

  /* "pyrex-lib/darray.pyx":63 */
  __pyx_v_new_used_count = (__pyx_v_darray->used_count - 1);

  /* "pyrex-lib/darray.pyx":64 */
  __pyx_v_darray->used_count = __pyx_v_new_used_count;

  /* "pyrex-lib/darray.pyx":65 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("pytracer.darray_fast_remove_last");
  __pyx_r = (-1);
  __pyx_L0:;
  return __pyx_r;
}

static PyObject *__pyx_n_fflush;


static int __pyx_f_8pytracer_safe_fflush(FILE *__pyx_v_stream) {
  int __pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;

  /* "pyrex-lib/files.pyx":20 */
  __pyx_1 = ((-1) == fflush(__pyx_v_stream));
  if (__pyx_1) {
    __pyx_2 = PyInt_FromLong(errno); if (!__pyx_2) {__pyx_filename = __pyx_f[4]; __pyx_lineno = 21; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[4]; __pyx_lineno = 21; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_2);
    Py_INCREF(__pyx_n_fflush);
    PyTuple_SET_ITEM(__pyx_3, 1, __pyx_n_fflush);
    __pyx_2 = 0;
    __pyx_2 = PyObject_CallObject(PyExc_OSError, __pyx_3); if (!__pyx_2) {__pyx_filename = __pyx_f[4]; __pyx_lineno = 21; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_2, 0, 0);
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    {__pyx_filename = __pyx_f[4]; __pyx_lineno = 21; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "pyrex-lib/files.pyx":22 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("pytracer.safe_fflush");
  __pyx_r = (-1);
  __pyx_L0:;
  return __pyx_r;
}

static PyObject *__pyx_n_fread;


static size_t __pyx_f_8pytracer_safe_fread(void *__pyx_v_ptr,size_t __pyx_v_size,FILE *__pyx_v_stream) {
  int __pyx_v_rc;
  size_t __pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;

  /* "pyrex-lib/files.pyx":26 */
  __pyx_v_rc = fread(__pyx_v_ptr,1,__pyx_v_size,__pyx_v_stream);

  /* "pyrex-lib/files.pyx":27 */
  __pyx_1 = (__pyx_v_rc == (-1));
  if (__pyx_1) {
    __pyx_2 = PyInt_FromLong(errno); if (!__pyx_2) {__pyx_filename = __pyx_f[4]; __pyx_lineno = 28; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[4]; __pyx_lineno = 28; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_2);
    Py_INCREF(__pyx_n_fread);
    PyTuple_SET_ITEM(__pyx_3, 1, __pyx_n_fread);
    __pyx_2 = 0;
    __pyx_2 = PyObject_CallObject(PyExc_OSError, __pyx_3); if (!__pyx_2) {__pyx_filename = __pyx_f[4]; __pyx_lineno = 28; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_2, 0, 0);
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    {__pyx_filename = __pyx_f[4]; __pyx_lineno = 28; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "pyrex-lib/files.pyx":29 */
  __pyx_r = __pyx_v_rc;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("pytracer.safe_fread");
  __pyx_r = (-1);
  __pyx_L0:;
  return __pyx_r;
}

static PyObject *__pyx_n_fwrite;


static size_t __pyx_f_8pytracer_safe_fwrite(void *__pyx_v_ptr,size_t __pyx_v_size,FILE *__pyx_v_stream) {
  int __pyx_v_rc;
  size_t __pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;

  /* "pyrex-lib/files.pyx":33 */
  __pyx_v_rc = fwrite(__pyx_v_ptr,1,__pyx_v_size,__pyx_v_stream);

  /* "pyrex-lib/files.pyx":34 */
  __pyx_1 = (__pyx_v_rc == (-1));
  if (__pyx_1) {
    __pyx_2 = PyInt_FromLong(errno); if (!__pyx_2) {__pyx_filename = __pyx_f[4]; __pyx_lineno = 35; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[4]; __pyx_lineno = 35; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_2);
    Py_INCREF(__pyx_n_fwrite);
    PyTuple_SET_ITEM(__pyx_3, 1, __pyx_n_fwrite);
    __pyx_2 = 0;
    __pyx_2 = PyObject_CallObject(PyExc_OSError, __pyx_3); if (!__pyx_2) {__pyx_filename = __pyx_f[4]; __pyx_lineno = 35; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_2, 0, 0);
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    {__pyx_filename = __pyx_f[4]; __pyx_lineno = 35; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "pyrex-lib/files.pyx":36 */
  __pyx_r = __pyx_v_rc;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("pytracer.safe_fwrite");
  __pyx_r = (-1);
  __pyx_L0:;
  return __pyx_r;
}

static void __pyx_f_8pytracer_call_invocation_empty(__pyx_t_8pytracer_CallInvocation *__pyx_v_invocation) {
  int __pyx_1;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":47 */
  memset(__pyx_v_invocation,0,(sizeof((__pyx_v_invocation[0]))));

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":48 */
  __pyx_1 = __pyx_f_8pytracer_darray_init((&__pyx_v_invocation->children),(sizeof(graphfile_linkable_t))); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 48; goto __pyx_L1;}

  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_WriteUnraisable("pytracer.call_invocation_empty");
  __pyx_L0:;
}

static PyObject *__pyx_f_8pytracer_fwrite_string(PyObject *__pyx_v_name,FILE *__pyx_v_index_file) {
  char *__pyx_v_name_buf;
  Py_ssize_t __pyx_v_name_length;
  short __pyx_v_short_name_length;
  PyObject *__pyx_r;
  int __pyx_1;
  size_t __pyx_2;
  Py_INCREF(__pyx_v_name);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":54 */
  __pyx_1 = PyString_AsStringAndSize(__pyx_v_name,(&__pyx_v_name_buf),(&__pyx_v_name_length)); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 54; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":55 */
  __pyx_v_short_name_length = __pyx_v_name_length;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":58 */
  #ifndef PYREX_WITHOUT_ASSERTIONS
  if (!(__pyx_v_short_name_length == __pyx_v_name_length)) {
    PyErr_SetNone(PyExc_AssertionError);
    {__pyx_filename = __pyx_f[5]; __pyx_lineno = 58; goto __pyx_L1;}
  }
  #endif

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":60 */
  __pyx_2 = __pyx_f_8pytracer_safe_fwrite((&__pyx_v_short_name_length),(sizeof(__pyx_v_short_name_length)),__pyx_v_index_file); if (__pyx_2 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 60; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":61 */
  __pyx_2 = __pyx_f_8pytracer_safe_fwrite(__pyx_v_name_buf,__pyx_v_name_length,__pyx_v_index_file); if (__pyx_2 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 61; goto __pyx_L1;}

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("pytracer.fwrite_string");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_name);
  return __pyx_r;
}

static int __pyx_f_8pytracer_freeEntry(rotating_node_t *__pyx_v_header,void *__pyx_v_arg) {
  int __pyx_r;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":64 */
  free(__pyx_v_header);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":65 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}

static PyObject *__pyx_n_graphfile_writer_init;


static int __pyx_f_8pytracer_6Tracer___cinit__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_8pytracer_6Tracer___cinit__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_fileobj = 0;
  PyObject *__pyx_v_index_fileobj = 0;
  int __pyx_r;
  FILE *__pyx_1;
  int __pyx_2;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  static char *__pyx_argnames[] = {"fileobj","index_fileobj",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "OO", __pyx_argnames, &__pyx_v_fileobj, &__pyx_v_index_fileobj)) return -1;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_fileobj);
  Py_INCREF(__pyx_v_index_fileobj);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":83 */
  ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->next_code_index = 0;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":84 */
  __pyx_1 = __pyx_f_8pytracer_file_from_obj(__pyx_v_index_fileobj); if (__pyx_1 == NULL) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 84; goto __pyx_L1;}
  ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->index_file = __pyx_1;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":85 */
  Py_INCREF(__pyx_v_index_fileobj);
  Py_DECREF(((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->index_fileobj);
  ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->index_fileobj = __pyx_v_index_fileobj;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":87 */
  __pyx_1 = __pyx_f_8pytracer_file_from_obj(__pyx_v_fileobj); if (__pyx_1 == NULL) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 87; goto __pyx_L1;}
  __pyx_2 = (0 != graphfile_writer_init((&((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->writer),__pyx_1));
  if (__pyx_2) {
    __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 88; goto __pyx_L1;}
    __pyx_4 = PyTuple_New(1); if (!__pyx_4) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 88; goto __pyx_L1;}
    Py_INCREF(__pyx_n_graphfile_writer_init);
    PyTuple_SET_ITEM(__pyx_4, 0, __pyx_n_graphfile_writer_init);
    __pyx_5 = PyObject_CallObject(__pyx_3, __pyx_4); if (!__pyx_5) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 88; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __Pyx_Raise(__pyx_5, 0, 0);
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    {__pyx_filename = __pyx_f[5]; __pyx_lineno = 88; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":89 */
  Py_INCREF(__pyx_v_fileobj);
  Py_DECREF(((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->fileobj);
  ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->fileobj = __pyx_v_fileobj;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":90 */
  ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->tracer_pid = (-1);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("pytracer.Tracer.__cinit__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_fileobj);
  Py_DECREF(__pyx_v_index_fileobj);
  return __pyx_r;
}

static void __pyx_f_8pytracer_6Tracer___dealloc__(PyObject *__pyx_v_self); /*proto*/
static void __pyx_f_8pytracer_6Tracer___dealloc__(PyObject *__pyx_v_self) {
  Py_INCREF(__pyx_v_self);
  graphfile_writer_fini((&((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->writer));

  Py_DECREF(__pyx_v_self);
}

static int __pyx_f_8pytracer_6Tracer_call_invocation_init(struct __pyx_obj_8pytracer_Tracer *__pyx_v_self,__pyx_t_8pytracer_CallInvocation *__pyx_v_invocation,PyObject *__pyx_v_code_obj,int __pyx_v_lineno,double __pyx_v_user_time,double __pyx_v_sys_time,double __pyx_v_real_time) {
  int __pyx_r;
  int __pyx_1;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_code_obj);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":100 */
  __pyx_1 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)__pyx_v_self->__pyx_vtab)->_index_of_code(__pyx_v_self,__pyx_v_code_obj); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 100; goto __pyx_L1;}
  __pyx_v_invocation->data.index = __pyx_1;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":101 */
  __pyx_v_invocation->data.lineno = __pyx_v_lineno;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":102 */
  __pyx_v_invocation->data.user_time = __pyx_v_user_time;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":103 */
  __pyx_v_invocation->data.sys_time = __pyx_v_sys_time;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":104 */
  __pyx_v_invocation->data.real_time = __pyx_v_real_time;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":105 */
  __pyx_1 = __pyx_f_8pytracer_darray_init((&__pyx_v_invocation->children),(sizeof(graphfile_linkable_t))); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 105; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":106 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("pytracer.Tracer.call_invocation_init");
  __pyx_r = (-1);
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_code_obj);
  return __pyx_r;
}

static PyObject *__pyx_n_f_code;
static PyObject *__pyx_n_f_lineno;

static int __pyx_f_8pytracer_6Tracer__trace_event(struct __pyx_obj_8pytracer_Tracer *__pyx_v_self,PyObject *__pyx_v_frame,int __pyx_v_event,void *__pyx_v_trace_arg) {
  double __pyx_v_user_time;
  double __pyx_v_sys_time;
  double __pyx_v_real_time;
  int __pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  int __pyx_4;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_frame);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":111 */
  __pyx_1 = (__pyx_v_self->tracer_pid != getpid());
  if (__pyx_1) {
    __pyx_r = 0;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":115 */
  __pyx_1 = (__pyx_v_event != PyTrace_CALL);
  if (__pyx_1) {
    __pyx_1 = (__pyx_v_event != PyTrace_RETURN);
  }
  if (__pyx_1) {
    __pyx_r = 0;
    goto __pyx_L0;
    goto __pyx_L3;
  }
  __pyx_L3:;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":118 */
  __pyx_1 = __pyx_f_8pytracer_get_user_sys_times((&__pyx_v_user_time),(&__pyx_v_sys_time)); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 118; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":119 */
  __pyx_1 = __pyx_f_8pytracer_get_real_time((&__pyx_v_real_time)); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 119; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":121 */
  __pyx_1 = (__pyx_v_event == PyTrace_CALL);
  if (__pyx_1) {
    __pyx_2 = PyObject_GetAttr(__pyx_v_frame, __pyx_n_f_code); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 122; goto __pyx_L1;}
    __pyx_3 = PyObject_GetAttr(__pyx_v_frame, __pyx_n_f_lineno); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 122; goto __pyx_L1;}
    __pyx_1 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 122; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_4 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)__pyx_v_self->__pyx_vtab)->_push_call(__pyx_v_self,__pyx_2,__pyx_1,__pyx_v_user_time,__pyx_v_sys_time,__pyx_v_real_time); if (__pyx_4 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 122; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    goto __pyx_L4;
  }
  /*else*/ {
    __pyx_1 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)__pyx_v_self->__pyx_vtab)->_pop_call(__pyx_v_self,__pyx_v_user_time,__pyx_v_sys_time,__pyx_v_real_time); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 124; goto __pyx_L1;}
  }
  __pyx_L4:;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":125 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("pytracer.Tracer._trace_event");
  __pyx_r = (-1);
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_frame);
  return __pyx_r;
}

static int __pyx_f_8pytracer_6Tracer__push_call(struct __pyx_obj_8pytracer_Tracer *__pyx_v_self,PyObject *__pyx_v_code_obj,int __pyx_v_lineno,double __pyx_v_user_time,double __pyx_v_sys_time,double __pyx_v_real_time) {
  __pyx_t_8pytracer_CallInvocation *__pyx_v_invocation;
  int __pyx_r;
  void *__pyx_1;
  int __pyx_2;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_code_obj);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":130 */
  __pyx_1 = __pyx_f_8pytracer_darray_add((&__pyx_v_self->stack)); if (__pyx_1 == NULL) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 130; goto __pyx_L1;}
  __pyx_v_invocation = ((__pyx_t_8pytracer_CallInvocation *)__pyx_1);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":131 */
  __pyx_2 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)__pyx_v_self->__pyx_vtab)->call_invocation_init(__pyx_v_self,__pyx_v_invocation,__pyx_v_code_obj,__pyx_v_lineno,__pyx_v_user_time,__pyx_v_sys_time,__pyx_v_real_time); if (__pyx_2 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 131; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":132 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("pytracer.Tracer._push_call");
  __pyx_r = (-1);
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_code_obj);
  return __pyx_r;
}

static int __pyx_f_8pytracer_6Tracer__pop_call(struct __pyx_obj_8pytracer_Tracer *__pyx_v_self,double __pyx_v_user_time,double __pyx_v_sys_time,double __pyx_v_real_time) {
  __pyx_t_8pytracer_CallInvocation *__pyx_v_invocation;
  graphfile_linkable_t __pyx_v_linkable;
  graphfile_linkable_t *__pyx_v_new_child_ptr;
  int __pyx_r;
  void *__pyx_1;
  int __pyx_2;
  void *__pyx_3;
  Py_INCREF(__pyx_v_self);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":139 */
  __pyx_1 = __pyx_f_8pytracer_darray_last((&__pyx_v_self->stack)); if (__pyx_1 == NULL) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 139; goto __pyx_L1;}
  __pyx_v_invocation = ((__pyx_t_8pytracer_CallInvocation *)__pyx_1);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":140 */
  __pyx_v_invocation->data.user_time = (__pyx_v_user_time - __pyx_v_invocation->data.user_time);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":141 */
  __pyx_v_invocation->data.sys_time = (__pyx_v_sys_time - __pyx_v_invocation->data.sys_time);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":142 */
  __pyx_v_invocation->data.real_time = (__pyx_v_real_time - __pyx_v_invocation->data.real_time);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":143 */
  __pyx_2 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)__pyx_v_self->__pyx_vtab)->_write(__pyx_v_self,((char *)(&__pyx_v_invocation->data)),(sizeof(__pyx_v_invocation->data)),(&__pyx_v_invocation->children),(&__pyx_v_linkable)); if (__pyx_2 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 143; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":145 */
  __pyx_f_8pytracer_darray_fini((&__pyx_v_invocation->children));

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":146 */
  __pyx_2 = __pyx_f_8pytracer_darray_fast_remove_last((&__pyx_v_self->stack)); if (__pyx_2 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 146; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":148 */
  __pyx_1 = __pyx_f_8pytracer_darray_last((&__pyx_v_self->stack)); if (__pyx_1 == NULL) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 148; goto __pyx_L1;}
  __pyx_v_invocation = ((__pyx_t_8pytracer_CallInvocation *)__pyx_1);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":149 */
  __pyx_3 = __pyx_f_8pytracer_darray_add((&__pyx_v_invocation->children)); if (__pyx_3 == NULL) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 149; goto __pyx_L1;}
  __pyx_v_new_child_ptr = ((graphfile_linkable_t *)__pyx_3);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":150 */
  (__pyx_v_new_child_ptr[0]) = __pyx_v_linkable;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":151 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("pytracer.Tracer._pop_call");
  __pyx_r = (-1);
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_n_id;
static PyObject *__pyx_n_co_filename;
static PyObject *__pyx_n_co_name;

static int __pyx_f_8pytracer_6Tracer__index_of_code(struct __pyx_obj_8pytracer_Tracer *__pyx_v_self,PyObject *__pyx_v_code) {
  unsigned long __pyx_v_key;
  __pyx_t_8pytracer_CodeIndexEntry *__pyx_v_node;
  int __pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  unsigned long __pyx_4;
  int __pyx_5;
  size_t __pyx_6;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_code);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":158 */
  __pyx_1 = __Pyx_GetName(__pyx_b, __pyx_n_id); if (!__pyx_1) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 158; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(1); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 158; goto __pyx_L1;}
  Py_INCREF(__pyx_v_code);
  PyTuple_SET_ITEM(__pyx_2, 0, __pyx_v_code);
  __pyx_3 = PyObject_CallObject(__pyx_1, __pyx_2); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 158; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  __pyx_4 = PyInt_AsUnsignedLongMask(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 158; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  __pyx_v_key = __pyx_4;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":159 */
  __pyx_v_node = ((__pyx_t_8pytracer_CodeIndexEntry *)RotatingTree_Get((&__pyx_v_self->written_indexes),((void *)__pyx_v_key)));

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":160 */
  __pyx_5 = (__pyx_v_node != NULL);
  if (__pyx_5) {
    __pyx_r = __pyx_v_node->code_index;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":163 */
  __pyx_v_node = ((__pyx_t_8pytracer_CodeIndexEntry *)malloc((sizeof(__pyx_t_8pytracer_CodeIndexEntry))));

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":164 */
  __pyx_v_node->header.key = ((void *)__pyx_v_key);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":165 */
  __pyx_v_node->code_index = __pyx_v_self->next_code_index;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":168 */
  #ifndef PYREX_WITHOUT_ASSERTIONS
  if (!(__pyx_v_self->next_code_index != 0)) {
    PyErr_SetNone(PyExc_AssertionError);
    {__pyx_filename = __pyx_f[5]; __pyx_lineno = 168; goto __pyx_L1;}
  }
  #endif

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":170 */
  __pyx_6 = __pyx_f_8pytracer_safe_fwrite((&__pyx_v_node->code_index),(sizeof(__pyx_v_node->code_index)),__pyx_v_self->index_file); if (__pyx_6 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 170; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":172 */
  __pyx_1 = PyObject_GetAttr(__pyx_v_code, __pyx_n_co_filename); if (!__pyx_1) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 172; goto __pyx_L1;}
  __pyx_2 = __pyx_f_8pytracer_fwrite_string(__pyx_1,__pyx_v_self->index_file); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 172; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":173 */
  __pyx_3 = PyObject_GetAttr(__pyx_v_code, __pyx_n_co_name); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 173; goto __pyx_L1;}
  __pyx_1 = __pyx_f_8pytracer_fwrite_string(__pyx_3,__pyx_v_self->index_file); if (!__pyx_1) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 173; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":175 */
  RotatingTree_Add((&__pyx_v_self->written_indexes),(&__pyx_v_node->header));

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":176 */
  __pyx_v_self->next_code_index = (__pyx_v_node->code_index + 1);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":177 */
  __pyx_r = __pyx_v_node->code_index;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("pytracer.Tracer._index_of_code");
  __pyx_r = (-1);
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_code);
  return __pyx_r;
}

static PyObject *__pyx_n_graphfile_writer_write;


static int __pyx_f_8pytracer_6Tracer__write(struct __pyx_obj_8pytracer_Tracer *__pyx_v_self,char *__pyx_v_buffer,unsigned int __pyx_v_buffer_length,__pyx_t_8pytracer_darray *__pyx_v_children,graphfile_linkable_t *__pyx_v_result) {
  int __pyx_v_status;
  int __pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  Py_INCREF(__pyx_v_self);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":182 */
  __pyx_v_status = graphfile_writer_write((&__pyx_v_self->writer),__pyx_v_buffer,__pyx_v_buffer_length,((graphfile_linkable_t *)__pyx_v_children->array),__pyx_v_children->used_count,__pyx_v_result);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":184 */
  __pyx_1 = (__pyx_v_status != 0);
  if (__pyx_1) {
    __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 185; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 185; goto __pyx_L1;}
    Py_INCREF(__pyx_n_graphfile_writer_write);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_n_graphfile_writer_write);
    __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 185; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_4, 0, 0);
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    {__pyx_filename = __pyx_f[5]; __pyx_lineno = 185; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":186 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("pytracer.Tracer._write");
  __pyx_r = (-1);
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_8pytracer_6Tracer__push_root(struct __pyx_obj_8pytracer_Tracer *__pyx_v_self) {
  __pyx_t_8pytracer_CallInvocation *__pyx_v_invocation;
  PyObject *__pyx_r;
  void *__pyx_1;
  Py_INCREF(__pyx_v_self);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":190 */
  __pyx_1 = __pyx_f_8pytracer_darray_add((&__pyx_v_self->stack)); if (__pyx_1 == NULL) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 190; goto __pyx_L1;}
  __pyx_v_invocation = ((__pyx_t_8pytracer_CallInvocation *)__pyx_1);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":191 */
  __pyx_f_8pytracer_call_invocation_empty(__pyx_v_invocation);

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("pytracer.Tracer._push_root");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_n_graphfile_writer_set_root;


static PyObject *__pyx_f_8pytracer_6Tracer__pop_root(struct __pyx_obj_8pytracer_Tracer *__pyx_v_self) {
  graphfile_linkable_t __pyx_v_root;
  __pyx_t_8pytracer_CallInvocation *__pyx_v_invocation;
  PyObject *__pyx_r;
  void *__pyx_1;
  int __pyx_2;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  Py_INCREF(__pyx_v_self);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":196 */
  #ifndef PYREX_WITHOUT_ASSERTIONS
  if (!(__pyx_v_self->stack.used_count == 1)) {
    PyErr_SetNone(PyExc_AssertionError);
    {__pyx_filename = __pyx_f[5]; __pyx_lineno = 196; goto __pyx_L1;}
  }
  #endif

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":198 */
  __pyx_1 = __pyx_f_8pytracer_darray_last((&__pyx_v_self->stack)); if (__pyx_1 == NULL) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 198; goto __pyx_L1;}
  __pyx_v_invocation = ((__pyx_t_8pytracer_CallInvocation *)__pyx_1);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":199 */
  __pyx_2 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)__pyx_v_self->__pyx_vtab)->_write(__pyx_v_self,NULL,0,(&__pyx_v_invocation->children),(&__pyx_v_root)); if (__pyx_2 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 199; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":200 */
  __pyx_2 = __pyx_f_8pytracer_darray_fast_remove_last((&__pyx_v_self->stack)); if (__pyx_2 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 200; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":201 */
  __pyx_2 = (0 != graphfile_writer_set_root((&__pyx_v_self->writer),(&__pyx_v_root)));
  if (__pyx_2) {
    __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_Error); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 202; goto __pyx_L1;}
    __pyx_4 = PyTuple_New(1); if (!__pyx_4) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 202; goto __pyx_L1;}
    Py_INCREF(__pyx_n_graphfile_writer_set_root);
    PyTuple_SET_ITEM(__pyx_4, 0, __pyx_n_graphfile_writer_set_root);
    __pyx_5 = PyObject_CallObject(__pyx_3, __pyx_4); if (!__pyx_5) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 202; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __Pyx_Raise(__pyx_5, 0, 0);
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    {__pyx_filename = __pyx_f[5]; __pyx_lineno = 202; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("pytracer.Tracer._pop_root");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_8pytracer_6Tracer__pop_to_root(struct __pyx_obj_8pytracer_Tracer *__pyx_v_self) {
  double __pyx_v_user_time;
  double __pyx_v_sys_time;
  double __pyx_v_real_time;
  PyObject *__pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  Py_INCREF(__pyx_v_self);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":206 */
  __pyx_1 = __pyx_f_8pytracer_get_user_sys_times((&__pyx_v_user_time),(&__pyx_v_sys_time)); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 206; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":207 */
  __pyx_1 = __pyx_f_8pytracer_get_real_time((&__pyx_v_real_time)); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 207; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":208 */
  while (1) {
    __pyx_1 = (__pyx_v_self->stack.used_count > 1);
    if (!__pyx_1) break;
    __pyx_1 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)__pyx_v_self->__pyx_vtab)->_pop_call(__pyx_v_self,__pyx_v_user_time,__pyx_v_sys_time,__pyx_v_real_time); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 209; goto __pyx_L1;}
  }

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":210 */
  __pyx_2 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)__pyx_v_self->__pyx_vtab)->_pop_root(__pyx_v_self); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 210; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  __Pyx_AddTraceback("pytracer.Tracer._pop_to_root");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_8pytracer_6Tracer__wrap_os_exit(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_8pytracer_6Tracer__wrap_os_exit(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_status = 0;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  static char *__pyx_argnames[] = {"status",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_status)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_status);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":213 */
  __pyx_1 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->__pyx_vtab)->_pop_to_root(((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)); if (!__pyx_1) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 213; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":214 */
  __pyx_1 = PyTuple_New(1); if (!__pyx_1) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 214; goto __pyx_L1;}
  Py_INCREF(__pyx_v_status);
  PyTuple_SET_ITEM(__pyx_1, 0, __pyx_v_status);
  __pyx_2 = PyObject_CallObject(((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->_prev_os_exit, __pyx_1); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 214; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  __Pyx_AddTraceback("pytracer.Tracer._wrap_os_exit");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_status);
  return __pyx_r;
}

static PyObject *__pyx_n__exit;
static PyObject *__pyx_n__wrap_os_exit;
static PyObject *__pyx_n_exc_info;

static PyObject *__pyx_k13p;

static char __pyx_k13[] = "Cannot create a nested trace";

static PyObject *__pyx_f_8pytracer_6Tracer_trace(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_8pytracer_6Tracer_trace(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_func = 0;
  PyObject *__pyx_v_exc_type;
  PyObject *__pyx_v_exc_value;
  PyObject *__pyx_v_exc_tb;
  PyObject *__pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  PyObject *__pyx_6 = 0;
  PyObject *__pyx_7 = 0;
  static char *__pyx_argnames[] = {"func",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_func)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_func);
  __pyx_v_exc_type = Py_None; Py_INCREF(Py_None);
  __pyx_v_exc_value = Py_None; Py_INCREF(Py_None);
  __pyx_v_exc_tb = Py_None; Py_INCREF(Py_None);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":217 */
  #ifndef PYREX_WITHOUT_ASSERTIONS
  if (!(((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->tracer_pid == (-1))) {
    PyErr_SetObject(PyExc_AssertionError, __pyx_k13p);
    {__pyx_filename = __pyx_f[5]; __pyx_lineno = 217; goto __pyx_L1;}
  }
  #endif

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":218 */
  __pyx_1 = __pyx_f_8pytracer_darray_init((&((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->stack),(sizeof(__pyx_t_8pytracer_CallInvocation))); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 218; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":219 */
  __pyx_2 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->__pyx_vtab)->_push_root(((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 219; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":220 */
  ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->tracer_pid = getpid();

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":221 */
  ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->written_indexes = EMPTY_ROTATING_TREE;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":222 */
  /*try:*/ {

    /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":223 */
    PyEval_SetProfile(((Py_tracefunc)(&__pyx_f_8pytracer_callback)),__pyx_v_self);

    /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":224 */
    __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_os); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 224; goto __pyx_L3;}
    __pyx_3 = PyObject_GetAttr(__pyx_2, __pyx_n__exit); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 224; goto __pyx_L3;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->_prev_os_exit);
    ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->_prev_os_exit = __pyx_3;
    __pyx_3 = 0;

    /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":225 */
    __pyx_2 = PyObject_GetAttr(__pyx_v_self, __pyx_n__wrap_os_exit); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 225; goto __pyx_L3;}
    __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_os); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 225; goto __pyx_L3;}
    if (PyObject_SetAttr(__pyx_3, __pyx_n__exit, __pyx_2) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 225; goto __pyx_L3;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;

    /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":226 */
    /*try:*/ {
      /*try:*/ {
        /*try:*/ {
          __pyx_2 = PyObject_CallObject(__pyx_v_func, 0); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 229; goto __pyx_L11;}
          __pyx_r = __pyx_2;
          __pyx_2 = 0;
          goto __pyx_L10;
        }
        /*finally:*/ {
          int __pyx_why;
          PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
          int __pyx_exc_lineno;
          __pyx_why = 0; goto __pyx_L12;
          __pyx_L10: __pyx_why = 3; goto __pyx_L12;
          __pyx_L11: {
            __pyx_why = 4;
            Py_XDECREF(__pyx_3); __pyx_3 = 0;
            Py_XDECREF(__pyx_2); __pyx_2 = 0;
            PyErr_Fetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
            __pyx_exc_lineno = __pyx_lineno;
            goto __pyx_L12;
          }
          __pyx_L12:;

          /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":231 */
          #ifndef PYREX_WITHOUT_ASSERTIONS
          __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_os); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 231; goto __pyx_L13;}
          __pyx_2 = PyObject_GetAttr(__pyx_3, __pyx_n__exit); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 231; goto __pyx_L13;}
          Py_DECREF(__pyx_3); __pyx_3 = 0;
          __pyx_3 = PyObject_GetAttr(__pyx_v_self, __pyx_n__wrap_os_exit); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 231; goto __pyx_L13;}
          if (PyObject_Cmp(__pyx_2, __pyx_3, &__pyx_1) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 231; goto __pyx_L13;}
          __pyx_1 = __pyx_1 == 0;
          Py_DECREF(__pyx_2); __pyx_2 = 0;
          Py_DECREF(__pyx_3); __pyx_3 = 0;
          if (!__pyx_1) {
            PyErr_SetNone(PyExc_AssertionError);
            {__pyx_filename = __pyx_f[5]; __pyx_lineno = 231; goto __pyx_L13;}
          }
          #endif

          /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":232 */
          __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_os); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 232; goto __pyx_L13;}
          if (PyObject_SetAttr(__pyx_2, __pyx_n__exit, ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->_prev_os_exit) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 232; goto __pyx_L13;}
          Py_DECREF(__pyx_2); __pyx_2 = 0;

          /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":233 */
          PyEval_SetProfile(NULL,Py_None);
          goto __pyx_L14;
          __pyx_L13:;
          if (__pyx_why == 4) {
            Py_XDECREF(__pyx_exc_type);
            Py_XDECREF(__pyx_exc_value);
            Py_XDECREF(__pyx_exc_tb);
          }
          goto __pyx_L8;
          __pyx_L14:;
          switch (__pyx_why) {
            case 3: goto __pyx_L5;
            case 4: {
              PyErr_Restore(__pyx_exc_type, __pyx_exc_value, __pyx_exc_tb);
              __pyx_lineno = __pyx_exc_lineno;
              __pyx_exc_type = 0;
              __pyx_exc_value = 0;
              __pyx_exc_tb = 0;
              goto __pyx_L8;
            }
          }
        }
      }
      goto __pyx_L9;
      __pyx_L8:;
      Py_XDECREF(__pyx_3); __pyx_3 = 0;
      Py_XDECREF(__pyx_2); __pyx_2 = 0;

      /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":234 */
      /*except:*/ {
        __Pyx_AddTraceback("pytracer.trace");
        if (__Pyx_GetException(&__pyx_3, &__pyx_2, &__pyx_4) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 234; goto __pyx_L6;}

        /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":235 */
        __pyx_1 = (((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->tracer_pid == getpid());
        if (__pyx_1) {

          /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":236 */
          __pyx_5 = __Pyx_GetName(__pyx_m, __pyx_n_sys); if (!__pyx_5) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 236; goto __pyx_L6;}
          __pyx_6 = PyObject_GetAttr(__pyx_5, __pyx_n_exc_info); if (!__pyx_6) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 236; goto __pyx_L6;}
          Py_DECREF(__pyx_5); __pyx_5 = 0;
          __pyx_5 = PyObject_CallObject(__pyx_6, 0); if (!__pyx_5) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 236; goto __pyx_L6;}
          Py_DECREF(__pyx_6); __pyx_6 = 0;
          __pyx_6 = PyObject_GetIter(__pyx_5); if (!__pyx_6) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 236; goto __pyx_L6;}
          Py_DECREF(__pyx_5); __pyx_5 = 0;
          __pyx_5 = __Pyx_UnpackItem(__pyx_6); if (!__pyx_5) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 236; goto __pyx_L6;}
          Py_DECREF(__pyx_v_exc_type);
          __pyx_v_exc_type = __pyx_5;
          __pyx_5 = 0;
          __pyx_5 = __Pyx_UnpackItem(__pyx_6); if (!__pyx_5) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 236; goto __pyx_L6;}
          Py_DECREF(__pyx_v_exc_value);
          __pyx_v_exc_value = __pyx_5;
          __pyx_5 = 0;
          __pyx_5 = __Pyx_UnpackItem(__pyx_6); if (!__pyx_5) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 236; goto __pyx_L6;}
          Py_DECREF(__pyx_v_exc_tb);
          __pyx_v_exc_tb = __pyx_5;
          __pyx_5 = 0;
          if (__Pyx_EndUnpack(__pyx_6) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 236; goto __pyx_L6;}
          Py_DECREF(__pyx_6); __pyx_6 = 0;

          /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":237 */
          /*try:*/ {
            __pyx_5 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->__pyx_vtab)->_pop_root(((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)); if (!__pyx_5) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 238; goto __pyx_L16;}
            Py_DECREF(__pyx_5); __pyx_5 = 0;
          }
          goto __pyx_L17;
          __pyx_L16:;
          Py_XDECREF(__pyx_6); __pyx_6 = 0;
          Py_XDECREF(__pyx_5); __pyx_5 = 0;

          /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":239 */
          /*except:*/ {
            __Pyx_AddTraceback("pytracer.trace");
            if (__Pyx_GetException(&__pyx_6, &__pyx_5, &__pyx_7) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 239; goto __pyx_L6;}
            __Pyx_Raise(__pyx_v_exc_type, __pyx_v_exc_value, __pyx_v_exc_tb);
            {__pyx_filename = __pyx_f[5]; __pyx_lineno = 241; goto __pyx_L6;}
            Py_DECREF(__pyx_6); __pyx_6 = 0;
            Py_DECREF(__pyx_5); __pyx_5 = 0;
            Py_DECREF(__pyx_7); __pyx_7 = 0;
            goto __pyx_L17;
          }
          __pyx_L17:;
          goto __pyx_L15;
        }
        __pyx_L15:;

        /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":242 */
        __Pyx_Raise(__pyx_3, __pyx_2, __pyx_4);
        {__pyx_filename = __pyx_f[5]; __pyx_lineno = 242; goto __pyx_L6;}
        Py_DECREF(__pyx_3); __pyx_3 = 0;
        Py_DECREF(__pyx_2); __pyx_2 = 0;
        Py_DECREF(__pyx_4); __pyx_4 = 0;
        goto __pyx_L9;
      }
      __pyx_L9:;
    }
    /*finally:*/ {
      int __pyx_why;
      PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
      int __pyx_exc_lineno;
      __pyx_why = 0; goto __pyx_L7;
      __pyx_L5: __pyx_why = 3; goto __pyx_L7;
      __pyx_L6: {
        __pyx_why = 4;
        Py_XDECREF(__pyx_6); __pyx_6 = 0;
        Py_XDECREF(__pyx_5); __pyx_5 = 0;
        Py_XDECREF(__pyx_7); __pyx_7 = 0;
        Py_XDECREF(__pyx_3); __pyx_3 = 0;
        Py_XDECREF(__pyx_2); __pyx_2 = 0;
        Py_XDECREF(__pyx_4); __pyx_4 = 0;
        PyErr_Fetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
        __pyx_exc_lineno = __pyx_lineno;
        goto __pyx_L7;
      }
      __pyx_L7:;
      __pyx_1 = (((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->tracer_pid == getpid());
      if (__pyx_1) {
        __pyx_6 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->__pyx_vtab)->_pop_root(((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)); if (!__pyx_6) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 247; goto __pyx_L18;}
        Py_DECREF(__pyx_6); __pyx_6 = 0;
        goto __pyx_L19;
      }
      __pyx_L19:;
      goto __pyx_L20;
      __pyx_L18:;
      if (__pyx_why == 4) {
        Py_XDECREF(__pyx_exc_type);
        Py_XDECREF(__pyx_exc_value);
        Py_XDECREF(__pyx_exc_tb);
      }
      goto __pyx_L3;
      __pyx_L20:;
      switch (__pyx_why) {
        case 3: goto __pyx_L2;
        case 4: {
          PyErr_Restore(__pyx_exc_type, __pyx_exc_value, __pyx_exc_tb);
          __pyx_lineno = __pyx_exc_lineno;
          __pyx_exc_type = 0;
          __pyx_exc_value = 0;
          __pyx_exc_tb = 0;
          goto __pyx_L3;
        }
      }
    }
  }
  /*finally:*/ {
    int __pyx_why;
    PyObject *__pyx_exc_type, *__pyx_exc_value, *__pyx_exc_tb;
    int __pyx_exc_lineno;
    __pyx_why = 0; goto __pyx_L4;
    __pyx_L2: __pyx_why = 3; goto __pyx_L4;
    __pyx_L3: {
      __pyx_why = 4;
      Py_XDECREF(__pyx_5); __pyx_5 = 0;
      Py_XDECREF(__pyx_7); __pyx_7 = 0;
      Py_XDECREF(__pyx_3); __pyx_3 = 0;
      Py_XDECREF(__pyx_2); __pyx_2 = 0;
      Py_XDECREF(__pyx_4); __pyx_4 = 0;
      Py_XDECREF(__pyx_6); __pyx_6 = 0;
      PyErr_Fetch(&__pyx_exc_type, &__pyx_exc_value, &__pyx_exc_tb);
      __pyx_exc_lineno = __pyx_lineno;
      goto __pyx_L4;
    }
    __pyx_L4:;

    /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":249 */
    RotatingTree_Enum(((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->written_indexes,(&__pyx_f_8pytracer_freeEntry),NULL);

    /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":250 */
    ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->written_indexes = NULL;

    /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":251 */
    ((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->tracer_pid = (-1);

    /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":252 */
    __pyx_f_8pytracer_darray_fini((&((struct __pyx_obj_8pytracer_Tracer *)__pyx_v_self)->stack));
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
  Py_XDECREF(__pyx_5);
  Py_XDECREF(__pyx_6);
  Py_XDECREF(__pyx_7);
  __Pyx_AddTraceback("pytracer.Tracer.trace");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_exc_type);
  Py_DECREF(__pyx_v_exc_value);
  Py_DECREF(__pyx_v_exc_tb);
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_func);
  return __pyx_r;
}

static int __pyx_f_8pytracer_callback(struct __pyx_obj_8pytracer_Tracer *__pyx_v_tracer,PyObject *__pyx_v_frame,int __pyx_v_event,void *__pyx_v_trace_arg) {
  int __pyx_r;
  int __pyx_1;
  Py_INCREF(__pyx_v_tracer);
  Py_INCREF(__pyx_v_frame);

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":255 */
  __pyx_1 = ((struct __pyx_vtabstruct_8pytracer_Tracer *)__pyx_v_tracer->__pyx_vtab)->_trace_event(__pyx_v_tracer,__pyx_v_frame,__pyx_v_event,__pyx_v_trace_arg); if (__pyx_1 == (-1)) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 255; goto __pyx_L1;}

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":256 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("pytracer.callback");
  __pyx_r = (-1);
  __pyx_L0:;
  Py_DECREF(__pyx_v_tracer);
  Py_DECREF(__pyx_v_frame);
  return __pyx_r;
}

static __Pyx_InternTabEntry __pyx_intern_tab[] = {
  {&__pyx_n_Error, "Error"},
  {&__pyx_n__exit, "_exit"},
  {&__pyx_n__wrap_os_exit, "_wrap_os_exit"},
  {&__pyx_n_co_filename, "co_filename"},
  {&__pyx_n_co_name, "co_name"},
  {&__pyx_n_exc_info, "exc_info"},
  {&__pyx_n_f_code, "f_code"},
  {&__pyx_n_f_lineno, "f_lineno"},
  {&__pyx_n_fflush, "fflush"},
  {&__pyx_n_fread, "fread"},
  {&__pyx_n_fwrite, "fwrite"},
  {&__pyx_n_getrusage, "getrusage"},
  {&__pyx_n_gettimeofday, "gettimeofday"},
  {&__pyx_n_graphfile_writer_init, "graphfile_writer_init"},
  {&__pyx_n_graphfile_writer_set_root, "graphfile_writer_set_root"},
  {&__pyx_n_graphfile_writer_write, "graphfile_writer_write"},
  {&__pyx_n_id, "id"},
  {&__pyx_n_max, "max"},
  {&__pyx_n_os, "os"},
  {&__pyx_n_sys, "sys"},
  {0, 0}
};

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_k6p, __pyx_k6, sizeof(__pyx_k6)},
  {&__pyx_k13p, __pyx_k13, sizeof(__pyx_k13)},
  {0, 0, 0}
};

static PyObject *__pyx_tp_new_8pytracer__Linkable(PyTypeObject *t, PyObject *a, PyObject *k) {
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  return o;
}

static void __pyx_tp_dealloc_8pytracer__Linkable(PyObject *o) {
  (*o->ob_type->tp_free)(o);
}

static struct PyMethodDef __pyx_methods_8pytracer__Linkable[] = {
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

PyTypeObject __pyx_type_8pytracer__Linkable = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "pytracer._Linkable", /*tp_name*/
  sizeof(struct __pyx_obj_8pytracer__Linkable), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_8pytracer__Linkable, /*tp_dealloc*/
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
  __pyx_methods_8pytracer__Linkable, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  0, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_8pytracer__Linkable, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};
static struct __pyx_vtabstruct_8pytracer_Tracer __pyx_vtable_8pytracer_Tracer;

static PyObject *__pyx_tp_new_8pytracer_Tracer(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_8pytracer_Tracer *p;
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  p = ((struct __pyx_obj_8pytracer_Tracer *)o);
  *(struct __pyx_vtabstruct_8pytracer_Tracer **)&p->__pyx_vtab = __pyx_vtabptr_8pytracer_Tracer;
  p->fileobj = Py_None; Py_INCREF(Py_None);
  p->index_fileobj = Py_None; Py_INCREF(Py_None);
  p->_prev_os_exit = Py_None; Py_INCREF(Py_None);
  if (__pyx_f_8pytracer_6Tracer___cinit__(o, a, k) < 0) {
    Py_DECREF(o); o = 0;
  }
  return o;
}

static void __pyx_tp_dealloc_8pytracer_Tracer(PyObject *o) {
  struct __pyx_obj_8pytracer_Tracer *p = (struct __pyx_obj_8pytracer_Tracer *)o;
  {
    PyObject *etype, *eval, *etb;
    PyErr_Fetch(&etype, &eval, &etb);
    ++o->ob_refcnt;
    __pyx_f_8pytracer_6Tracer___dealloc__(o);
    if (PyErr_Occurred()) PyErr_WriteUnraisable(o);
    --o->ob_refcnt;
    PyErr_Restore(etype, eval, etb);
  }
  Py_XDECREF(p->fileobj);
  Py_XDECREF(p->index_fileobj);
  Py_XDECREF(p->_prev_os_exit);
  (*o->ob_type->tp_free)(o);
}

static int __pyx_tp_traverse_8pytracer_Tracer(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_8pytracer_Tracer *p = (struct __pyx_obj_8pytracer_Tracer *)o;
  if (p->fileobj) {
    e = (*v)(p->fileobj, a); if (e) return e;
  }
  if (p->index_fileobj) {
    e = (*v)(p->index_fileobj, a); if (e) return e;
  }
  if (p->_prev_os_exit) {
    e = (*v)(p->_prev_os_exit, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_8pytracer_Tracer(PyObject *o) {
  struct __pyx_obj_8pytracer_Tracer *p = (struct __pyx_obj_8pytracer_Tracer *)o;
  PyObject *t;
  t = p->fileobj; 
  p->fileobj = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->index_fileobj; 
  p->index_fileobj = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->_prev_os_exit; 
  p->_prev_os_exit = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  return 0;
}

static struct PyMethodDef __pyx_methods_8pytracer_Tracer[] = {
  {"_wrap_os_exit", (PyCFunction)__pyx_f_8pytracer_6Tracer__wrap_os_exit, METH_VARARGS|METH_KEYWORDS, 0},
  {"trace", (PyCFunction)__pyx_f_8pytracer_6Tracer_trace, METH_VARARGS|METH_KEYWORDS, 0},
  {0, 0, 0, 0}
};

static struct PyMemberDef __pyx_members_8pytracer_Tracer[] = {
  {"fileobj", T_OBJECT, offsetof(struct __pyx_obj_8pytracer_Tracer, fileobj), READONLY, 0},
  {"index_fileobj", T_OBJECT, offsetof(struct __pyx_obj_8pytracer_Tracer, index_fileobj), READONLY, 0},
  {0, 0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_Tracer = {
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

static PySequenceMethods __pyx_tp_as_sequence_Tracer = {
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

static PyMappingMethods __pyx_tp_as_mapping_Tracer = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_Tracer = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_8pytracer_Tracer = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "pytracer.Tracer", /*tp_name*/
  sizeof(struct __pyx_obj_8pytracer_Tracer), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_8pytracer_Tracer, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_Tracer, /*tp_as_number*/
  &__pyx_tp_as_sequence_Tracer, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_Tracer, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_Tracer, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  0, /*tp_doc*/
  __pyx_tp_traverse_8pytracer_Tracer, /*tp_traverse*/
  __pyx_tp_clear_8pytracer_Tracer, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_8pytracer_Tracer, /*tp_methods*/
  __pyx_members_8pytracer_Tracer, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  0, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_8pytracer_Tracer, /*tp_new*/
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

PyMODINIT_FUNC initpytracer(void); /*proto*/
PyMODINIT_FUNC initpytracer(void) {
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  __pyx_init_filenames();
  __pyx_m = Py_InitModule4("pytracer", __pyx_methods, 0, 0, PYTHON_API_VERSION);
  if (!__pyx_m) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 17; goto __pyx_L1;};
  Py_INCREF(__pyx_m);
  __pyx_b = PyImport_AddModule("__builtin__");
  if (!__pyx_b) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 17; goto __pyx_L1;};
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 17; goto __pyx_L1;};
  if (__Pyx_InternStrings(__pyx_intern_tab) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 17; goto __pyx_L1;};
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 17; goto __pyx_L1;};
  if (PyType_Ready(&__pyx_type_8pytracer__Linkable) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 69; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "_Linkable", (PyObject *)&__pyx_type_8pytracer__Linkable) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 69; goto __pyx_L1;}
  __pyx_ptype_8pytracer__Linkable = &__pyx_type_8pytracer__Linkable;
  __pyx_vtabptr_8pytracer_Tracer = &__pyx_vtable_8pytracer_Tracer;
  *(void(**)(void))&__pyx_vtable_8pytracer_Tracer.call_invocation_init = (void(*)(void))__pyx_f_8pytracer_6Tracer_call_invocation_init;
  *(void(**)(void))&__pyx_vtable_8pytracer_Tracer._trace_event = (void(*)(void))__pyx_f_8pytracer_6Tracer__trace_event;
  *(void(**)(void))&__pyx_vtable_8pytracer_Tracer._push_call = (void(*)(void))__pyx_f_8pytracer_6Tracer__push_call;
  *(void(**)(void))&__pyx_vtable_8pytracer_Tracer._pop_call = (void(*)(void))__pyx_f_8pytracer_6Tracer__pop_call;
  *(void(**)(void))&__pyx_vtable_8pytracer_Tracer._index_of_code = (void(*)(void))__pyx_f_8pytracer_6Tracer__index_of_code;
  *(void(**)(void))&__pyx_vtable_8pytracer_Tracer._write = (void(*)(void))__pyx_f_8pytracer_6Tracer__write;
  *(void(**)(void))&__pyx_vtable_8pytracer_Tracer._push_root = (void(*)(void))__pyx_f_8pytracer_6Tracer__push_root;
  *(void(**)(void))&__pyx_vtable_8pytracer_Tracer._pop_root = (void(*)(void))__pyx_f_8pytracer_6Tracer__pop_root;
  *(void(**)(void))&__pyx_vtable_8pytracer_Tracer._pop_to_root = (void(*)(void))__pyx_f_8pytracer_6Tracer__pop_to_root;
  __pyx_type_8pytracer_Tracer.tp_free = _PyObject_GC_Del;
  if (PyType_Ready(&__pyx_type_8pytracer_Tracer) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 72; goto __pyx_L1;}
  if (__Pyx_SetVtable(__pyx_type_8pytracer_Tracer.tp_dict, __pyx_vtabptr_8pytracer_Tracer) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 72; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "Tracer", (PyObject *)&__pyx_type_8pytracer_Tracer) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 72; goto __pyx_L1;}
  __pyx_ptype_8pytracer_Tracer = &__pyx_type_8pytracer_Tracer;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":26 */
  __pyx_1 = __Pyx_Import(__pyx_n_os, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 26; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_os, __pyx_1) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 26; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":27 */
  __pyx_1 = __Pyx_Import(__pyx_n_sys, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 27; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_sys, __pyx_1) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 27; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":67 */
  __pyx_1 = PyDict_New(); if (!__pyx_1) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 67; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(1); if (!__pyx_2) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 67; goto __pyx_L1;}
  Py_INCREF(PyExc_Exception);
  PyTuple_SET_ITEM(__pyx_2, 0, PyExc_Exception);
  __pyx_3 = __Pyx_CreateClass(__pyx_2, __pyx_1, __pyx_n_Error, "pytracer"); if (!__pyx_3) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 67; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  if (PyObject_SetAttr(__pyx_m, __pyx_n_Error, __pyx_3) < 0) {__pyx_filename = __pyx_f[5]; __pyx_lineno = 67; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/a/home/eyal/devel/pythontracer/tracer/pytracer.pyx":254 */
  return;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("pytracer");
}

static char *__pyx_filenames[] = {
  "times.pyx",
  "memory.pyx",
  "python.pyx",
  "darray.pyx",
  "files.pyx",
  "pytracer.pyx",
};

/* Runtime support code */

static void __pyx_init_filenames(void) {
  __pyx_f = __pyx_filenames;
}

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list) {
    PyObject *__import__ = 0;
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    __import__ = PyObject_GetAttrString(__pyx_b, "__import__");
    if (!__import__)
        goto bad;
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    module = PyObject_CallFunction(__import__, "OOOO",
        name, global_dict, empty_dict, list);
bad:
    Py_XDECREF(empty_list);
    Py_XDECREF(__import__);
    Py_XDECREF(empty_dict);
    return module;
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

static void __Pyx_WriteUnraisable(char *name) {
    PyObject *old_exc, *old_val, *old_tb;
    PyObject *ctx;
    PyErr_Fetch(&old_exc, &old_val, &old_tb);
    ctx = PyString_FromString(name);
    PyErr_Restore(old_exc, old_val, old_tb);
    if (!ctx)
        ctx = Py_None;
    PyErr_WriteUnraisable(ctx);
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

static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb) {
    PyThreadState *tstate = PyThreadState_Get();
    PyErr_Fetch(type, value, tb);
    PyErr_NormalizeException(type, value, tb);
    if (PyErr_Occurred())
        goto bad;
    Py_INCREF(*type);
    Py_INCREF(*value);
    Py_INCREF(*tb);
    Py_XDECREF(tstate->exc_type);
    Py_XDECREF(tstate->exc_value);
    Py_XDECREF(tstate->exc_traceback);
    tstate->exc_type = *type;
    tstate->exc_value = *value;
    tstate->exc_traceback = *tb;
    return 0;
bad:
    Py_XDECREF(*type);
    Py_XDECREF(*value);
    Py_XDECREF(*tb);
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

static int __Pyx_SetVtable(PyObject *dict, void *vtable) {
    PyObject *pycobj = 0;
    int result;
    
    pycobj = PyCObject_FromVoidPtr(vtable, 0);
    if (!pycobj)
        goto bad;
    if (PyDict_SetItemString(dict, "__pyx_vtable__", pycobj) < 0)
        goto bad;
    result = 0;
    goto done;

bad:
    result = -1;
done:
    Py_XDECREF(pycobj);
    return result;
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
