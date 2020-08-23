# 流和FILE对象

在第三章中,所有的I/O函数都是围绕文件描述符的.当打开一个文件使,即返回一个文件描述符,然后该文件描述符就用于后续的I/O操作.而对于标准I/O库,它们的操作是围绕**流**进行的.当用标准I/O库打开或创建一个文件时,我们已使一个流与一个文件相关联.

标准I/O文件流可用于单字节或多字节(宽)子集符.**流的定向**决定了所读写的字符是单字节还是多字节

当一个流最初被创建时,它并没有定向

如若在未定向的流上使用一个多字节I/O函数,则将该流的定向设置为宽定向

若在未定向的流上使用一个单字节I/O函数,则将该流的定向设为字节定向

只有两个函数可改变流的定向,`freopen`函数清除一个流的定向,`fwide`函数可用于设置流的定向

```c
#include<stdio.h>
#include<wchar.h>
int fwide( FILE *fp,int mode);
```

返回值:若流是宽定向,返回正值,若流是字节定向,返回负值,若流未定向,返回0

根据`mode`参数的不同,`fwide`函数执行不同的工作

* 若`mode`参数值为负,`fwide`将试图使指定的流是字节定向的
* 若`mode`参数值为正,`fwide`将试图使指定的流使宽定向的
* 若`mode`参数值为0,`fwide`将不试图设置流的定向,但返回标识该流定向的值

# 标准输入,标准输出,标准错误

对一个进程羽定义了3个流,并且这3个流可以自动地被进程使用,它们是:标准输入,标准输出,标准错误

这3个标准I/O流通过预定义文件指针`stdin`,`stdout`,`stderr`加以引用,这3个文件指针定义在头文件<`stdio.h`>中

# 缓冲

标准I/O库提供缓冲的目的是为了尽可能的减少使用`read`和`write`调用的次数

标准I/O提供了一下3种类型的缓冲

* 全缓冲.在这种情况下,在填满标准I/O缓冲区后才进行实际的I/O操作
* 行缓冲:在这种情况下,当在输入和输出种遇到换行符时,标准I/O库执行I/O操作
* 不带缓冲:标准I/O库不对字符进行缓冲存储

术语冲洗说明标准I/O缓冲区的写操作

# 打开流

下列3个函数打开一个标准I/O流

```c
#include<stdio.h>
FILE *fopen(const char *restrict pathname,const char *restrict type);
FILE *freopen(const char *restrict pathname,const char *restrict type,FILE *restrict fp);
FILE *fdopen(int fd,const char *type);
```

返回值:若成功,返回文件指针,若出错,返回`NULL`

3个函数区别如下:

* `fopen`函数打开路径名为`pathname`得到一个指定的文件
* `freopen`函数在一个指定的流上打开一个指定的文件,若该流已经打开,则先关闭该流,若该流已经定向,则使用`freopen`清除该定向.此函数一般用于将一个指定的文件打开为一个预定义的流:标准输入,标准输出,标准错误
* `fdopen`函数取一个已有的文件描述符,并使一个标准I/O流与该描述符相结合.此函数常用于由创建管道和网络通信通道函数返回的描述符

`type`参数指定对该I/O流的读,写方式:

| type            | 说明                                 | open标志                              |
| --------------- | ------------------------------------ | ------------------------------------- |
| r或`rb`         | 为读打开                             | `O_RDONLY`                            |
| w或`wb`         | 把文件截断至0长,或为写而创建         | `O_WRONLY` \| `O_CREAT` \| `O_TRUNC`  |
| a或ab           | 追加:为在文件尾写而打开,或为写而创建 | `O_WRONLY` \| `O_CREAT` \| `O_APPEND` |
| r+ 或r+b或`rb+` | 为读和写而打开                       | `O_RDWR`                              |
| w+或w+b或`wb+`  | 把文件截断至0长,或为读和写而打开     | `O_RDWR` \| `O_CREAT` \| `O_TRUNC`    |
| a+或a+b或ab+    | 为在文件尾读和写而打开或创建         | `O_RDWR` \| `O_CREAT` \| `O_APPEND`   |

 对于`fdopen`,`type`参数的意义稍有区别,因为该描述符已被打开,所以`fdopen`为写而打开并截断该文件.

