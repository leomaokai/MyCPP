pwd   显示当前路径

cd         切换路径  
cd /       切到根路径
cd ~       切换到主目录，root目录
cd ..      上一级
cd ../..   向上两级

ls         列出目录内容（list缩写）
ls -l      带l参数，显示文件属性
ls -l filename  显示某个文件的文件属性
ls *.txt    显示.txt结尾的文件


cat      显示文件内容
cat -n  filename    带参数n，显示行号

grep    查找文件的内容
grep  ab  words   查找words文件中带ab的行
grep  ab  words1 word2   查找2个文件中带ab的行
egrep   带有更完整的正则匹配功能
egrep "^a.*b$" words  匹配words文件中a开头b结尾的行

find /home -name words   查找home文件下的words文件

whereis python    查找程序位置

touch  生成一个空文件
mkdir  生成目录
mkdir -p umts/baseband  带参数p 一级级往下创建目录

mv  移动文件，也可以相当于重命名
cp  复制文件

rmdir  只能删除空目录
rm  filename    删除文件，删除时需要确认是否删除
rm -f filename  参数f，删除时不需要确认，只直接删除
rm -r  xxx      参数r，递归删除xxx目录下的所有文件

ls -l    查看文件属性

total 16
-rwxr-xr-x 1 root root   74 Apr 12 18:00 hello
drwxr-xr-x 2 root root 4096 Apr 12 23:13 umts
-rw-r--r-- 1 root root   36 Apr 12 16:09 words
-rw-r--r-- 1 root root   36 Apr 12 22:38 words2

第1位文件类型：- 普通文件  d 目录 
2-10,属主、属组、其他人的权限
后面 连接数、属主、属组、文件大小（Byte）、最后修改日期

chmod  改变文件权限
chmod 用户组+/-权限
用户组：属主（u）、属组（g）、其他（o）、所有人（a）
权限： 读（r）、写（w）、执行（x）

chmod u+x words  添加属主对words文件的执行权限
chmod a-x words   删除所有人对words文件的执行权限

