if(NOT TARGET libbcrypt)

  # Module library
  file(GLOB SOURCE_FILES "libbcrypt/libbcrypt.c" "libbcrypt/crypt_blowfish/crypt_blowfish.c" "libbcrypt/crypt_blowfish/crypt_gensalt.c" "libbcrypt/crypt_blowfish/wrapper.c")
  if(MSVC)
    # C4244: 'conversion' conversion from 'type1' to 'type2', possible loss of data
    # C4267: 'var' : conversion from 'size_t' to 'type', possible loss of data
    # C4996: 'identifier': The POSIX name for this item is deprecated.
    set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} /wd4244 /wd4267 /wd4996")
  endif()
  add_library(libbcrypt ${SOURCE_FILES})
  target_include_directories(libbcrypt PUBLIC "libbcrypt")

  # Module folder
  set_target_properties(libbcrypt PROPERTIES FOLDER modules/libbcrypt)

endif()
