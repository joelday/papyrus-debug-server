vcpkg_from_github(
        OUT_SOURCE_PATH SOURCE_PATH
        REPO CharmedBaryon/CommonLibSSE
        REF d16f29f96841e42617785b935a9a1cbee98e2e88
        SHA512 f26a0624b59876e5e71c4da7c2472ed9e58d832f1a1153f7c776fe050f7b36da07fa710963cf2977cb92b56b078f10d0bacbf213b51aa0426c6e3f5dd4714dcd
        HEAD_REF main
)

vcpkg_configure_cmake(
        SOURCE_PATH "${SOURCE_PATH}"
        #PREFER_NINJA
        OPTIONS -DBUILD_TESTS=off -DSKSE_SUPPORT_XBYAK=on
)

vcpkg_install_cmake()
vcpkg_cmake_config_fixup(PACKAGE_NAME CommonLibSSE CONFIG_PATH lib/cmake)
vcpkg_copy_pdbs()

file(GLOB CMAKE_CONFIGS "${CURRENT_PACKAGES_DIR}/share/CommonLibSSE/CommonLibSSE/*.cmake")
file(INSTALL ${CMAKE_CONFIGS} DESTINATION "${CURRENT_PACKAGES_DIR}/share/CommonLibSSE")
file(INSTALL "${SOURCE_PATH}/cmake/CommonLibSSE.cmake" DESTINATION "${CURRENT_PACKAGES_DIR}/share/CommonLibSSE")

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/share/CommonLibSSE/CommonLibSSE")
file(MAKE_DIRECTORY "${CURRENT_PACKAGES_DIR}/include/CommonLibSSE")
file(RENAME "${CURRENT_PACKAGES_DIR}/include/SKSE" "${CURRENT_PACKAGES_DIR}/include/CommonLibSSE/SKSE")
file(RENAME "${CURRENT_PACKAGES_DIR}/include/RE" "${CURRENT_PACKAGES_DIR}/include/CommonLibSSE/RE")
file(RENAME "${CURRENT_PACKAGES_DIR}/include/REL" "${CURRENT_PACKAGES_DIR}/include/CommonLibSSE/REL")

file(
        INSTALL "${SOURCE_PATH}/LICENSE"
        DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
        RENAME copyright)
