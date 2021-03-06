cmake_minimum_required(VERSION 3.19)
project(emt-cpp LANGUAGES CXX VERSION 0.1.0)
message(STATUS "${PROJECT_NAME} VERSION ${CMAKE_PROJECT_VERSION}")

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cc)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# add_subdirectory(drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
# ##############################################################################

# Include libsodium
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(Drogon CONFIG REQUIRED)
find_package(Sodium REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE sodium)

if (CMAKE_CXX_STANDARD LESS 20)
    # With C++14, use boost to support any and string_view
    message(STATUS "USE C++14")
    find_package(Boost 1.61.0 REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
else ()
    message(STATUS "USE C++20")
endif ()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(exceptions EXCEPT_SRC)

#drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#        ${CMAKE_CURRENT_BINARY_DIR})

# use the following line to create views with namespaces.
drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views ${CMAKE_CURRENT_BINARY_DIR} TRUE)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME} PRIVATE ${SRC_DIR} ${CTL_SRC} ${FILTER_SRC} ${PLUGIN_SRC} ${MODEL_SRC} ${EXCEPT_SRC})

# ##############################################################################
# uncomment the following line for dynamically loading views 
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)
