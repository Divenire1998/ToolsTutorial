add_executable(optimize_sphere_by_sim3
  optimize_sphere_by_sim3.cpp
)

set_target_properties(optimize_sphere_by_sim3 PROPERTIES OUTPUT_NAME optimize_sphere_by_sim3${EXE_POSTFIX})
target_link_libraries(optimize_sphere_by_sim3 g2o_core g2o_types_slam3d g2o_types_sim3 g2o_stuff)
