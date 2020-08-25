# 基本用法

```cmake
cmake_minimum_required (VERSION 2.8) #要求cmake最低的版本号
project (demo) # 定义当前工程名字
set(CMAKE_BUILD_TYPE "Debug")#设置debug模式，如果没有这一行将不能调试设断点
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
add_executable(main main.c)
#进入子目录下执行 CMakeLists.txt文件 这里的lib和tests里面都有可编译的代码文件
add_subdirectory(lib)
add_subdirectory(tests)
```

```cmake
cmake_minimum_required (VERSION 2.8)
project (demo)
aux_source_directory(. SRC_LIST) # 定义变量，存储当前目录下的所有源文件
add_executable(main ${SRC_LIST})
```

# 实践

```
bin  			存放最终的可执行文件
build			存放编译中间文件(cmake ..与make)
include			存放头文件
src				存放源代码文件
CMakeLists.txt		cmake语句
```

项目总目录下的`CMakeLists.txt`文件

```cmake
cmake_minimum_required(VERSION 3.0)
project(chat)

# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置最终的可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)#头文件
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)

include_directories(${PROJECT_SOURCE_DIR}/thirdparty)#第三方库

# 加载子目录
add_subdirectory(src)
```

子目录`src`下的`CMakeLists.txt`

```cmake
add_subdirectory(server)
add_subdirectory(client)
```

子目录`server`下的`CMakeLists.txt`

```cmake
# 定义了一个SRC_LIST变量，包含了该目录下所有的源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)

# 指定生成可执行文件
add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})
# 指定可执行文件链接时需要依赖的库文件
target_link_libraries(ChatServer muduo_net muduo_base mysqlclient hiredis pthread)
```

子目录`client`下的`CMakeLists.txt`

```cmake
# 定义了一个SRC_LIST变量，包含了该目录下所有的源文件
aux_source_directory(. SRC_LIST)

# 指定生成可执行文件
add_executable(ChatClient ${SRC_LIST})
# 指定可执行文件链接时需要依赖的库文件
target_link_libraries(ChatClient pthread)
```

```
CMake常用的预定义变量
PROJECT_NAME : 通过 project() 指定项目名称
PROJECT_SOURCE_DIR : 工程的根目录
PROJECT_BINARY_DIR : 执行 cmake 命令的目录
CMAKE_CURRENT_SOURCE_DIR : 当前 CMakeList.txt 文件所在的目录
CMAKE_CURRENT_BINARY_DIR : 编译目录，可使用 add subdirectory 来修改
EXECUTABLE_OUTPUT_PATH : 二进制可执行文件输出位置
LIBRARY_OUTPUT_PATH : 库文件输出位置
BUILD_SHARED_LIBS : 默认的库编译方式 ( shared 或 static ) ，默认为 static
CMAKE_C_FLAGS : 设置 C 编译选项
CMAKE_CXX_FLAGS : 设置 C++ 编译选项
CMAKE_CXX_FLAGS_DEBUG : 设置编译类型 Debug 时的编译选项
CMAKE_CXX_FLAGS_RELEASE : 设置编译类型 Release 时的编译选项
CMAKE_GENERATOR : 编译器名称
CMAKE_COMMAND : CMake 可执行文件本身的全路径
CMAKE_BUILD_TYPE : 工程编译生成的版本， Debug / Release
```

