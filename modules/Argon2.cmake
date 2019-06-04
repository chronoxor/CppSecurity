if(NOT TARGET Argon2)

  # Module library
  file(GLOB SOURCE_FILES "Argon2/src/argon2.c" "Argon2/src/core.c" "Argon2/src/encoding.c" "Argon2/src/opt.c" "Argon2/src/thread.c" "Argon2/src/blake2/blake2b.c")
  message(${SOURCE_FILES})
  if(MSVC)
    # C4100: unreferenced formal parameter
    # C4204: nonstandard extension used: non-constant aggregate initializer
    set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} /wd4100 /wd4204")
  else()
    set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} -Wno-format -Wno-implicit-function-declaration -Wno-incompatible-pointer-types")
  endif()
  add_library(Argon2 ${SOURCE_FILES})
  target_include_directories(Argon2 PUBLIC "Argon2/include")

  # Module folder
  set_target_properties(Argon2 PROPERTIES FOLDER modules/Argon2)

endif()
