set(ROOT "${hpxio_SOURCE_DIR}/hpxio")

if(HPX_DEFAULT_BUILD_TARGETS)
  add_hpx_component(base_file
    FOLDER "Core/IO/Components"
    HEADER_ROOT ${ROOT}
    AUTOGLOB
    ESSENTIAL)
else()
  add_hpx_component(base_file
    FOLDER "Core/IO/Components"
    HEADER_ROOT ${ROOT}
    AUTOGLOB)
endif()

