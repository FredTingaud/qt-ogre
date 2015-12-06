#pragma once

#include <QMainWindow>

#include <qt-ogre/ogre-sample.hxx>
#include <qt-ogre/ogre-widget.hxx>

class MainWindow : public QMainWindow
{
   Q_OBJECT;

   using super = QMainWindow;

public:
   MainWindow();

protected:
   Q_SLOT void initializeSample();
   Q_SLOT void renderOgre();
   Q_SLOT void resizeOgre();
   Q_SLOT void zoomOgre(QWheelEvent* e);
   Q_SLOT void resetOgreCamera();
   Q_SLOT void startDrag(QMouseEvent* e);
   Q_SLOT void dragOgre(QMouseEvent* e);

private:
   void createFrameUpdater();
   QWidget * createLayout();

private:
   OgreWidget widget_;
   OgreSample sample_;
   QPointF dragPos_;
};
