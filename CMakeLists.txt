cmake_minimum_required(VERSION 3.17)
project(genjson)

set(CMAKE_CXX_STANDARD 17)


file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/schema/include)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/schema/include/gen)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/schema/*.schema")
set(GENERATED_HEADERS "")
foreach(file ${files})

    # generate output header file name based on schema name
    string(REPLACE ".schema" ".h" output ${file})

    # extract only name with extension
    get_filename_component(output_name "${output}" NAME)

    # output_name_we used as unique namespace
    get_filename_component(output_name_we "${output}" NAME_WE)
    string (REPLACE " " "_" output_name_we "${output_name_we}")

    # absolute path to the generated header
    set(output_filepath ${CMAKE_CURRENT_SOURCE_DIR}/schema/include/gen/${output_name})

    # print info in the cmake log
    message(STATUS "Adding json ${file}")
    message(STATUS "Adding header ${output_filepath}")

    add_custom_command(
            OUTPUT  ${output_filepath}
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/quicktype_gen.sh "${file}" "${output_filepath}" "${output_name_we}"
            DEPENDS ${file}
    )

    # generate list of all generated headers
    list(APPEND GENERATED_HEADERS ${output_filepath})
endforeach()

add_executable(genjson main.cpp ${GENERATED_HEADERS})
target_include_directories(genjson PRIVATE
        ./schema/include
        ./lib)