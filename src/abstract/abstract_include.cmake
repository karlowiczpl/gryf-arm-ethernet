add_library(abstract_files STATIC)

target_sources(abstract_files PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/parser/parser.c
  ${CMAKE_CURRENT_LIST_DIR}/analyse/analyse.c
)

target_include_directories(abstract_files PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/parser
  ${CMAKE_CURRENT_LIST_DIR}/
  ${CMAKE_CURRENT_LIST_DIR}/analyse
)

