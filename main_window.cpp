#include "main_window.h"
#include "ui_main_window.h"
#include <QKeyEvent>

#include "render.h"

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , scene_view( 0 )
{
    ui->setupUi(this);
    _area = new QMdiArea( this );
    _area -> setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    _area -> setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    setCentralWidget( _area );

    attachSceneView( _area, "scene1", QRect(0, 0, 1280, 800) );
}
void MainWindow::attachSceneView( QMdiArea* area
                                  , const QString& title
                                  , const QRect& size )
{
    scene_view = new SceneView( this, &size );
    area -> addSubWindow( scene_view );
    scene_view -> setWindowTitle( title );
}
void MainWindow::on_actionSave_triggered()
{
    if( 0 != scene_view )
        scene_view -> test_save();
}
//void MainWindow::keyPressEvent( QKeyEvent* event )
//{
//    if( event->key() == Qt::Key_W)
//        std::cout << "[MainWindow::keyPressEvent...] key W" << std::endl;
//    else
//        QMainWindow::keyPressEvent( event );
//    return;
//}
//void MainWindow::keyReleaseEvent( QKeyEvent* event )
//{
//    if( event->key() == Qt::Key_W)
//        std::cout << "[MainWindow::keyReleaseEvent...] key W" << std::endl;
//    else
//        QMainWindow::keyPressEvent( event );
//    return;
//}
MainWindow::~MainWindow()
{
    delete ui;
}
