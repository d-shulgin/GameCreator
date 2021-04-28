#include "model.h"
#include <QDir>
#include <QFileInfo>

Model::Model(const QString& path, const QString& namae )
    : View( namae )
    , _modify( false )
    , _path( path )
{
    bind_fields();
    createModel();
}
/// @section: path of shape ///////////////// |
const QString& Model::path() const         // |
{
    return _path;
}
void Model::setPath( const QString& path ) // |
{
    QString origin = this -> path();
    _path = path;
    _modify = _modify || (origin != this -> path());
    return;
}
/// @section: shapes /////////////////////////////////// |
const Shape* Model::shape_const( size_t index ) const // |
{
    if( index < shapes().count() )
    {
        const XMLObject* object = _shapes.itemAt( index );
        if( 0 != object )
        {
            if( object -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Shape::class_name()) )
                return( static_cast<const Shape*>(object) );
        }
    }
    return( 0 );
}
/// @section: vertices ///// |
void Model::createModel() // |
{
    if( path().isEmpty() )
        return;
    QFile file( path() );
    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        std::cout << "[Model::createModel...] " << path().toStdString() << std::endl;
        QString object_name;
        QString material_name;
        std::vector< QVector3D > coords;
        std::vector< QVector2D > UVcoords;
        std::vector< QVector3D > normals;
        Shape* shape = 0;
        int line = 0;

        QFileInfo info(file);
        QDir dir(info.path());
        // info |
        {
            //data/models/sandy/Sandy.obj
            //  absoluteFilePath: D:/Projects/Games/GameCreator/data/models/sandy/Sandy.obj
            //      absolutePath: D:/Projects/Games/GameCreator/data/models/sandy
            //          baseName: Sandy
            //        bundleName:
            //  canonicalFilePath: D:/Projects/Games/GameCreator/data/models/sandy/Sandy.obj
            //     canonicalPath: D:/Projects/Games/GameCreator/data/models/sandy
            //  completeBaseName: Sandy
            //    completeSuffix: obj
            //          fileName: Sandy.obj
            //          filePath: data/models/sandy/Sandy.obj
            //             group:
            //             owner:
            //              path: data/models/sandy
            //          readLink:
            //            suffix: obj
            //     symLinkTarget:
//            std::cout << "   absoluteFilePath: " << info.absoluteFilePath().toStdString() << std::endl;
//            std::cout << "       absolutePath: " << info.absolutePath().toStdString() << std::endl;
//            std::cout << "           baseName: " << info.baseName().toStdString() << std::endl;
//            std::cout << "         bundleName: " << info.bundleName().toStdString() << std::endl;
//            std::cout << "  canonicalFilePath: " << info.canonicalFilePath().toStdString() << std::endl;
//            std::cout << "      canonicalPath: " << info.canonicalPath().toStdString() << std::endl;
//            std::cout << "   completeBaseName: " << info.completeBaseName().toStdString() << std::endl;
//            std::cout << "     completeSuffix: " << info.completeSuffix().toStdString() << std::endl;
//            std::cout << "           fileName: " << info.fileName().toStdString() << std::endl;
//            std::cout << "           filePath: " << info.filePath().toStdString() << std::endl;
//            std::cout << "              group: " << info.group().toStdString() << std::endl;
//            std::cout << "              owner: " << info.owner().toStdString() << std::endl;
//            std::cout << "               path: " << info.path().toStdString() << std::endl;
//            std::cout << "           readLink: " << info.readLink().toStdString() << std::endl;
//            std::cout << "             suffix: " << info.suffix().toStdString() << std::endl;
//            std::cout << "      symLinkTarget: " << info.symLinkTarget().toStdString() << std::endl;
        }

        QTextStream in( &file );
        while( !in.atEnd() )
        {
            QString str = in.readLine();
            if( str.isEmpty() )
            {
                ++ line;
                continue;
            }
            QStringList components = str.split( " ", QString::SkipEmptyParts );
            QString key = components.front();
            if     ( key == "#"      )
            {
                if( components.size() > 1 )
                    std::cout << "comment: " << str.toStdString() << std::endl;
            }
            else if( key == "mtllib" )
            {
                if( components.size() > 1 )
                {
                    materialsMgr().loadFileMtl( dir.filePath(components[1]) /*, &texturesMgr()*/ );
                }
            }
            else if( key == "o"      )
            {
                if( components.size() > 1 )
                    object_name = components[1];
                else
                    object_name = "";
                shape = 0;
            }
            else if( key == "v"      )
            {
                float x = ( components.size() > 1 ? components[1].toFloat() : 0.0f );
                float y = ( components.size() > 2 ? components[2].toFloat() : 0.0f );
                float z = ( components.size() > 3 ? components[3].toFloat() : 0.0f );
                coords.push_back( QVector3D(x, y, z) );
            }
            else if( key == "vt"     )
            {
                float x = ( components.size() > 1 ? components[1].toFloat() : 0.0f );
                float y = ( components.size() > 2 ? components[2].toFloat() : 0.0f );
                UVcoords.push_back( QVector2D(x, y) );
            }
            else if( key == "vn"     )
            {
                float x = ( components.size() > 1 ? components[1].toFloat() : 0.0f );
                float y = ( components.size() > 2 ? components[2].toFloat() : 0.0f );
                float z = ( components.size() > 3 ? components[3].toFloat() : 0.0f );
                normals.push_back( QVector3D(x, y, z) );
            }
            else if( key == "usemtl" )
            {
                if( components.size() > 1 )
                {
                    material_name = QString("%1/%2").arg(info.baseName()).arg(components[1]);
                    addShape( shape = new Shape(material_name, object_name) );
                }
                else
                    throw( Exception(Error::incorrect_material_name, QString("createModel... line: %1").arg(line)) );
            }
            else if( key == "f" && 0 != shape )
            {
                int index = _vertices.count();
                std::vector< GLuint > indices;
                for( int i = 1; i < components.size(); ++i )
                {
                    QStringList num = components[i].split( "/", QString::SkipEmptyParts );
                    if( num.size() == 3 )
                    {
                        float x = coords[num[0].toUInt() - 1].x();
                        float y = coords[num[0].toUInt() - 1].y();
                        float z = coords[num[0].toUInt() - 1].z();
                        float tx = UVcoords[num[1].toUInt() - 1].x();
                        float ty = UVcoords[num[1].toUInt() - 1].y();
                        float nx = normals[num[2].toUInt() - 1].x();
                        float ny = normals[num[2].toUInt() - 1].y();
                        float nz = normals[num[2].toUInt() - 1].z();
                        _vertices << Vertex( x, y, z, tx, ty, nx, ny, nz, 1.0f, 1.0f, 1.0f, 1.0f );
                    }
                    else
                        throw( Exception(Error::incorrect_vertex_info, QString("createModel... line: %1").arg(line)) );
                }
                Vector3 tangent;
                Vector3 bitangent;
                getTB( index, &tangent, &bitangent );
                if     ( components.size() == 4 ) // triangle |
                {
                    indices.push_back( 2 + index );
                    indices.push_back( 1 + index );
                    indices.push_back( 0 + index );

                    _vertices.setTangent( index + 0, tangent );
                    _vertices.setTangent( index + 1, tangent );
                    _vertices.setTangent( index + 2, tangent );

                    _vertices.setBiTangent( index + 0, bitangent );
                    _vertices.setBiTangent( index + 1, bitangent );
                    _vertices.setBiTangent( index + 2, bitangent );
                }
                else if( components.size() == 5 ) // quad     |
                {
                    indices.push_back( 2 + index );
                    indices.push_back( 1 + index );
                    indices.push_back( 0 + index );
                    indices.push_back( 3 + index );
                    indices.push_back( 1 + index );
                    indices.push_back( 2 + index );

                    _vertices.setTangent( index + 0, tangent );
                    _vertices.setTangent( index + 1, tangent );
                    _vertices.setTangent( index + 2, tangent );
                    _vertices.setTangent( index + 3, tangent );

                    _vertices.setBiTangent( index + 0, bitangent );
                    _vertices.setBiTangent( index + 1, bitangent );
                    _vertices.setBiTangent( index + 2, bitangent );
                    _vertices.setBiTangent( index + 3, bitangent );
                }
                shape -> add( indices );
            }
            ++ line;
        }
        file.close();
    }
    return;
}
void Model::getTB( int index, Vector3* tangent, Vector3* bitangent )
{
    if( 0 != tangent || 0 != bitangent )
    {
        QVector3D p0 = vertices().position( index + 0 ).vec();
        QVector3D p1 = vertices().position( index + 1 ).vec();
        QVector3D p2 = vertices().position( index + 2 ).vec();

        QVector2D uv0 = vertices().UVcoords( index + 0 );
        QVector2D uv1 = vertices().UVcoords( index + 1 );
        QVector2D uv2 = vertices().UVcoords( index + 2 );

        QVector3D dp1 = p1 - p0;
        QVector3D dp2 = p2 - p0;
        QVector2D duv1 = uv1 - uv0;
        QVector2D duv2 = uv2 - uv0;

        float r = 1.0f / (duv1.x()*duv2.y() - duv1.y()*duv2.x());
        if( 0 != tangent )
            (*tangent) = Vector3( (dp1*duv2.y() - dp2*duv1.y())*r );
        if( 0 != bitangent )
            (*bitangent) = Vector3( (dp2*duv1.x() - dp1*duv2.x())*r );
    }
    return;
}
/// @section: drawable /////////////////////////////////// |
void Model::draw( QGLFunctions* functions ) const       // |
{
    if( !visibility() )
        return;
    QString store_program = programsMgr().activated_program();
    View::draw( functions );
    for( size_t i = 0; i < shapes().count(); ++i )
    {
        shape_const(i) -> draw( functions, vertices() );
    }
    bind_program( functions, store_program );
    return;
}
void Model::drawShadow( QGLFunctions* functions ) const // |
{
    if( !visibility() )
        return;
    View::drawShadow( functions );
    if( shadowEnable() )
    {
        for( size_t i = 0; i < shapes().count(); ++i )
        {
            shape_const(i) -> drawShadow( functions, vertices() );
        }
    }
    return;
}
Model::~Model()
{
}



