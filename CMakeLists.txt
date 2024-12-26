cmake_minimum_required(VERSION 3.10)
project(hotcalls VERSION 1.0.0)

# 设置安装前缀（如果没有指定，则使用 /usr/local）
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Installation prefix" FORCE)
endif()

# 包含 GNUInstallDirs
include(GNUInstallDirs)

set(CMAKE_C_COMPILER gcc CACHE STRING "C compiler")

# 编译选项
add_compile_options(-Wall -g -O3)
include_directories(${PROJECT_SOURCE_DIR}/include)

# 定义头文件列表
file(GLOB HOTCALLS_HEADERS
    "${PROJECT_SOURCE_DIR}/include/*.h"
)

# 构建共享库
add_library(hotcalls SHARED
    src/hotcalls.c
    src/spinlock.c
)

# 设置库的版本信息
set_target_properties(hotcalls PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# 构建测试程序
add_executable(hot_calls_test src/hot_calls_test.c)
target_link_libraries(hot_calls_test 
    hotcalls
    pthread
)

# 安装规则
install(TARGETS hotcalls
    COMPONENT runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}
)

install(FILES ${HOTCALLS_HEADERS}
    COMPONENT devel
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/hotcalls
)

install(TARGETS hot_calls_test
    COMPONENT runtime
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
)

# 设置组件
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_GROUPING ONE_PER_GROUP)
set(CPACK_COMPONENTS_ALL runtime devel)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

# 设置包名称
set(CPACK_PACKAGE_NAME "libhotcalls")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")

# 添加包维护者信息
set(CPACK_PACKAGE_CONTACT "DUNE Team <dune@example.com>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "DUNE Team <dune@example.com>")

# 设置组件包名称
set(CPACK_DEBIAN_RUNTIME_PACKAGE_NAME "libhotcalls")
set(CPACK_DEBIAN_DEVEL_PACKAGE_NAME "libhotcalls-dev")

# 设置文件名格式
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-Linux")

# 设置包依赖
set(CPACK_DEBIAN_RUNTIME_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6)")
set(CPACK_DEBIAN_DEVEL_PACKAGE_DEPENDS "libhotcalls (= ${PROJECT_VERSION})")

# 设置包描述
set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "Hot Calls runtime library")
set(CPACK_COMPONENT_DEVEL_DESCRIPTION "Hot Calls development files")

# 确保生成独立的包
set(CPACK_COMPONENTS_ALL runtime devel)

# 确保运行包不包含头文件
set(CPACK_DEBIAN_RUNTIME_PACKAGE_CONFLICTS "libhotcalls-dev (<< ${PROJECT_VERSION})")
set(CPACK_DEBIAN_DEVEL_PACKAGE_DEPENDS "libhotcalls (= ${PROJECT_VERSION})")

# 包含 CPack
include(CPack)