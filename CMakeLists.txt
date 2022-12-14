cmake_minimum_required(VERSION 3.24 FATAL_ERROR)


PROJECT("matrixAverage" C)

OPTION(BUILD_WITH_OPENMP "Build with OPENMP" OFF)
IF(BUILD_WITH_OPENMP)
# to set the /openmp switch
find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
ENDIF(BUILD_WITH_OPENMP)


SET(matrixAverage-src 
matrixAverage.c
)

SET(matrixAverage-header
)

ADD_EXECUTABLE(
    matrixAverage
${matrixAverage-src} 
${matrixAverage-header}
)

IF(BUILD_WITH_OPENMP)
set_target_properties(matrixAverage PROPERTIES OUTPUT_NAME "matrixAverage_omp")
ENDIF(BUILD_WITH_OPENMP)