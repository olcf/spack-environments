#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <complex>

#include "cblas.h"

#include "util.hh"
#include "blas.hh"
#include "print_matrix.hh"

// from run_tests.py
//     [ 'axpy',  dtype      + n + incx + incy ],

int main () {
    //typedef scalar_type<double, double> scalar_t;
    //typedef real_type<scalar_t> real_t;
    typedef long long lld;

    double alpha    = 1.0;
    int64_t n       = 20;
    int64_t incx    = 1;
    int64_t incy    = 1;
//    int64_t verbose = 0;

    int64_t size_x = 20;
    int64_t size_y = 20;

    size_t size_xx = (n - 1) * std::abs(incx) + 1;
    size_t size_yy = (n - 1) * std::abs(incy) + 1;
    double* x      = new double[ size_xx ];
    double* y      = new double[ size_yy ];
    double* yref   = new double[ size_yy ];
    //yref = y;
    double* y0     = new double[ size_yy ];
    //y0 = y;

    int64_t idist = 1;
    int iseed[4] = { 0, 0, 0, 1 };
    lapack_larnv( idist, iseed, size_x, x );
    lapack_larnv( idist, iseed, size_y, y );
    cblas_copy( n, y, incy, yref, incy );
    cblas_copy( n, y, incy, y0,   incy );

    //print_vector (n, x, incx);
    //print_vector (n, y, incx);
    //print_vector (n, yref, incx);

    blas::axpy( n, alpha, x, incx, y, incy );
    cblas_axpy( n, alpha, x, incx, yref, incy );

    //print_vector (n, x, incx);
    print_vector (n, y, incx);
    // force error
    //yref[5] += 0.0005;
    print_vector (n, yref, incx);

    double error = 0;
    int64_t ix = (incx > 0 ? 0 : (-n + 1)*incx);
    int64_t iy = (incy > 0 ? 0 : (-n + 1)*incy);


    // Error check
    for (int64_t i = 0; i<n; ++i) {
        y[iy] = std::abs( y[iy] - yref[iy] ) / (2*(std::abs( alpha * x[ix] ) + std::abs( y0[iy] )));
        //if (i==5) {
        if (i==-1) {
            printf ("x[5]: %.8f\n", x[ix]);
            printf ("y[5]: %.8f\n", y[iy]);
            printf ("y0[5]: %.8f\n", y0[iy]);
            printf ("yref[5]: %.8f\n", yref[iy]);

        }
        error = std::max( error, std::real( y[iy] ) );
        ix += incx;
        iy += incy;
    }

    printf ("error: %.8f\n", error);
}
