find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARY NAMES gmp)
find_library(GMPXX_LIBRARY NAMES gmpxx)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMP DEFAULT_MSG GMP_LIBRARY GMP_INCLUDE_DIR)

if(GMP_FOUND)
    set(GMP_INCLUDE_DIRS ${GMP_INCLUDE_DIR})

    if(NOT TARGET gmp::gmp)
        add_library(gmp::gmp UNKNOWN IMPORTED)
        set_target_properties(
            gmp::gmp
            PROPERTIES
                IMPORTED_LOCATION "${GMP_LIBRARY}"
                INTERFACE_INCLUDE_DIRECTORIES "${GMP_INCLUDE_DIR}"
        )
    endif()

    set(GMP_LIBRARIES gmp::gmp)

    if(GMPXX_LIBRARY)
        if(NOT TARGET gmp::gmpxx)
            add_library(gmp::gmpxx UNKNOWN IMPORTED)
            set_target_properties(
                gmp::gmpxx
                PROPERTIES
                    IMPORTED_LOCATION "${GMPXX_LIBRARY}"
                    INTERFACE_INCLUDE_DIRECTORIES "${GMP_INCLUDE_DIR}"
                    INTERFACE_LINK_LIBRARIES gmp::gmp
            )
        endif()
        list(APPEND GMP_LIBRARIES gmp::gmpxx)
    endif()
endif()
