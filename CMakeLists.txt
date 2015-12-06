project (qt-ogre)

cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

set(CMAKE_AUTOMOC ON)

# Create an "installer" folder in the target install folder.
# Set output in a "bin" subdirectory of this target folder.
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/installer)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_INSTALL_PREFIX}/bin)
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

find_package(Qt5Widgets REQUIRED)
find_package(OGRE REQUIRED)

add_subdirectory(qt-ogre)

if(WIN32)
  # Use classic main declaration and get rid of the console.
  set(QT_USE_QTMAIN TRUE)
  ADD_DEFINITIONS(-DQT_DLL)

  # Create a target called deploy-qt that automatically add all necessary qt files for distribution.
  get_target_property(QtCore_location Qt5::Core LOCATION)
  get_filename_component(QT_BIN ${QtCore_location} DIRECTORY)
  add_custom_target(deploy-qt set "PATH=%PATH%;${QT_BIN}"
                    COMMAND
                    ${QT_BIN}/windeployqt $<TARGET_FILE:qt-ogre>
                    )
endif(WIN32)

#Install necessary files to run the application
set(BINARIES_REL
  ${OGRE_BINARY_REL}
  ${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
  ${CMAKE_CURRENT_SOURCE_DIR}/resources/plugins.cfg
  )

set(BINARIES_DBG
  ${OGRE_BINARY_DBG}
  ${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
  ${CMAKE_CURRENT_SOURCE_DIR}/resources/plugins_d.cfg
  )

install(FILES
        ${BINARIES_REL}
        DESTINATION
        bin
        CONFIGURATIONS
        Release)

install(FILES
        ${BINARIES_DBG}
        DESTINATION
        bin
        CONFIGURATIONS
        Debug)
