cmake_minimum_required (VERSION 2.6)

find_package (PkgConfig REQUIRED)
pkg_search_module (VTE REQUIRED vte)
link_directories (${VTE_LIBRARY_DIRS})
include_directories (${VTE_INCLUDE_DIRS})

set (SCROLLBACK_LINES 10000)
set (WORD_CHARS "-A-Za-z0-9:./?%&#_=+@~")

set (SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable (tinyterm "${SOURCE_DIR}/tinyterm.c")
target_link_libraries (tinyterm ${VTE_LIBRARIES})

install (TARGETS tinyterm
    RUNTIME DESTINATION /usr/bin)

