service mysql start

service mysql restart

service mysql stop

# 库管理

创建数据库									create database <数据库名>

显示所有的数据库						show databases （注意：最后有个s）

删除数据库									drop database <数据库名>

连接数据库									use <数据库名>

查看当前使用的数据库					select database();

当前数据库包含的表信息				show tables; 

查看数据库的字符集						show create database 数据库名

更改数据库字符集						alter database 数据库名 character set gbk

# 表管理

建表								create table <表名> ( <字段名> <类型> 																	[,..<字段名n> <类型n>]);

获取表结构					desc 表名或者show columns from 表名

删除表							drop table <表名>

更改表名						alter table 原表名 rename  to 新表名;

在表中增加字段			alter table 表名 add column字段 类型 其它

删除字段						alter table 表名 drop column  字段

修改字段名称				alter table 表名 change 原名 新名 类型

修改字段类型                 alter table 表名 modify  字段 类型

# 表数据管理

插入数据							insert into <表名>  [( <字段名>]  values  ( 值 )

查询表中的数据				select <字段，字段，...> from < 表名 > where < 表达式 >

删除表中数据				   delete from 表名 where 表达式

修改表中数据 				  update 表名 set 字段=新值,…where 条件

全部删除						  truncate table 表名 

# 表数据查询

查询所有列					select  *  from 表名

查询指定列					select	字段,字段 ,...	from 表名

查询时添加常量列		select	字段,...,'常量列'  别名  from 表名

查询时合并列				select  字段1+字段2+字段3 as 别名 from  表名  (仅限于数字类型int)

去除重复记录				select	distinct  ....

条件查询						select  *  from  表名  where  条件表达式		

* 条件表达式    比较运算符   between and     like  		

* 通配符		%  匹配0或多个字符     _  匹配1个字符   like 'zhang%'      

* 逻辑   		与 AND     或  OR     非  NOT

聚合查询       通过包含一个聚合函数(Sum 或 Avg)来汇总来自多个行的信息

* avg()求平均值	max()求最大值	min()最小值    count()求记录数    sum()求和
* select  count(*)  from  表名              select  count(字段)  from  表名
  * count  函数会自动排除null的数据
  * 使用  *  在效率方面不如  字段(内容不为空)
* select  max(字段)   from   表名
* select   avg(字段)   from   表名

分页查询         limit  

* select  *   from  表名  **limit**  start,pagsize

*  select  *  from  表名  limit  (pageno-1)*pagesize,pagesize

查询排序       order  by  

* 降序          select  *  from   表名   **order**  **by**  字段  **desc**
* 升序          select  *  from   表名   **order**  **by**  字段  **asc**
* 多列排序    select *  from   表名   **order**  **by**   字段1  **desc**, 字段2  **asc**
  * 先按照第一排序条件进行,在第一排序相同的情况按第二排序条件进行

分组查询     group   by

* select   字段1,**count(*)**   from    表名   **group**   **by**  字段1
* 分组查询需要配合聚合查询
* 分组过滤   having       where只针对单行过滤
  * select  字段1,count(*)   from   表名   group  by  字段1  **having**  条件表达式

# 数据库设计

