# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (ResPiClint)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS}  -O0 -Wall -fpermissive")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -fpermissive")

set(OpenCV_DIR /usr/loacl/lib)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


#添加头文件路径
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${OpenCV_INCLUDE_DIRS})

# 查找当前目录下的所有源文件
#aux_source_directory(dir VAR)发现一个目录下所有的源代码文件并将列表存储在一个变量中
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./src DIR_SRCS)
# 指定生成目标
add_executable(ResPiClint ${DIR_SRCS})
target_link_libraries (ResPiClint ${OpenCV_LIBS})
target_link_libraries (ResPiClint pthread)
