
#设置编译源文件列表
set(SRC_LIST ./test.cpp)

#设置可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置可行文件名，依赖源文件
add_executable(server ${SRC_LIST})

#设置包含头文件路径
#include_directories()

#设置库文件搜索路径
#link_directories()

#设置链接库文件
target_link_libraries(server muduo_net muduo_base pthread)


