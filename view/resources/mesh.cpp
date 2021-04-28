#include "mesh.h"
#include "../render_item.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>

Mesh::Mesh( const QString& namae
            , const QString& path )
    : XMLObject()
    , _modify( false )
    , _name( namae )
    , _filepath( path )
    , _VBO( 0 )
    // ///////////////////////////////////////// |
{
    bind_fields();
}
void Mesh::load( QGLFunctions* functions )    // |
{
    if( is_loaded() )
        return;
    if( !filepath().isEmpty() )
    {
        QFile file( filepath() );
        if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            std::cout << "[Mesh::load...] " << filepath().toStdString() << std::endl;

            Vertices vertices;
            std::vector< unsigned int > indices;

            QString name_obj;
            QString name_mtl;
            std::vector< QVector3D > coords;
            std::vector< QVector2D > UVcoords;
            std::vector< QVector3D > normals;

            QFileInfo info(file);
            QDir dir(info.path());
            QFileInfo info_mtl;

            unsigned int line = 0;
            QTextStream in( &file );
            while( !in.atEnd() )
            {
                QString str = in.readLine();
                if( str.isEmpty() )
                {
                    ++ line;
                    continue;
                }
                QStringList parts = str.split( " ", QString::SkipEmptyParts );
                QString key = parts.front();
                if      ( key == "#"      )
                {
                    if( parts.size() > 1 )
                        std::cout << str.toStdString() << std::endl;
                }
                else if ( key == "mtllib" )
                {
                    if( parts.size() > 1 )
                    {
                        info_mtl = QFileInfo( parts[1] );
                        RenderItem::materialsMgr().loadFileMtl( dir.filePath(info_mtl.fileName()) );
                    }
                    else
                        throw( Exception(Error::incorrect_material, QString("load... line: %1").arg(line)) );
                }
                else if ( key == "o"      )
                {
                    if( parts.size() > 1 )
                        name_obj = parts[1];
                    else
                        name_obj = "";
                    if( indices.size() > 0 )
                    {
                        addShape( new MeshShape(createEBO(functions, indices), indices.size(), name_mtl) );
                        indices.clear();
                    }
                }
                else if ( key == "v"      )
                {
                    float x = parts.size() > 1 ? parts[1].toFloat() : 0.0f;
                    float y = parts.size() > 2 ? parts[2].toFloat() : 0.0f;
                    float z = parts.size() > 3 ? parts[3].toFloat() : 0.0f;
                    coords.push_back( QVector3D(x, y, z) );
                }
                else if ( key == "vt"     )
                {
                    float u = parts.size() > 1 ? parts[1].toFloat() : 0.0f;
                    float v = parts.size() > 2 ? parts[2].toFloat() : 0.0f;
                    UVcoords.push_back( QVector2D(u, v) );
                }
                else if ( key == "vn"     )
                {
                    float x = parts.size() > 1 ? parts[1].toFloat() : 0.0f;
                    float y = parts.size() > 2 ? parts[2].toFloat() : 0.0f;
                    float z = parts.size() > 3 ? parts[3].toFloat() : 0.0f;
                    normals.push_back( QVector3D(x, y, z) );
                }
                else if ( key == "usemtl" )
                {
                    if( parts.size() > 1 )
                    {
                        if( indices.size() > 0 )
                        {
                            addShape( new MeshShape(createEBO(functions, indices), indices.size(), name_mtl) );
                            indices.clear();
                        }
                        name_mtl = QString("%1/%2").arg(info_mtl.baseName()).arg(parts[1]);
                    }
                    else
                        throw( Exception(Error::incorrect_material_name, QString("load... line: %1").arg(line)) );
                }
                else if ( key == "f"      )
                {
                    int index = vertices.count();
                    for( int i = 1; i < parts.size(); ++i )
                    {
                        QStringList number = parts[i].split( "/", QString::SkipEmptyParts );
                        size_t i1 = number.size() > 0 ? number[0].toUInt() - 1 : 0;
                        size_t i2 = number.size() > 1 ? number[1].toUInt() - 1 : 0;
                        size_t i3 = number.size() > 2 ? number[2].toUInt() - 1 : 0;
                        vertices << Vertex( coords[i1], UVcoords[i2], normals[i3], QVector4D(1.0f, 1.0f, 1.0f, 1.0f) );
                    }
                    Vector3 tangent, bitangent;
                    {
                        QVector3D p0 = vertices.position( index + 0 ).vec();
                        QVector3D p1 = vertices.position( index + 1 ).vec();
                        QVector3D p2 = vertices.position( index + 2 ).vec();

                        QVector2D uv0 = vertices.UVcoords( index + 0 );
                        QVector2D uv1 = vertices.UVcoords( index + 1 );
                        QVector2D uv2 = vertices.UVcoords( index + 2 );

                        QVector3D dp1 = p1 - p0;
                        QVector3D dp2 = p2 - p0;
                        QVector2D duv1 = uv1 - uv0;
                        QVector2D duv2 = uv2 - uv0;

                        float r = 1.0f / (duv1.x()*duv2.y() - duv1.y()*duv2.x());
                        tangent = Vector3( (dp1*duv2.y() - dp2*duv1.y())*r );
                        bitangent = Vector3( (dp2*duv1.x() - dp1*duv2.x())*r );
                    }
                    if      ( parts.size() == 4 ) // triangle |
                    {
                        indices.push_back( 2 + index );
                        indices.push_back( 1 + index );
                        indices.push_back( 0 + index );

                        vertices.setTangent( index + 0, tangent );
                        vertices.setTangent( index + 1, tangent );
                        vertices.setTangent( index + 2, tangent );
                        vertices.setBiTangent( index + 0, bitangent );
                        vertices.setBiTangent( index + 1, bitangent );
                        vertices.setBiTangent( index + 2, bitangent );
                    }
                    else if ( parts.size() == 5 ) // quad     |
                    {
                        indices.push_back( 2 + index );
                        indices.push_back( 1 + index );
                        indices.push_back( 0 + index );
                        indices.push_back( 3 + index );
                        indices.push_back( 1 + index );
                        indices.push_back( 2 + index );

                        vertices.setTangent( index + 0, tangent );
                        vertices.setTangent( index + 1, tangent );
                        vertices.setTangent( index + 2, tangent );
                        vertices.setTangent( index + 3, tangent );
                        vertices.setBiTangent( index + 0, bitangent );
                        vertices.setBiTangent( index + 1, bitangent );
                        vertices.setBiTangent( index + 2, bitangent );
                        vertices.setBiTangent( index + 3, bitangent );
                    }
                    else
                        throw( Exception(Error::incorrect_frame_structure, QString("load... line: %1").arg(line)) );
                }
                ++line;
            }
            if( indices.size() > 0 )
            {
                addShape( new MeshShape(createEBO(functions, indices), indices.size(), name_mtl) );
                indices.clear();
            }
            createVBO( functions, vertices );
            file.close();
        }
    }
    return;
}
void Mesh::release( QGLFunctions* functions ) // |
{
    if( 0 != functions )
    {
        if( 0 != _VBO )
        {
            functions -> glDeleteBuffers( 1, &_VBO );
            _VBO = 0;
        }
        for( size_t i = 0; i < shapes().count(); ++i )
        {
            MeshShape* shape = this -> shape(i);
            if( 0 != shape )
                shape -> release( functions );
        }
        _shapes.reset();
    }
    return;
}
bool Mesh::is_loaded() const                  // |
{
    return( 0 != _VBO && shapes().count() > 0 );
}
/// @section: name ///////////////////////// |
const QString& Mesh::name() const         // |
{
    return( _name );
}
void Mesh::setName( const QString& name ) // |
{
    _modify = _modify || (name != this -> name());
    _name = name;
    return;
}
/// @section: filepath ///////////////////////////// |
const QString& Mesh::filepath() const             // |
{
    return( _filepath );
}
void Mesh::setFilepath( const QString& filepath ) // |
{
    _modify = _modify || (filepath != this -> filepath());
    _filepath = filepath;
    return;
}
/// @section: VBO ///////////////////////////////////////////////////// |
void Mesh::createVBO( QGLFunctions* functions                        // |
                      , const Vertices& vertices )                   // |
{
    if( 0 != functions && 0 == _VBO )
    {
        functions -> glGenBuffers( 1, &_VBO );
        if( 0 != _VBO )
        {
            functions -> glBindBuffer( GL_ARRAY_BUFFER, _VBO );
            functions -> glBufferData( GL_ARRAY_BUFFER
                                       , sizeof(float)*vertices.buffer().size()
                                       , &vertices.buffer()[0]
                                       , GL_STATIC_DRAW );
            functions -> glBindBuffer( GL_ARRAY_BUFFER, 0 );
            std::cout << "[Mesh::createVBO...] VBO = " << _VBO << "; vertices = " << vertices.count() << "; buffer.size = " << vertices.buffer().size() << std::endl;
        }
        else
            throw( Exception(Error::incorrect_VBO, "createVBO") );
    }
    return;
}
GLuint Mesh::createEBO( QGLFunctions* functions                      // |
                        , const std::vector<unsigned int>& indices ) // |
{
    GLuint EBO = 0;
    if( 0 != functions )
    {
        functions -> glGenBuffers( 1, &EBO );
        if( 0 != EBO )
        {
            functions -> glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
            functions -> glBufferData( GL_ELEMENT_ARRAY_BUFFER
                                       , sizeof(unsigned int)*indices.size()
                                       , &indices[0]
                                       , GL_STATIC_DRAW );
            functions -> glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
            std::cout << "[Mesh::createEBO...] EBO = " << EBO << "; indices = " << indices.size() << std::endl;
            return( EBO );
        }
        else
            throw( Exception(Error::incorrect_EBO, "createEBO") );
    }
    return( EBO );
}
void Mesh::bind( QGLFunctions* functions ) const                     // |
{
    if( 0 != functions && 0 != _VBO )
    {
        functions -> glBindBuffer( GL_ARRAY_BUFFER, _VBO );
    }
    return;
}
void Mesh::unbind( QGLFunctions* functions ) const                   // |
{
    if( 0 != functions )
    {
        functions -> glBindBuffer( GL_ARRAY_BUFFER, 0 );
    }
    return;
}
/// @section: shapes ///////////////////// |
void Mesh::addShape( MeshShape* shape ) // |
{
    _shapes << static_cast< XMLObject* >( shape );
    return;
}
MeshShape* Mesh::shape( size_t index )  // |
{
    if( index < shapes().count() )
    {
        XMLObject* object = _shapes[index];
        if( 0 != object
                && object->xml_class_name().split(".", QString::SkipEmptyParts).contains(MeshShape::class_name()) )
        {
            return( static_cast<MeshShape*>(object) );
        }
    }
    return( 0 );
}
Mesh::~Mesh()
{
}


MeshShape::MeshShape(GLuint id
                     , GLsizei size
                     , const QString& mtl )
    : XMLObject()
    , _modify( false )
    , _EBO( id )
    , _material( mtl )
    , _size( size )
    // ////////////////////////////////////////////// |
{
    std::cout << "[MeshShape...] constructor: id = " << id << "; mtl = " << mtl.toStdString() << std::endl;
    bind_fields();
}
void MeshShape::release( QGLFunctions* functions ) // |
{
    if( 0 != functions && 0 != _EBO )
    {
        functions -> glDeleteBuffers( 1, &_EBO );
        _EBO = 0;
        _size = 0;
        _material.clear();
    }
    return;
}
/// @section: EBO //////////////////////////////////////// |
void MeshShape::bind( QGLFunctions* functions ) const   // |
{
    if( 0 != functions && 0 != _EBO )
    {
        functions -> glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _EBO );
    }
    return;
}
void MeshShape::unbind( QGLFunctions* functions ) const // |
{
    if( 0 != functions )
    {
        functions -> glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }
    return;
}
MeshShape::~MeshShape()
{
}

