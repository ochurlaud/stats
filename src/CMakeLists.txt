# Source files
list(APPEND SRCS keyboardlog.cpp)
list(APPEND SRCS main.cpp)

include_directories(".")
add_executable(${EXECUTABLE_NAME} ${SRCS} ${RSRCS_RCC} ${FORMS_MOC})

