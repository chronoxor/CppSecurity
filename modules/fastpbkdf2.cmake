if(NOT TARGET fastpbkdf2)

  # Module library
  file(GLOB SOURCE_FILES "fastpbkdf2/fastpbkdf2.c")
  add_library(fastpbkdf2 ${SOURCE_FILES})
  target_include_directories(fastpbkdf2 PUBLIC "fastpbkdf2" PUBLIC ${OPENSSL_INCLUDE_DIR})
  target_link_libraries(fastpbkdf2 ${OPENSSL_LIBRARIES})

  # Module folder
  set_target_properties(fastpbkdf2 PROPERTIES FOLDER modules/fastpbkdf2)

endif()
