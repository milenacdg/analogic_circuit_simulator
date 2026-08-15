
add_subdirectory(rapport)
add_subdirectory(presentation)

add_custom_target(pdfs)
add_dependencies(pdfs pres rapp)

add_custom_target(f-pdfs)
add_dependencies(f-pdfs final-pres final-rapp)