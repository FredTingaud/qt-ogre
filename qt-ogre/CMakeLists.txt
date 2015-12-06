include_directories(..)
include_directories(${OGRE_INCLUDE_DIRS})

add_executable(qt-ogre
               main.cxx
               main-window.cxx
               main-window.hxx
               ogre-widget.cxx
               ogre-widget.hxx
               ogre-sample.cxx
               ogre-sample.hxx
               )

target_link_libraries(qt-ogre Qt5::Widgets ${OGRE_LIBRARIES})
