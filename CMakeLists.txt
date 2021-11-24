cmake_minimum_required(VERSION 3.16.3)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(os_project C)

add_executable(decoder decoder.c)
add_executable(finder finder.c)
add_executable(placer placer.c)
add_executable(main main.c)

