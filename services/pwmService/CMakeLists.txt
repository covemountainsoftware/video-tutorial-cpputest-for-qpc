include_directories(include)
add_subdirectory(test)
add_library(pwmService include/pwmService.h src/pwmService.c)
target_link_libraries(pwmService pwm)
target_include_directories(pwmService PUBLIC include)

# TODO: setting up QP should probably be a higher level build option
add_compile_definitions(QACTIVE_CAN_STOP)
include_directories(${QP_CPP_INCLUDE_DIR})
include(${CMS_CMAKE_DIR}/qpcPosixPortCMakeSupport.cmake)
