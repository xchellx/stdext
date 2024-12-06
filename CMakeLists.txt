# stdext cmake list

cmake_minimum_required(VERSION 3.28, FATAL_ERROR)

project(stdext LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../extern/cmake-modules")

include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
git_describe(GIT_TAG --tags)
git_local_changes(GIT_LOCAL_CHANGES)

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/include/configure/stdext_version.h")
    configure_file("${PROJECT_SOURCE_DIR}/include/configure/stdext_version.h.in" "${PROJECT_SOURCE_DIR}/include/configure/stdext_version.h" @ONLY)
endif()

option(STDEXT_INCLUDE_ERROR_STRINGS "Include extended error strings within stdext." OFF)
option(STDEXT_CSLPRINTF_H_INLINE_CLANG "Inline functions in cslprintf.h using clang extensions." OFF)
option(STDEXT_CSLPRINTF_H_INLINE_GCC "Inline functions in cslprintf.h using gcc extensions." OFF)

option(STDEXT_STATIC "Build static library." ON)
if(STDEXT_STATIC)
    set(STDEXT_BUILD_TYPE STATIC)
    set(STDEXT_LINK_TYPE ARCHIVE)
else()
    set(STDEXT_BUILD_TYPE SHARED)
    set(STDEXT_LINK_TYPE LIBRARY)
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/include/configure/stdext_settings.h")
    configure_file("${PROJECT_SOURCE_DIR}/include/configure/stdext_settings.h.in" "${PROJECT_SOURCE_DIR}/include/configure/stdext_settings.h" @ONLY)
endif()

add_library(stdext ${STDEXT_BUILD_TYPE}
    ${PROJECT_SOURCE_DIR}/include/stdext.h
    
    ${PROJECT_SOURCE_DIR}/include/stdext/catexit.h
    ${PROJECT_SOURCE_DIR}/include/stdext/cbasename.h
    ${PROJECT_SOURCE_DIR}/include/stdext/cdata.h
    ${PROJECT_SOURCE_DIR}/include/stdext/cgetchar.h
    ${PROJECT_SOURCE_DIR}/include/stdext/cmacros.h
    ${PROJECT_SOURCE_DIR}/include/stdext/cmalloc.h
    ${PROJECT_SOURCE_DIR}/include/stdext/cmath.h
    ${PROJECT_SOURCE_DIR}/include/stdext/cslprintf.h
    ${PROJECT_SOURCE_DIR}/include/stdext/csprintf_s.h
    ${PROJECT_SOURCE_DIR}/include/stdext/cstat.h
    ${PROJECT_SOURCE_DIR}/include/stdext/cstrcmpi.h
    ${PROJECT_SOURCE_DIR}/include/stdext/cstrto_s.h
    
    ${PROJECT_SOURCE_DIR}/src/stdext/catexit.c
    ${PROJECT_SOURCE_DIR}/src/stdext/cbasename.c
    ${PROJECT_SOURCE_DIR}/src/stdext/cgetchar.c
    ${PROJECT_SOURCE_DIR}/src/stdext/cmalloc.c
    ${PROJECT_SOURCE_DIR}/src/stdext/cmath.c
    ${PROJECT_SOURCE_DIR}/src/stdext/cslprintf.c
    ${PROJECT_SOURCE_DIR}/src/stdext/csprintf_s.c
    ${PROJECT_SOURCE_DIR}/src/stdext/cstrto_s.c)

target_include_directories(stdext
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include)

target_compile_features(stdext
    PRIVATE
        c_std_99
        c_function_prototypes
        c_variadic_macros)

set_target_properties(stdext
    PROPERTIES
        C_STANDARD 99
        C_STANDARD_REQUIRED ON)

target_precompile_headers(stdext
    PUBLIC
        "$<$<COMPILE_LANGUAGE:C>:${PROJECT_SOURCE_DIR}/include/configure/stdext_version.h>"
        "$<$<COMPILE_LANGUAGE:C>:${PROJECT_SOURCE_DIR}/include/configure/stdext_settings.h>")

install(TARGETS stdext
    ${STDEXT_LINK_TYPE} DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
