cmake_minimum_required(VERSION 2.6)

project(LambdaImageAdaptor)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

find_package(ITK REQUIRED ITKCommon ITKImageAdaptors)
include(${ITK_USE_FILE})

add_executable(LambdaImageAdaptor LambdaImageAdaptor.cpp)
target_link_libraries(LambdaImageAdaptor ${ITK_LIBRARIES})
add_custom_target(LambdaImageAdaptorSources SOURCES
itkLambdaImageAdaptor.h)
