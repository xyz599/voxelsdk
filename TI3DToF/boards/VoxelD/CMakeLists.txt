add_library(voxeld SHARED
  VoxelDCamera.cpp
  VoxelDCameraFactory.cpp
  ${COMMON_LIB_FILES}
)

set_voxel_library_output_directory(voxeld)

generate_export_header(voxeld
  EXPORT_FILE_NAME "SymbolExports.h"
  EXPORT_MACRO_NAME SYMBOL_EXPORT
)

target_link_libraries(voxeld 
  ti3dtof voxel ${COMMON_LIBS}
)

install(TARGETS voxeld
  LIBRARY DESTINATION lib/voxel COMPONENT ti3dtof
  ARCHIVE DESTINATION lib/voxel COMPONENT ti3dtof
  RUNTIME DESTINATION lib/voxel COMPONENT ti3dtof
)

list(APPEND CONF_FILES
  boards/VoxelD/VoxelDCamera.conf
  boards/VoxelD/VoxelDCameraNormal.conf
)

set(CONF_FILES "${CONF_FILES}" PARENT_SCOPE)

list(APPEND UDEV_FILES
  boards/VoxelD/72-VoxelD.rules
)

set(UDEV_FILES "${UDEV_FILES}" PARENT_SCOPE)

set_target_properties(voxeld PROPERTIES 
                      VERSION ${VOXEL_VERSION} 
                      SOVERSION ${VOXEL_ABI_VERSION})

