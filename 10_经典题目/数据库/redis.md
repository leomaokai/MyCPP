# redis中hash和zset,在相同数量的情况下,谁占用的空间高?

redis存储原理,dict hashtable    k,v   k:string   v:string,hash,list,zset,stream,set

小于128占用空间差不多,都是用压缩列表存储

128<x<512 hash(压缩列表)占用内存低

大于512 

* 没有扩容缩容
  * 最差的情况(n+1刚好扩容)  n->2n   zset占用小
  * 最好的情况   hash占用空间小
* 扩容
  * 2*n  hash占用空间多
  * 进行rehash了  2.5n 
* 缩容
  * 1.9n   
  * 进行rehash更多了

hash:

* 在小于512数据时使用压缩列表
* 大于512时,使用dict hashtable   数组+链表+hash函数

zset:

* 小于128 压缩列表
* 大于128 跳表