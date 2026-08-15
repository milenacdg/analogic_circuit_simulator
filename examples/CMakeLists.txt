file(GLOB usage_examples ex-*.cpp)




foreach(f ${usage_examples})
  get_filename_component(the_example ${f} NAME_WE) 
  add_executable(${the_example} ${f}) 
  
  
  target_include_directories(${the_example} PUBLIC ${CMAKE_SOURCE_DIR}/src)

  target_link_libraries(${the_example} PUBLIC crt)

  set_target_properties     (${the_example} PROPERTIES COMPILE_FLAGS   "${PROJECT_CFLAGS} -Wall")

  
  install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${the_example} 
          DESTINATION bin 
          RENAME ${CMAKE_PROJECT_NAME}-${the_example})
endforeach(f)
