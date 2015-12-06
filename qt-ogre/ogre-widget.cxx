#include "ogre-widget.hxx"

#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreCamera.h>

#include <QMoveEvent>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QWidget>

OgreWidget::OgreWidget(QWidget* parent/* = 0*/)
  : QWidget(parent)
{
  setAttribute(Qt::WA_OpaquePaintEvent);
  setAttribute(Qt::WA_PaintOnScreen);
  setFocusPolicy(Qt::StrongFocus);
}

void
OgreWidget::focusInEvent(QFocusEvent *e)
{
  Q_EMIT focusChanged(true);
}

void
OgreWidget::focusOutEvent(QFocusEvent *e)
{
  Q_EMIT focusChanged(false);
}

void
OgreWidget::keyPressEvent(QKeyEvent* e)
{
  Q_EMIT keyPressEventSignal(e);
}

QPaintEngine*
OgreWidget::paintEngine() const
{
  return 0;
}

void
OgreWidget::wheelEvent(QWheelEvent *e)
{
  Q_EMIT wheelEventSignal(e);
  e->accept();
}

void
OgreWidget::mousePressEvent(QMouseEvent* e)
{
  Q_EMIT mousePressEventSignal(e);
}

void
OgreWidget::mouseReleaseEvent(QMouseEvent* e)
{
  Q_EMIT mouseReleaseEventSignal(e);
}

void
OgreWidget::mouseMoveEvent(QMouseEvent* e)
{
  Q_EMIT mouseMoveEventSignal(e);
}

void
OgreWidget::keyReleaseEvent(QKeyEvent* e)
{
  Q_EMIT keyReleaseEventSignal(e);
}

void OgreWidget::showEvent(QShowEvent* e)
{
   Q_EMIT showEventSignal(e);
}

void OgreWidget::resizeEvent(QResizeEvent* e)
{
   Q_EMIT resizeEventSignal(e);
}
