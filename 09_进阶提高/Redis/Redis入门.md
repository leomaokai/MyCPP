# NoSQL

什么是NoSQL?

* NoSQL为非关系型数据库,数据之间是无联系,无关系,数据的结构是松散的,可变的

传统关系数据库的瓶颈:

* 无法处理大量集中的高并发操作
* 表中存储数量有限
* 无法简单地通过硬件,服务节点来提高系统性能
* 软件和硬件的成本较大

NoSQL的优势:

* 大数据量,高性能
* 灵活的数据模型
* 高可用
* 低成本

NoSQL的劣势:

* 无关系,数据之间无联系
* 没有公认的标准
* 没有关系型数据库的约束,没有索引的概念
* 没有事务
* 没有丰富的数据类型

# 基本操作

Redis是基于KV结构的作为缓存使用的NoSQL数据库,可以减轻对数据库的查询压力

[基本命令](../../04_基础工具/redis.md)

# 对象

## 对象的类型与编码

每个对象由一个`redisObject`结构表示

```c
typedef struct redisObject{
    unsigned type:4;//类型
    unsigned encoding:4;//编码
    void *ptr;//指向底层实现数据结构的指针
    ...
}
```

键总是一个字符串对象,而值可以是五种类型对象

五大类型:通过`type`命令返回键对应的值对象的类型

* string,字符串对象
* list,列表对象
* hash,哈希对象
* set,集合对象
* zset,有序集合对象

  每种类型至少使用了两种不同的编码(底层实现),通过`OBJECT ENCODING`命令输出对象得编码

```
* string
  * int(整数值),embstr(embstr编码实现的简单动态字符串),raw(简单动态字符串)
* list
  * ziplist(压缩列表),linkedlist(双端列表)
* hash
  * ziplist(压缩列表),hashtable(字典)
* set
  * intset(整数集合),hashtable(字典)
* zset
  * ziplist(压缩列表),skiplist(跳表)
```

通过`encoding`属性来设定对象所使用的编码,而不是为特定类型的对象关联一种固定的编码,根据不同的使用场景来为一个对象设置不同的编码,从而优化对象在某一场景下的效率,极大的提升了redis的灵活性和效率

## string

字符串对象的编码可以是int,embstr,raw

* 如果一个字符串对象保存的是整数值,并且这个整数值可以用long类型来表示,那么字符串对象的编码为int
* 如果字符串对象保存一个字符串值,并且字符串值得长度小于等于39字节,那么字符串对象使用embstr编码得方式来保存这个字符串值,否则,使用raw编码

![](img\string01.png)

![](img\string02.png)

![](img\string03.png)

在执行append命令后,对象得编号从embstr转换成raw

![](img\string04.png)

## list

列表的编码有ziplist和linkedlist

* ziplist编码的对象使用压缩列表作为底层,每个压缩列表结点有一个列表元素
* linkedlist编码的列表对象使用双端列表作为底层实现,每个双端链表结点都保存了一个字符串对象,而每个字符串对象都保存了一个列表元素

当列表同时满足以下两个条件时,使用ziplist编码,否则使用linkedlist

* 列表对象保存得所有字符串元素得长度都小于64字节
* 列表保存得元素数量小于512

## hash

哈希的编码可以是ziplist和hashtable 

* ziplist编码的哈希对象使用压缩列表作为底层实现,每当有新的键值对要加入到哈希对象时,先将键推入到列表表尾,再将值推入到列表表尾
* hashtable编码的哈希对象使用字典作为底层实现,哈希对象对象中的每个键值对都使用一个字典键值对来保存

当哈希对象可以同时满足以下两个条件时,哈希对象使用ziplist,否则hashtable

* 哈希对象保存的所有键值对的键和值的字符串长度都小于64字节
* 哈希对象保存的键值对数量小于512个

![](img\hash01.png)

## set

集合对象编码可以是intsett和hashtable

* intset编码t的集合对象使用整数集合作为底层实现,集合对象包含的所有元素都被保存再整数集合里面
* hashtable编码的哈希对象使用字典作为底层实现,字典的每个键都是一个字符串对象,每个字符串对象包含了一个集合元素,而字典的值全部设置为NULL

当集合对象同时满足以下两个条件时,对象使用intset编码,否则hashtable

* 集合对象保存的所有元素都是整数值
* 集合对象保存的元素对象数量不超过512个

## zset

有序集合的编码可以是ziplist和skiplist

* ziplist编码的有序集合对象使用压缩列表作为底层实现,每个集合元素使用两个紧挨在一个压缩列表结点来保存,第一个结点保存元素的成员,而第二个元素则保存元素的分值
* skiplist编码的有序集合对象使用zset结构作为底层实现,一个zset结构同时包含一个字典和一个跳跃表

当有序集合对象同时满足以下两个条件时,使用ziplist否则使用skiplist

* 有序集合保存的元素数量小于128个
* 有序集合保存的所有元素成员的长度都小于64字节

![](img\zset01.png)

![](img\zset02.png)

# 配置文件

默认单位

![](img\config01.png)

* 配置文件单位对大小写不敏感

## 配置文件包含 INCLUDES 

![](img\config02.png)

## 网络配置 NETWORK 

```bash
bind 127.0.0.1 ::1  #绑定的ip
protected-mode yes  #保护模式
port 6379	#端口设置
```

## 通用 GENERAL 

```bash
daemonize yes	#以守护进程的方式运行
pidfile /var/run/redis/redis-server.pid	#后台运行进程文件

#日志
# Specify the server verbosity level.
# This can be one of:
# debug (a lot of information, useful for development/testing)
# verbose (many rarely useful info, but not a mess like the debug level)
# notice (moderately verbose, what you want in production probably)
# warning (only very important / critical messages are logged)
loglevel notice
logfile /var/log/redis/redis-server.log  #日志的文件位置
databases 16	#默认数据库数量
```

