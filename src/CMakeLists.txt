set(ROOT "${hpxio_SOURCE_DIR}/hpxio")

if(HPX_DEFAULT_BUILD_TARGETS)
  add_hpx_component(base_file
    FOLDER "Core/Components"
    HEADER_ROOT ${ROOT}
    SOURCES base_file.cpp
    ESSENTIAL)
else()
  add_hpx_component(base_file
    FOLDER "Core/Components"
    HEADER_ROOT ${ROOT}
    SOURCES base_file.cpp
    )
endif()
