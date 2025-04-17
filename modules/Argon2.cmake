if(NOT TARGET Argon2)

  # External packages
  find_package(Threads REQUIRED)

  # Module library
  file(GLOB SOURCE_FILES "Argon2/src/argon2.c" "Argon2/src/core.c" "Argon2/src/encoding.c" "Argon2/src/thread.c" "Argon2/src/blake2/blake2b.c")
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    file(GLOB SOURCE_PALTFORM_FILES "Argon2/src/ref.c")
  else()
    file(GLOB SOURCE_PALTFORM_FILES "Argon2/src/opt.c")
  endif()
  add_library(Argon2 ${SOURCE_FILES} ${SOURCE_PALTFORM_FILES})
  if(MSVC)
    # C4100: 'identifier' : unreferenced formal parameter
    # C4204: nonstandard extension used : non-constant aggregate initializer
    set_target_properties(Argon2 PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} /wd4100 /wd4204")
  else()
    set_target_properties(Argon2 PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
  endif()
  target_include_directories(Argon2 PUBLIC "Argon2/include")
  target_link_libraries(Argon2 Threads::Threads)

  # Module folder
  set_target_properties(Argon2 PROPERTIES FOLDER "modules/Argon2")

endif()
