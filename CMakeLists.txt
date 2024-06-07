cmake_minimum_required(VERSION 3.6)

project("proj_name")

##########################
####### COMPILER #########
##########################
# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG)
endif()
###############################
########## PACKAGES ###########
###############################
###GLFW###
# GLFW BUILD options
option (GLFW_INSTALL OFF)
option (GLFW_BUILD_DOCS OFF)
option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
add_subdirectory ("external/glfw")  # <-- BUILDS GLFW
add_definitions (-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake/modules")
if(UNIX)
  find_package(OpenGL REQUIRED COMPONENTS OpenGL)
  set(LIBS X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype)
endif()

###imgui###
file(GLOB IMGUI_SOURCES "external/imgui/*.cpp")
list(APPEND IMGUI_SOURCES "external/imgui/backends/imgui_impl_glfw.cpp")
list(APPEND IMGUI_SOURCES "external/imgui/backends/imgui_impl_opengl3.cpp")
list(APPEND IMGUI_SOURCES "external/imgui/misc/cpp/imgui_stdlib.cpp")
list(APPEND IMGUI_SOURCES "external/imgui/misc/debuggers/imgui.natvis" "external/imgui/misc/debuggers/imgui.natstepfilter")

###############################
######## SOURCES ##############
###############################
#file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.{cpp,c,cc,cxx}")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

###################################
######## MAIN TARGET ##############
###################################
set (MAIN_TARGET "main")
add_executable(${MAIN_TARGET} ${SOURCES} "external/glad.c" ${IMGUI_SOURCES} "external/eigen.natvis" "external/stb_image.cpp" )
set_target_properties(${MAIN_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
######### INCLUDES ##########
target_include_directories(${MAIN_TARGET} PUBLIC "include" 
"external/glfw/include" "external/imgui" "external/imgui/backends" "external/imgui/misc/cpp")

target_link_libraries(${MAIN_TARGET} glfw ${LIBS} OpenGL::OpenGL)

###############################
######### RESOURCES DIR ###########
###############################
# Configure a header file to pass the assets directory to the source code
set(RESOURCES_DIR "resources")
configure_file("${PROJECT_SOURCE_DIR}/config/PathConfig.h.in" "${CMAKE_BINARY_DIR}/config/PathConfig.h")
target_include_directories(${MAIN_TARGET} PUBLIC "${CMAKE_BINARY_DIR}/config")
