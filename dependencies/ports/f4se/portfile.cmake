vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
        FEATURES
        "plugin"              BUILD_PLUGIN
        "scripts"             INSTALL_SCRIPTS
        "internal-xbyak"      INSTALL_INTERNAL_XBYAK
        )

if (BUILD_PLUGIN)
  if (VCPKG_LIBRARY_LINKAGE STREQUAL dynamic)
    message(WARNING "Warning: SKSE only supports static linkage, overriding setting.")
  endif ()
  if (VCPKG_CRT_LINKAGE STREQUAL dyanmic)
    message(WARNING "Warning: SKSE only supports static linkage against CRT, overriding setting.")
  endif ()
  set(VCPKG_LIBRARY_LINKAGE static)
  set(VCPKG_CRT_LINKAGE static)

  vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO ianpatt/f4se
    REF 1523c6beca93273d69dba48cde1b0c16c33baa90 # the git commit at tag v0.6.23 has a typo in the cmake files, it is fixed on master but not released yet.
    SHA512 9ee708950927adda7e8b9ec2f0cae94f47097f8a276e3560cf3a1dfe88125593469c61f45b4094960d33a5020cabf61d629331b7728a1cb5a04cba92f8e2fc56
    HEAD_REF master
  )

  vcpkg_configure_cmake(
    SOURCE_PATH "${SOURCE_PATH}"
    PREFER_NINJA
  )

  vcpkg_install_cmake()
  vcpkg_copy_pdbs()
  vcpkg_cmake_config_fixup(
    PACKAGE_NAME f4se
    CONFIG_PATH "lib/cmake/f4se"
  )

  file(
    INSTALL "${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-dbg/f4se/f4se-config.cmake"
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/f4se"
  )

  file(GLOB F4SE_CMAKE_FILES
    "${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-*/f4se/CMakeFiles/Export/**/*.cmake"
  )
  file(
    INSTALL ${F4SE_CMAKE_FILES}
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/f4se"
  )

  file(GLOB F4SE_COMMON_CMAKE_FILES
    "${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-*/f4se_common/CMakeFiles/Export/**/*.cmake"
  )
  file(
    INSTALL ${F4SE_CMAKE_FILES}
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/f4se_common"
  )

  file(GLOB F4SE_LOADER_COMMON_CMAKE_FILES
  "${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-*/f4se_loader/f4se_loader_common/CMakeFiles/Export/**/*.cmake"
  )
  file(
    INSTALL ${F4SE_LOADER_COMMON_CMAKE_FILES}
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/f4se_loader_common"
  )

  if (NOT INSTALL_INTERNAL_XBYAK)
    file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/include/xbyak")
    file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/share/xbyak")
  endif()
  file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
  file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share")

endif()

if (INSTALL_SCRIPTS)
  vcpkg_download_distfile(F4SE_DISTRO
    URLS "https://f4se.silverlock.org/beta/f4se_0_06_23.7z"
    FILENAME f4se_0_6_23.zip
    SHA512 a35460b3ede4e626d6e93e70f84c455cac802550cfbedb5a520f569f7d147c8eb4ce2f4402a8b88e31591e076d09cee0869d44ee28fb96ffd2836f95af6e8bf4
  )

  vcpkg_extract_source_archive(
      "${F4SE_DISTRO}"
  )

  file(GLOB F4SE_SCRIPTS
    "${CURRENT_BUILDTREES_DIR}/src/f4se_0_06_23/Data/Scripts/Source/*.psc"
  )

  file(COPY ${F4SE_SCRIPTS}
       DESTINATION "${CURRENT_PACKAGES_DIR}/contrib/papyrus/f4se"
  )

endif()
