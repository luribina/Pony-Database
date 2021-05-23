add_subdirectory(commands)

set( ALL_SOURCE_FILES
        ${COMMANDS_SOURCEFILE}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Pony.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Invoker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileDatabase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileReader.cpp
        PARENT_SCOPE)