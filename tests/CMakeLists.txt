enable_testing()

file (GLOB sources *.cc)

foreach(ccfile ${sources})
  get_filename_component(file ${ccfile} NAME_WE)
  add_executable(${file} ${ccfile})
  add_test(${file} ${file})
endforeach()
