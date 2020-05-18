cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR})

aux_source_directory(${CMAKE_SOURCE_DIR}/core/src CORE_SRC_LIST)

add_library(sonix-ae STATIC IMPORTED )
set_target_properties(sonix-ae PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libSonixCamera.a")

aux_source_directory(${CMAKE_SOURCE_DIR}/src SONIX_SRC_LIST)


add_library( # Specifies the name of the library.
        sonix-jni

        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).

        ${SONIX_SRC_LIST}
        sonix_face_ae_jni.cpp
        )

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log )

target_link_libraries(sonix-jni sonix-ae ${log-lib})