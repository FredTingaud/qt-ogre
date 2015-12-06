#pragma once
#include <QWidget>

namespace Ogre
{
  class RenderWindow;
}

// Forward
class QPaintEngine;
class QResizeEvent;
class QFocusEvent;
class QWheelEvent;
class QMouseEvent;

class OgreWidget
  : public QWidget
{
  Q_OBJECT;
public:
  OgreWidget(QWidget* parent = 0);
  virtual ~OgreWidget() = default;

  inline HWND getWinId()
  {
    return (HWND)winId();
  }

protected:
  virtual QPaintEngine* paintEngine() const override;
  virtual void focusInEvent(QFocusEvent *e) override;
  virtual void focusOutEvent(QFocusEvent *e) override;

  virtual void wheelEvent(QWheelEvent* e) override;
  virtual void mousePressEvent(QMouseEvent* e) override;
  virtual void mouseReleaseEvent(QMouseEvent* e) override;
  virtual void mouseMoveEvent(QMouseEvent* e) override;
  virtual void keyPressEvent(QKeyEvent* e) override;
  virtual void keyReleaseEvent(QKeyEvent* e) override;
  virtual void showEvent(QShowEvent* e) override;
  virtual void resizeEvent(QResizeEvent* e) override;

  Q_SIGNAL void focusChanged(bool focused);
  Q_SIGNAL void wheelEventSignal(QWheelEvent* e);
  Q_SIGNAL void mousePressEventSignal(QMouseEvent* e);
  Q_SIGNAL void mouseReleaseEventSignal(QMouseEvent* e);
  Q_SIGNAL void mouseMoveEventSignal(QMouseEvent* e);
  Q_SIGNAL void keyPressEventSignal(QKeyEvent* e);
  Q_SIGNAL void keyReleaseEventSignal(QKeyEvent* e);
  Q_SIGNAL void showEventSignal(QShowEvent* e);
  Q_SIGNAL void resizeEventSignal(QResizeEvent* e);
};
