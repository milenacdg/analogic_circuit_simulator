##################
# Header section #
##################

file(GLOB headers crt*.hpp)
install(FILES ${headers} DESTINATION include/${CMAKE_PROJECT_NAME})

###################
# Library section #
###################

file(GLOB libfiles crt*.cpp)
add_library(crt SHARED ${libfiles})

# target_include_directories(crt PUBLIC ${EIGEN3_INCLUDE_DIRS})
target_include_directories(crt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(crt PUBLIC ${EIGEN3_LIBRARIES})

install(TARGETS crt DESTINATION lib)

######################
# Executable section #
######################

#add_executable(translator translate.cpp)

#target_include_directories(translator PUBLIC ${EIGEN3_INCLUDE_DIRS})
#target_include_directories(translator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(translator PUBLIC crt)

#install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/translator 
#        RENAME ${CMAKE_PROJECT_NAME}-translator 
#        DESTINATION bin 
#        COMPONENT binary)
