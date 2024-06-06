cmake_minimum_required(VERSION 3.6)

project(proj_name)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#
# GLFW options
#
option (GLFW_INSTALL OFF)
option (GLFW_BUILD_DOCS OFF)
option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
add_subdirectory ("external/glfw")
add_definitions (-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")



####### FIND PACKAGES #########
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake/modules")

if(UNIX)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  find_package(OpenGL REQUIRED COMPONENTS OpenGL)
  set(LIBS X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype)
endif()

######## SOURCES ##############
#file(GLOB_RECURSE SOURCES "src/*.{cpp,c,cc,cxx}")
file(GLOB_RECURSE SOURCES "src/*.cpp")
list(APPEND SOURCES "external/glad.c")

######## MAIN TARGET ##############
set (MAIN_TARGET "main")
add_executable(${MAIN_TARGET} ${SOURCES})
set_target_properties(${MAIN_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

target_include_directories(${MAIN_TARGET} PUBLIC "include" "external/glfw/include")

#target_link_directories(${MAIN_TARGET} PUBLIC "libs")
target_link_libraries(${MAIN_TARGET} glfw ${LIBS} OpenGL::OpenGL)
