include_directories(include)
add_library(pwm include/pwm.h src/pwm.c)
target_include_directories(pwm PUBLIC include)
