# CMakeList.txt: Network_Assistant 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。

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

# 启用 Windows 资源编译器（用于 .rc 文件）
enable_language(RC)

# =============== Qt6 配置 ===============
# 告诉 CMake 在 D:\Qt\6.9.3\msvc2022_64 下查找 Qt6
set(CMAKE_PREFIX_PATH "D:/Qt/6.9.3/msvc2022_64" CACHE PATH "Qt6 安装路径")

# 查找 Qt6，需要 Core, Gui, Widgets 等模块
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
    Core5Compat
)


# =============== 可执行文件定义 ===============
# 添加可执行文件
# 包含：C++ 源文件、头文件、UI 文件
# 将源代码添加到此项目的可执行文件。
add_executable (Network_Assistant
 "main.cpp"
 "main_window.ui" "main_window.h" "main_window.cpp"
 "custom_widget/led_widget.h" "custom_widget/led_widget.cpp" 
 "custom_widget/toggle_button.h" "custom_widget/toggle_button.cpp"
 "custom_widget/debounced_spin_box.h" "custom_widget/debounced_spin_box.cpp"
 "custom_widget/notification_bubble.h" "custom_widget/notification_bubble.cpp"
 "custom_widget/notification_manager.h" "custom_widget/notification_manager.cpp"
 "custom_widget/auto_width_combobox.h" "custom_widget/auto_width_combobox.cpp"
 "sundry/sundry.h" "sundry/sundry.cpp" 
 "sundry/sundry_qt.h" "sundry/sundry_qt.cpp"
 "network_settings_box.h" "network_settings_box.cpp"
 "receive_settings_box.h" "receive_settings_box.cpp"
 "receive_widget.h" "receive_widget.cpp"
 "send_settings_box.h" "send_settings_box.cpp"
 "single_send_widget.ui" "single_send_widget.h" "single_send_widget.cpp"
 "multiple_send_widget.ui" "multiple_send_widget.h" "multiple_send_widget.cpp"
 "target_box.h" "target_box.cpp" 
 "global.h" "global.cpp"
 "app.rc"
 "icon.qrc"
     "custom_widget/scrollable_list_widget.cpp" "custom_widget/scrollable_list_widget.h" "custom_widget/editable_tabwidget.h" "custom_widget/editable_tabwidget.cpp")

# 显式将 CMake 自动生成文件的输出目录添加到包含路径
# 这有助于 IDE (如 VS) 的 IntelliSense 找到 ui_*.h 和 moc_*.cpp
target_include_directories(Network_Assistant PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/custom_widget"
    "${CMAKE_CURRENT_SOURCE_DIR}/sundry"
)

# =============== 启用 Qt 的自动处理 ===============
# 启用 Qt6 的自动 moc、uic、rcc 处理
# CMake 会自动检测 .h 中的 Q_OBJECT、.ui 文件、.qrc 文件并调用相应工具
set_target_properties(Network_Assistant PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# =============== 链接 Qt 库 ===============
# 将 Qt6 的 Core, Gui, Widgets 等链接到可执行文件
target_link_libraries(Network_Assistant PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Core5Compat
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Network_Assistant PROPERTY CXX_STANDARD 20)
endif()



set_target_properties(Network_Assistant PROPERTIES
    WIN32_EXECUTABLE OFF   # 是否隐藏控制台窗口
)
