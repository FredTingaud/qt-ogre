#include <qt-ogre/main-window.hxx>
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // Ogre doesn't work correctly if the current dir is different from the application directory.
  QDir::setCurrent(QCoreApplication::applicationDirPath());

  MainWindow window;
  window.setVisible(true);
  return app.exec();
}
