cmake_minimum_required(VERSION 3.14)

project(cpt CXX)

add_subdirectory(cptpp)
add_subdirectory(libcpt)

include(GNUInstallDirs)
install(TARGETS cpt PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libcpt)
install(TARGETS cptpp RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
# install(EXPORT cptConfig NAMESPACE cpt:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
