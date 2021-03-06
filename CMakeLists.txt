cmake_minimum_required(VERSION 3.13.0)
cmake_policy(SET CMP0079 NEW)
cmake_policy(SET CMP0077 NEW)
project(oic)

# User options

set(APP_NAME Osomi\ Core)
set(APP_PACKAGE Osomi_Core)
set(IS_GAME true)
set(APP_VERSION 1.0) 

# Default options

add_definitions(-D__PROJECT_NAME__="${APP_NAME}")

set(HOME_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Enable multi processor compilation. Use C++ standard and enable all warnings (except nameless structs)
if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /MP /W4 /permissive- /wd4201 /EHsc")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd /MP /W4 /permissive- /wd4201 /EHsc")
endif()

# No console option

option(no_console "no_console" OFF)

if(no_console)
	add_definitions(-D__NO_CONSOLE__)
	message ("-- Console - disabled")
else()
	message ("-- Console - enabled")
endif()

# Android

option(Android "Android" OFF)
option(VR "VR" OFF)

if(Android)

	if(DEFINED ENV{ANDROID_NDK})

		message("-- Android - enabled")
	
		set(ANDROID_NDK, $ENV{ANDROID_NDK})
	
		include_directories(${ANDROID_SYSROOT}/usr/include)
		include_directories(${ANDROID_NDK}/sources/android/native_app_glue)
	
		set(CMAKE_VERBOSE_MAKEFILE 0)
	
		set(Vulkan ON)
		set(Desktop OFF)
		add_definitions(-D__PHONE__)
		
		link_libraries(android)
	
	else()
	
		message(FATAL_ERROR "-- Android - disabled: please set ANDROID_NDK in system variables!")
	
	endif()

elseif(WIN32)

	set(Vulkan ON)
	add_definitions(-D__DESKTOP__)
	add_definitions(-D__WINDOWS__)
	set(Windows ON)
	set(Desktop ON)
	
	option(Raytracing "Raytracing" ON)
		
	link_libraries(Xinput9_1_0.lib)

else()

endif()

if(Raytracing)
	add_definitions(-D__RAYTRACING__)
	message("-- Raytracing - enabled")
endif()

if(VR)
	add_definitions(-D__VR__)
	message("-- VR support - enabled")
endif()

if(Vulkan)
	add_definitions(-D__VULKAN__)
	message("-- Vulkan - enabled")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(-D__DEBUG__)
	message("-- Debug - enabled")
endif()

# dependencies
add_subdirectory(deps)
	
# ocore
add_subdirectory(ostlc)
add_subdirectory(owc)

add_subdirectory(ogc)
set_property(TARGET ostlc owc ogc PROPERTY FOLDER ocore)

# desktop conversion tools
add_subdirectory(oibaker)
set_property(TARGET oibaker PROPERTY FOLDER tools)

# app projects
add_subdirectory(app)
set_property(TARGET app PROPERTY FOLDER application)

if(Windows)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT app_windows)
endif()
