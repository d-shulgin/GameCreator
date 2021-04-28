#include "text_block.h"

TextBlock::TextBlock( const QString& program
                      , const QString& font
                      , const QString& text )
    : View()
    , _modify( false )
    , _font( font )
    , _letter( text )
{
    _program = program;
    bind_fields();
    changeLetterData();
}
/// @section: font... ///////////////////////////////////////// |
void TextBlock::bind_data( QGLFunctions* functions ) const   // |
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

        if( -1 != position_loc   )
        {
            functions -> glVertexAttribPointer( position_loc, Vertex::sizePosition()
                                                , GL_FLOAT, GL_FALSE, Vertex::stride()
                                                , (void*)(Vertex::offsetPosition()*sizeof(float)) );
            functions -> glEnableVertexAttribArray( position_loc );
        }
        if( -1 != texturePos_loc )
        {
            functions -> glVertexAttribPointer( texturePos_loc, Vertex::sizeUVCoords()
                                                , GL_FLOAT, GL_FALSE, Vertex::stride()
                                                , (void*)(Vertex::offsetUVCoords()*sizeof(float)) );
            functions -> glEnableVertexAttribArray( texturePos_loc );
        }
        if( -1 != normal_loc     )
        {
            functions -> glVertexAttribPointer( normal_loc, Vertex::sizeNormal()
                                                , GL_FLOAT, GL_FALSE, Vertex::stride()
                                                , (void*)(Vertex::offsetNormal()*sizeof(float)) );
            functions -> glEnableVertexAttribArray( normal_loc );
        }
        if( -1 != color_loc      )
        {
            functions -> glVertexAttribPointer( color_loc, Vertex::sizeColor()
                                                , GL_FLOAT, GL_FALSE, Vertex::stride()
                                                , (void*)(Vertex::offsetColor()*sizeof(float)) );
            functions -> glEnableVertexAttribArray( color_loc );
        }
        if( -1 != tangent_loc    )
        {
            functions -> glVertexAttribPointer( tangent_loc, Vertex::sizeTangent()
                                                , GL_FLOAT, GL_FALSE, Vertex::stride()
                                                , (void*)(Vertex::offsetTangent()*sizeof(float)) );
            functions -> glEnableVertexAttribArray( tangent_loc );
        }
        if( -1 != bitangent_loc  )
        {
            functions -> glVertexAttribPointer( bitangent_loc, Vertex::sizeBiTangent()
                                                , GL_FLOAT, GL_FALSE, Vertex::stride()
                                                , (void*)(Vertex::offsetBiTangent()*sizeof(float)) );
            functions -> glEnableVertexAttribArray( bitangent_loc );
        }
    }
    return;
}
void TextBlock::unbind_data( QGLFunctions* functions ) const // |
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

        if( -1 != position_loc   )
        {
            functions -> glDisableVertexAttribArray( position_loc );
        }
        if( -1 != texturePos_loc )
        {
            functions -> glDisableVertexAttribArray( texturePos_loc );
        }
        if( -1 != normal_loc     )
        {
            functions -> glDisableVertexAttribArray( normal_loc );
        }
        if( -1 != color_loc      )
        {
            functions -> glDisableVertexAttribArray( color_loc );
        }
        if( -1 != tangent_loc    )
        {
            functions -> glDisableVertexAttribArray( tangent_loc );
        }
        if( -1 != bitangent_loc  )
        {
            functions -> glDisableVertexAttribArray( bitangent_loc );
        }
    }
    return;
}
const QString& TextBlock::font() const                       // |
{
    return( _font );
}
void TextBlock::setFont( const QString& font )               // |
{
    _modify = _modify || (font != this -> font());
    _font = font;
    changeLetterData();
    return;
}
/// @section: letter... /////////////////////////////////////////// |
const QString& TextBlock::letter() const                         // |
{
    return( _letter );
}
void TextBlock::setLetter( const QString& letter )               // |
{
    _modify = _modify || (letter != this -> letter());
    _letter = letter;
    changeLetterData();
    return;
}
void TextBlock::changeLetterData()                               // |
{
    if( !this -> font().isEmpty() )
    {
        const Font* font = fontLib().getFont( this -> font() );
        float offsetX = 0.0f;
        float offsetY = 0.0f;
        _letterWidth  = 0.0f;
        _letter_data.clear();
        for( int i = 0; i < letter().count(); ++i )
        {
            float divider = font -> data().height();
            const CharData* characterData = font -> data().getSymbol( letter().at(i) );
            if( 0 != characterData )
            {
                if( characterData->code() != QString(" ") )
                {
                    const Char* character = font -> symbol( letter().at(i) );
                    float x = characterData->bearingX()/divider;
                    float y = -characterData->bearingY()/divider;
                    _letter_data.push_back( LetterData(QVector2D(offsetX + x, offsetY + y)
                                                       , character->indices()) );
                }
                else
                {
                    _letter_data.push_back( LetterData(QVector2D(offsetX, offsetY)) );
                }
                _letterWidth += characterData->advance()/divider;
            }
            else
            {
                /// @exception: glyph not found....
            }
            offsetX = letterWidth();
        }
    }
    return;
}
void TextBlock::bind_character( QGLFunctions* functions          // |
                                , const Font* font               // |
                                , size_t index                   // |
                                , const QVector2D& added ) const // |
{
    if( 0 != font && index < _letter_data.size() )
    {
        const LetterData& glyphData = _letter_data[index];
        ProgramShader* program_shader = programsMgr().getProgram();
        if( 0 != program_shader )
        {
            programsMgr().uniform().initFontOffset( functions
                                                    , program_shader
                                                    , QVector2D(glyphData.offset().x() + added.x()
                                                                , glyphData.offset().y() + added.y()) );
        }
        font -> bindChar( functions, glyphData.indices() );
    }
    return;
}
void TextBlock::unbind_character( QGLFunctions* functions        // |
                                  , const Font* font ) const     // |
{
    if( 0 != font && 0 != functions )
        font -> unbindChar( functions );
    return;
}
/// @section: material... ///////////////////////////////////////// |
const QString& TextBlock::material() const                       // |
{
    return( _material );
}
void TextBlock::setMaterial( const QString& material )           // |
{
    _modify = _modify || (material != this -> material());
    _material = material;
    return;
}
void TextBlock::bind_material( QGLFunctions* functions ) const   // |
{
    if( 0 != functions )
    {
        Material* material = materialsMgr().getMaterial( this -> material() );
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
                        functions -> glActiveTexture( unit );
                        glBindTexture( GL_TEXTURE_2D, texture -> id() );
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
                        functions -> glActiveTexture( unit );
                        glBindTexture( GL_TEXTURE_2D, texture -> id() );
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
                        functions -> glActiveTexture( unit );
                        glBindTexture( GL_TEXTURE_2D, texture -> id() );
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
                        functions -> glActiveTexture( unit );
                        glBindTexture( GL_TEXTURE_2D, texture -> id() );
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
                        functions -> glActiveTexture( unit );
                        glBindTexture( GL_TEXTURE_2D, texture -> id() );
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
void TextBlock::unbind_material( QGLFunctions* functions ) const // |
{
    if( 0 != functions )
    {
        Material* material = materialsMgr().getMaterial( this -> material() );
        if( 0 != material /*&& 0 != program_const()*/ )
        {
            ProgramShader* program_shader = programsMgr().getProgram();
            if( 0 != program_shader )
            {
                if( !material -> ambientMapColor().isEmpty()  )
                {
                    /// @todo: thinks about this (texture)
                    Texture* texture = texturesMgr().getTexture( material -> ambientMapColor() );
                    if( 0 != texture /*&& texture -> id() > 0*/ )
                    {
                        GLenum unit = programsMgr().textureUnits().get( "AmbientMap" );
                        if( programsMgr().textureUnits().check(unit) )
                        {
                            programsMgr().ref_textureUnits().unlock( "AmbientMap" );
                            functions -> glActiveTexture( unit );
                            glBindTexture( GL_TEXTURE_2D, 0 );
                            programsMgr().uniform().material().initAmbientMap( functions
                                                                               , program_shader
                                                                               , -1 );
                        }
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
                            functions -> glActiveTexture( unit );
                            glBindTexture( GL_TEXTURE_2D, 0 );
                            programsMgr().uniform().material().initDiffuseMap( functions
                                                                               , program_shader
                                                                               , -1 );
                        }
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
                            functions -> glActiveTexture( unit );
                            glBindTexture( GL_TEXTURE_2D, 0 );
                            programsMgr().uniform().material().initSpecularMap( functions
                                                                                , program_shader
                                                                                , -1 );
                        }
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
                            functions -> glActiveTexture( unit );
                            glBindTexture( GL_TEXTURE_2D, 0 );
                            programsMgr().uniform().material().initDissolveMap( functions
                                                                                , program_shader
                                                                                , -1 );
                        }
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
                            functions -> glActiveTexture( unit );
                            glBindTexture( GL_TEXTURE_2D, 0 );
                            programsMgr().uniform().material().initNormalMap( functions
                                                                              , program_shader
                                                                              , -1 );
                        }
                    }
                }
            }
        }
    }
    return;
}
/// @section: drawable /////////////////////////////////////// |
void TextBlock::draw( QGLFunctions* functions ) const       // |
{
    if( !visibility() )
        return;
    QString store_program = programsMgr().activated_program();
    View::draw( functions );

    const Font* font = fontLib().getFont( this -> font() );
    if( 0 != font )
    {
        glEnable( GL_TEXTURE_2D );
        font -> bind( functions );
        bind_data( functions );
        bind_material( functions );
        for( size_t i = 0; i < static_cast<size_t>(letter().count()); ++i )
        {
            if( letter().at(i) != QString(" ") )
            {
                bind_character( functions, font, i, QVector2D() );
                glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
                unbind_character( functions, font );
            }
        }
        unbind_material( functions );
        unbind_data( functions );
        font -> unbind( functions );
    }
    bind_program( functions, store_program );

    return;
}
void TextBlock::drawShadow( QGLFunctions* functions ) const // |
{
}
void TextBlock::draw( QGLFunctions* functions               // |
                      , float offsetX ) const               // |
{
    if( !visibility() )
        return;
    QString store_program = programsMgr().activated_program();
    View::draw( functions );

    const Font* font = fontLib().getFont( this -> font() );
    if( 0 != font )
    {
        glEnable( GL_TEXTURE_2D );
        font -> bind( functions );
        bind_data( functions );
        bind_material( functions );
        for( size_t i = 0; i < static_cast<size_t>(letter().count()); ++i )
        {
            if( letter().at(i) != QString(" ") )
            {
                bind_character( functions, font, i, QVector2D(offsetX, 0.0f) );
                glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
                unbind_character( functions, font );
            }
        }
        unbind_material( functions );
        unbind_data( functions );
        font -> unbind( functions );
    }
    bind_program( functions, store_program );

    return;
}
void TextBlock::drawShadow( QGLFunctions* functions         // |
                            , float ) const                 // |
{
}
TextBlock::~TextBlock()
{
}
