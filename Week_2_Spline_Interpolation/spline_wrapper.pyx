# spline_wrapper.pyx
import numpy as np  # Add this line
cimport numpy as np

cdef extern from "spline.c":
    void spline(double *x, double *y, int n, double yp1, double ypn, double *y2, double *u)
    void splint(double *xa, double *ya, double *y2a, int n, double x, double *y)

def calculate_spline(np.ndarray[np.float64_t, ndim=1] x, np.ndarray[np.float64_t, ndim=1] y, double yp1, double ypn):
    cdef int n = x.shape[0]
    cdef np.ndarray[np.float64_t, ndim=1] y2 = np.zeros(n, dtype=np.float64)
    cdef np.ndarray[np.float64_t, ndim=1] u = np.zeros(n, dtype=np.float64)
    spline(&x[0], &y[0], n, yp1, ypn, &y2[0], &u[0])
    return y2

def evaluate_spline(np.ndarray[np.float64_t, ndim=1] xa, np.ndarray[np.float64_t, ndim=1] ya, np.ndarray[np.float64_t, ndim=1] y2a, double x):
    cdef double y
    splint(&xa[0], &ya[0], &y2a[0], xa.shape[0], x, &y)
    return y