ModelV2::ModelV2( const QString& name_mesh
                  , const QString& namae )
    : View( namae )
    , _modify( false )
    , _name_mesh( name_mesh )
    // //////////////////// |
{
    bind_fields();
}
/// @section: mesh //////////////////////////////////////////////// |
void ModelV2::bind_material( QGLFunctions* functions             // |
                             , const QString& name_mtl ) const   // |
{
    if( 0 != functions )
    {
        Material* material = materialsMgr().getMaterial( name_mtl );
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
//                        functions -> glActiveTexture( textureUnit[textureUnitID] );
                        GLenum unit = programsMgr().ref_textureUnits().lock( "AmbientMap" );
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
//                        functions -> glActiveTexture( textureUnit[textureUnitID] );
                        GLenum unit = programsMgr().ref_textureUnits().lock( "DiffuseMap" );
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
//                        functions -> glActiveTexture( textureUnit[textureUnitID] );
                        GLenum unit = programsMgr().ref_textureUnits().lock( "SpecularMap" );
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
//                        functions -> glActiveTexture( textureUnit[textureUnitID] );
                        GLenum unit = programsMgr().ref_textureUnits().lock( "DissolveMap" );
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
                        //functions -> glActiveTexture( textureUnit[textureUnitID] );
                        GLenum unit = programsMgr().ref_textureUnits().lock( "NormalMap" );
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
void ModelV2::unbind_material( QGLFunctions* functions           // |
                               , const QString& name_mtl ) const // |
{
    if( 0 != functions )
    {
        Material* material = materialsMgr().getMaterial( name_mtl );
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
                    /// @todo: thinks about this (texture)
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
//                        functions -> glActiveTexture( textureUnit[textureUnitID] );
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
void ModelV2::bind_data( QGLFunctions* functions ) const         // |
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
void ModelV2::unbind_data( QGLFunctions* functions ) const       // |
{
    /// @todo:
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
/// @section: drawable ///////////////////////////////////// |
void ModelV2::draw( QGLFunctions* functions ) const       // |
{
    if( !visibility() )
        return;
    QString store_program = programsMgr().activated_program();
    View::draw( functions );
    Mesh* mesh = meshLib().getMesh( name_mesh() );

    if( 0 != mesh )
    {
        glEnable( GL_TEXTURE_2D );
        mesh -> bind( functions );
        bind_data( functions );
        for( size_t i = 0; i < mesh -> shapes().count(); ++i )
        {
            mesh -> shape(i) -> bind( functions );
            bind_material( functions, mesh -> shape(i) -> material() );
            glDrawElements( GL_TRIANGLES, mesh -> shape(i) -> size(), GL_UNSIGNED_INT, 0 );
            unbind_material( functions, mesh -> shape(i) -> material() );
            mesh -> shape(i) -> unbind( functions );
        }
        unbind_data( functions );
        mesh -> unbind( functions );
    }

    bind_program( functions, store_program );
    return;
}
void ModelV2::drawShadow( QGLFunctions* functions ) const // |
{
    if( !visibility() )
        return;
    if( !shadowEnable() )
        return;
    View::drawShadow( functions );
    Mesh* mesh = meshLib().getMesh( name_mesh() );
    if( 0 != mesh )
    {
        glEnable( GL_TEXTURE_2D );
        mesh -> bind( functions );
        bind_data( functions );
        for( size_t i = 0; i < mesh -> shapes().count(); ++i )
        {
            mesh -> shape(i) -> bind( functions );
            bind_material( functions, mesh -> shape(i) -> material() );
            glDrawElements( GL_TRIANGLES, mesh -> shape(i) -> size(), GL_UNSIGNED_INT, 0 );
            unbind_material( functions, mesh -> shape(i) -> material() );
            mesh -> shape(i) -> unbind( functions );
        }
        unbind_data( functions );
        mesh -> unbind( functions );
    }
    return;
}
ModelV2::~ModelV2()
{
}

