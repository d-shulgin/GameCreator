#include "sprite.h"

Sprite::Sprite( const QString& namae )
    : View( namae )
    , _modify( false )
    , _width( 100.0f )
    , _height( 100.0f )
{
    bind_fields();
    createQuad();
}
Sprite::Sprite( float w
                , float h
                , const QString& picture_name
                , const QString& namae )
    : View( namae )
    , _modify( false )
    , _width( w )
    , _height( h )
    , _picture_name( picture_name )
    // ////////////////////////// |
{
    bind_fields();
    createQuad();
}
/// @section: data of vertices /////////////////////////// |
void Sprite::createQuad()                               // |
{
    float w = width();
    float h = height();
    _bounding = Bounding( w, h );
    _vertices.reset();
    _vertices << Vertex( 0.0f,   -h,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( 0.0f, 0.0f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex(    w,   -h,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex(    w, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f );
    _indices.push_back( 0  );
    _indices.push_back( 1  );
    _indices.push_back( 2  );
    _indices.push_back( 2  );
    _indices.push_back( 1  );
    _indices.push_back( 3  );
    return;
}
void Sprite::bind_data( QGLFunctions* functions ) const // |
{
    if( 0 == functions )
        return;
    ProgramShader* program_shader = programsMgr().getProgram();
    if( 0 != program_shader && program_shader -> is_linked() )
    {
        int position_loc   = program_shader -> attributeLoc( functions, programsMgr().attr().position() );
        int normal_loc     = program_shader -> attributeLoc( functions, programsMgr().attr().normal() );
        int texturePos_loc = program_shader -> attributeLoc( functions, programsMgr().attr().texturePos() );
        int color_loc      = program_shader -> attributeLoc( functions, programsMgr().attr().color() );
        int offset = 0;
        if( -1 != position_loc )
        {
            functions -> glEnableVertexAttribArray( position_loc );
            functions -> glVertexAttribPointer( position_loc, Vertex::sizePosition()
                                                , GL_FLOAT, false, Vertex::stride()
                                                , &vertices().buffer()[offset] );
        }
        offset += Vertex::sizePosition();
        if( -1 != texturePos_loc )
        {
            functions -> glEnableVertexAttribArray( texturePos_loc );
            functions -> glVertexAttribPointer( texturePos_loc, Vertex::sizeUVCoords()
                                                , GL_FLOAT, false, Vertex::stride()
                                                , &vertices().buffer()[offset] );
        }
        offset += Vertex::sizeUVCoords();
        if( -1 != normal_loc )
        {
            functions -> glEnableVertexAttribArray( normal_loc );
            functions -> glVertexAttribPointer( normal_loc, Vertex::sizeNormal()
                                                , GL_FLOAT, false, Vertex::stride()
                                                , &vertices().buffer()[offset] );
        }
        offset += Vertex::sizeNormal();
        if( -1 != color_loc )
        {
            functions -> glEnableVertexAttribArray( color_loc );
            functions -> glVertexAttribPointer( color_loc, Vertex::sizeColor()
                                                , GL_FLOAT, false, Vertex::stride()
                                                , &vertices().buffer()[offset] );
        }
    }
    return;
}
void Sprite::setColor( const Color& color )             // |
{
    _vertices.changeColor( color );
    return;
}
/// @section: picture ////////////////////////////// |
void Sprite::bind_picture(QGLFunctions* functions // |
                           , const QString& namae // |
                           , int unit_id ) const  // |
{
    if( 0 != functions )
    {
        glBindTexture( GL_TEXTURE_2D, texturesMgr().getPicture(namae) -> texture() );
        programsMgr().uniform().initTextureUnit( functions
                                                 , programsMgr().getProgram()
                                                 , unit_id );
    }
    return;
}
/// @section: drawable ////////////////////////////// |
void Sprite::draw( QGLFunctions* functions ) const // |
{
    if( !visibility() )
        return;
    if( 0 == functions )
        return;
    QString store_program = programsMgr().activated_program();
    View::draw( functions );
    glEnable( GL_TEXTURE_2D );
    // bind... picture #001
    {
        functions -> glActiveTexture( GL_TEXTURE0 );
        bind_picture( functions, _picture_name, 0 );
    }
    bind_data( functions );
    glDrawElements( GL_TRIANGLES, indices().size(), GL_UNSIGNED_INT, &_indices[0] );
    bind_program( functions, store_program );
    return;
}
Sprite::~Sprite()
{
}


SpriteDbg::SpriteDbg( const QString& namae )
    : Sprite( namae )
    , _modify( false )
    , _texture_id( 0 )
{
    bind_fields();
}
SpriteDbg::SpriteDbg( float w
                      , float h
                      , GLuint id
                      , const QString& namae )
    : Sprite( w, h, "", namae )
    , _modify( false )
    , _texture_id( id )
{
    bind_fields();
}
/// @section: texture id /////////////////////////////////// |
GLuint SpriteDbg::texture_id() const                      // |
{
    return _texture_id;
}
void SpriteDbg::setTexture_id( const GLuint& texture_id ) // |
{
    _texture_id = texture_id;
}
/// @section: picture ////////////////////////////////// |
void SpriteDbg::bind_picture( QGLFunctions* functions // |
                              , const QString&        // |
                              , int unit_id ) const   // |
{
    if( 0 != functions && texture_id() != 0 )
    {
        glBindTexture( GL_TEXTURE_2D, texture_id() );
        programsMgr().uniform().initTextureUnit( functions
                                                 , programsMgr().getProgram()
                                                 , unit_id );
    }
    return;
}
SpriteDbg::~SpriteDbg()
{
}

