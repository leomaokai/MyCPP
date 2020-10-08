# 配置账户
```bash
git config --global user.name “your_username”  #设置用户名
git config --global user.email “Email” #设置邮箱地址
git config --system --list	#查看系统配置/Git/etc/gitconfig
git config --global --list	#查看用户配置/用户/用户名/gitconfig
git init	#创建新的git仓库
git clone username@host:/path/to/repository	#检出服务器上的仓库
git remote add origin <server>	#将本地仓库连接某个远程仓库
master: 默认开发分支
origin: 默认远程版本库
```

# 修改和提交

```bash
git status #查看状态
git diff #查看变更内容
git add . #跟踪所有改动过的文件
git add <file> #跟踪指定文件
git commit -m "commit message" #提交所有更新过的文件
git commit --amend	#修改最后一次提交
git log	#查看提交历史
```

# 撤销

```bash
git reset --hard HEAD	#撤销工作目录中所有未提交文件的修改内容
git revert <commit>		#撤销指定的提交
```

# 远程操作

```bash
git remote -v 				#查看远程版本库信息
git remote show <remote>	#查看指定远程版本库信息
git remote add <remote> <url> 	#添加远程版本库
git fetch <remote> 				#从远程库获取代码
git pull <remote> <branch>		#下载代码及快速合并
git push <remote> <branch>		#上传代码及快速合并
git push <remote> :<branch/tagname>	#删除远程分支或标签
git push --tags					#上传所有标签
```

# 分支与标签

```bash
git branch						#显示所有本地分支
git checkout <branch/tag>		#切换到指定分支或标签
git branch <new-branch> 		#创建新分支
git branch -d <branch>			#删除本地分支
git tag							#显示所有本地标签
git branch <tagname>	 		#创建新标签
git branch -d <tagname>			#删除本地标签
git merge <branch>				#合并指定分支到当前分支
git rebase <branch> 			#衍合指定分支到当前分支
```

# 概念

git和svn的区别:

* svn是集中版本控制系统,版本库是集中放在中央服务器的,工作时,用自己的电脑从中央服务器得到最新的版本,工作完成,再将其推送到中央服务,必须联网才能工作
* git是分布式版本控制系统,没有中央服务器,每个人的电脑就是一个完整的版本库,工作时不需要联网

git工作区域:

* 本地:	工作区    暂存区	本地仓库
* 远程:    git远程仓库remote directory
* 工作区- git add ->暂存区- git commit ->本地仓库- git push ->远程仓库
* 远程仓库- git pull ->本地仓库- git reset ->暂存区- git checkout ->工作区

![](img\git01.png)