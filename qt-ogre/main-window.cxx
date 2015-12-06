#include <qt-ogre/main-window.hxx>

#include <QCoreApplication>
#include <QTimer>
#include <QWheelEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

/**
 * The Main window layouts the window and transfers Qt signal to the Ogre renderer.
 */
MainWindow::MainWindow()
   : sample_(qPrintable(QCoreApplication::applicationDirPath()))
{
   setCentralWidget(createLayout());

   connect(&widget_, SIGNAL(showEventSignal(QShowEvent*)), SLOT(initializeSample()));
   connect(&widget_, SIGNAL(resizeEventSignal(QResizeEvent*)), SLOT(resizeOgre()));
   connect(&widget_, SIGNAL(wheelEventSignal(QWheelEvent*)), SLOT(zoomOgre(QWheelEvent*)));
   connect(&widget_, SIGNAL(mousePressEventSignal(QMouseEvent*)), SLOT(startDrag(QMouseEvent*)));
   connect(&widget_, SIGNAL(mouseMoveEventSignal(QMouseEvent*)), SLOT(dragOgre(QMouseEvent*)));

   createFrameUpdater();
}

QWidget * MainWindow::createLayout()
{
   QWidget* result = new QWidget(this);
   QVBoxLayout* layout = new QVBoxLayout();
   QLabel* title = new QLabel(tr("Here is an embedded Ogre window"), this);
   title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
   layout->addWidget(title);
   layout->addWidget(&widget_);
   QPushButton* resetButton = new QPushButton("Reset camera");
   connect(resetButton, SIGNAL(clicked(bool)), SLOT(resetOgreCamera()));
   layout->addWidget(resetButton);
   result->setLayout(layout);
   return result;
}

/**
 * Manually call the ogre renderer every frame.
 */
void MainWindow::createFrameUpdater()
{
   QTimer *timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(renderOgre()));
   timer->start(30);
}

void MainWindow::resetOgreCamera()
{
   sample_.resetCamera();
}

/**
 * This is where the magic happens.
 * When the widget has been displayed, it has an actual window handle, that we can
 * pass to Ogre.
 * Ogre will create its renderer window using this same handle.
 */
void MainWindow::initializeSample()
{
   sample_.initialize(widget_.getWinId(), widget_.width(), widget_.height());
}

/**
 * Render one ogre frame.
 */
void MainWindow::renderOgre()
{
   sample_.update();
}

void MainWindow::resizeOgre()
{
   sample_.resize(widget_.width(), widget_.height());
}

void MainWindow::zoomOgre(QWheelEvent* e)
{
   sample_.zoom(-e->delta() / 50.f);
}

void MainWindow::startDrag(QMouseEvent* e)
{
   dragPos_ = e->pos();
}

void MainWindow::dragOgre(QMouseEvent* e)
{
   float moveX = (dragPos_.x() - e->pos().x()) / widget_.width();
   float moveY = (dragPos_.y() - e->pos().y()) / widget_.height();
   sample_.moveCamera(moveX, moveY);
   dragPos_ = e->pos();
}