用追加写类型打开一个文件后,每次写都将数据写到文件的当前尾端处.如果有多进程用标准I/O追加方式打开同一个文件,那么来自每个进程的数据都将正确地写到文件中.

调用`fclose`关闭一个打开的流

```c
#include<stdio.h>
int fclose(FILE *fp);
```

返回值,若成功,返回0.若出错,返回`EOF`

在该文件被关闭之前,冲洗缓冲区的输出数据.缓冲区中的任何输入数据被丢弃.如果标准I/O库已经为流自动分配了一个缓冲区,则释放此缓冲区

当一个进程正常终止时(直接调用`exit`函数或从`main`函数返回),则所有带未写缓冲数据的标准I/O流都被冲洗,所有打开的标准I/O流都被关闭

# 读和写流

一旦打开流,则可在3种不同类型的非格式化I/O中进行选择,对其进行读,写操作

* 每次打开一个字符的I/O,一次读或写一个字符,如果流是带缓冲的,则标准I/O函数处理所有缓冲
* 每次一行的I/O,如果想要一次写或读一行,则使用`fgets`和`fputs`,每行都以一个换行符终止
* 直接I/O,`fread`和`fwrite`函数支持这种类型的I/O.每次I/O操作读或写某种数量的对象,而每个对象具有指定的长度.

以下3个函数可用于一次读一个字符

```c
#include<stdio.h>
int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);
```

返回值:若成功,返回下一个字符,若已到达文件尾端或出错,返回`EOF`

函数`getchar`等同于`getc(stdin)`.前两个函数的区别是,`getc`可被实现为宏,而`fgetc`不能被实现为宏.

为了区分这两种不同的情况,必须调用`ferror`或`feof`

```c
#inlclude<stdio.h>
int ferror(FILE *fp);
int feof(FILE *fp);
/*两个函数的返回值:若条件为真,返回非0,否则,返回0*/
void clearerr(FILE *fp);
```

在大多数实现中,为每个流在FILE对象中维护了两个标志:

* 出错标志
* 文件结束标志

调用`clearerr`可以清除这两个标志

从流中读取数据后,可以调用`ungetc`将字符再压送回流中

```c
#include<stdio.h>
int ungetc(int c,FILE *fp);
```

返回值:若成功,返回c,若出错返回`EOF`

压送回流中的字符以后又可从流中读出,但读出字符的顺序与压送回的顺序相反

# 每次一行I/O

下面两个函数提供每次输入一行的功能

```c
#include<stdio.h>
char *fgets(char *restrict buf,int n,FILE *restrict fp);
char *gets(char *buf);
```

返回值:若成功,返回`buf`,若已到达文件尾端或出错,返回`NULL`

这两个函数都指定了缓冲区的地址,读入的行将送入其中.gets从标准输入读,而`fgets`则从指定的流读

对于`fgets`,必须指定缓冲的长度n.此函数一直读到下一个换行符为止,但是不能超过n-1个字符

`gets`是一个不推荐使用的函数,其问题是调用者在使用gets时不能指定缓冲区的长度,可能造成缓冲区溢出

`fputs`和`puts`提供了每次输出一行的功能

```c
#include<stdio.h>
int fputs(const char *restrict str,FILE *restrict fp);
int puts(const char *str);
```

返回值:若成功,返回非负值,若出错,返回`EOF`

函数`fputs`将一个以`null`字节终止的字符串写到指定的流,尾端的终止符`null`不写出

`puts`将一个以`null`字节终止的字符串写到标准输出

# 标准I/O的效率

使用getc和putc将标准输入复制到标准输出

```c
#include"apue.h"
int main(void)
{
    int c;
    while((c=getc(stdin))!=EOF)
        if(putc(c,stdout)==EOF)
            err_sys("output error");
    if(ferrot(stdin))
        err_sys("input error");
    exit(0);
}
```

