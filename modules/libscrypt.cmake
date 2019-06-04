if(NOT TARGET libscrypt)

  # Module library
  file(GLOB SOURCE_FILES 
    "libscrypt/b64.c"
    "libscrypt/crypto-mcf.c"
    "libscrypt/crypto_scrypt-check.c"
    "libscrypt/crypto_scrypt-hash.c"
    "libscrypt/crypto_scrypt-nosse.c"
    "libscrypt/crypto-scrypt-saltgen.c"
    "libscrypt/sha256.c"
    "libscrypt/slowequals.c"
  )
  if(MSVC)
    # C4013: 'function' undefined; assuming extern returning int
    # C4131: 'function' : uses old-style declarator
    # C4244: 'conversion' conversion from 'type1' to 'type2', possible loss of data
    # C4245: 'conversion' : conversion from 'type1' to 'type2', signed/unsigned mismatch
    set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} /wd4013 /wd4131 /wd4244 /wd4245")
  endif()
  add_library(libscrypt ${SOURCE_FILES})
  target_include_directories(libscrypt PUBLIC "libscrypt")

  # Module folder
  set_target_properties(libscrypt PROPERTIES FOLDER modules/libscrypt)

endif()
