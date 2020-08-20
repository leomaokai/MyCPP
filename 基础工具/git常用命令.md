配置账户
git config --global user.name “your_username” #设置用户名

git config --global user.email “your_registered_github_Email” #设置邮箱地址


git init          #在当前目录创建一个本地仓库
git status        #查看状态
git add app1.py   #将app.py添加到缓存
git add .         #将所有文件添加到缓存，如果要忽略上传某些文件，新建个.gitignore 文件，在里面加上你要忽略的文件和文件夹   如：log.txt     文件夹 /dir1

git rm --cached 文件名   将文件从缓存中删除

git commit -m '备注信息'  #上传本地仓库

git branch v2   #创建分支v2
git checkout v2  #切换分支

git merge v2     #先切换到master，再输这个命令，合并分支


上传数据到远程仓库(与本地仓库名相同)
现在github新建一个仓库，复制仓库地址 
如果本地数据没有上传本地仓库，要先上传
git remote add origin +地址
git push -u origin master

远程仓库拷贝到本地
git clone 仓库地址   
git pull      #将最新的远程仓库同步到本地
————————————————
