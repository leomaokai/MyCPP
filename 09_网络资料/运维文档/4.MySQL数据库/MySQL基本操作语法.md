##MySQL基本操作语法

#### 1、登录数据库

mysql -h -u -p

####2、查看数据库版本

mysql > select version();

####3、查看当前登录用户

mysql > select user();

####4、查看完整建表语句

mysql > show create database 数据库名称;

####5、创建数据库用户并授权

mysql > grant all[权限] on 数据库.数据表 to 用户名称@'登录ip' identified by '用户密码';

####6、查看用户拥有权限

mysql > show grants for 用户名称@‘登录ip’\G;

####7、查看数据库的所有用户

mysql>select user,host from mysql.user;

####8、创建数据库

mysql > create database 数据库名称;

####9、切换使用数据库

mysql > use 数据库名称;

####10、查看当前所在数据库

mysql > select database();

####11、查看表结构的三种方法

mysql > desc 数据表名称;

mysql > show columns from 数据表名称;

mysql > show create table 数据表名称\G;

####12、插入一条数据

mysql > insert into 数据表名称 values(值,‘值’);

####13、批量插入数据

mysql > insert into 数据表名称 values(值,'值'),(值,'值');

####14、查询记录

①所有记录

mysql > select * from 数据库名称.数据表名称;

使用use已经切换到需要操作的库

mysql > select * from 数据表名称;

②查询字段等于值

mysql > select * from 数据表名称 where 字段名='值';

③查询字段大于值

mysql > select * from 数据表名称 where 字段名 > '值';

####15、查询并修改字段值

mysql > update 数据表名称 set 修改的字段名称 = '修改为的值' where 查询的字段名称 = ‘查询的值’；

####16、在数据表中字段之后加入新字段

mysql > alter table 数据表名称 add 新增字段名称 字段类型 after 字段名称;

####17、备份数据库到文件中

mysqldump

####18、删除表中的所有数据

mysql > delete from 数据表名称

mysql > truncate table 数据表名称

####19、查看所有数据库

mysql >  show databases;

####20、查看当前库所有数据表

mysql > show tables;

####21、删除数据表

mysql > drop table 数据表名称;

####22、删除数据库

mysql > drop database 数据库名称;

####23、从备份文件恢复数据

mysql -u用户名称 -p用户密码 < 数据备份文件路径

####24、查看数据表字符集

mysql > show variables like 'character_set%';

####25、启动mysqld服务端，无密码参数

--skip-grant-tables

####26、修改表引擎

mysql > alter table 数据表名称 ENGINE=修改为的引擎名称;

##MySQL索引管理

主键索引

唯一索引

普通索引

复合索引

全文索引

前缀索引

MySQL状态管理查看

####1、查询数据库链接数

mysql > show processlist;参数解释：

####2、查询数据库全局状态

mysql > show global status;

Aborted_clients              由于客户没有正确关闭连接已经死掉，已经放弃的连接数量。 

Aborted_connects          尝试已经失败的MySQL服务器的连接的次数。 

Connections                   试图连接MySQL服务器的次数。 

Created_tmp_tables       当执行语句时，已经被创造了的隐含临时表的数量。 

Delayed_insert_threads  正在使用的延迟插入处理器线程的数量。 

Delayed_writes               用INSERT DELAYED写入的行数。 

Delayed_errors               用INSERT DELAYED写入的发生某些错误(可能重复键值)的行数。 

Flush_commands            执行FLUSH命令的次数。 

Handler_delete                请求从一张表中删除行的次数。 

Handler_read_first           请求读入表中第一行的次数。 

Handler_read_key            请求数字基于键读行。 

Handler_read_next           请求读入基于一个键的一行的次数。 

Handler_read_rnd             请求读入基于一个固定位置的一行的次数。 

Handler_update                请求更新表中一行的次数。 

Handler_write                   请求向表中插入一行的次数。 

Key_blocks_used              用于关键字缓存的块的数量。 

Key_read_requests           请求从缓存读入一个键值的次数。 

Key_reads                        从磁盘物理读入一个键值的次数。 

Key_write_requests          请求将一个关键字块写入缓存次数。 

Key_writes                        将一个键值块物理写入磁盘的次数。 

Max_used_connections      同时使用的连接的最大数目。 

Not_flushed_key_blocks     在键缓存中已经改变但是还没被清空到磁盘上的键块。 

Not_flushed_delayed_rows 在INSERT DELAY队列中等待写入的行的数量。 

Open_tables                       打开表的数量。 

Open_files                          打开文件的数量。 

Open_streams                    打开流的数量(主要用于日志记载） 

Opened_tables                    已经打开的表的数量。 

Questions                           发往服务器的查询的数量。 

Slow_queries                       要花超过long_query_time时间的查询数量。 

Threads_connected              当前打开的连接的数量。 

Threads_running                  不在睡眠的线程数量。 

Uptime                                服务器工作了多少秒。

####3、查询数据库运行时间

mysql > show global status like 'uptime';

####4、查询数据库全局变量

mysql > show global varibles;