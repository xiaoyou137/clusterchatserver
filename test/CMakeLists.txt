#跳过cmake之前的检查
set(CMAKE_C_COMPILER_WORKS 1)
#要求cmake最低版本
cmake_minimum_required(VERSION 2.8.12.2)
#项目名称
project(demo)



#配置使用当前机器上最新gcc版本
set(CMAKE_C_COMPILER "/opt/rh/devtoolset-10/root/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-10/root/usr/bin/g++")

#设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2")
#设置使用的C++11版本
set(CMAKE_CXX_STANDARD 11)

#加载子目录
add_subdirectory(testmuduo)
add_subdirectory(testjson)