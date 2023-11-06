cmake_minimum_required (VERSION 2.8.11)
project(roam_apps)

# Find the OpenCV library
find_package(OpenCV REQUIRED)

# include directories 
include_directories(${OpenCV_INCLUDE_DIRS})

#--------------------------------------------------------------------------
# roam executables
#--------------------------------------------------------------------------
add_executable(roam_cli main_single_mask.cpp main_utils.cpp)
target_link_libraries(roam_cli ${OpenCV_LIBS} roam_lib cv_tools_lib om_utils)
set_target_properties(roam_cli PROPERTIES DEBUG_POSTFIX _d)

# The following command will generate a list of runtime dependencies
# for the target 'roam_cli'
install(CODE [[
    file(GET_RUNTIME_DEPENDENCIES
        LIBRARIES $<TARGET_FILE:roam_cli>
        RESOLVED_DEPENDENCIES_VAR _r_deps
        UNRESOLVED_DEPENDENCIES_VAR _u_deps
        DIRECTORIES $<TARGET_FILE_DIR:roam_cli>
        PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
        POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
    )
    foreach(_file ${_r_deps})
        file(INSTALL
            DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
            TYPE SHARED_LIBRARY
            FOLLOW_SYMLINK_CHAIN
            FILES "${_file}"
        )
    endforeach()
    if(_u_deps)
        message(WARNING "Unresolved dependencies detected: ${_u_deps}")
    endif()
]])

# Make sure to set the install directory
install(TARGETS roam_cli RUNTIME DESTINATION bin)


add_executable(draw_contours draw_contours.cpp main_utils.cpp)
target_link_libraries(draw_contours ${OpenCV_LIBS} roam_lib cv_tools_lib om_utils)
set_target_properties(draw_contours PROPERTIES DEBUG_POSTFIX _d)

#--------------------------------------------------------------------------
# roam evaluation
#--------------------------------------------------------------------------
add_executable(eval_overall eval_overall.cpp main_utils.cpp)
target_link_libraries(eval_overall ${OpenCV_LIBS})
set_target_properties(eval_overall PROPERTIES DEBUG_POSTFIX _d)

add_executable(eval_perframe eval_perframe.cpp main_utils.cpp)
target_link_libraries(eval_perframe ${OpenCV_LIBS})
set_target_properties(eval_perframe PROPERTIES DEBUG_POSTFIX _d)