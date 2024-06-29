# chatserver文档

# clusterchatserver

基于muduo网络库实现的集群聊天服务器

**分支version-0.1.0**：未使用数据库连接池版本

# 使用说明

运行 [autobuild.sh](https://github.com/xiaoyou137/clusterchatserver/blob/version-0.1.0/autobuild.sh) ，可执行文件生成在bin目录下

# 功能设计实现

- chatserver.cpp & hpp：网络I/O模块，负责调用muduo网络库接口。
- chatservice.cpp & hpp：网络服务模块，将各个网络服务与消息类型id一一映射。
- model文件夹下的cpp & hpp: 数据库chat中的各个table对应的ORM操作类，封装了对各个表的操作，用来分离业务层和数据库层代码
- db.cpp 和 db.hpp：数据库mysql操作封装
- redis.cpp & hpp：利用redis发布-订阅功能，充当服务器之间的消息队列，用于跨服务器通信。

## chatserver聊天服务器主要包含以下功能点：

- 网络I/O使用muduo网络库，muduo提供了epoll+I/O多路复用+线程池，和one loop per thread+主从reactor模型，实现了高并发I/O服务。

![image text](https://github.com/xiaoyou137/groceries-repo/blob/main/pics/muduo-reactor-model.png)

- 使用json进行消息的序列化与反序列化。
- 使用cmake构建项目编译环境。
- 使用mysql数据库作为落地存储。
- 使用nginx的反向代理和tcp负载均衡，对聊天服务器集群部署。
- 使用redis订阅发布功能作为服务器间通信的消息对垒，hiredis进行redis客户端编程。

# 关键技术点

muduo网络库编程、mysql数据库编程、hiredis编程、json序列化与反序列化、C++11多线程编程、线程互斥、unordered_map关联容器、观察者模式、单例模式
