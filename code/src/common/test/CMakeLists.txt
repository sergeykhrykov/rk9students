cmake_minimum_required(VERSION 2.8.8)

set(PROJECT_NAME ${target})
project(${PROJECT_NAME} C CXX)

message(STATUS "Test: ${target}_test")

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread)
endif()

if(MSVC)
    #vc 2012 fix for vararg templates
    set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif() 

set(EXT_PROJECTS_DIR ${CMAKE_SOURCE_DIR}/src/_ext)
add_subdirectory(${EXT_PROJECTS_DIR}/gtest ${CMAKE_BINARY_DIR}/gtest)

#-------------------
# Test
#-------------------
add_definitions(${MSVC_COMPILER_DEFS})

enable_testing()

set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

set(TEST_SRC_FILES test.cpp)

add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})

set_target_properties(${PROJECT_TEST_NAME}
    PROPERTIES
    #${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)

include_directories(${GTEST_INCLUDE_DIRS} ${DEFAULT_INCLUDE_DIRECTORIES})

add_dependencies(${PROJECT_TEST_NAME} googletest)


if(NOT WIN32 OR MINGW)
    target_link_libraries(${PROJECT_TEST_NAME}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
        )
else()
    target_link_libraries(${PROJECT_TEST_NAME}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
    target_link_libraries(${PROJECT_TEST_NAME}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
endif()

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(${PROJECT_TEST_NAME}
    #PRIVATE
    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME}::common
)

add_test(test1 ${PROJECT_TEST_NAME})
