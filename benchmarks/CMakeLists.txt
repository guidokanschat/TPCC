enable_testing()

file (GLOB sources *.cc)

foreach(ccfile ${sources})
  get_filename_component(file ${ccfile} NAME_WE)
  add_executable(${file} ${ccfile})
  set_target_properties(${file} PROPERTIES COMPILE_FLAGS "-O3 -save-temps")
  add_test(${file} ${file})
endforeach()
