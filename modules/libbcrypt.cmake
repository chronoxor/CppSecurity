if(NOT TARGET libbcrypt)

  # Module library
  file(GLOB SOURCE_FILES "libbcrypt/src/bcrypt.c" "libbcrypt/src/crypt_blowfish.c" "libbcrypt/src/crypt_gensalt.c" "libbcrypt/src/wrapper.c")
  if(MSVC)
    # C4005: 'identifier' : macro redefinition
    # C4013: 'function' undefined; assuming extern returning int
    # C4047: 'operator' : 'identifier1' differs in levels of indirection from 'identifier2'
    # C4067: unexpected tokens following preprocessor directive - expected a newline
    # C4101: 'identifier' : unreferenced local variable
    # C4244: 'conversion' conversion from 'type1' to 'type2', possible loss of data
    # C4267: 'var' : conversion from 'size_t' to 'type', possible loss of data
    set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} /wd4005 /wd4013 /wd4047 /wd4067 /wd4101 /wd4244 /wd4267")
  endif()
  add_library(libbcrypt ${SOURCE_FILES})
  if(MSVC)
    target_include_directories(libbcrypt PUBLIC "libbcrypt/include")
  elseif()
    target_include_directories(libbcrypt PUBLIC "libbcrypt/include/bcrypt")
  endif()

  # Module folder
  set_target_properties(libbcrypt PROPERTIES FOLDER modules/libbcrypt)

endif()
