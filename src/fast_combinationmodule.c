#include <Python.h>


double _fast_combination(unsigned long n, long k) {
    
    double product = 1;
    double i;
    for (i = 1.0; i<=k; i++) {
        product *= ((n+1-i)/i);
    }
    return product;
}


static PyObject* fast_combination(PyObject* self, PyObject* args) {
    // signed longs for clean bound checking, as PyArg_ParseTuple doesn't
    // check for overflow. LONG_MAX is more enough number, methinks...
    long n;
    long k;
    double result;
    
    if(!PyArg_ParseTuple(args, "kk", &n, &k)) 
        return NULL;

    // range check. n|k > LONG_MAX will wrap, so if a user inputs something
    // *really* big, well then technically, this could represented by a positive
    // number again, but presumably they'll trigger a MemoryError with that one
    if (0 >= k || 0 >= n) {
        char msg[75];
        sprintf(msg, "n and k must be in the range (0,%ld]", LONG_MAX);
        PyErr_SetString(PyExc_ValueError, msg);
        return NULL; 
    }
    else if (k > n) {
        PyErr_SetString(PyExc_ValueError, "Only n >= k is meaningful");
        return NULL;
    }
    else {
        result = _fast_combination(n, k);
    }
    // return a FPN. Decimal part somewhat meaningless, but caller responsible
    // for filetering this out, if need be.
    return Py_BuildValue("f", result);
}


static PyMethodDef FastCombinationMethods[] = {
     {"nCk", fast_combination, METH_VARARGS, "Compute a nCk combination \
        via the multuiplicative method"},
     {NULL, NULL, 0, NULL}
};


PyMODINIT_FUNC
initfast_combination(void) {
    (void) Py_InitModule("fast_combination", FastCombinationMethods);
} 