可以用fgetc和fputc改写该程序,这两个一定时函数,而不是宏

使用fgets和fputs每次读写一行将标准输入复制到标准输出

```c
#include"apue.h"
int main(void)
{
    char buf[MAXLINE];
    whlie(fgets(buf,MAXLINE,stdin)!=NULL)
        if(fputs(buf,stdout)==EOF)
            err_sys("output error");
    if(ferror(stdin))
        err_sys("input error");
    exit(0);
}
```

对于这3个标准I/O版本的每一个,其用户CPU时间都大于最佳read版本.因为标准I/O循环次数过多,而read版本循环次数较少(因为缓冲区).因为系统CPU时间几乎相同,所以用户CPU时间的差别以及等待I/O结束所消耗时间的差别造成了时钟时间的差别

系统CPU时间几乎相同,原因是所有这些程序对内核提出的读写请求数基本相同.注意,使用标准I/O例程的一个优点是无需考虑缓冲及最佳I/O长度的选择.在使用fgets时需要考虑最佳行长,但是与选择最佳I/O长度比较,这要方便得多

若调用相同得函数次数,标准I/O比I/O快得多,原因是系统调用与普通函数相比需要花费等多的时间

通过比较我们了解到的基本事实是:标准I/O库与直接调用read和write函数相比并不慢很多.对于大多数比较复杂的应用程序,最主要的用户CPU时间是由应用本身的各种处理消耗的,而不是由标准I/O例程消耗的

# 二进制I/O

下列两个函数执行二进制I/O操作

```c
#include<stdio.h>
size_t fread(void *restrict ptr,size_t size,size_t nobj,FILE *restrict fp);
size_t fwrite(const void *restrict ptr,size_t size,size_t nobj,FILE *restrict fp);
```

返回值:读或写的对象数

* 读或写一个二进制数组.例如,为了将一个浮点数组的2~5个元素写至一文件上

```c
float data[10];
if (fwrite(&data[2],sizeof(float),4,fp)!=4)
    err_sys("fwrite error");
```

其中,指定siez为每个数组元素的长度,nobj为预写的元素个数

* 读或写一个结构

```c
struct{
    short count;
    long tatal;
    char name[NAMESIZE];
}item;
if(fwrite(&item,sizeof(item),1,fp)!=1)
    err_sys("fwrite error");
```

其中,指定size为结构的长度,nobj为1(要写的对象个数)

将这两个例子结合起来就可以读或写一个结构数组.为了做到这一点,size应当是该结构的siezof,nobj应是该数组中的元素个数.

# 格式化I/O

**格式化输出**

```c
#include<stdio.h>
int printf(const char *restrict format, ...);
int fprintf(FILE *restrict fp,const char *restrict format,...);
int dprintf(int fd,const char *restrict format,...);
/*若成功,返回输出字符数,若编码出错,返回负值*/
int sprintf(char *restrict buf,const char *restrict format,...);
/*若成功,返回存入数组的字符串,若出编码错,返回负值*/
int snprintf(char *restrict buf,size_t n,const char *restrict format,...);
/*若缓冲区足够大,返回将要存入数组的字符数,若编码出错,返回负值*/
```

`printf`将格式化数据写到标准输出,`fprintf`写至指定的流,`dprintf`写至指定的文件描述符,`sprintf`将格式化的字符送入数组`buf`中.`sprintf`在该字符的尾端自动加一个null字符,但该字符不包含在返回值中.

注意,sprintf函数可能回造成由buf指向的缓冲区的溢出.调用者有责任确保该缓冲区足够大.因为缓冲区溢出回造成程序不稳定甚至安全隐患,为了解决这种缓冲区溢出问题,引入了snprintf函数.在该函数中,缓冲区长度是一个显示参数,超过缓冲区尾端写的所有字符都被丢弃

