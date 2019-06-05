if(NOT TARGET fastpbkdf2)

  # Module library
  file(GLOB SOURCE_FILES "fastpbkdf2/fastpbkdf2.c")
#  if(MSVC)
#    # C4244: 'conversion' conversion from 'type1' to 'type2', possible loss of data
#    # C4267: 'var' : conversion from 'size_t' to 'type', possible loss of data
#    # C4996: 'identifier': The POSIX name for this item is deprecated.
#    set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} /wd4244 /wd4267 /wd4996")
#  endif()
  add_library(fastpbkdf2 ${SOURCE_FILES})
  target_include_directories(fastpbkdf2 PUBLIC "fastpbkdf2" PUBLIC ${OPENSSL_INCLUDE_DIR})
  target_link_libraries(fastpbkdf2 ${OPENSSL_LIBRARIES})

  # Module folder
  set_target_properties(fastpbkdf2 PROPERTIES FOLDER modules/fastpbkdf2)

endif()
