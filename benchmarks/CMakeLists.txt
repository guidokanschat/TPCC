enable_testing()

file (GLOB sources *.cc)

foreach(ccfile ${sources})
  get_filename_component(file ${ccfile} NAME_WE)
  add_executable(benchmark_${file} ${ccfile})
  set_target_properties(benchmark_${file} PROPERTIES
    OUTPUT_NAME ${file}
    COMPILE_FLAGS "-O3 -save-temps")
  add_test(NAME benchmark_${file}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/check.py ${file}.s 3)
endforeach()
