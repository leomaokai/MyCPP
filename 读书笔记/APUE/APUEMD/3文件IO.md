# 文件描述符

对于内核而言，许多打开的文件都是通过文件描述符引用的。文件描述符是一个非负整数。当打开一个现有文件或创建一个新的文件时，内核向进程返回一个文件描述符。当读、写一个文件时，使用open或creat返回文件描述符标识该文件，将其作为参数传送给read或write。

文件描述符0与进程的标准输入关联

文件描述符1与标准输出关联

文件描述符2与标准错误关联

0、1、2的符号常量为STDIN_FILENO、STDOUT_FILENO、STDERR_FILENO

这些常量都在头文件<unistd.h>中定义

# 函数open与openat

```c
#include<fcntl.h>

int open (const char *path, int oflag,.../*mode_t mode*/);

int openat (int fd, const char *path, int oflag,.../*mode_t mode*/);
```

两函数的返回值:若成功,返回文件描述符,若出错,返回-1

path参数是要打开或创建文件的名字

oflag参数可以用来说明此函数的多个选项

|      | `oflag`参数 | 说明       |
| ---- | ----------- | ---------- |
| 01   | O_RDONLY    | 只读打开   |
| 02   | O_WRONLY    | 只写打开   |
| 03   | O_RDWR      | 读、写打开 |
| 04   | O_EXEC      | 只执行打开 |
| 05   | O_SEARCH    | 只搜索打开 |

这5给常量种必须指定一个且只能指定一个

|      | `oflag`参数 | 说明                                                         |
| ---- | ----------- | ------------------------------------------------------------ |
| 06   | O_APPEND    | 每次写时都追加到文件尾端                                     |
| 07   | O_CLOEXEC   | 把FD_CLOEXEC设置为文件描述符标志                             |
| 08   | O_CREAT     | 若此文件不存在则创建它                                       |
| 09   | O_DIRECTORY | 如果path引用的不是目录，则出错                               |
| 10   | O_EXCL      | 创建文件时若文件存在，则出错                                 |
| 11   | O_NOCTTY    |                                                              |
| 12   | O_NOFOLLOW  |                                                              |
| 13   | O_NONBLOCK  |                                                              |
| 14   | O_SYNC      |                                                              |
| 15   | O_TRUNC     | 如果此文件存在，而且为只写或读-写成功打开，则将其长度截断为0 |
| 16   | O_TTY_INIT  |                                                              |
| 17   | O_DSYNC     |                                                              |
| 18   | O_RSYNC     |                                                              |

fd参数把open和openat函数区分开,共有3种可能性

* path参数指定的是绝对路径名,在这种情况下,fd参数被忽略,openat函数就相当于open函数
* path参数指定的是相对路径名,fd参数指出了相对路径名在文件系统中的开始地址.fd参数是通过打开相对路径名所在的目录来获取
* path参数指定了相对路径名,fd参数具有特殊值AT_FDCWN.在这种情况下,路径名在当前工作目录中获取,openat函数在操作上与open函数类似

# 函数creat

```c
#include<fcntl.h>

int creat (const char *path, mode_t mode);
```

返回值:若成功,返回为只写打开的文件描述符,若出错,返回-1

```c
/*等效于*/
open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
```

creat的一个不足之处是它以只写方式打开所创建的文件.

用open可用读写创建

```c
open(path, O_RDWR | O_CREAT | O_TRUNC, mode);
```

# 函数close

```c
#include<unistd.h>
int close(int fd);
```

返回值:若成功,返回0,若出错,返回-1

关闭一个文件时还会释放该进程加在该文件上的所有记录锁.

当一个进程终止时,内核自动关闭它所有的打开文件.很多进程都利用这一功能而不显示地用close关闭打开文件.

# 函数lseek

调用lseek显式地为一个打开的文件设置偏移量

```c
#include<unistd.h>
off_t lseek(int fd, off_t offset, int whence);
```

返回值:若成功,返回新的文件偏移量,若出错,返回-1

参数offset的解释与参数whence的值有关

* 若whence是SEEK_SET,则将该文件的偏移量设置为距文件开始处offset个字节
* 若whence是SEEK_CUR,则将该文件的偏移量设置为其当前值加offset,offset可正可负
* 若whence是SEEK_END,则将该文件的偏移量设置为文件长度加offset,offset可正可负

# 函数read

调用read函数从打开文件中读数据

```c
#include<unistd.h>
ssize_t read(int fd, void *buf, size_t nbytes);
```

返回值:读到的字节数,若已到文件尾,返回0,出错误,返回-1

很多情况可使实际读到的字节数少于要求读到的字节数

读操作从文件的当前偏移量处开始,在成功返回之前,该偏移量将增加实际读到的字节数

# 函数write

调用write函数向打开文件写数据

```c
#include<unistd.h>
ssize_t write(int fd, const void *buf, size_t nbytes);
```

返回值:若成功,返回已写的字节数,若出错,返回-1

其返回值通常与参数`nbytes`相同,否则表示出错

对于普通文件,写操作从文件的当前偏移量处开始,如果在打开该文件时,指定了O_APPEND选项,则在每次写操作之前,将文件偏移量设置在文件的当前结尾处,在一次成功写之后,该文件偏移量增加实际写的字节数

