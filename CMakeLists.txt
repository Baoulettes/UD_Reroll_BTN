cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "Reroll_hook")
set(DOKKAN_SDK_REV "r9")
set(PROJECT_LIBS dokkansdk)

#----------------------------------------------------------------------#
#=== DO NOT EDIT BELOW THIS LINE UNLESS YOU KNOW WHAT YOU ARE DOING ===#
#----------------------------------------------------------------------#
project(${PROJECT_NAME})
file(GLOB_RECURSE PROJECT_SRC "src/*.h" "src/*.cpp" "src/*.c")
get_filename_component(UD_SDK_ROOT "${CMAKE_SOURCE_DIR}/../.." REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
message(STATUS "UniDokkan SDK Root: ${UD_SDK_ROOT}")
add_subdirectory("${UD_SDK_ROOT}/dokkan-sdk-${DOKKAN_SDK_REV}" "${CMAKE_BINARY_DIR}/dokkan-sdk")
add_library(${PROJECT_NAME} SHARED ${PROJECT_SRC})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE_NAME:${PROJECT_NAME}>)