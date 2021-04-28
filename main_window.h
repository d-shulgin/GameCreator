#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMdiArea>

#include "editors/scene_view.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMdiArea*   _area;

    void attachSceneView( QMdiArea*, const QString&, const QRect& );

private:
    SceneView* scene_view;

private slots:
    void on_actionSave_triggered();

//protected:
//    virtual void keyPressEvent( QKeyEvent* );
//    virtual void keyReleaseEvent( QKeyEvent* );
};

#endif // MAIN_WINDOW_H
