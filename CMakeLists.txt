cmake_minimum_required (VERSION 2.8)
set(PROJECT jdks)

enable_testing()

INCLUDE (CPack)
INCLUDE (CTest)

INCLUDE (common.cmake)

set(CMAKE_BUILD_TYPE "Debug")

if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake|MSBuild)")
else()
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
endif()

SET(CPACK_GENERATOR "TGZ")

