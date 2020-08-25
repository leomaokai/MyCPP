# Lua基本语法

`lua i`或`lua`启用交互式编程

脚本式编程:

`vim hello.lua`

```lua
print("hello lua!")  --两个减号是单行注释
--[[
lua标识符用于定义一个变量,一般约定,以下划线加大写字母的名字被保留用于全部变量

lua是一个区分大小写的编程语言

在默认情况下,变量总是认为是全局的
全局变量不需要声明,给一个变量赋值后即创建这个全局变量,使用没有初始化的全局变量会得到nil
--]]
print(b)  --使用没有初始化的全局变量
```

`lua hello.lua`

```
hello lua!
nil
```

# 数据类型

lua是动态类型语言,变量不要类型定义,只需要为变量赋值

| 数据类型 | 说明                                         |
| -------- | -------------------------------------------- |
| nil      | 表示一个无效值,作比较时加双引号              |
| boolean  | 类似c++中bool类型                            |
| number   | 表示双精度类型的实浮点数                     |
| string   | 字符串                                       |
| function | 由C或Lua编写的函数                           |
| userdata | 表示任意存储在变量中的C数据结构              |
| thread   | 表示执行的独立线路,用于执行协同程序          |
| table    | 关联数组,数组的索引可以是数字,字符串或表类型 |

可以使用type函数测试给定变量或者值的类型

```lua
print(type("Hello world"))      --> string
print(type(10.4*3))             --> number
print(type(print))              --> function
print(type(type))               --> function
print(type(true))               --> boolean
print(type(nil))                --> nil
print(type(type(X)))            --> string
```

**nil**

对于全局变量赋值一个nil值相当于删除此变量

同理,对于table表里的变量赋值nil也相当于删除

**boolean**

boolean类型只有两个可选值,true和false

lua把false和nil看作false

其余的都是true,数字0也是true

**number**

lua默认只有一种number类型即double双精度类型

所以任意数字的type都是number类型

**string**

字符串由一对双引号或单引号来表示

也可以用2个`[[]]`来表示一块字符串

在对一个数字字符串上进行算术操作时，Lua 会尝试将这个数字字符串转成一个数字

使用 `..`来连接字符串

```lua
> print("a" .. 'b')
ab
> print(123 .. 456)
123456
```

使用`#`计算字符串的长度

```lua
> str="hello lua"
> print(#str)
9
```

**table**

```lua
--local 定义局部变量
local tab1={} --空表
local tab2={'a','b','c','d'}  --直接初始化
```

```lua
--关联数组
arr={}
arr["key"]="value"
key=2
arr[key]=10
arr[key]=a[key]+10
for k,v in pairs(arr) do
    print(k .. ":" .. v)
end
```

```
key : value
2 : 20
```

lua表的默认初始索引为1开始

table不会固定长度大小,有新数据添加时table长度会自动增长,没初始的table都是nil

**function**

```lua
function swp(a,b)
    tmp=a
    a=b
    b=tmp
    print(a)
    print(b)
end
a=10
b=15
swp(a,b)
```

# 变量

