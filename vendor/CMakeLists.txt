# Common
add_subdirectory(${PYRO_COMMON_DIR})


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
