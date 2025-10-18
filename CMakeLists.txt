# CMakeList.txt: Network_Assistant 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.16)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# 设置项目名称
project ("Network_Assistant")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =============== Qt6 配置 ===============
# 告诉 CMake 在 D:\Qt\6.9.3\msvc2022_64 下查找 Qt6
set(CMAKE_PREFIX_PATH "D:/Qt/6.9.3/msvc2022_64" CACHE PATH "Qt6 安装路径")

# 查找 Qt6，需要 Core, Gui, Widgets 模块
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
)


# =============== 可执行文件定义 ===============
# 添加可执行文件
# 包含：C++ 源文件、头文件、UI 文件
# 将源代码添加到此项目的可执行文件。
add_executable (Network_Assistant
"main.cpp"
"main_window.ui"
"main_window.h"
"main_window.cpp"
 "led_widget.h" "led_widget.cpp")

# 显式将 CMake 自动生成文件的输出目录添加到包含路径
# 这有助于 IDE (如 VS) 的 IntelliSense 找到 ui_*.h 和 moc_*.cpp
target_include_directories(Network_Assistant PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_BINARY_DIR}"
)

# =============== 启用 Qt 的自动处理 ===============
# 这三行启用 Qt6 的自动 moc、uic、rcc 处理
# CMake 会自动检测 .h 中的 Q_OBJECT、.ui 文件、.qrc 文件并调用相应工具
set_target_properties(Network_Assistant PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# =============== 链接 Qt 库 ===============
# 将 Qt6 的 Core, Gui, Widgets 链接到你的可执行文件
target_link_libraries(Network_Assistant PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Network_Assistant PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
