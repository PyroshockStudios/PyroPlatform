# Common

# Default path for PyroCommon if user does not provide one
if(NOT TARGET PyroCommon)
    include(FetchContent)
    # find the package locally first
    find_package(PyroCommon CONFIG QUIET)
    # If not found, fetch it directly from repository
    if(NOT PyroCommon_FOUND)
        message(STATUS "PyroCommon not found locally. Fetching from GitHub...")
        FetchContent_Declare(
            PyroCommon
            GIT_REPOSITORY https://github.com/PyroshockStudios/PyroCommon.git
            GIT_TAG        master
        )
        FetchContent_MakeAvailable(PyroCommon)
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