格式说明控制其余参数任何编写,以后又如何显示.每个参数按照转换说明编写,转换说明以百分号`%`开始,除转换说明外,格式字符中的其他字符按原样,不经任何修改被复制输出

**格式化输入**

```c
#include<stdio.h>
int scanf(const char *restrict format,...);
int fscanf(FILE *restrict fp,const char *restrict format,...);
int sscanf(const cahr *restrict buf,const char *restrict foemat,...);
```

返回值:赋值的输入项数,若输入出错或在任一转换前已到达文件尾端,返回EOF

scanf族用于分析输入字符串,并将字符序列转换成指定类型的变量.在格式化之后的各参数包含了变量的地址,用转换结果对这些变量赋值

格式说明控制任何转换参数,以便对它们赋值,转换说明以`%`字符开始.除转换说明和空白字符外,格式字符串中的其他字符必须与输入匹配.若一个字符不匹配,则停止后续处理,不再读输入的其余部分

# 实现细节

在UNIX中,标准I/O库最终都要调用第三章中说明的I/O例程.每个标准I/O流都有一个与其相关联的文件描述符,可以对一个流调用fileno函数以获得其描述符

```c
#include<stdio.h>
int fileno(FILE *fp);
```

返回值:与该流相关联的文件描述符

如果要调用dup或fcntl等函数,则需要此函数

# 临时文件

ISO C标准I/O库提供了两个函数以帮吗创建临时文件

```c
#include<stdio.h>
char *tmpnam(char *ptr);
/*返回值:指向唯一路径名的指针*/
FILE *tmpfile(void);
/*返回值:若出现,返回文件指针,若出错,返回NULL*/
```

tmpnam函数产生一个与现有文件名不同的一个有效路径字符串.每次调用它时,都产生一个不同的路径名,最多调用次数时TMP_MAX,定义在<stdio_h>中

tmpflie创建一个临时二进制文件,在关闭该文件或程序结束时将自动删除这种文件

# 内存流

标准I/O库把数据缓存在内存中,因此每次一字符和每次一行的I/O更有效.我们也可以通过调用setbuf或setvbuf函数让I/O库使用我们自己的缓冲区.

有三个函数可用于内存流的创建,第一个是fmemopen

```c
#include<stdio.h>
FILE *fmemopen(void *reatrict buf,size_t size,const char *restrict type);
```

返回值,若成功,返回流指针,若出错,返回NULL

fmemopen函数允许调用者提供缓冲区用于内存流:buf指向缓冲区的开始位置,size参数指向缓冲区大小的字节数.如果buf参数为空,fmemopen函数分配size字节数的缓冲区.在这种情况下,当流关闭时缓冲区会被释放

用于创建内存流的其他两个函数是分别是open_memstream和open_wmemstream

```c
#include<stdio.h>
FILE *open_memstream(char **bufp,size_t *sizep);
#include<wchar.h>
FILE *open_wmemstream(wchar_ **bufp,size_t *sizep);
```

open_memstream函数创建的流是面向字节的,open_wmemstream函数创建的流是面向宽字节的.这两个函数与fmemopen函数的不同点在于:

* 创建的流只能写打开
* 不能指定自己的缓冲区,但可以分别通过bufp和sizep参数访问缓冲区地址和大小
* 关闭流后需要自行释放缓冲区
* 对流添加字节会增加缓冲区大小

因为避免了缓冲区溢出,内存流非常适用创建字符串.因为内存流只会访问内存,不访问磁盘上的文件,所以对于把标准I/O流作为参数用于临时文件的函数来说,会有很大的性能提升

# 标准I/O的替代软件

标准I/O库的一个不足之处是效率不高,这与它需要复制的数据量有关.当使用每此一行函数fgets和fputs时,通常需要复制两次数据:一次是在内核和标准I/O缓冲区之间(当调用read和write时),第二次是在标准I/O缓冲区和用户进程中的行缓冲区之间.快速I/O库避免了这一点,其方法是使读一行的函数返回指向该行的指针,而不是将改行复制到另一个缓冲区.