![](img\config03.png)

## 快照 SNAPSHOTTING

* 在规定的时间内执行了多少次操作,会持久化到文件  

```bash
save 900 1		#900秒内如果至少有一个key修改,就进行持久哈
save 300 10		#300秒至少10次修改,进行持久化
save 60 10000
stop-writes-on-bgsave-error yes	#持久化如果出错,继续工作
rdbcompression yes	#压缩rdb文件,需要消耗资源
rdbchecksum yes		#保存rdb文件时,进行错误校验
dir /var/lib/redis	#rdb文件保存的目录
```

![](img\config04.png)

 主从复制配置 REPLICATION 

## 安全 SECURITY 

* 设置密码,默认没有密码

![](img\config05.png)

## 客户端 CLIENTS

* ,设置最大连接客户端的数量 

![](img\config06.png)

## 内存处理策略 MEMORY MANAGEMENT

![](img\config07.png)

## AOF配置 APPEND ONLY MODE 

* 默认不开启,大部分情况下,RDB完成够用了
* 持久化后文件的名字

![](img\config08.png)

![](img\config09.png)

* 每次修改sync,消耗性能
* 每一秒执行一次sync,可能丢失1s的数据
* 不执行sync,操作系统自己同步数据,性能最高

# 持久化

Redis是内存数据库,如果不将内存中的数据库状态保存到磁盘中,那么一旦服务器进程退出,服务器中的数据状态就会消失,所以Redis提供了持久化功能,默认情况下为RDB

## RDB ( Redis DataBase )

在指定时间间隔内将内存中的数据集快照写入磁盘,恢复时将快照文件直接读到内存里

```bash
save # 等待直到RDB文件创建完成,会阻塞服务器
bgsave # 派出子进程,并由子进程创建RDB文件,服务器默认
```

![](C:\Users\LEOMESSI\Desktop\MyCpp\09_进阶提高\Redis\img\rdb01.png)

配置文件 SNAPSHOTTING  模块负责RDB配置

默认rdb文件名`dump.rdb`

![](img\rdb02.png)

默认 BGSAVE 执行条件

![](img\rdb03.png)

* 900秒内,至少修改1次  300秒内,至少修改10次  60秒内,至少修改10000次
* 执行`flushall`命令,产生RDB文件
* 退出redis,也会产生RDB文件

如何恢复RDB文件

* 将RDB文件放入redis启动目录,redis启动时会自动检查`dump.rdb`文件

![](img\rdb04.png)

RDB的优点:

* 适合大规模的数据恢复
* 对数据的完整性要求不高

RDB缺点:

* 需要一定时间间隔进行操作,如果redis意外宕机了,则最后一次修改数据就没有了
* 子进程需要一定的内存空间

一般情况下,在主从复制中,RDB就是备用的

## AOF (Append Only File)

将所有命令都记录下来,恢复时把文件中的命令全部执行一次

![](img\aof01.png)

以日志的形行记录每个写操作,将redis执行过的所有指令记录下来(读操作不记录),只许追加文件但不可以改写文件,redis启动之初会读取该文件重新构建数据

配置文件 APPEND ONLY MODE 模块负责AOF配置

默认是不开启的,默认文件名`appendonly.aof`,在redis启动目录

![](img\aof02.png)

* 如果服务器开启了AOF持久化功能,那么服务器会优先使用AOF文件来还原数据库状态
* 如果aof文件出错,redis是不能启动的,需要修复aof文件,redis提供了一个工具`redis-check-aof --fix appendonly.aof`

AOF优点:

![](img\config09.png)

* 每次修改sync,消耗性能
* 每一秒执行一次sync,可能丢失1s的数据
* 不执行sync,操作系统自己同步数据,性能最高

AOF缺点:

* 相对于数据文件来说,AOF远远大于RDB,修复的速度比较慢
* AOF运行效率比RDB慢

AOF重写:

![](img\aof03.png)

* 如果aof文件大于64mb,redis会fork一个子进程进行aof文件重写操作
* 同时,redis设置了一个AOF重写缓冲区,这个缓冲区在创建子进程重写时开始使用,当redis服务器执行完一个写命令后,它会同时将这个命令发送到AOF缓冲区和AOF重写缓冲区
* 当子进程完成AOF重写工作后,服务器会将AOF重写缓冲区中的所有内容写到新的AOF文件中
* 重写原理:从数据库中读取键现在的值,然后用一条命令取记录键值对,代替之前记录这个键值对的多条命令

## 总结

* RDB持久化方式能够在指定的时间间隔内对你的数据进行快照存储
* AOF持久化方式记录每次对服务器写的操作,当服务器重启时会重新执行这些命令来恢复原来的数据,Redis还能对AOF文件进行后台重写,使得AOF文件的体积不至于过大
* 如果只做缓存,只希望数据在服务器运行时存在,可以不使用任何持久化

# 主从复制



# 发布订阅

Redis发布订阅(pub/sub)是一种消息通信模式:发送者(pub)发送消息,订阅者(sub)接收消息

```bash
subscribe "news.it" #客户端执行此命令将成为"news.it"频道的订阅者
publish "news.it" "hello" #客户端执行此命令向频道发送消息
unsubscribe "news.it" #退订频道
psubscribe pattern #订阅一个或多个符合给定模式的频道
pubsub pattern #查看订阅与发布系统状态
punsubscribe pattern #退订所有给定模式的频道
```



# 事务

# 宕机后手动配置主机

# 哨兵模式

# 缓存穿透和雪崩