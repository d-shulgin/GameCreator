#include "shape.h"

Shape::Shape( const QString& material, const QString& namae )
    : RenderItem()
    , _modify( false )
    , _name( namae )
    , _materialName( material )
    // ////////////////////////// |
{
    bind_fields();
}
/// @section: program ////////////////////////////////////// |
void Shape::bind_program( QGLFunctions* functions ) const // |
{
    programsMgr().bind( functions, program() );
    return;
}
void Shape::bind_program( QGLFunctions* functions         // |
                          , const QString& namae ) const  // |
{
    if( !namae.isEmpty() )
        programsMgr().bind( functions, namae );
    return;
}
/// @section: name ////////////////////////// |
const QString& Shape::name() const         // |
{
    return( _name );
}
void Shape::setName( const QString& name ) // |
{
    QString origin = this -> name();
    _name = name;
    _modify = _modify || (origin != this -> name());
    return;
}
/// @section: indices ////////////////////////////////////// |
void Shape::bind_data( QGLFunctions* functions            // |
                       , const Vertices& vertices ) const // |
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
        int tangent_loc    = program_shader -> attributeLoc( functions, programsMgr().attr().tangent() );
        int bitangent_loc  = program_shader -> attributeLoc( functions, programsMgr().attr().bitangent() );
        int offset = 0;
        if( -1 != position_loc )
        {
            functions -> glEnableVertexAttribArray( position_loc );
            functions -> glVertexAttribPointer( position_loc, Vertex::sizePosition()
                                                , GL_FLOAT, false, Vertex::stride()
                                                , &vertices.buffer()[offset] );
        }
        offset += Vertex::sizePosition();
        if( -1 != texturePos_loc )
        {
            functions -> glEnableVertexAttribArray( texturePos_loc );
            functions -> glVertexAttribPointer( texturePos_loc, Vertex::sizeUVCoords()
                                                , GL_FLOAT, false, Vertex::stride()
                                                , &vertices.buffer()[offset] );
        }
        offset += Vertex::sizeUVCoords();
        if( -1 != normal_loc )
        {
            functions -> glEnableVertexAttribArray( normal_loc );
            functions -> glVertexAttribPointer( normal_loc, Vertex::sizeNormal()
                                                , GL_FLOAT, false, Vertex::stride()
                                                , &vertices.buffer()[offset] );
        }
        offset += Vertex::sizeNormal();
        if( -1 != color_loc )
        {
            functions -> glEnableVertexAttribArray( color_loc );
            functions -> glVertexAttribPointer( color_loc, Vertex::sizeColor()
                                                , GL_FLOAT, false, Vertex::stride()
                                                , &vertices.buffer()[offset] );
        }
        offset += Vertex::sizeColor();
        if( -1 != tangent_loc )
        {
            functions -> glEnableVertexAttribArray( tangent_loc );
            functions -> glVertexAttribPointer( tangent_loc, Vertex::sizeTangent()
                                                , GL_FLOAT, false, Vertex::stride()
                                                , &vertices.buffer()[offset] );
        }
        offset += Vertex::sizeTangent();
        if( -1 != bitangent_loc )
        {
            functions -> glEnableVertexAttribArray( bitangent_loc );
            functions -> glVertexAttribPointer( bitangent_loc, Vertex::sizeBiTangent()
                                                , GL_FLOAT, false, Vertex::stride()
                                                , &vertices.buffer()[offset] );
        }
    }
    return;
}
void Shape::add( const std::vector<GLuint>& v )     // |
{
    _indices.insert(_indices.end(), v.begin(), v.begin()+v.size() );
    return;
}
/// @section: material //////////////////////////////////////// |
void Shape::bind_material( QGLFunctions* functions ) const   // |
{
    if( 0 != functions )
    {
        Material* material = materialsMgr().getMaterial( materialName() );
        if( 0 != material /*&& 0 != program_const()*/ )
        {
            ProgramShader* program_shader = programsMgr().getProgram();
            if( 0 != program_shader )
            {
                programsMgr().uniform().material().initAmbientColor( functions
                                                                     , program_shader
                                                                     , material -> ambientColor() );
                programsMgr().uniform().material().initDiffuseColor( functions
                                                                     , program_shader
                                                                     , material -> diffuseColor() );
                programsMgr().uniform().material().initSpecularColor( functions
                                                                      , program_shader
                                                                      , material -> specularColor() );
                programsMgr().uniform().material().initSpecularExp( functions
                                                                    , program_shader
                                                                    , material -> specularExponent() );
                programsMgr().uniform().material().initDissolve( functions
                                                                 , program_shader
                                                                 , material -> dissolve() );
                programsMgr().uniform().material().initHalo( functions
                                                             , program_shader
                                                             , material -> halo() );
//                int textureUnitID = 0;
//                std::vector< GLenum > textureUnit;
//                textureUnit.push_back( GL_TEXTURE0 );
//                textureUnit.push_back( GL_TEXTURE1 );
//                textureUnit.push_back( GL_TEXTURE2 );
//                textureUnit.push_back( GL_TEXTURE3 );
//                textureUnit.push_back( GL_TEXTURE4 );
//                textureUnit.push_back( GL_TEXTURE5 );
//                textureUnit.push_back( GL_TEXTURE6 );
//                textureUnit.push_back( GL_TEXTURE7 );
                if( !material -> ambientMapColor().isEmpty()  )
                {
                    Texture* texture = texturesMgr().getTexture( material -> ambientMapColor() );
                    if( 0 == texture )
                    {
                        texturesMgr().addTexture( new Texture(material -> ambientMapColor(), true) );
                        texture = texturesMgr().getTexture( material -> ambientMapColor() );
                    }
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().ref_textureUnits().lock( "AmbientMap" );
//                        functions -> glActiveTexture( textureUnit[textureUnitID] );
                        functions -> glActiveTexture( unit );
                        glBindTexture( GL_TEXTURE_2D, texture -> id() );
//                        programsMgr().uniform().material().initAmbientMap( functions
//                                                                           , program_shader
//                                                                           , textureUnitID );
//                        textureUnitID ++;
                        programsMgr().uniform().material().initAmbientMap( functions
                                                                           , program_shader
                                                                           , unit );
                    }
                }
                if( !material -> diffuseMapColor().isEmpty()  )
                {
                    Texture* texture = texturesMgr().getTexture( material -> diffuseMapColor() );
                    if( 0 == texture )
                    {
                        texturesMgr().addTexture( new Texture(material -> diffuseMapColor(), true) );
                        texture = texturesMgr().getTexture( material -> diffuseMapColor() );
                    }
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().ref_textureUnits().lock( "DiffuseMap" );
//                        functions -> glActiveTexture( textureUnit[textureUnitID] );
                        functions -> glActiveTexture( unit );
                        glBindTexture( GL_TEXTURE_2D, texture -> id() );
//                        programsMgr().uniform().material().initDiffuseMap( functions
//                                                                           , program_shader
//                                                                           , textureUnitID );
//                        textureUnitID ++;
                        programsMgr().uniform().material().initDiffuseMap( functions
                                                                           , program_shader
                                                                           , unit );
                    }
                }
                if( !material -> specularMapColor().isEmpty() )
                {
                    Texture* texture = texturesMgr().getTexture( material -> specularMapColor() );
                    if( 0 == texture )
                    {
                        texturesMgr().addTexture( new Texture(material -> specularMapColor(), true) );
                        texture = texturesMgr().getTexture( material -> specularMapColor() );
                    }
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().ref_textureUnits().lock( "SpecularMap" );
//                        functions -> glActiveTexture( textureUnit[textureUnitID] );
                        functions -> glActiveTexture( unit );
                        glBindTexture( GL_TEXTURE_2D, texture -> id() );
//                        programsMgr().uniform().material().initSpecularMap( functions
//                                                                            , program_shader
//                                                                            , textureUnitID );
//                        textureUnitID ++;
                        programsMgr().uniform().material().initSpecularMap( functions
                                                                            , program_shader
                                                                            , unit );
                    }
                }
                if( !material -> dissolveMap().isEmpty()      )
                {
                    Texture* texture = texturesMgr().getTexture( material -> dissolveMap() );
                    if( 0 == texture )
                    {
                        texturesMgr().addTexture( new Texture(material -> dissolveMap(), true) );
                        texture = texturesMgr().getTexture( material -> dissolveMap() );
                    }
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().ref_textureUnits().lock( "DissolveMap" );
//                        functions -> glActiveTexture( textureUnit[textureUnitID] );
                        functions -> glActiveTexture( unit );
                        glBindTexture( GL_TEXTURE_2D, texture -> id() );
//                        programsMgr().uniform().material().initDissolveMap( functions
//                                                                            , program_shader
//                                                                            , textureUnitID );
//                        textureUnitID ++;
                        programsMgr().uniform().material().initDissolveMap( functions
                                                                            , program_shader
                                                                            , unit );
                    }
                }
                if( !material -> normalMap().isEmpty()        )
                {
                    Texture* texture = texturesMgr().getTexture( material -> normalMap() );
                    if( 0 == texture )
                    {
                        texturesMgr().addTexture( new Texture(material -> normalMap(), true) );
                        texture = texturesMgr().getTexture( material -> normalMap() );
                    }
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().ref_textureUnits().lock( "NormalMap" );
//                        functions -> glActiveTexture( textureUnit[textureUnitID] );
                        functions -> glActiveTexture( unit );
                        glBindTexture( GL_TEXTURE_2D, texture -> id() );
//                        programsMgr().uniform().material().initNormalMap( functions
//                                                                          , program_shader
//                                                                          , textureUnitID );
//                        textureUnitID ++;
                        programsMgr().uniform().material().initNormalMap( functions
                                                                          , program_shader
                                                                          , unit );
                    }
                }
            }
        }
    }
    return;
}
void Shape::unbind_material( QGLFunctions* functions ) const // |
{
    if( 0 != functions )
    {
        Material* material = materialsMgr().getMaterial( materialName() );
        if( 0 != material /*&& 0 != program_const()*/ )
        {
            ProgramShader* program_shader = programsMgr().getProgram();
            if( 0 != program_shader )
            {
//                int textureUnitID = 0;
//                std::vector< GLenum > textureUnit;
//                textureUnit.push_back( GL_TEXTURE0 );
//                textureUnit.push_back( GL_TEXTURE1 );
//                textureUnit.push_back( GL_TEXTURE2 );
//                textureUnit.push_back( GL_TEXTURE3 );
//                textureUnit.push_back( GL_TEXTURE4 );
//                textureUnit.push_back( GL_TEXTURE5 );
//                textureUnit.push_back( GL_TEXTURE6 );
//                textureUnit.push_back( GL_TEXTURE7 );

                if( !material -> ambientMapColor().isEmpty()  )
                {
                    Texture* texture = texturesMgr().getTexture( material -> ambientMapColor() );
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().textureUnits().get( "AmbientMap" );
                        if( programsMgr().textureUnits().check(unit) )
                        {
                            programsMgr().ref_textureUnits().unlock( "AmbientMap" );
//                            functions -> glActiveTexture( textureUnit[textureUnitID] );
                            functions -> glActiveTexture( unit );
                            glBindTexture( GL_TEXTURE_2D, 0 );
                            programsMgr().uniform().material().initAmbientMap( functions
                                                                               , program_shader
                                                                               , -1 );
                        }
//                        textureUnitID ++;
                    }
                }
                if( !material -> diffuseMapColor().isEmpty()  )
                {
                    Texture* texture = texturesMgr().getTexture( material -> diffuseMapColor() );
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().textureUnits().get( "DiffuseMap" );
                        if( programsMgr().textureUnits().check(unit) )
                        {
                            programsMgr().ref_textureUnits().unlock( "DiffuseMap" );
//                            functions -> glActiveTexture( textureUnit[textureUnitID] );
                            functions -> glActiveTexture( unit );
                            glBindTexture( GL_TEXTURE_2D, 0 );
                            programsMgr().uniform().material().initDiffuseMap( functions
                                                                               , program_shader
                                                                               , -1 );
                        }
//                        textureUnitID ++;
                    }
                }
                if( !material -> specularMapColor().isEmpty() )
                {
                    Texture* texture = texturesMgr().getTexture( material -> specularMapColor() );
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().textureUnits().get( "SpecularMap" );
                        if( programsMgr().textureUnits().check(unit) )
                        {
                            programsMgr().ref_textureUnits().unlock( "SpecularMap" );
//                            functions -> glActiveTexture( textureUnit[textureUnitID] );
                            functions -> glActiveTexture( unit );
                            glBindTexture( GL_TEXTURE_2D, 0 );
                            programsMgr().uniform().material().initSpecularMap( functions
                                                                                , program_shader
                                                                                , -1 );
                        }
//                        textureUnitID ++;
                    }
                }
                if( !material -> dissolveMap().isEmpty()      )
                {
                    Texture* texture = texturesMgr().getTexture( material -> dissolveMap() );
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().textureUnits().get( "DissolveMap" );
                        if( programsMgr().textureUnits().check(unit) )
                        {
                            programsMgr().ref_textureUnits().unlock( "DissolveMap" );
//                            functions -> glActiveTexture( textureUnit[textureUnitID] );
                            functions -> glActiveTexture( unit );
                            glBindTexture( GL_TEXTURE_2D, 0 );
                            programsMgr().uniform().material().initDissolveMap( functions
                                                                                , program_shader
                                                                                , -1 );
                        }
//                        textureUnitID ++;
                    }
                }
                if( !material -> normalMap().isEmpty()        )
                {
                    Texture* texture = texturesMgr().getTexture( material -> normalMap() );
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().textureUnits().get( "NormalMap" );
                        if( programsMgr().textureUnits().check(unit) )
                        {
                            programsMgr().ref_textureUnits().unlock( "NormalMap" );
//                            functions -> glActiveTexture( textureUnit[textureUnitID] );
                            functions -> glActiveTexture( unit );
                            glBindTexture( GL_TEXTURE_2D, 0 );
                            programsMgr().uniform().material().initNormalMap( functions
                                                                              , program_shader
                                                                              , -1 );
                        }
//                        textureUnitID ++;
                    }
                }
            }
        }
    }
    return;
}
/// @section: material ////////////////////////////////////// |
const QString& Shape::materialName() const                 // |
{
    return _materialName;
}
void Shape::setMaterialName( const QString& materialName ) // |
{
    QString origin = this -> materialName();
    _materialName = materialName;
    _modify = _modify || (origin != this -> materialName());
    return;
}
/// @section: drawable ///////////////////////////////////// |
void Shape::draw( QGLFunctions* functions                 // |
                  , const Vertices& vertices ) const      // |
{
    if( 0 == functions )
        return;
    QString store_program = programsMgr().activated_program();
    bind_program( functions );

    glEnable( GL_TEXTURE_2D );
    bind_material( functions );
    bind_data( functions, vertices );
    glDrawElements( GL_TRIANGLES, indices().size(), GL_UNSIGNED_INT, &_indices[0] );
    unbind_material( functions );
    bind_program( functions, store_program );
    return;
}
void Shape::drawShadow( QGLFunctions* functions           // |
                        , const Vertices& vertices) const // |
{
    if( 0 == functions )
        return;
//    std::cout << "[Shape::drawShadow...] : " << name().toStdString() << std::endl;
    bind_data( functions, vertices );
    std::cout << "after bind data... " << name().toStdString() << ":" << _indices.size() << std::endl;
    glDrawElements( GL_TRIANGLES, indices().size(), GL_UNSIGNED_INT, &_indices[0] );
    std::cout << "[Shape::drawShadow...] << finish >>" << std::endl;
    return;
}
Shape::~Shape()
{
}
