// from lapack_wrappers.hh
template < typename TX > inline
void lapack_larnv( int64_t idist, int iseed[4], int64_t size, TX *x )
{
    for (int64_t i = 0; i < size; ++i) {
        x[i] = rand() / TX ( RAND_MAX );
    }
}

template < typename TX > inline
void lapack_larnv( int64_t idist, int iseed[4], int64_t size, std::complex <TX> *x )
{
    for (int64_t i = 0; i < size; ++i) {
        x[i] = std::complex <TX>( rand() / TX ( RAND_MAX ), rand() / TX ( RAND_MAX ));
    }
}

// from cblas_wrappers.hh
inline void
cblas_axpy(
    int n, float alpha,
    float const *x, int incx,
    float*       y, int incy )
{
    cblas_saxpy( n, alpha, x, incx, y, incy );
}

inline void
cblas_axpy(
    int n, double alpha,
    double const *x, int incx,
    double*       y, int incy )
{
    cblas_daxpy( n, alpha, x, incx, y, incy );
}

inline void
cblas_axpy(
    int n, std::complex<float> alpha,
    std::complex<float> const *x, int incx,
    std::complex<float>*       y, int incy )
{
    cblas_caxpy( n, &alpha, x, incx, y, incy );
}

inline void
cblas_axpy(
    int n, std::complex<double> alpha,
    std::complex<double> const *x, int incx,
    std::complex<double>*       y, int incy )
{
    cblas_zaxpy( n, &alpha, x, incx, y, incy );
}

// -----------------------------------------------------------------------------
inline void
cblas_copy(
    int n,
    float const *x, int incx,
    float*       y, int incy )
{
    cblas_scopy( n, x, incx, y, incy );
}

inline void
cblas_copy(
    int n,
    double const *x, int incx,
    double*       y, int incy )
{
    cblas_dcopy( n, x, incx, y, incy );
}

inline void
cblas_copy(
    int n,
    std::complex<float> const *x, int incx,
    std::complex<float>*       y, int incy )
{
    cblas_ccopy( n, x, incx, y, incy );
}

inline void
cblas_copy(
    int n,
    std::complex<double> const *x, int incx,
    std::complex<double>*       y, int incy )
{
    cblas_zcopy( n, x, incx, y, incy );
}
