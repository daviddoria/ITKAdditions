cmake_minimum_required(VERSION 2.6)

PROJECT(NormImageAdaptor)

FIND_PACKAGE(ITK REQUIRED ITKCommon ITKImageAdaptors)
INCLUDE(${USE_ITK_FILE})

ADD_EXECUTABLE(NormImageAdaptor TestNormImageAdaptor.cpp)
TARGET_LINK_LIBRARIES(NormImageAdaptor ${ITK_LIBRARIES})
