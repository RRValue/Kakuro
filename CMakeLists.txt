cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED ENV{Qt6_DIR})
    message(FATAL, "Qt6_DIR not found")
else()
    set(CMAKE_PREFIX_PATH $ENV{Qt6_DIR})
endif()

set(PROJECT_BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(ProjectName Kakuro)
project(${ProjectName})

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find and assert external libs
find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui Widgets)

qt_standard_project_setup()

file(GLOB_RECURSE ComponentHeader ${CMAKE_CURRENT_SOURCE_DIR}/${ProjectName}/*.h)
file(GLOB_RECURSE ComponentSources ${CMAKE_CURRENT_SOURCE_DIR}/${ProjectName}/*.cpp)
file(GLOB_RECURSE ComponentUI ${CMAKE_CURRENT_SOURCE_DIR}/${ProjectName}/*.ui)

qt_add_executable(${ProjectName}
    ${ComponentHeader}
    ${ComponentSources}
    ${ComponentUI})

# internal includes
target_include_directories(${ProjectName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# external libs
target_link_libraries(${ProjectName}  PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# properties
if(MSVC)
    set_target_properties(${ProjectName} PROPERTIES PDB_OUTPUT_DIRECTORY ${PROJECT_BIN_PATH})
    set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_PATH})
endif(MSVC)

# copy qt dlls to debug/release
add_custom_command(
    TARGET ${ProjectName}
    POST_BUILD
    COMMAND
        CD $<$<CONFIG:Debug>:${PROJECT_BIN_PATH}/Debug>$<$<CONFIG:Release>:${PROJECT_BIN_PATH}/Release> && 
        ${WINDEPLOYQT_EXECUTABLE} ${ProjectName}.exe 
            --verbose 0 
            $<$<CONFIG:Debug>:--debug>$<$<CONFIG:Release>:--release> 
            --dir . 
            --plugindir plugins 
            --no-translations 
            --compiler-runtime 
            --pdb
    )

qt_finalize_project()