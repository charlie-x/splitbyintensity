cmake_minimum_required (VERSION 3.23)

if(APPLE)
set(VCPKG_HOST_TRIPLET "x64-osx" CACHE STRING "") 
endif()

project(splitbyintensity)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

message(STATUS "Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# Automatically locate and include vcpkg manifest dependencies
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg.json")
  set(VCPKG_MANIFEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
  set(VCPKG_FEATURE_FLAGS "manifests")
endif()

add_executable(${PROJECT_NAME}
    splitbyintensity.cpp
   
)

set(OpenCV_STATIC ON)

find_package(OpenCV REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE OpenCV::OpenCV)
#target_link_libraries(${PROJECT_NAME} PRIVATE opencv_world )
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

include_directories( ${OpenCV_INCLUDE_DIRS} )
