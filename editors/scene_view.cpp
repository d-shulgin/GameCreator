#include "scene_view.h"
#include "ui_scene_view.h"

#include <QKeyEvent>

SceneView::SceneView(QWidget *parent, const QRect* size) :
    QWidget(parent),
    ui(new Ui::SceneView)
{
    ui->setupUi(this);
    setMinimumSize(size->width(), size->height());
    _render = new Render( this );
}

SceneView::~SceneView()
{
    delete ui;
}

void SceneView::test_save()
{
    if( 0 == _render )
        return;
    QDomDocument xml;
    QDomElement el_root = xml.createElement("object");
    xml.appendChild( el_root );
    el_root.setAttribute( XMLWord(XMLID::_class).to_string(), _render -> get_scene() -> xml_class_name() );
    _render -> get_scene() -> Save( xml, el_root );

    QDir path( QDir::current() );
    path.cd( "data" ); /// @todo: tmp
    QFile file( path.filePath("scene.xml") );
    if( file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
    {
        const int INDENT_SIZE = 4;
        QTextStream out( &file );
        xml.save( out, INDENT_SIZE );
        file.close();
    }
    return;
}

