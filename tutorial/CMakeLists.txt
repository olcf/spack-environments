cmake_minimum_required (VERSION 3.15)
project (test1 CXX)

add_executable (test1 test_axpy.cc)

find_package (blaspp)
find_package (BLAS)
find_package (CBLAS)

#include( "CBLASConfig.cmake" )
#if (NOT blaspp_cblas_found)
#    message( WARNING "CBLAS not found; tester cannot be built." )
#    return()
#endif()

#message (" blaspp cblas libraries: ${blaspp_cblas_libraries}")
#message (" blas libraries: ${BLAS_LIBRARIES}")
#message (" cblas libraries: ${CBLAS_LIBRARIES}")
#target_link_libraries (test1 blaspp "${blaspp_cblas_libraries}")
#target_link_libraries (test1 blaspp cblas)
target_link_libraries (test1 blaspp ${BLAS_LIBRARIES} ${CBLAS_LIBRARIES})

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(test1 OpenMP::OpenMP_CXX)
endif()

target_compile_features (test1 PUBLIC cxx_std_11)

#find_path (cblas_found "cblas.h")
#message ("cblas.h found: ${cblas_found}")

#target_include_directories (test1 PUBLIC "${cblas_found}")
