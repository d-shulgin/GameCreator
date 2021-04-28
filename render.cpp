#include "render.h"
#include <iostream>
#include <QTimerEvent>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QMouseEvent>

Render::Render( QWidget *parent )
    : QGLWidget( parent )
    , QGLFunctions()
    , _camera_ctrl( 0 )
    , _camera_speed( 0.250f )
    , _move_forward( false )
    , _move_backward( false )
    , _move_left( false )
    , _move_right( false )
    , _move_up( false )
    , _move_down( false )
    , _camera_rotate_on( false )
    , _camera_rotate_Z( false )
    , _mouse_left( false )
    // /////////////////////////////////// |
{
    setFocusPolicy( Qt::ClickFocus );
//    base_color = QColor(0, 0, 255);
    base_color = QColor(0, 0, 0);
    setGeometry( parent->geometry() );

    QGLFormat format = this->format();
    format.setSamples( 16 );
    format.setDepthBufferSize( 24 );
    format.setSwapInterval( 0 );
    setFormat( format );

    Engine::initialize();
    initDebug();

    // test quaternion  |
    {
        //    QVector3D up(0.0f, 1.0f, 0.0f);
        //    QVector3D direct( 0.0f, -1.0f, -1.0f );
        //    QQuaternion qr = QQuaternion::fromAxisAndAngle( up, 10.0f );
        //    QQuaternion ql = QQuaternion::fromAxisAndAngle( up, -10.0f );
        //    std::cout << std::endl;
        //    std::cout << std::endl;
        //    std::cout << std::endl;
        //    std::cout << "==========================================" << std::endl;
        //    std::cout << "Test direction vector:" << std::endl;
        //    for( int i = 0; i < 5; i++ )
        //    {
        //        direct.normalize();
        //        std::cout << "(" << direct.x() << "; " << direct.y() << "; " << direct.z() << ")" << std::endl;
        //        direct = qr.rotatedVector( direct );
        //    }
        //    direct.normalize();
        //    std::cout << "(" << direct.x() << "; " << direct.y() << "; " << direct.z() << ")" << std::endl;
        //    QVector3D right = QVector3D::crossProduct( direct, up );
        //    right.normalize();
        //    QQuaternion qt = QQuaternion::fromAxisAndAngle( right, -20.0f );
        //    std::cout << "right: (" << right.x() << "; " << right.y() << "; " << right.z() << ")" << std::endl;
        //    direct = qt.rotatedVector( direct );
        //    for( int i = 0; i < 5; ++i )
        //    {
        //        direct.normalize();
        //        direct = ql.rotatedVector( direct );
        //    }
        //    direct.normalize();
        //    right = QVector3D::crossProduct( direct, up );
        //    right.normalize();
        //    QQuaternion qb = QQuaternion::fromAxisAndAngle( right, 20.0f );
        //    std::cout << "right: (" << right.x() << "; " << right.y() << "; " << right.z() << ")" << std::endl;
        //    direct = qb.rotatedVector( direct );
        //    direct.normalize();
        //    std::cout << "result = (" << direct.x() << "; " << direct.y() << "; " << direct.z() << ")" << std::endl;
        //    std::cout << "==========================================" << std::endl;
        //    std::cout << std::endl;
        //    std::cout << std::endl;
        //    std::cout << std::endl;
    }
    // test read file   |
    {
        //    std::cout << "Test: read file...." << std::endl;
        //    QFile file( "://shaders/main.vsh" );
        //    if( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
        //    {
        //        QTextStream stream( &file );
        //        QString sources = stream.readAll();
        //        std::cout << sources.toStdString();
        //    }
        //    std::cout << "File end..." << std::endl;
    }
}
Render::~Render()
{
    RenderItem::meshLib().release( context()->functions() );
    RenderItem::fontLib().release( context()->functions() );
}


void Render::initializeGL()             // |
{
    initializeGLFunctions();
    qglClearColor( base_color );
    initShaders();
    loadTextures();
    loadFonts();
    loadMesh();

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    createTest2Scene();
    _scene.initialize( context() -> functions() );
    initDebugLayer();

    _timer.start( 10, this );
    return;
}
void Render::resizeGL( int w, int h )   // |
{
    glViewport( 0, 0, w, h );
    _scene.resize( w, h );
    return;
}
void Render::paintGL()                  // |
{
    _fps.update();
    if( !_fps.frames().empty() )
    {
        Text* fps = XMLObject::ptr_cast< Text >( _scene.dbg_layer()->getView( "fps_indicator" ));
        if( 0 != fps )
        {
            TextBlock* indicator = fps -> block(1);
            if( 0 != indicator )
                indicator -> setLetter( QString("%1").arg(static_cast<double>(_fps.frames().at(0)),0,'g',4) );
        }
    }

    _scene.prepareDraw();
    _scene.draw( context() -> functions() );
    //glFlush();
    glFinish();
    return;
}


