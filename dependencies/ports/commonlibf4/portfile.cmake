vcpkg_from_github(
  OUT_SOURCE_PATH SOURCE_PATH
  REPO nikitalita/CommonLibF4
  REF eef6972d698dbd93545f807e25c1f2370feb0a9d
  SHA512 ad5753514479d3c7b7a76ff7d8a509a84026f91c74303be9261d0a5830d84ab2f92d135f13cfce308063c5c6e20704e7264c04776a77674c617ebe749066f63d
  HEAD_REF master
)
     
#set(SOURCE_PATH "C:\\Users\\Nikita\\Workspace\\skyrim-mod-workspace\\CommonLibF4-merge-ws\\CommonLibF4")

if ( VCPKG_HOST_IS_WINDOWS AND VCPKG_TARGET_IS_WINDOWS AND NOT VCPKG_TARGET_IS_MINGW AND DEFINED $ENV{VisualStudioVersion} )
  set( MSVC_RUNTIME_VCPKG_CONFIG_ARG "-DCMAKE_MSVC_RUNTIME_LIBRARY=\"MultiThreaded$<$<CONFIG:Debug>:Debug>DLL\"")
  # 2022 requires `/external:anglebrackets` to build with the above argument
  if ( $ENV{VisualStudioVersion} STREQUAL "17.0")
    set( CXX_FLAGS_VCPKG_CONFIG_ARG "-DCMAKE_CXX_FLAGS=\"/EHsc /MP /W4 /WX /external:anglebrackets /external:W0\"")
  else()
    set( CXX_FLAGS_VCPKG_CONFIG_ARG "-DCMAKE_CXX_FLAGS=\"/EHsc /MP /W4 /WX /external:W0\"")
  endif()  
else()
  set( MSVC_RUNTIME_VCPKG_CONFIG_ARG "")
  set( CXX_FLAGS_VCPKG_CONFIG_ARG "")
endif()  

# set(MSVC_RUNTIME_ARG "Some Text")
vcpkg_configure_cmake(
  SOURCE_PATH "${SOURCE_PATH}"
  PREFER_NINJA
  OPTIONS
    -DVCPKG_OVERLAY_PORTS="${SOURCE_PATH}/cmake/ports/"
    -DBoost_USE_STATIC_LIBS=ON
    -DBoost_USE_STATIC_RUNTIME=OFF
    -DBoost_USE_STATIC_LIBS=ON
    -DF4SE_SUPPORT_XBYAK=ON
    -DCMAKE_EXE_LINKER_FLAGS_RELEASE="/DEBUG:FASTLINK"
    ${MSVC_RUNTIME_VCPKG_CONFIG_ARG}
    ${CXX_FLAGS_VCPKG_CONFIG_ARG}
)

vcpkg_install_cmake()
vcpkg_copy_pdbs()
vcpkg_cmake_config_fixup(     
  PACKAGE_NAME CommonLibF4   
  CONFIG_PATH "lib/cmake/CommonLibF4"   
)
file(GLOB CMAKE_CONFIGS "${CURRENT_PACKAGES_DIR}/share/CommonLibF4/CommonLibF4/*.cmake")
file(INSTALL ${CMAKE_CONFIGS} DESTINATION "${CURRENT_PACKAGES_DIR}/share/CommonLibF4")

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/share/CommonLibF4/CommonLibF4")
# file(MAKE_DIRECTORY "${CURRENT_PACKAGES_DIR}/include/CommonLibF4")  
# file(RENAME "${CURRENT_PACKAGES_DIR}/include/F4SE" "${CURRENT_PACKAGES_DIR}/include/CommonLibF4/F4SE")
# file(RENAME "${CURRENT_PACKAGES_DIR}/include/RE" "${CURRENT_PACKAGES_DIR}/include/CommonLibF4/RE")
# file(RENAME "${CURRENT_PACKAGES_DIR}/include/REL" "${CURRENT_PACKAGES_DIR}/include/CommonLibF4/REL")

file(
  INSTALL "${SOURCE_PATH}/LICENSE"
  DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
  RENAME copyright)
