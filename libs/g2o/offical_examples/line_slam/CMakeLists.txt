# add_executable(line_test line_test.cpp)
# target_link_libraries(line_test types_slam3d_addons types_slam3d)
# set_target_properties(line_test PROPERTIES OUTPUT_NAME line_test${EXE_POSTFIX})

add_executable(simulator_3d_line simulator_3d_line.cpp)
target_link_libraries(simulator_3d_line g2o_solver_eigen g2o_types_slam3d_addons g2o_core g2o_stuff g2o_types_slam3d)
set_target_properties(simulator_3d_line PROPERTIES OUTPUT_NAME simulator_3d_line${EXE_POSTFIX})
