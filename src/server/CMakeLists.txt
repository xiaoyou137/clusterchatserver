#设置编译源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)

#生成可执行文件
add_executable(ChatServer ${SRC_LIST} ${MODEL_LIST} ${REDIS_LIST})

#链接时依赖的库文件
target_link_libraries(ChatServer muduo_net muduo_base dbconnectionpool mysqlclient hiredis pthread)

