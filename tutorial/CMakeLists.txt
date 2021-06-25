cmake_minimum_required (VERSION 3.15)
project (test1 CXX)

add_executable (test1 test_axpy.cc)

find_package (blaspp)
find_package (BLAS)
find_package (CBLAS)

target_link_libraries (test1 blaspp ${BLAS_LIBRARIES} ${CBLAS_LIBRARIES})

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(test1 OpenMP::OpenMP_CXX)
endif()

target_compile_features (test1 PUBLIC cxx_std_11)
