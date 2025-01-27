# Copyright (c) OpenMMLab. All rights reserved.

cmake_minimum_required(VERSION 3.14)
project(mmdeploy_python)

set(MMDEPLOY_PYTHON_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/common.cpp)

set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    add_subdirectory(${CMAKE_SOURCE_DIR}/../../../third_party/pybind11
            ${CMAKE_CURRENT_BINARY_DIR}/pybind11)
    find_package(MMDeploy REQUIRED)
elseif (NOT TARGET pybind11)
    add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/pybind11 pybind11)
endif ()

macro(mmdeploy_python_add_module name)
    if (TARGET mmdeploy_${name})
        list(APPEND MMDEPLOY_PYTHON_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/${name}.cpp)
    endif ()
endmacro()

mmdeploy_python_add_module(classifier)
mmdeploy_python_add_module(detector)
mmdeploy_python_add_module(segmentor)
mmdeploy_python_add_module(text_detector)
mmdeploy_python_add_module(text_recognizer)
mmdeploy_python_add_module(restorer)
mmdeploy_python_add_module(pose_detector)
mmdeploy_python_add_module(rotated_detector)

pybind11_add_module(${PROJECT_NAME} ${MMDEPLOY_PYTHON_SRCS})

mmdeploy_load_static(${PROJECT_NAME} MMDeployStaticModules)
mmdeploy_load_dynamic(${PROJECT_NAME} MMDeployDynamicModules)
target_link_libraries(${PROJECT_NAME} PRIVATE MMDeployLibs)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR})
