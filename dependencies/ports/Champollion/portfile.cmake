vcpkg_from_github(
  OUT_SOURCE_PATH SOURCE_PATH
  REPO Orvid/Champollion
  REF 94b0e4db7f5f279a969da98e89ef79739fd4ac19
  SHA512 101f9d0d7171fb4d6f4ceb4221dfc55dda2442020762d189f29fa20194ac2b1c421331e151c7eef3f9e40055aba51d6c7976df639b2d5372170c156f85062ffd
  HEAD_REF master
)
# Check if one or more features are a part of a package installation.
# See /docs/maintainers/vcpkg_check_features.md for more details
vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
  INVERTED_FEATURES
	  standalone   CHAMPOLLION_STATIC_LIBRARY
)
vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
		OPTIONS
      ${FEATURE_OPTIONS}
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME Champollion CONFIG_PATH lib/cmake/Champollion)
file(
        INSTALL "${SOURCE_PATH}/LICENSE"
        DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
        RENAME copyright)
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
