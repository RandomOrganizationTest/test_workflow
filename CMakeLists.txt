cmake_minimum_required(VERSION 3.18)

project(test_workflow)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/commonoptions.cmake)
conan_basic_setup()

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
include_directories(BEFORE SYSTEM ${CONAN_INCLUDE_DIRS_BOOST})
include_directories(BEFORE SYSTEM ${CONAN_INCLUDE_DIRS_RAPIDJSON})

add_library(${PROJECT_NAME}-static STATIC ${CMAKE_SOURCE_DIR}/src/test_workflow.cpp)
target_link_libraries(${PROJECT_NAME}-static ${CONAN_LIBS})

add_library(${PROJECT_NAME} SHARED ${CMAKE_SOURCE_DIR}/src/test_workflow.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-static ${CONAN_LIBS})

enable_testing()

add_executable(unit_test ${CMAKE_SOURCE_DIR}/src/unit_test/main.cpp)
target_link_libraries(unit_test test_workflow ${CONAN_LIBS})
add_test(NAME unit_test
    COMMAND ${CMAKE_BINARY_DIR}/bin/unit_test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})