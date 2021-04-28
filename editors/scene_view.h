#ifndef SCENE_VIEW_H
#define SCENE_VIEW_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "../render.h"


namespace Ui {
class SceneView;
}

class SceneView : public QWidget
{
    Q_OBJECT

public:
    explicit SceneView(QWidget *parent = 0, const QRect* = 0 );
    ~SceneView();

    void test_save();

private:
    Ui::SceneView *ui;
    Render* _render;

};

#endif // SCENE_VIEW_H