/// @section: scenes ///////////// |
void Render::createTestScene()  // |
{
    _scene.addLayer( new LayerGUI() );
    // 2D scene
    {
        _scene.layer(0) -> addProgram( "shader: main" );
//        _scene.layer(0) -> addProgram( new LayerProgram("shader: main") );
        _scene.layer(0) -> addCamera( new Ortho(Resolution(1920, 1200)
                                                , 0.0f, 0.0f, 1920.0f, -1200.0, -1.0f, 1.0f) );
        Ortho* camera_1 = XMLObject::ptr_cast< Ortho >( _scene.layer(0) -> camera(0) );
        if( 0 != camera_1 )
        {
//            camera_1 -> addProgram( new CameraProgram("shader: main") );
            camera_1 -> addProgram( "shader: main" );
            camera_1 -> transform_Modify( Position(0.0f, 0.0f, -1.0f) );
        }
        _scene.layer(0) -> addView( new Sprite(1920.0f, 1200.0f, "img: background") );
        _scene.layer(0) -> addView( new Sprite(256.0f, 256.0f, "img: face", "face") );
        Sprite* sprite = XMLObject::ptr_cast< Sprite >( _scene.layer(0)->getView("face") );
        if( 0 != sprite )
            sprite -> transform_Modify( Position(100.0f, -100.0f, 0.0f) );
    }
    _scene.addLayer( new Layer3D() );
    // 3D scene
    {
        _scene.layer(1) -> addProgram( "shader: main" );
        _scene.layer(1) -> addProgram( "shader: sky_box" );
        _scene.layer(1) -> addProgram( "shader: model" );
//        _scene.layer(1) -> addProgram( new LayerProgram("shader: main") );
//        _scene.layer(1) -> addProgram( new LayerProgram("shader: sky_box") );
//        _scene.layer(1) -> addProgram( new LayerProgram("shader: model") );
        /// @note: perspective camera       |
        {
    //        _scene.layer(1) -> addCamera( new Perspective(Resolution(1920, 1200)
    //                                                      , Angle(63.435f * 1.00f, Angle::degrees_unit)) );
    //        Perspective* camera_2 = XMLObject::ptr_cast< Perspective >( _scene.layer(1) -> camera(0) );
    //        if( 0 != camera_2 )
    //        {
    //            camera_2 -> transform_Modify( Translate(0.0f, 0.0f, -200.0f));
    //            _camera_ctrl = static_cast<Camera*>( camera_2 );
    //        }
        }
        /// @note: eye perspective camera   |
        {
            _scene.layer(1) -> addCamera( new Eye(Resolution(1920, 1200)
                                                  // Angle(63.435f * 1.00f, Angle::degrees_unit)
                                                  , Angle(45.0f * 1.00f, Angle::degrees_unit)
                                                  , 0.10f, 2000.0f) );
            Eye* camera_2 = XMLObject::ptr_cast< Eye >( _scene.layer(1) -> camera(0) );
            if( 0 != camera_2 )
            {
//                camera_2 -> addProgram( new CameraProgram("shader: main") );
//                camera_2 -> addProgram( new CameraProgram("shader: sky_box") );
//                camera_2 -> addProgram( new CameraProgram("shader: model") );
                camera_2 -> addProgram( "shader: main" );
                camera_2 -> addProgram( "shader: sky_box" );
                camera_2 -> addProgram( "shader: model" );
                camera_2 -> translate( Vector3(0.0f, 0.0f, 200.0f) );
                _camera_ctrl = static_cast<Camera*>( camera_2 );
            }
        }
        _scene.layer(1) -> addView( new SkyBox("img: sky_box", "sky") );
        SkyBox* sky = XMLObject::ptr_cast< SkyBox >( _scene.layer(1)->getView("sky") );
        if( 0 != sky )
            sky -> setProgram( "shader: sky_box" );
        _scene.layer(1) -> addView( new Group("root") );
        Group* group_1 = XMLObject::ptr_cast< Group >( _scene.layer(1)->getView("root") );
        if( 0 != group_1 )
        {
            group_1 -> addChild( new Box(40.0f, 40.0f, 40.0f, "img: face", "box") );
            Box* box = XMLObject::ptr_cast< Box >( _scene.layer(1) -> getView("root.box") );
            if( 0 != box )
            {
                box -> transform_Modify( Position(0.0f, 0.0f, 0.0f) );
                box -> transform_Modify( Rotate(Angle(36.0f, Angle::degrees_unit)
                                                , Vector3(0.30f, 1.0f, 0.0f)) );
            }
            group_1 -> addChild( new Sprite(400.0f, 200.0f, "img: bricks", "quad(1)") );
            Sprite* sprite = XMLObject::ptr_cast< Sprite >( _scene.layer(1) -> getView("root.quad(1)") );
            if( 0 != sprite )
            {
                sprite -> transform_Modify( Position(-200.0f, +100.0f, -100.0f) );
                sprite -> transform_Modify( Rotate(Angle(0.0f, Angle::degrees_unit)
                                                   , Vector3(1.0f, 0.0f, 0.0f)) );
            }
            group_1 -> addChild( new Sprite(400.0f, 200.0f, "img: wood", "quad(2)") );
            sprite = XMLObject::ptr_cast< Sprite >( _scene.layer(1) -> getView("root.quad(2)") );
            if( 0 != sprite )
            {
                sprite -> transform_Modify( Position(-200.0f, -100.0f, -100.0f) );
                sprite -> transform_Modify( Rotate(Angle(-90.0f, Angle::degrees_unit)
                                                   , Vector3(1.0f, 0.0f, 0.0f)) );
            }

            group_1 -> addChild( new Model("://data/models/angel/Angel.obj", "angel") );
            Model* angel = XMLObject::ptr_cast< Model >( _scene.layer(1) -> getView("root.angel") );
            if( 0 != angel )
            {
                angel -> setProgram( "shader: model" );
                angel -> transform_Modify( Position(-90.0f, 0.0f, 0.0f) );
                angel -> transform_Modify( Scale(50.0f, 50.0f, 50.0f) );
            }

            group_1 -> addChild( new Model("D:/Projects/Games/GameCreator/data/models/sandy/Sandy.obj", "sandy") );
            Model* character = XMLObject::ptr_cast< Model >( _scene.layer(1) -> getView("root.sandy") );
            if( 0 != character )
            {
                character -> setProgram( "shader: model" );
                character -> transform_Modify( Position(-90.0f, 0.0f, -50.0f) );
                character -> transform_Modify( Scale(50.0f, 50.0f, 50.0f) );
            }

            group_1 -> addChild( new Model("D:/Projects/Games/GameCreator/data/models/StoneFort/StoneFort.obj", "house") );
            Model* house = XMLObject::ptr_cast< Model >( _scene.layer(1) -> getView("root.house") );
            if( 0 != house )
            {
                house -> setProgram( "shader: model" );
                house -> transform_Modify( Position(90.0f, 0.0f, 0.0f) );
                house -> transform_Modify( Scale(500.0f, 500.0f, 500.0f) );
            }

            group_1 -> addChild( new Model("D:/Projects/Games/GameCreator/data/models/cube/cube.obj", "test_cube") );
            Model* test = XMLObject::ptr_cast< Model >( _scene.layer(1) -> getView("root.test_cube") );
            if( 0 != test )
            {
                test -> setProgram( "shader: model" );
                test -> transform_Modify( Position(0.0f, 0.0f, 90.0f) );
                test -> transform_Modify( Scale(5.0f, 5.0f, 5.0f) );
            }

//            group_1 -> addChild( new Shape("://data/models/monkey.obj", "img: wood", "monkey") );
//            Shape* monkey = XMLObject::ptr_cast< Shape >( _scene.layer(1)->getView("root.monkey") );
//            if( 0 != monkey )
//            {
//                monkey -> transform_Modify( Position(90.0f, 0.0f, 0.0f) );
//                monkey -> transform_Modify( Scale(20.0f, 20.0f, 20.0f) );
//            }


//            group_1 -> addChild( new Shape("://data/models/angel/Angel.obj", "img: wood", "angel") );
//            Shape* angel = XMLObject::ptr_cast< Shape >( _scene.layer(1) -> getView("root.angel") );
//            if( 0 != angel )
//            {
//                angel -> transform_Modify( Position(-90.0f, 0.0f, 50.0f) );
//                angel -> transform_Modify( Scale(50.0f, 50.0f, 50.0f) );
//            }


//            group_1 -> addChild( new Shape("://data/models/loli/loli.obj", "img: wood", "loli") );
//            Shape* loli = XMLObject::ptr_cast< Shape >( _scene.layer(1) -> getView("root.loli") );
//            if( 0 != loli )
//            {
//                loli -> transform_Modify( Position(-90.0f, 0.0f, 100.0f) );
//                loli -> transform_Modify( Scale(0.50f, 0.50f, 0.50f) );
//            }
        }
        /// @note: lights
//        _scene.layer(1) -> addLight( new LightTMP() );
//        LightTMP* light = _scene.layer(1) -> light(0);
//        if( 0 != light )
//        {
//            light -> addProgram( new LightTMPProgram("shader: main") );
//            light -> addProgram( new LightTMPProgram("shader: model") );
//            light -> transform_Modify( Position(-50.0f, 100.0f, 200.0f));
//            light -> setPower( 2.30f );
//        }

        _scene.layer(1) -> addLight( new LightDirection() );
        LightDirection* light = XMLObject::ptr_cast< LightDirection >( _scene.layer(1) -> light(0) );
        if( 0 != light )
        {
            light -> addProgram( "shader: main" );
            light -> addProgram( "shader: model" );
//            light -> addProgram( new LightProgram("shader: main") );
//            light -> addProgram( new LightProgram("shader: model") );
            light -> setAmbientColor( Vector3(0.10f, 0.10f, 0.10f) );
            light -> setSpecularColor( Vector3(1.0f, 0.0f, 0.0f) );
            light -> setPower( 0.80f );
            light -> setDirection( Vector3(10.0f, -10.0f, -10.0f) );
        }

//        _scene.layer(1) -> addLight( new LightPoint() );
//        LightPoint* light = XMLObject::ptr_cast< LightPoint >( _scene.layer(1) -> light(0) );
//        if( 0 != light )
//        {
//            light -> addProgram( new LightProgram("shader: main") );
//            light -> addProgram( new LightProgram("shader: model") );
//            light -> setAmbientColor( Vector3(0.10f, 0.10f, 0.10f) );
//            light -> setPower( 2.30f );
//            light -> setPosition( Vector3(0.0f, 100.0f, 200.0f) );
//        }

        _scene.layer(1) -> addLight( new LightSpot() );
        LightSpot* spot = XMLObject::ptr_cast< LightSpot >( _scene.layer(1) -> light(1) );
        if( 0 != spot )
        {
            spot -> addProgram( "shader: main" );
            spot -> addProgram( "shader: model" );
//            spot -> addProgram( new LightProgram("shader: main") );
//            spot -> addProgram( new LightProgram("shader: model") );
            spot -> setAmbientColor( Vector3(0.10f, 0.10f, 0.10f) );
            spot -> setSpecularColor( Vector3(1.0f, 1.0f, 0.0f) );
            spot -> setDiffuseColor( Vector3(1.0f, 1.0f, 0.80f) );
            spot -> setPower( 2.30f );
            spot -> setPosition( Vector3(0.0f, 100.0f, 200.0f) );
            spot -> setDirection( Vector3(-20.0f, -100.0f, -200.0f) );
            spot -> setAngle( Angle(25.0f, Angle::degrees_unit) );
        }
    }
    return;
}
void Render::createTest2Scene() // |
{
    _scene.addLayer( new Layer3D() );
    _scene.layer(0) -> addProgram( "shader: main" );
    _scene.layer(0) -> addProgram( "shader: sky_box" );
    _scene.layer(0) -> addProgram( "shader: model" );
    _scene.layer(0) -> addProgram( "shader: font" );

    // camera...
    _scene.layer(0) -> addCamera( new Eye(Resolution(1920, 1200)
                                          , Angle(45.0f * 1.00f, Angle::degrees_unit)
                                          , 0.10f, 2000.0f) );
    Eye* camera = XMLObject::ptr_cast< Eye >( _scene.layer(0) -> camera(0) );
    if( 0 != camera )
    {
        camera -> addProgram( "shader: main" );
        camera -> addProgram( "shader: sky_box" );
        camera -> addProgram( "shader: model" );
        camera -> addProgram( "shader: font" );
        camera -> setPosition( Vector3(0.0f, 10.0f, 50.0f) );
        camera -> setTarget( Vector3(0.0f, 0.0f, 0.0f) );
        _camera_ctrl = static_cast<Camera*>( camera );
    }
    // sky box...
    _scene.layer(0) -> addView( new SkyBox("img: sky_box", "sky") );
    SkyBox* sky = XMLObject::ptr_cast< SkyBox >( _scene.layer(0)->getView("sky") );
    if( 0 != sky )
        sky -> setProgram( "shader: sky_box" );
    // land...
//    _scene.layer(0) -> addView( new Sprite(400.0f, 400.0f, "img: land", "land") );
//    Sprite* land = XMLObject::ptr_cast< Sprite >( _scene.layer(0) -> getView("land") );
//    if( 0 != land )
//    {
//        land -> transform_Modify( Position(-200.0f, 0.0f, -200.0f) );
//        land -> transform_Modify( Rotate(Angle(-90.0f, Angle::degrees_unit), Vector3(1.0f, 0.0f, 0.0f)) );
//        //land -> setShadow( false );
//    }


    // girl...
//    _scene.layer(0) -> addView( new Model("data/models/sandy/Sandy.obj", "girl") );
//    Model* girl = XMLObject::ptr_cast< Model >( _scene.layer(0)->getView("girl") );
//    if( 0 != girl )
//    {
//        girl -> setProgram( "shader: model" );
//        girl -> transform_Modify( Scale(10.0f, 10.0f, 10.0f) );
//        //girl -> setShadowEnable( true );
//        Vector3 v = girl -> getGlobalPos();
//        std::cout << "Girl: " << v.x() << "; " << v.y() << "; " << v.z() << std::endl;
//    }

    _scene.layer(0) -> addView( new ModelV2("mesh: box", "box") );
    ModelV2* box = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("box") );
    if( 0 != box )
    {
        box -> setProgram( "shader: model" );
        box -> transform_Modify( Scale(100.0f, 1.0f, 100.0f) );
        box -> transform_Modify( Position(0.0f, -1.0f, 0.0f) );
        box -> setShadowEnable( false );
        box -> setShadowFilter( View::ShadowFilter::PCF );
    }

    _scene.layer(0) -> addView( new ModelV2("mesh: plate", "face") );
    ModelV2* face = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("face") );
    if( 0 != face )
    {
        face -> setProgram( "shader: model" );
        face -> transform_Modify( Scale(1.0f, 1.0f, 1.0f) );
        face -> transform_Modify( Position(0.0, 10.0, 0.0) );
        face -> setShadowEnable( false );
        face -> setShadowFilter( View::ShadowFilter::PCF );
    }

    // test VBO
    _scene.layer(0) -> addView( new ModelV2("mesh: sandy", "snady#001") );
    ModelV2* sandy_1 = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("snady#001") );
    if( 0 != sandy_1 )
    {
        sandy_1 -> setProgram( "shader: model" );
        sandy_1 -> transform_Modify( Scale(6.0f, 6.0f, 6.0f) );
        sandy_1 -> transform_Modify( Rotate(Angle(15.0f, Angle::degrees_unit), Vector3(0.0f, 1.0f, 0.0f)) );
        sandy_1 -> transform_Modify( Position(-10.0f, 0.0f, -30.0f) );
        sandy_1 -> setShadowEnable( true );
        sandy_1 -> setShadowFilter( View::ShadowFilter::PCF );
    }
    /// more sandy |
    {
//        _scene.layer(0) -> addView( new ModelV2("mesh: sandy", "snady#002") );
//        ModelV2* sandy_2 = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("snady#002") );
//        if( 0 != sandy_2 )
//        {
//            sandy_2 -> setProgram( "shader: model" );
//            sandy_2 -> transform_Modify( Scale(6.0f, 6.0f, 6.0f) );
//            sandy_2 -> transform_Modify( Position(5.0f, 0.0f, -30.0f) );
//        }
//        _scene.layer(0) -> addView( new ModelV2("mesh: sandy", "snady#003") );
//        ModelV2* sandy_3 = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("snady#003") );
//        if( 0 != sandy_3 )
//        {
//            sandy_3 -> setProgram( "shader: model" );
//            sandy_3 -> transform_Modify( Scale(6.0f, 6.0f, 6.0f) );
//            sandy_3 -> transform_Modify( Position(10.0f, 0.0f, -30.0f) );
//        }
//        _scene.layer(0) -> addView( new ModelV2("mesh: sandy", "snady#004") );
//        ModelV2* sandy_4 = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("snady#004") );
//        if( 0 != sandy_4 )
//        {
//            sandy_4 -> setProgram( "shader: model" );
//            sandy_4 -> transform_Modify( Scale(6.0f, 6.0f, 6.0f) );
//            sandy_4 -> transform_Modify( Position(15.0f, 0.0f, -30.0f) );
//        }
//        _scene.layer(0) -> addView( new ModelV2("mesh: sandy", "snady#005") );
//        ModelV2* sandy_5 = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("snady#005") );
//        if( 0 != sandy_5 )
//        {
//            sandy_5 -> setProgram( "shader: model" );
//            sandy_5 -> transform_Modify( Scale(6.0f, 6.0f, 6.0f) );
//            sandy_5 -> transform_Modify( Position(20.0f, 0.0f, -30.0f) );
//        }
//        _scene.layer(0) -> addView( new ModelV2("mesh: sandy", "snady#006") );
//        ModelV2* sandy_6 = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("snady#006") );
//        if( 0 != sandy_6 )
//        {
//            sandy_6 -> setProgram( "shader: model" );
//            sandy_6 -> transform_Modify( Scale(6.0f, 6.0f, 6.0f) );
//            sandy_6 -> transform_Modify( Position(25.0f, 0.0f, -30.0f) );
//        }
//        _scene.layer(0) -> addView( new ModelV2("mesh: sandy", "snady#007") );
//        ModelV2* sandy_7 = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("snady#007") );
//        if( 0 != sandy_7 )
//        {
//            sandy_7 -> setProgram( "shader: model" );
//            sandy_7 -> transform_Modify( Scale(6.0f, 6.0f, 6.0f) );
//            sandy_7 -> transform_Modify( Position(30.0f, 0.0f, -30.0f) );
//        }
//        _scene.layer(0) -> addView( new ModelV2("mesh: sandy", "snady#008") );
//        ModelV2* sandy_8 = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("snady#008") );
//        if( 0 != sandy_8 )
//        {
//            sandy_8 -> setProgram( "shader: model" );
//            sandy_8 -> transform_Modify( Scale(6.0f, 6.0f, 6.0f) );
//            sandy_8 -> transform_Modify( Position(35.0f, 0.0f, -30.0f) );
//        }
//        _scene.layer(0) -> addView( new ModelV2("mesh: sandy", "snady#009") );
//        ModelV2* sandy_9 = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("snady#009") );
//        if( 0 != sandy_9 )
//        {
//            sandy_9 -> setProgram( "shader: model" );
//            sandy_9 -> transform_Modify( Scale(6.0f, 6.0f, 6.0f) );
//            sandy_9 -> transform_Modify( Position(40.0f, 0.0f, -30.0f) );
//        }
//        _scene.layer(0) -> addView( new ModelV2("mesh: sandy", "snady#010") );
//        ModelV2* sandy_10 = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("snady#010") );
//        if( 0 != sandy_10 )
//        {
//            sandy_10 -> setProgram( "shader: model" );
//            sandy_10 -> transform_Modify( Scale(6.0f, 6.0f, 6.0f) );
//            sandy_10 -> transform_Modify( Position(45.0f, 0.0f, -30.0f) );
//        }
    }
    // dog
    _scene.layer(0) -> addView( new ModelV2("mesh: dog", "dog") );
    ModelV2* dog = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0) -> getView("dog") );
    if( 0 != dog )
    {
        dog -> setProgram( "shader: model" );
        dog -> transform_Modify( Scale(10.0f, 10.0f, 10.0f) );
        dog -> transform_Modify( Rotate(Angle(15.0f, Angle::degrees_unit), Vector3(0.0f, 1.0f, 0.0f)) );
        dog -> transform_Modify( Position(-11.0f, 0.0f, -28.0f) );
        dog -> setShadowEnable( true );
        dog -> setShadowFilter( View::ShadowFilter::PCF );
    }
    // tree...
    _scene.layer(0) -> addView( new Group("group_of_trees") );
    Group* grp = XMLObject::ptr_cast< Group >( _scene.layer(0) -> getView("group_of_trees") );
    if( 0 != grp )
    {
        grp -> addChild( new ModelV2("mesh: tree", "tree") );
        ModelV2* tree = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0)->getView("group_of_trees.tree") );
        if( 0 != tree )
        {
            tree -> setProgram( "shader: model" );
            tree -> transform_Modify( Position(20.0f, 0.0f, 0.0f) );
            tree -> transform_Modify( Scale(3.0f, 3.0f, 3.0f) );
            tree -> setShadowEnable( true );
        }
        for( size_t i = 1; i <= 15; ++i )
        {
            QString name = QString("tree#%1").arg(i);
            std::cout << "Tree: " << name.toStdString() << std::endl;
            grp -> addChild( new ModelV2("mesh: tree", name) );
            ModelV2* tree = XMLObject::ptr_cast< ModelV2 >( _scene.layer(0)->getView(QString("group_of_trees.%1").arg(name)) );
            if( 0 != tree )
            {
                tree -> setProgram( "shader: model" );
                tree -> transform_Modify( Position((::rand()%10 - 5)*20.0f, 0.0f, (::rand()%10 - 5)*20.0f) );
                tree -> transform_Modify( Scale(3.0f, 3.0f, 3.0f) );
                tree -> transform_Modify( Rotate(Angle(::rand()%12*30.0f, Angle::degrees_unit), Vector3(0.0f, 1.0f, 0.0f)) );
                tree -> setShadowEnable( true );
            }
        }
    }
    /// @todo: test text
    _scene.layer(0) -> addView( new Text("text_example") );
    Text* fps = XMLObject::ptr_cast< Text >( _scene.layer(0) -> getView("text_example") );
    if( 0 != fps )
    {
        fps -> setProgram( "shader: font" );
        fps -> transform_Modify( Position(0.0f, 5.0f, 0.0f) );
        fps -> addBlock( new TextBlock("shader: font", "font: main", "Please, press ") );
        fps -> addBlock( new TextBlock("shader: font", "font: main", "SPACE") );
        fps -> addBlock( new TextBlock("shader: font", "font: main", " button to start new game.") );
        TextBlock* block = fps -> block(0);
        if( 0 != block )
            block -> setMaterial( "mtl: font_FPS" );
        block = fps -> block(1);
        if( 0 != block )
            block -> setMaterial( "mtl: font_FPS(blue)" );
        block = fps -> block(2);
        if( 0 != block )
            block -> setMaterial( "mtl: font_FPS" );
        fps -> setShadowEnable( false );
    }

    // light direction...
    _scene.layer(0) -> addLight( new LightDirection() );
    LightDirection* sun = XMLObject::ptr_cast< LightDirection >( _scene.layer(0)->light(0) );
    if( 0 != sun )
    {
        sun -> addProgram( "shader: main" );
        sun -> addProgram( "shader: model" );
        sun -> addProgram( "shader: font" );
        sun -> setAmbientColor( Vector3(0.30f, 0.30f, 0.30f) );
//        sun -> setDiffuseColor( Vector3(1.0f, 0.80f, 0.2f) );
//        sun -> setSpecularColor( Vector3(1.0f, 0.50f, 0.0f) );
        sun -> setPower( 1.20f );
        sun -> setDirection( Vector3(0.0f, -10.0f, -10.0f) );

        sun -> setShadow( new ShadowDirection("shader: shadow", Shadow::Quality::finest) );
        ShadowDirection* shadow = XMLObject::ptr_cast< ShadowDirection >( sun -> shadow() );
//        if( 0 != shadow )
//            shadow -> setTarget( "girl" );
        if( 0 != shadow && 0 != dog )
        {
            //shadow -> setActive( false );
            shadow -> setTarget( dog -> getGlobalPos() );
        }
    }
    return;
}
/// @section: shaders //////// |
void Render::initShaders()  // |
{
    RenderItem::programsMgr().add( new ProgramShader("shader: main"    ) );
    {
        ProgramShader* program = RenderItem::programsMgr().getProgram( "shader: main" );
        if( 0 != program )
        {
            program -> attach( new Shader(Shader::Type::vertex, "://shaders/main.vsh") );
            program -> attach( new Shader(Shader::Type::fragment, "://shaders/main.fsh") );
        }
    }
    RenderItem::programsMgr().add( new ProgramShader("shader: sky_box" ) );
    {
        ProgramShader* program = RenderItem::programsMgr().getProgram( "shader: sky_box" );
        if( 0 != program )
        {
            program -> attach( new Shader(Shader::Type::vertex, "://shaders/skybox.vsh") );
            program -> attach( new Shader(Shader::Type::fragment, "://shaders/skybox.fsh") );
        }
    }
    RenderItem::programsMgr().add( new ProgramShader("shader: model"   ) );
    {
        ProgramShader* program = RenderItem::programsMgr().getProgram( "shader: model" );
        if( 0 != program )
        {
            program -> attach( new Shader(Shader::Type::vertex, "://shaders/model.vsh") );
            program -> attach( new Shader(Shader::Type::fragment, "://shaders/model.fsh") );
        }
    }
    RenderItem::programsMgr().add( new ProgramShader("shader: shadow"  ) );
    {
        ProgramShader* program = RenderItem::programsMgr().getProgram( "shader: shadow" );
        if( 0 != program )
        {
            program -> attach( new Shader(Shader::Type::vertex, "://shaders/shadow.vsh") );
            program -> attach( new Shader(Shader::Type::fragment, "://shaders/shadow.fsh") );
        }
    }
    RenderItem::programsMgr().add( new ProgramShader("shader: depth"   ) );
    {
        ProgramShader* program = RenderItem::programsMgr().getProgram( "shader: depth" );
        if( 0 != program )
        {
            program -> attach( new Shader(Shader::Type::vertex, "://shaders/main.vsh") );
            program -> attach( new Shader(Shader::Type::fragment, "://shaders/depth.fsh") );
        }
    }
    RenderItem::programsMgr().add( new ProgramShader("shader: font_FPS") );
    {
        ProgramShader* program = RenderItem::programsMgr().getProgram( "shader: font_FPS" );
        if( 0 != program )
        {
            program -> attach( new Shader(Shader::Type::vertex, "://shaders/font/fps.vsh") );
            program -> attach( new Shader(Shader::Type::fragment, "://shaders/font/fps.fsh") );
        }
    }
    RenderItem::programsMgr().add( new ProgramShader("shader: font") );
    {
        ProgramShader* program = RenderItem::programsMgr().getProgram( "shader: font" );
        if( 0 != program )
        {
            program -> attach( new Shader(Shader::Type::vertex, "://shaders/font/main.vsh") );
            program -> attach( new Shader(Shader::Type::fragment, "://shaders/font/main.fsh") );
        }
    }
    RenderItem::programsMgr().compileAll( context()->functions() );
    return;
}
/// @section: textures /////// |
void Render::loadTextures() // |
{
    RenderItem::texturesMgr().load( "img: face",       "://data/face.png" );
    RenderItem::texturesMgr().load( "img: background", "://data/bgr.png" );
    RenderItem::texturesMgr().load( "img: land",       "data/grass.png" );
    RenderItem::texturesMgr().load( "img: mask_2x2",   "://data/mask_2x2.png" );
    RenderItem::texturesMgr().load( "img: wood",       "://data/wood.png" );
    RenderItem::texturesMgr().load( "img: bricks",     "://data/bricks_2.png" );
    RenderItem::texturesMgr().load( "img: sky_box",    "://data/sky/sky1_4096.png" );

    RenderItem::texturesMgr().load( "debug: mask_2x2",       "://data/mask_2x2.png" );
    RenderItem::texturesMgr().load( "debug: icon_camera",    "://data/debug/camera_icon1_128.png" );
    RenderItem::texturesMgr().load( "debug: icon_camera(Z)", "://data/debug/camera_icon2_128.png" );

    RenderItem::materialsMgr().addMaterial( new Material("mtl: font_FPS") );
    Material* font_FPS = RenderItem::materialsMgr().getMaterial("mtl: font_FPS");
    if( 0 != font_FPS )
    {
        font_FPS -> setAmbientColor( Vector3(1.0f, 1.0f, 1.0f) );
        font_FPS -> setDiffuseColor( Vector3(1.0f, 0.0f, 0.0f) );
        font_FPS -> setSpecularColor( Vector3(0.50f, 0.50f, 0.50f) );
        font_FPS -> setSpecularExponent( 100.0f );
        font_FPS -> setDissolve( 1.0f );
    }
    RenderItem::materialsMgr().addMaterial( new Material("mtl: font_FPS(blue)") );
    font_FPS = RenderItem::materialsMgr().getMaterial("mtl: font_FPS(blue)");
    if( 0 != font_FPS )
    {
        font_FPS -> setAmbientColor( Vector3(1.0f, 1.0f, 1.0f) );
        font_FPS -> setDiffuseColor( Vector3(0.0f, 0.0f, 1.0f) );
        font_FPS -> setSpecularColor( Vector3(0.50f, 0.50f, 0.50f) );
        font_FPS -> setSpecularExponent( 100.0f );
        font_FPS -> setDissolve( 1.0f );
    }
    // example  |
    {
        //    texture_sky = bindTexture( QImage("://data/sky/sky1_4096.png").mirrored() );
        //    std::cout << "texture_sky = " << texture_sky << std::endl;
        //    glActiveTexture( GL_TEXTURE0 );
        //    glBindTexture( GL_TEXTURE_2D, texture_sky );
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //    glBindTexture( GL_TEXTURE_2D, 0 );
    }
    return;
}
/// @section: fonts /////// |
void Render::loadFonts() // |
{
    RenderItem::fontLib().load( "font: FPS", "data/fonts/fps.xml" );
    RenderItem::fontLib().load( "font: main", "data/fonts/main.xml" );
    RenderItem::fontLib().upload( context() -> functions() );
}
/// @section: mesh //////// |
void Render::loadMesh()  // |
{
    RenderItem::meshLib().load( "mesh: cube",  "data/models/cube/cube.obj"   );
    RenderItem::meshLib().load( "mesh: sandy", "data/models/sandy/Sandy.obj" );
    RenderItem::meshLib().load( "mesh: tree",  "data/models/tree/tree.obj"   );
    RenderItem::meshLib().load( "mesh: dog",   "data/models/taksa/taksa.obj" );
    RenderItem::meshLib().load( "mesh: box",   "data/models/cube/cube.obj"   );
    RenderItem::meshLib().load( "mesh: plate", "data/models/plate/plate.obj" );
    RenderItem::meshLib().upload( context() -> functions() );
}
/// @section: debug ////////////////////////////// |
void Render::initDebug()                        // |
{
    cameraRotateEnable( false );
    cameraRotateZEnable( false );
    return;
}
void Render::initDebugLayer()                   // |
{
    _scene.attachDbgLayer( new LayerGUI() );
//    _scene.dbg_layer()->addProgram( new LayerProgram("shader: main") );
    _scene.dbg_layer()->addProgram( "shader: main" );
    _scene.dbg_layer()->addProgram( "shader: depth" );
    _scene.dbg_layer()->addProgram( "shader: font_FPS" );
    _scene.dbg_layer()->addCamera( new Ortho(Resolution(1920, 1200)
                                             , 0.0f, 0.0f, 1920.0f, -1200.0, -1.0f, 1.0f) );
    Ortho* camera_debug = XMLObject::ptr_cast< Ortho >( _scene.dbg_layer() -> camera(0) );
    if( 0 != camera_debug )
    {
//        camera_debug -> addProgram( new CameraProgram("shader: main") );
        camera_debug -> addProgram( "shader: main" );
        camera_debug -> addProgram( "shader: depth" );
        camera_debug -> addProgram( "shader: font_FPS" );
        camera_debug -> transform_Modify( Position(0.0f, 0.0f, -1.0f) );
    }
    // camera_active   |
    {
        _scene.dbg_layer()->addView( new Group("camera_active") );
        Group* camera_active = XMLObject::ptr_cast< Group >( _scene.dbg_layer()->getView("camera_active") );
        if( 0 != camera_active )
        {
            camera_active -> transform_Modify( Position(10.0f, -10.0f, 0.0f) );
            camera_active ->addChild( new Sprite(64, 64, "debug: mask_2x2", "CTRL") );
            camera_active ->addChild( new Sprite(64, 64, "debug: icon_camera") );
        }
        cameraRotateEnable( is_cameraRotateEnabled() );
    }
    // camera_rotate_Z |
    {
        _scene.dbg_layer()->addView( new Group("camera_rotate_Z") );
        Group* camera_rotate_Z = XMLObject::ptr_cast< Group >( _scene.dbg_layer()->getView("camera_rotate_Z") );
        if( 0 != camera_rotate_Z )
        {
            camera_rotate_Z -> transform_Modify( Position(10.0f + 64.0f + 5.0f, -10.0f, 0.0f) );
            camera_rotate_Z->addChild( new Sprite(64, 64, "debug: mask_2x2", "CTRL") );
            camera_rotate_Z->addChild( new Sprite(64, 64, "debug: icon_camera(Z)") );
        }
        cameraRotateZEnable( is_cameraRotateZOnly() );
    }
    // debug: show texture
    {
        GLuint shadowID = 0;
        LightDirection* sun = XMLObject::ptr_cast< LightDirection >( _scene.layer(0)->light(0) );
        if( 0 != sun )
        {
            ShadowDirection* shadow = XMLObject::ptr_cast< ShadowDirection >( sun -> shadow() );
            if( 0 != shadow )
                shadowID = shadow -> depthMap();
        }

        _scene.dbg_layer()->addView( new SpriteDbg(256, 256
                                                   //, RenderItem::texturesMgr().getPicture("img: face")->texture()
                                                   , shadowID
                                                   ,"showTexture") );
        SpriteDbg* sprite = XMLObject::ptr_cast< SpriteDbg >( _scene.dbg_layer()->getView("showTexture") );
        if( 0 != sprite )
        {
            sprite -> setProgram( "shader: depth" );
            sprite -> transform_Modify( Position(1920.0f - 10.0f - sprite->width(), -10.0f, 0.0f) );
        }
    }
    // debug: show FPS
    {
        _scene.dbg_layer() -> addView( new Text("fps_indicator") );
        Text* fps = XMLObject::ptr_cast< Text >( _scene.dbg_layer() -> getView("fps_indicator") );
        if( 0 != fps )
        {
            std::cout << "FPS counter show...." << std::endl;
            fps -> setProgram( "shader: font_FPS" );
            fps -> transform_Modify( Position(158.0f, -40.0f, 0.0f) );
            fps -> transform_Modify( Scale(40.0f, 40.0f, 1.0f) );
            fps -> addBlock( new TextBlock("shader: font_FPS", "font: FPS", "fps: ") );
            fps -> addBlock( new TextBlock("shader: font_FPS", "font: FPS", "200.00") );
            fps -> addBlock( new TextBlock("shader: font_FPS", "font: FPS", " frames") );
            TextBlock* block = fps -> block(0);
            if( 0 != block )
                block -> setMaterial( "mtl: font_FPS" );
            block = fps -> block(1);
            if( 0 != block )
                block -> setMaterial( "mtl: font_FPS(blue)" );
            block = fps -> block(2);
            if( 0 != block )
                block -> setMaterial( "mtl: font_FPS" );
            fps -> setShadowEnable( false );
        }
    }
    return;
}
void Render::cameraRotateEnable( bool enable )  // |
{
    _camera_rotate_on = enable;
    if( 0 != _scene.dbg_layer() )
    {
        Sprite* background = XMLObject::ptr_cast< Sprite >( _scene.dbg_layer()->getView("camera_active.CTRL") );
        if( 0 != background )
        {
            if( is_cameraRotateEnabled() )
                background -> setColor( Color(1.0f, 1.0f, 1.0f) );
            else
                background -> setColor( Color(0.40f, 0.40f, 0.40f) );
        }
    }
    return;
}
void Render::cameraRotateZEnable( bool enable ) // |
{
    _camera_rotate_Z = enable;
    if( 0 != _scene.dbg_layer() )
    {
        Sprite* background = XMLObject::ptr_cast< Sprite >( _scene.dbg_layer()->getView("camera_rotate_Z.CTRL") );
        if( 0 != background )
        {
            if( is_cameraRotateZOnly() )
                background -> setColor( Color(1.0f, 1.0f, 1.0f) );
            else
                background -> setColor( Color(0.40f, 0.40f, 0.40f) );
        }
    }
    return;
}
/// @section: events ///////////////////////////////////// |
void Render::focusInEvent( QFocusEvent* event )         // |
{
    grabKeyboard();
    QGLWidget::focusInEvent( event );
}
void Render::focusOutEvent( QFocusEvent* event )        // |
{
    releaseKeyboard();
    QGLWidget::focusOutEvent( event );
}
void Render::keyPressEvent( QKeyEvent* event )          // |
{
    if( event -> isAutoRepeat() )
        QGLWidget::keyPressEvent( event );
    else
    {
        switch ( event -> key() )
        {
        case Qt::Key_W:         // move: forward                    |
        {
            _move_forward  = true;
            _move_backward = false;
            break;
        }
        case Qt::Key_S:         // move: backward                   |
        {
            _move_forward = false;
            _move_backward = true;
            break;
        }
        case Qt::Key_A:         // move: left                       |
        {
            _move_left = true;
            _move_right = false;
            break;
        }
        case Qt::Key_D:         // move: right                      |
        {
            _move_left  = false;
            _move_right = true;
            break;
        }
        case Qt::Key_Space:     // move: up                         |
        {
            _move_up = true;
            _move_down = false;
            break;
        }
        case Qt::Key_C:         // move: down                       |
        {
            _move_up = false;
            _move_down = true;
            break;
        }
        case Qt::Key_Q:         // camera control (On/Off)          |
        {
            cameraRotateEnable( !is_cameraRotateEnabled() );
            cameraRotateZEnable( false );
            _mouse_left = false;
            if( is_cameraRotateEnabled() )
                grabMouse();
            else
                releaseMouse();
            break;
        }
        case Qt::Key_Control:   // camera Z-axis rotate (On/Off)    |
        {
            if( is_cameraRotateEnabled() )
            {
                cameraRotateZEnable( true );
            }
            break;
        }
        default:
            QGLWidget::keyPressEvent( event );
            break;
        }
    }
    return;
}
void Render::keyReleaseEvent( QKeyEvent* event )        // |
{
    if( event -> isAutoRepeat() )
        QGLWidget::keyPressEvent( event );
    else
    {
        switch ( event -> key() )
        {
        case Qt::Key_W:         // move: forward                    |
        {
            _move_forward = false;
            break;
        }
        case Qt::Key_S:         // move: backward                   |
        {
            _move_backward = false;
            break;
        }
        case Qt::Key_A:         // move: left                       |
        {
            _move_left = false;
            break;
        }
        case Qt::Key_D:         // move: right                      |
        {
            _move_right = false;
            break;
        }
        case Qt::Key_Space:     // move: up                         |
        {
            _move_up = false;
            break;
        }
        case Qt::Key_C:         // move: down                       |
        {
            _move_down = false;
            break;
        }
        case Qt::Key_Control:   // camera Z-axis rotate (On/Off)    |
        {
            if( is_cameraRotateEnabled() )
            {
                cameraRotateZEnable( false );
            }
            break;
        }
        default:
            QGLWidget::keyPressEvent( event );
            break;
        }
    }
    return;
}
void Render::mouseMoveEvent( QMouseEvent* event )       // |
{
    if( 0 != _camera_ctrl
            && is_cameraRotateEnabled()
            && _mouse_left )
    {
        QPointF delta = event -> localPos() - _mouse_left_pos;
        _mouse_left_pos = event -> localPos();

        Perspective* perspertive = XMLObject::ptr_cast< Perspective >( _camera_ctrl );
        if( 0 != perspertive )
        {

            QQuaternion quat_tb;
            QQuaternion quat_rl;
            QQuaternion quat_z;

            if( is_cameraRotateZOnly() )
            {
                Angle angle_z = Angle( delta.x()/4.0f, Angle::degrees_unit );
                quat_z = QQuaternion::fromAxisAndAngle( QVector3D(0.0f, 0.0f, 1.0f), angle_z.as_degrees() );
            }
            else
            {
//            Angle angle_y = Angle( delta.x()/4.0f, Angle::degrees_unit );
//            quat_rl = QQuaternion::fromAxisAndAngle( QVector3D(0.0f, 1.0f, 0.0f), angle_y.as_degrees() );
//            Angle angle_x = Angle( delta.y()/4.0f, Angle::degrees_unit );
//            quat_tb = QQuaternion::fromAxisAndAngle( quat_rl.rotatedVector( QVector3D(1.0f, 0.0f, 0.0f) ), angle_x.as_degrees() );

                Angle angle_x = Angle( delta.y()/4.0f, Angle::degrees_unit );
                quat_tb = QQuaternion::fromAxisAndAngle( QVector3D(1.0f, 0.0f, 0.0f), angle_x.as_degrees() );

                Angle angle_y = Angle( delta.x()/4.0f, Angle::degrees_unit );
                quat_rl = QQuaternion::fromAxisAndAngle( quat_tb.rotatedVector(QVector3D(0.0f, 1.0f, 0.0f)), angle_y.as_degrees() );
            }
            Transform tr = perspertive -> transform();
            QQuaternion quat = quat_z * quat_tb * quat_rl * tr.rotate().quat();
            perspertive -> transform_Modify( Rotate(quat) );

//            if( _scene.layer(1) != 0 )
//            {
//                Transform tr = _scene.layer(1)->camera(0)->transform();
//                //QQuaternion quat = quat_y * (quat_x * (quat_z * tr.rotate().quat()));
//                QQuaternion quat = quat_z * quat_tb * quat_rl * tr.rotate().quat();
//                _scene.layer(1)->camera(0)->transform_Modify( Rotate(quat) );
//            }
            update();
            event -> accept();
        }
        else
        {
            Eye* eye = XMLObject::ptr_cast< Eye >( _camera_ctrl );
            if( 0 != eye )
            {
                Angle angleH( delta.x()/4.0f, Angle::degrees_unit );
                Angle angleV( delta.y()/4.0f, Angle::degrees_unit );
                eye -> rotate( angleH, angleV );
            }
            else
                event -> ignore();
        }
    }
    else
        event -> ignore();
    return;
}
void Render::mousePressEvent( QMouseEvent* event )      // |
{
    if( is_cameraRotateEnabled() && event -> button() == Qt::LeftButton )
    {
        _mouse_left = true;
        _mouse_left_pos = event -> localPos();
        event -> accept();
    }
    else
        event -> ignore();

    return;
}
void Render::mouseReleaseEvent( QMouseEvent* event )    // |
{
    if( event -> button() == Qt::LeftButton )
    {
        _mouse_left = false;
        event -> accept();
    }
    else
        event -> ignore();
    return;
}
void Render::timerEvent( QTimerEvent* event )           // |
{
    if( 0 != _camera_ctrl )
    {
        Perspective* perspective = XMLObject::ptr_cast< Perspective >( _camera_ctrl );
        if( 0 != perspective )
        {
            if( is_move_forward() )
            {
                Transform tr0 = perspective -> transform();
                Transform tr;
                tr.setRotate( tr0.rotate() );
                QVector4D vec = QVector4D( 0.0f, 0.0f, +1.0f, 1.0f ) * tr.matrix();
                std::cout << "vec: " << vec.x() << "; " << vec.y() << "; " << vec.z() << std::endl;
                perspective -> transform_Modify( Position(tr0.position().x()+vec.x()
                                                           , tr0.position().y()+vec.y()
                                                           , tr0.position().z()+vec.z()) );
            }
            if( is_move_backward() )
            {
                Transform tr;
                tr.setRotate( perspective -> transform().rotate() );
                QVector4D vec = perspective -> transform().matrix() * QVector4D( 0.0f, 0.0f, -1.0f, 1.0f );
                perspective -> transform_Modify( Position(vec.x(), vec.y(), vec.z()) );
            }
        }
        else
        {
            Eye* eye = XMLObject::ptr_cast< Eye >( _camera_ctrl );
            if( 0 != eye )
            {
                if( is_move_forward()  )
                {
                    Vector3 move_to_forward = eye -> direction() * _camera_speed;
                    eye -> translate( move_to_forward );
                }
                if( is_move_backward() )
                {
                    Vector3 move_to_forward = eye -> direction() * -_camera_speed;
                    eye -> translate( move_to_forward );
                }
                if( is_move_right()    )
                {
                    Vector3 move_to_right = eye -> right() * _camera_speed;
                    eye -> translate( move_to_right );
                }
                if( is_move_left()     )
                {
                    Vector3 move_to_left = eye -> right() * -_camera_speed;
                    eye -> translate( move_to_left );
                }
                if( is_move_up()       )
                {
                    Vector3 move_to_up = eye -> up() * _camera_speed;
                    eye -> translate( move_to_up );
                }
                if( is_move_down()     )
                {
                    Vector3 move_to_down = eye -> up() * -_camera_speed;
                    eye -> translate( move_to_down );
                }
            }
        }
    }
    updateGL();
    event -> accept();
    return;
}

