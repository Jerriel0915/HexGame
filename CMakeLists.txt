# CMakeList.txt: HexGame 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("HexGame")

# 将源代码添加到此项目的可执行文件。
add_executable (HexGame "src/mainApp.cpp"  "include/Board.h" "include/GLOBAL.h" "include/HexGame.h" "include/HexRecord.h" "src/Board.cpp" "src/HexGame.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HexGame PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
