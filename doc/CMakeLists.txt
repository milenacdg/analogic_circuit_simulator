find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
   message("Doxygen not found, I will not generate/install the documentation")
else()
   configure_file(Doxyfile.in Doxyfile) 
					
   set(DOC_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/${CMAKE_PROJECT_NAME})
   set(APIDOC_DIR      ${CMAKE_CURRENT_BINARY_DIR}/html)
   set(DOXYGEN_INPUT   ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
   set(DOXYGEN_OUTPUT  ${APIDOC_DIR}/index.html)

   add_custom_command(
     OUTPUT            ${DOXYGEN_OUTPUT}
     COMMAND           ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
     COMMAND           ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
     COMMAND           ${CMAKE_COMMAND} -E echo "Done."
     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
     DEPENDS           ${DOXYGEN_INPUT}
  )

  add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})

  install(DIRECTORY   ${APIDOC_DIR}
          DESTINATION ${DOC_INSTALL_DIR}
          COMPONENT devel)
endif()