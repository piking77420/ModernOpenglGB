cmake_minimum_required(VERSION 3.10)

project(ModernOpenglGB)




set(CMAKE_CXX_STANDARD 23)
set(SOURCE_DIRECTORY "source/src")
set(INCLUDE_DIRECTORY "source/include")

file(GLOB_RECURSE HEADER_FILES "${INCLUDE_DIRECTORY}/*.h" "${INCLUDE_DIRECTORY}/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIRECTORY}/*.cpp" "${SOURCE_DIRECTORY}/*.c")

include_directories("${INCLUDE_DIRECTORY}")
include_directories("${INCLUDE_DIRECTORY}/Core")
include_directories("${INCLUDE_DIRECTORY}/Core/DataStructure/")
include_directories("${INCLUDE_DIRECTORY}/Core/Debug/Imgui/")
include_directories("${INCLUDE_DIRECTORY}/Core/DataStructure/Component/")
include_directories("${INCLUDE_DIRECTORY}/External")
include_directories("${INCLUDE_DIRECTORY}/Core/Math/")
include_directories("${INCLUDE_DIRECTORY}/LowRenderer")
include_directories("${INCLUDE_DIRECTORY}/Physics")
include_directories("${INCLUDE_DIRECTORY}/Ressources")
include_directories("${SOURCE_FILES}/External")

add_executable(ModernOpenglGB ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(ModernOpenglGB "${CMAKE_SOURCE_DIR}/source/src/External/lib/glfw3.lib")
