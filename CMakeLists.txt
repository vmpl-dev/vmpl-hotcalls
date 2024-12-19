cmake_minimum_required(VERSION 3.10)
project(hotcalls VERSION 1.0.0)

set(CMAKE_C_COMPILER gcc CACHE STRING "C compiler")

# 设置安装路径
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local/musl" CACHE PATH "Installation prefix" FORCE)
endif()

# 编译选项
add_compile_options(-Wall -g -O3)
include_directories(${PROJECT_SOURCE_DIR}/include)

# 配置头文件
configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/config.h.in
    ${PROJECT_SOURCE_DIR}/include/config.h
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
include(GNUInstallDirs)
install(TARGETS hotcalls
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(TARGETS hot_calls_test
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES include/hotcalls.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hotcalls
)

# CPack配置
set(CPACK_GENERATOR "TGZ;DEB")
set(CPACK_PACKAGE_NAME "libhotcalls")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Hot Calls Library")
set(CPACK_PACKAGE_CONTACT "mbs2021@163.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Benshan Mei")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")
set(CPACK_DEBIAN_PACKAGE_SECTION "libs")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
include(CPack)