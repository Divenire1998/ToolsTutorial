add_library(tutorial_slam2d_library SHARED 
  edge_se2_pointxy.cpp  se2.h                vertex_point_xy.h
  edge_se2.cpp    edge_se2_pointxy.h    vertex_se2.cpp
  edge_se2.h      vertex_point_xy.cpp  vertex_se2.h
  parameter_se2_offset.h parameter_se2_offset.cpp
  types_tutorial_slam2d.h types_tutorial_slam2d.cpp
  simulator.h simulator.cpp
  g2o_tutorial_slam2d_api.h
)

set_target_properties(tutorial_slam2d_library PROPERTIES OUTPUT_NAME ${LIB_PREFIX}tutorial_slam2d)

target_link_libraries(tutorial_slam2d_library g2o_core g2o_solver_eigen g2o_types_sba g2o_stuff)

add_executable(tutorial_slam2d tutorial_slam2d.cpp)

# set_target_properties(tutorial_slam2d PROPERTIES OUTPUT_NAME tutorial_slam2d${EXE_POSTFIX})

target_link_libraries(tutorial_slam2d tutorial_slam2d_library)
