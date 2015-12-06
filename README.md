# Qt - Ogre

A sample code of the interfacing of Qt and Ogre under Windows.
An ogre scene is rendered in a QWidget of a Qt Application.
It is the kind of code I use to create the editors for my game Afro-Rangers.

## Dependencies
- Qt 5.x.x
- Ogre 1.9.x
- CMake 3.x.x

## Installation
Call CMake on the root CMakeLists, providing the path to Qt5 and Ogre.
In commande line, it might be something along the line of:

    cmake path/to/project -D Qt5Widgets_DIR=/path/to/qt5/lib/cmake/Qt5Widgets -D OGRE_INCLUDE_DIR=${PATH_TO_OGRE}/include/OGRE

Then call:

    make install
    make deploy-qt
