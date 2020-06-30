cmake_minimum_required(VERSION 3.2)

# source files
set(SRC_FILES ${SRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ClassFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EvGen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EvGenClass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EvGenStateMachine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pushthread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE)
