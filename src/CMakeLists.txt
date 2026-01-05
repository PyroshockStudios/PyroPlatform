set(SH_SRC ${CMAKE_CURRENT_SOURCE_DIR}/PyroPlatform)

set(ENDF6_SRC "") 

file(GLOB PLATFORM_ROOT_SRC
    "${SH_SRC}/*.hpp"
    "${SH_SRC}/*.cpp"
)
list(APPEND ENDF6_SRC ${PLATFORM_ROOT_SRC})

# ------------------------------
# Platform file sources
# ------------------------------
if(PYRO_PLATFORM_FILE)
    file(GLOB PLATFORM_FILE_INTERFACE
        "${SH_SRC}/File/*.hpp"
    )
    list(APPEND ENDF6_SRC ${PLATFORM_FILE_INTERFACE})
	if (NOT PYRO_PLATFORM_DUMMY_INTERFACE)
		file(GLOB_RECURSE PLATFORM_FILE_SRC
			"${SH_SRC}/File/Platforms/${PYRO_PLATFORM_DIRNAME}/*.hpp"
			"${SH_SRC}/File/Platforms/${PYRO_PLATFORM_DIRNAME}/*.cpp"
		)
		list(APPEND ENDF6_SRC ${PLATFORM_FILE_SRC})

		if(APPLE)
			file(GLOB_RECURSE PLATFORM_FILE_MM
				"${SH_SRC}/File/Platforms/${PYRO_PLATFORM_DIRNAME}/*.mm"
			)
			list(APPEND ENDF6_SRC ${PLATFORM_FILE_MM})
		endif()
		if(UNIX)
			file(GLOB_RECURSE PLATFORM_FILE_UNIX
				"${SH_SRC}/File/Platforms/Unix/*.hpp"
				"${SH_SRC}/File/Platforms/Unix/*.cpp"
			)
			list(APPEND ENDF6_SRC ${PLATFORM_FILE_UNIX})
		endif()
	endif()
endif()

# ------------------------------
# Platform time sources
# ------------------------------
if(PYRO_PLATFORM_TIME)
    file(GLOB PLATFORM_TIME_INTERFACE
        "${SH_SRC}/Time/*.hpp"
    )
    list(APPEND ENDF6_SRC ${PLATFORM_TIME_INTERFACE})
	
	if (NOT PYRO_PLATFORM_DUMMY_INTERFACE)
		file(GLOB_RECURSE PLATFORM_TIME_SRC
			"${SH_SRC}/Time/Platforms/${PYRO_PLATFORM_DIRNAME}/*.hpp"
			"${SH_SRC}/Time/Platforms/${PYRO_PLATFORM_DIRNAME}/*.cpp"
		)
		list(APPEND ENDF6_SRC ${PLATFORM_TIME_SRC})

		if(APPLE)
			file(GLOB_RECURSE PLATFORM_TIME_MM
				"${SH_SRC}/Time/Platforms/${PYRO_PLATFORM_DIRNAME}/*.mm"
			)
			list(APPEND ENDF6_SRC ${PLATFORM_TIME_MM})
		endif()
		if(UNIX)
			file(GLOB_RECURSE PLATFORM_TIME_UNIX
				"${SH_SRC}/Time/Platforms/Unix/*.hpp"
				"${SH_SRC}/Time/Platforms/Unix/*.cpp"
			)
			list(APPEND ENDF6_SRC ${PLATFORM_TIME_UNIX})
		endif()
	endif()
endif()

# ------------------------------
# Platform windowing sources
# ------------------------------
if(PYRO_PLATFORM_WINDOWING)
    file(GLOB PLATFORM_WINDOWING_INTERFACE
        "${SH_SRC}/Window/*.hpp"
    )
    list(APPEND ENDF6_SRC ${PLATFORM_WINDOWING_INTERFACE})
	
	file(GLOB_RECURSE PLATFORM_WINDOWING_INPUT_SRC
		"${SH_SRC}/Window/Input/*.hpp"
		"${SH_SRC}/Window/Input/*.cpp"
	)
	list(APPEND ENDF6_SRC ${PLATFORM_WINDOWING_INPUT_SRC})
		
	if (NOT PYRO_PLATFORM_DUMMY_INTERFACE)
		file(GLOB_RECURSE PLATFORM_WINDOW_SRC
			"${SH_SRC}/Window/Platforms/${PYRO_PLATFORM_WINDOWING_DIRNAME}/*.hpp"
			"${SH_SRC}/Window/Platforms/${PYRO_PLATFORM_WINDOWING_DIRNAME}/*.cpp"
		)
		list(APPEND ENDF6_SRC ${PLATFORM_WINDOW_SRC})

		if(APPLE)
			file(GLOB_RECURSE PLATFORM_WINDOW_MM
				"${SH_SRC}/Window/Platforms/${PYRO_PLATFORM_WINDOWING_DIRNAME}/*.mm"
			)
			list(APPEND ENDF6_SRC ${PLATFORM_WINDOW_MM})
		endif()
	endif()
endif()


if (PYRO_PLATFORM_SHARED_LIBRARY)
add_library(PyroPlatform SHARED ${ENDF6_SRC})
target_compile_definitions(PyroPlatform PUBLIC PYRO_PLATFORM_SHARED_LIBRARY=1)
else()
add_library(PyroPlatform STATIC ${ENDF6_SRC})
endif()
add_library(PyroPlatform::PyroPlatform ALIAS PyroPlatform)


if (PYRO_PLATFORM_FILE) 
target_compile_definitions(PyroPlatform PUBLIC PYRO_PLATFORM_FILE=1)
endif()
if (PYRO_PLATFORM_TIME) 
target_compile_definitions(PyroPlatform PUBLIC PYRO_PLATFORM_TIME=1)
endif()
if (PYRO_PLATFORM_WINDOWING) 
target_compile_definitions(PyroPlatform PUBLIC PYRO_PLATFORM_WINDOWING=1)
endif()


foreach(_source IN ITEMS ${ENDF6_SRC})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${SH_SRC}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

target_include_directories(PyroPlatform
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/PyroPlatform/..>
        $<INSTALL_INTERFACE:include>
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include/PyroPlatform
    FILES_MATCHING PATTERN "*.hpp"
)

target_compile_features(PyroPlatform PRIVATE cxx_std_23)

target_link_libraries(PyroPlatform PUBLIC PyroCommon::PyroCommon)

if (PYRO_PLATFORM_WINDOWING_GLFW)
	target_link_libraries(PyroPlatform PUBLIC glfw)
endif()


if(UNIX AND NOT APPLE)
    target_link_libraries(PyroPlatform PRIVATE dl)
elseif(APPLE)
    # macOS has dlopen/dlsym in libc, so typically we need to link libdl
    # target_link_libraries(PyroPlatform PRIVATE dl)
endif()

# windows cope
set_target_properties(PyroPlatform PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS YES)
set_target_properties(PyroPlatform PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

