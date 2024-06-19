add_library(cpt INTERFACE)

file(GLOB LIBCPT_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/libcpt/*.hpp)
set_target_properties(cpt PROPERTIES PUBLIC_HEADER "${LIBCPT_INCLUDES}")
