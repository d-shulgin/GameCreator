#include "box.h"

Box::Box( const QString& namae )
    : View( namae )
    , _modify( false )
    , _width( 1.0f )
    , _height( 1.0f )
    , _length( 1.0f )
{
    bind_fields();
    createBox();
}
Box::Box( float width
          , float height
          , float length
          , const QString& picture_name
          , const QString& namae )
    : View( namae )
    , _modify( false )
    , _width( width )
    , _height( height )
    , _length( length )
    , _picture_name( picture_name )
    // ////////////////////////// |
{
    bind_fields();
    createBox();
}
/// @section: vertices & indices ////////////////////// |
void Box::createBox()                                // |
{
    float w_2 = width()  / 2.0f;
    float h_2 = height() / 2.0f;
    float l_2 = length() / 2.0f;
    _vertices.reset();
    //                                x     y     z      tx    ty      nx    ny    nz       r     g     b     a
    _vertices << Vertex( /* 0 - 3*/ -w_2, -h_2, +l_2,   0.0f, 1.0f,   0.0f, 0.0f, +1.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /* 1 - 1*/ -w_2, +h_2, +l_2,   0.0f, 0.0f,   0.0f, 0.0f, +1.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /* 2 - 4*/ +w_2, -h_2, +l_2,   1.0f, 1.0f,   0.0f, 0.0f, +1.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /* 3 - 2*/ +w_2, +h_2, +l_2,   1.0f, 0.0f,   0.0f, 0.0f, +1.0f,   1.0f, 1.0f, 1.0f, 1.0f )

              << Vertex( /* 4 - 1*/ -w_2, +h_2, +l_2,   0.0f, 1.0f,   0.0f, +1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /* 5 - 5*/ -w_2, +h_2, -l_2,   0.0f, 0.0f,   0.0f, +1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /* 6 - 2*/ +w_2, +h_2, +l_2,   1.0f, 1.0f,   0.0f, +1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /* 7 - 6*/ +w_2, +h_2, -l_2,   1.0f, 0.0f,   0.0f, +1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )

              << Vertex( /* 8 - 5*/ -w_2, +h_2, -l_2,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /* 9 - 7*/ -w_2, -h_2, -l_2,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*10 - 6*/ +w_2, +h_2, -l_2,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*11 - 8*/ +w_2, -h_2, -l_2,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f, 1.0f, 1.0f )

              << Vertex( /*12 - 7*/ -w_2, -h_2, -l_2,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*13 - 3*/ -w_2, -h_2, +l_2,   0.0f, 0.0f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*14 - 8*/ +w_2, -h_2, -l_2,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*15 - 4*/ +w_2, -h_2, +l_2,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )

              << Vertex( /*16 - 7*/ -w_2, -h_2, -l_2,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*17 - 5*/ -w_2, +h_2, -l_2,   0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*18 - 3*/ -w_2, -h_2, +l_2,   1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*19 - 1*/ -w_2, +h_2, +l_2,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )

              << Vertex( /*20 - 4*/ +w_2, -h_2, +l_2,   0.0f, 1.0f,   +1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*21 - 2*/ +w_2, +h_2, +l_2,   0.0f, 0.0f,   +1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*22 - 8*/ +w_2, -h_2, -l_2,   1.0f, 1.0f,   +1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f )
              << Vertex( /*23 - 6*/ +w_2, +h_2, -l_2,   1.0f, 0.0f,   +1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f );
    for( unsigned int i = 0; i < 6; ++i )
    {
        _indices.push_back( 0 + i*4 );
        _indices.push_back( 1 + i*4 );
        _indices.push_back( 2 + i*4 );
        _indices.push_back( 2 + i*4 );
        _indices.push_back( 1 + i*4 );
        _indices.push_back( 3 + i*4 );
    }
    return;
}
void Box::bind_data( QGLFunctions* functions ) const // |
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
/// @section: picture //////////////////////////// |
void Box::bind_picture( QGLFunctions* functions // |
                        , const QString& namae  // |
                        , int unit_id ) const   // |
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
/// @section: drawable //////////////////////// |
void Box::draw( QGLFunctions* functions ) const // |
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
Box::~Box()
{
}
