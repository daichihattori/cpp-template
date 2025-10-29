include_guard(GLOBAL)

include(FindPackageHandleStandardArgs)

find_path(
    GMP_INCLUDE_DIR
    NAMES gmp.h
)

find_library(GMP_LIBRARY NAMES gmp)
find_library(GMPXX_LIBRARY NAMES gmpxx)

find_package_handle_standard_args(
    GMP
    REQUIRED_VARS GMP_LIBRARY GMP_INCLUDE_DIR
    HANDLE_COMPONENTS
)

if (NOT GMP_FOUND)
    message(FATAL_ERROR "GMP library not found. Set GMP_ROOT, CMAKE_PREFIX_PATH, or install GMP.")
endif()

mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARY)

if (NOT TARGET gmp::gmp)
    add_library(gmp::gmp UNKNOWN IMPORTED)
    set_target_properties(gmp::gmp PROPERTIES
        IMPORTED_LOCATION "${GMP_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${GMP_INCLUDE_DIR}"
    )
endif()

if (GMPXX_LIBRARY AND NOT TARGET gmp::gmpxx)
    add_library(gmp::gmpxx UNKNOWN IMPORTED)
    set_target_properties(gmp::gmpxx PROPERTIES
        IMPORTED_LOCATION "${GMPXX_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${GMP_INCLUDE_DIR}"
    )
    target_link_libraries(gmp::gmpxx INTERFACE gmp::gmp)
endif()
