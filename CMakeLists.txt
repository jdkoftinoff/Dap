cmake_minimum_required (VERSION 2.8)
set(PROJECT jdksdap)

enable_testing()

INCLUDE (CPack)
INCLUDE (CTest)

INCLUDE (common.cmake)

set(CMAKE_BUILD_TYPE "Debug")

SET(CPACK_GENERATOR "TGZ")

