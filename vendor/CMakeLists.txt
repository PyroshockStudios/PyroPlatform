# Common

# Default path for PyroCommon if user does not provide one
if(NOT TARGET PyroCommon)
    find_package(PyroCommon CONFIG QUIET)
    if(NOT PyroCommon_FOUND)
        set(PYRO_COMMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/PyroCommon" CACHE PATH "Path to PyroCommon")
        if(NOT EXISTS "${PYRO_COMMON_DIR}/CMakeLists.txt")
            message(FATAL_ERROR "PyroCommon not found at ${PYRO_COMMON_DIR}")
        endif()
        set(PYRO_COMMON_BINARY_DIR "${CMAKE_BINARY_DIR}/PyroCommon")
        add_subdirectory(${PYRO_COMMON_DIR} ${PYRO_COMMON_BINARY_DIR})
    endif()
endif()

if (PYRO_PLATFORM_WINDOWING_GLFW)
    # glfw
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_BUILD_DOCS OFF)	
    # FIXME: should we always force X11 on linux, or make it configurable?
    if (UNIX AND NOT APPLE)
         find_package(X11 REQUIRED)
         set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
         set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
    endif()
    add_subdirectory(glfw)
endif()