# I/O的效率

程序只用read和write函数复制一个文件

```c
#include"apue.h"
#define BUFFSIZE 4096
int main(void)
{
    int n;
    char buf[BUFFSIZE];
    
    while(n = read(STDIN_FILENO,buf,BUFFSIZE)>0)
        if(write(STDOUT_FILENO,buf,n) != n)
            err_sys("write error");
    
    if(n<0)
        err_sys("read error");
    
    exit(0);
}
```

# 文件共享

内核使用3种数据结构表示打开文件,它们之间的关系决定了在文件共享方面一个进程对另一个进程可能产生的影响.

* 每个进程在进程表种都有一个记录项,记录项种包含一张打开文件描述符表,可将其视为一个矢量,每个描述符占用一项.与每个文件描述符相关联的是:

  - 文件描述符标志

  * 指向一个文件表项的指针

* 内核为所有打开文件维持一张文件表.每个文件表项包含:

  - 文件状态标志

  * 当前文件偏移量
  * 指向该文件v节点表项的指针

* 每个打开文件(或设备)都有一个v节点(v-node)结构.v节点包含了文件类型和对此文件进行各种操作函数的指针

多个进程读取同一文件都能正确工作,每个进程都有它自己的文件表项,其中也有它自己的当前文件偏移量.但是,当多个进程写同一文件时,则可能产生预想不到的结果.原子操作可避免这种情况

原子操作指的是由多步组成一个操作.如果该操作原子地执行,则要么执行完所有的步骤,要么一步也不执行,不可能只执行所有步骤的一个子集.

# 函数dup和dup2

下面两个函数都可用来复制一个现有的文件描述符

```c
#include<unistd.h>
int dup(int fd);
int dup2(int fd,int fd2);
```

返回值:若成功,返回新的文件描述符,若输出,返回-1

由`dup`返回的新文件描述符一定是当前可用文件描述符种的最小数值.对于`dup2`,可以用`fd2`参数指定新的描述符的值.如果`fd2`以及打开,则先将其关闭.若`fd`等于`fd2`,则`dup2`返回`fd2`,而不关闭它.否则,`fd2`的`FD_CLOEXEC`文件描述符标志就被清除,这样`fd2`在进程调用`exec`时是打开状态.

这些函数返回新文件描述符与参数`fd`共享一个文件表项

复制一个描述符的另一种方法是使用`fcntl`函数

```c
dup(fd);
/*等效于*/
fcntl(fd,F_DUPFD,0);
```

```c
dup2(fd,fd2);
/*等效于*/
close(fd2);
fcntl(fd,F_DUPFD,fd2);
```

`dup2`并不完全等同于`close`和`fcntl`.

`dup2`是一个原子操作,而`close`和`fcntl`包括两个函数的调用.

`dup2`和`fcntl`有一些不同的`errno`.

# 函数sync,fsync和fdatasync

当内核需要重用缓冲区来存放其他磁盘块数据时,它会把所有延长写数据块写入磁盘.为了保证磁盘上实际文件系统于缓冲区种内容一致性,UNIX系统提供了`sync`,`fsync`和`fdatasync`三个函数

```c
#include<unistd.h>
void sync(void);
```

`sync`只是将所修改过的块缓冲区排入写队列,然后就返回,它并不等待实际写磁盘操作结束.

通常,称为`update`的系统守护进程周期地调用`sync`函数,这就保证了定期冲洗内核地块缓冲区.命令`sync`也调用`sync`函数.

```c
#include<unistd.h>
int fsync(int fd);
int fdatasync(int fd);
```

返回值:若成功,返回0,若出错,返回-1

`fsync`函数只是对由文件描述符fd指定地一个文件起作用,并且等待写磁盘操作结束才返回.

`fsync`可用于数据库这样地应用程序,这种应用程序需要确保修改过地块立即写到磁盘上.

`fdatasync`类似于`fsync`,但它只影响文件地数据部分.

`fsync`还会同步更新文件的属性.

# 函数fcntl

`fcntl`函数可以改变已经打开文件的属性

```c
#include<fcntl.h>
int fcntl(int fd,int cmd,.../*int arg*/);
```

返回值:若成功,则依赖于cmd,若出错,返回-1

`fcntl`函数有一下5种功能

* 复制一个已有的描述符(cmd=F_DUPFD or F_DUPFD_CLOEXEC)
* 获取/设置文件描述符标志(cmd=F_GETFD or F_SETFD)
* 获取/设置文件状态标志(cmd=F_GETFL or F_SETFL)
* 获取/设置异步I/O所有权(cmd=F_GETOWN or F_SETOWN)
* 获取/设置记录锁(cmd=F_GETLK or F_SETLK or F_SETLKW)

# 函数ioctl

ioctl函数一直是操作的杂物箱，不能用本章其它函数表示的I/O操作通常能用ioctl表示.终端I/O是使用ioctl最多的地方

```c
#include<unistd.h>  /*system V*/
#include<sys/ioctl.h>  /*BSD and linux*/
int ioctl(int fd,int request,...);
```

返回值:若出错,返回-1,若成功,返回其他值

# /dev/fd

较新的系统都提供名为`/dev/fd`的目录,其目录项是名为0,1,2等的文件,打开`/dev/fd/n`等效于复制描述符n





