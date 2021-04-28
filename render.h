#ifndef RENDER_H
#define RENDER_H

#include <QGLWidget>
#include <QGLFunctions>
#include <QMatrix4x4>
#include <QGLShaderProgram>
#include <QBasicTimer>
#include <QPointF>

#include "view/engine.h"
#include "utils/fps_counter.h"
//#include "view/painter_ctrl.h"

class Render : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    explicit Render(QWidget *parent = 0);
    virtual ~Render();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QColor base_color;

private: /// @section: scenes
    Scene _scene;
    void createTestScene();
    void createTest2Scene();

public:
    Scene* get_scene() { return( &_scene ); }

//private: /// @section: painter controller
//    PainterCtrl _painter;

private: /// @section: shaders
    void initShaders();
private: /// @section: textures
    void loadTextures();
private: /// @section: fonts
    void loadFonts();
private: /// @section: mesh
    void loadMesh();

private: /// @section: debug
    FPSCounter _fps;

    void initDebug();
    void initDebugLayer();

private:
    Camera* _camera_ctrl; /// @todo: error external pointer of internal object
    // move camera
    float _camera_speed;
    bool _move_forward;  // key: W
    bool _move_backward; // key: S
    bool _move_left;     // key: A
    bool _move_right;    // key: D
    bool _move_up;       // key: Space
    bool _move_down;     // key: C

    bool is_move_forward() const { return( _move_forward ); }
    bool is_move_backward() const { return( _move_backward ); }
    bool is_move_right() const { return( _move_right ); }
    bool is_move_left() const { return( _move_left ); }
    bool is_move_up() const { return( _move_up ); }
    bool is_move_down() const { return( _move_down ); }

private:
    // rotate camera
    bool _camera_rotate_on; // key: Q
    bool _camera_rotate_Z;  // key: Ctrl
    bool _mouse_left;       // activate rotate
    QPointF _mouse_left_pos;

    void cameraRotateEnable( bool );
    void cameraRotateZEnable( bool );
    bool is_cameraRotateEnabled() const { return(_camera_rotate_on); }
    bool is_cameraRotateZOnly() const { return(_camera_rotate_Z); }

protected: /// @section: events
    virtual void focusInEvent( QFocusEvent* );
    virtual void focusOutEvent( QFocusEvent* );
    virtual void keyPressEvent( QKeyEvent* );
    virtual void keyReleaseEvent( QKeyEvent* );
    virtual void mouseMoveEvent( QMouseEvent * );
    virtual void mousePressEvent( QMouseEvent * );
    virtual void mouseReleaseEvent( QMouseEvent * );

private:
    QBasicTimer _timer;

protected:
    void timerEvent( QTimerEvent* event );


signals:

public slots:
};

#endif // RENDER_H
