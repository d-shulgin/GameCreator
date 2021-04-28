#include "font.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include "../render_item.h"

Font::Font( const QString& namae
            , const QString& path )
    : XMLObject()
    , _modify( false )
    , _name( namae )
    , _filepath( path )
    , _VBO( 0 )
    , _EBO( 0 )
    // ///////////////////////////////////////// |
{
    bind_fields();
}
void Font::load( QGLFunctions* functions )    // |
{
    if( is_loaded() )
        return;
    if( !filepath().isEmpty() )
    {
        QFile file( filepath() );
        if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            QDomDocument xml;
            QString error;
            int line = 0;
            int column = 0;
            if( xml.setContent(&file, &error, &line, &column) )
            {
                QDomElement root = xml.firstChildElement( "object" );
                if( !root.isNull() )
                {
                    _data.Load( root );
                }
            }
            if( _data.symbols().count() > 0 )
            {
                Vertices vertices;
                std::vector< unsigned int > indices;

                QFileInfo info( file );
                QDir dir( info.path() );
                _filepathPNG = dir.filePath( QString("%1.png").arg(info.baseName()) );
                std::cout << "filepathPNG: " << _filepathPNG.toStdString() << std::endl;
                Texture* texture = RenderItem::texturesMgr().getTexture( _filepathPNG );
                if( 0 == texture )
                    RenderItem::texturesMgr().addTexture( new Texture(_filepathPNG, true) );

//                UVcoords.push_back( QVector2D(0.0f, 0.0f) );
//                UVcoords.push_back( QVector2D(0.0f, 1.0f) );
//                UVcoords.push_back( QVector2D(1.0f, 0.0f) );
//                UVcoords.push_back( QVector2D(1.0f, 1.0f) );
//                normals.push_back( QVector3D(0.0f, 0.0f, 1.0f) );
//                coords.push_back( QVector3D(0.0f, 0.0f, 0.0f) ); // 0
                float divider = _data.ascent() + _data.descent();
                for( size_t i = 0; i < _data.symbols().count(); ++i )
                {
                    const CharData* symbol = _data.symbol( i );
                    float w = symbol -> width()  / divider;
                    float h = symbol -> height() / divider;

                    float tt = symbol -> texture().top();
                    float tl = symbol -> texture().left();
                    float tr = symbol -> texture().right();
                    float tb = symbol -> texture().bottom();

//                    coords.push_back( QVector3D(0.0f, -h, 0.0f) ); // 1; 4; 7 => 3*i + 1
//                    coords.push_back( QVector3D(w, 0.0f, 0.0f) );  // 2; 5; 8 => 3*i + 2
//                    coords.push_back( QVector3D(w, -h, 0.0f) );    // 3; 6; 9 => 3*i + 3

                    vertices << Vertex( QVector3D(w, 0.0f, 0.0f),    QVector2D(tr, tt), QVector3D(0.0f, 0.0f, 1.0f), QVector4D(1.0f, 1.0f, 1.0f, 1.0f) );
                    vertices << Vertex( QVector3D(0.0f, 0.0f, 0.0f), QVector2D(tl, tt), QVector3D(0.0f, 0.0f, 1.0f), QVector4D(1.0f, 1.0f, 1.0f, 1.0f) );
                    vertices << Vertex( QVector3D(0.0f, -h, 0.0f),   QVector2D(tl, tb), QVector3D(0.0f, 0.0f, 1.0f), QVector4D(1.0f, 1.0f, 1.0f, 1.0f) );
                    vertices << Vertex( QVector3D(w, -h, 0.0f),      QVector2D(tr, tb), QVector3D(0.0f, 0.0f, 1.0f), QVector4D(1.0f, 1.0f, 1.0f, 1.0f) );

                    indices.clear();
                    indices.push_back( 2 + i*4 );
                    indices.push_back( 1 + i*4 );
                    indices.push_back( 0 + i*4 );
                    indices.push_back( 3 + i*4 );
                    indices.push_back( 2 + i*4 );
                    indices.push_back( 0 + i*4 );
                    _characters << static_cast< XMLObject* >( new Char(symbol->code(), indices) );
                }
                createVBO( functions, vertices );
                createEBO( functions );
            }
            file.close();
        }

        // debug out
        {
            std::cout << "font... " << name().toStdString() << std::endl;
            std::cout << "name   : " << _data.name().toStdString() << std::endl;
            std::cout << "ascent : " << _data.ascent() << std::endl;
            std::cout << "descent: " << _data.descent() << std::endl;
            std::cout << "leading: " << _data.leading() << std::endl;
            std::cout << "symbols: (" << _data.symbols().count() << ")" << std::endl;
            for( size_t i = 0; i < _data.symbols().count(); ++i )
            {
                const CharData* symbol = _data.symbol(i);
                std::cout << "   '" << symbol -> code().toStdString() << "' -> advance: " << symbol -> advance() << std::endl;
            }
        }
    }
    return;
}
void Font::release( QGLFunctions* functions ) // |
{
    if( 0 != functions )
    {
        if( 0 != _VBO )
        {
            functions -> glDeleteBuffers( 1, &_VBO );
            _VBO = 0;
        }
        if( 0 != _EBO )
        {
            functions -> glDeleteBuffers( 1, &_EBO );
            _EBO = 0;
        }
    }
    return;
}
/// @section: name... /////////////////////// |
const QString& Font::name() const          // |
{
    return( _name );
}
void Font::setName( const QString& namae ) // |
{
    _modify = _modify || (namae != this -> name());
    _name = namae;
    return;
}
/// @section: path... /////////////////////////////// |
const QString& Font::filepath() const              // |
{
    return( _filepath );
}
const QString& Font::filepathPNG() const           // |
{
    return( _filepathPNG );
}
void Font::setFilepath( const QString& filepath )  // |
{
    _modify = _modify || (filepath != this -> filepath());
    _filepath = filepath;
    return;
}
/// @section: VBO /////////////////////////////////// |
void Font::createVBO( QGLFunctions* functions      // |
                      , const Vertices& vertices ) // |
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
            std::cout << "[Font::createVBO...] VBO = " << _VBO
                      << "; vertices = " << vertices.count()
                      << "; buffer.size = " << vertices.buffer().size() << std::endl;
        }
        else
            throw( Exception(Error::incorrect_VBO, "createVBO") );
    }
    return;
}
void Font::createEBO( QGLFunctions* functions )    // |
{
    if( 0 != functions )
    {
        functions -> glGenBuffers( 1, &_EBO );
        if( 0 != _EBO )
        {
            functions -> glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _EBO );
//            functions -> glBufferData( GL_ELEMENT_ARRAY_BUFFER
//                                       , sizeof(unsigned int)*indices.size()
//                                       , &indices[0]
//                    , GL_DYNAMIC_DRAW );
            functions -> glBufferData( GL_ELEMENT_ARRAY_BUFFER
                                       , sizeof(unsigned int)*6
                                       , 0, GL_DYNAMIC_DRAW );
            functions -> glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
            std::cout << "[Mesh::createEBO...] EBO = " << _EBO << std::endl;
        }
        else
            throw( Exception(Error::incorrect_EBO, "createEBO") );
    }
    return;
}
void Font::bind( QGLFunctions* functions ) const   // |
{
    if( 0 != functions && 0 != _VBO )
    {
        functions -> glBindBuffer( GL_ARRAY_BUFFER, _VBO );
        ProgramShader* program_shader = RenderItem::programsMgr().getProgram();
        if( 0 != program_shader && !filepathPNG().isEmpty() )
        {
            Texture* texture = RenderItem::texturesMgr().getTexture( filepathPNG() );
            if( 0 != texture )
            {
                GLenum unit = RenderItem::programsMgr().ref_textureUnits().lock( "fontUnit" );
                functions -> glActiveTexture( unit );
                glBindTexture( GL_TEXTURE_2D, texture -> id() );
                RenderItem::programsMgr().uniform().initFontUnit( functions
                                                                  , program_shader
                                                                  , unit );
            }
        }
    }
    return;
}
void Font::unbind( QGLFunctions* functions ) const // |
{
    if( 0 != functions )
    {
        functions -> glBindBuffer( GL_ARRAY_BUFFER, 0 );
        ProgramShader* program_shader = RenderItem::programsMgr().getProgram();
        if( 0 != program_shader && !filepathPNG().isEmpty() )
        {
            Texture* texture = RenderItem::texturesMgr().getTexture( filepathPNG() );
            if( 0 != texture )
            {
                GLenum unit = RenderItem::programsMgr().textureUnits().get( "fontUnit" );
                if( RenderItem::programsMgr().textureUnits().check(unit) )
                {
                    RenderItem::programsMgr().ref_textureUnits().unlock( "fontUnit" );
                    functions -> glActiveTexture( unit );
                    glBindTexture( GL_TEXTURE_2D, 0 );
                    RenderItem::programsMgr().uniform().initFontUnit( functions
                                                                      , program_shader
                                                                      , -1 );
                }
            }
        }
    }
    return;
}
/// @section: character set... ///////////////////////////////////////////// |
const Char* Font::symbol( size_t index ) const                            // |
{
    if( index < characters().count() )
    {
        const XMLObject* object = cref_characters().itemAt( index );
        if( 0 != object
                && object->xml_class_name().split(".", QString::SkipEmptyParts).contains(Char::class_name()) )
            return( static_cast<const Char*>(object) );
    }
    return( 0 );
}
const Char*Font::symbol( const QString& code ) const                      // |
{
    for( size_t i = 0; i < cref_characters().count(); ++i )
    {
        const Char* symbol = this->symbol( i );
        if( symbol -> code() == code )
            return( symbol );
    }
    return( 0 );
}
void Font::bindChar( QGLFunctions* functions                              // |
                     , const std::vector< unsigned int >& indices ) const // |
{
    if( 0 != functions && 0 != _EBO )
    {
        functions -> glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _EBO );
        functions -> glBufferSubData( GL_ELEMENT_ARRAY_BUFFER
                                      , 0, sizeof(unsigned int)*indices.size()
                                      , &indices[0] );
    }
    return;
}
void Font::unbindChar( QGLFunctions* functions ) const                    // |
{
    if( 0 != functions )
    {
        functions -> glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }
    return;
}
Font::~Font()
{
}


Char::Char( const QString& code
            , const std::vector<unsigned int>& indices )
    : XMLObject()
    , _modify( false )
    , _code( code )
    , _indices( indices )
{
    bind_fields();
}
/// @section: code... ////////////////////// |
const QString& Char::code() const         // |
{
    return _code;
}
void Char::setCode( const QString& code ) // |
{
    _modify = _modify || (code != this -> code());
    _code = code;
    return;
}
/// @section: indices... /////////////////////////////////////////// |
const std::vector<unsigned int>& Char::indices() const            // |
{
    return _indices;
}
void Char::setIndices( const std::vector<unsigned int>& indices ) // |
{
    _indices = indices;
}
Char::~Char()
{
}
