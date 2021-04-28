#include "materials_mgr.h"
#include <QDir>
#include <QFileInfo>

MaterialsMgr::MaterialsMgr()
    : XMLObject()
    , _modify( false )
{
    bind_fields();
}
/// @section: materials //////////////////////////////////////////////////////// |
Material* MaterialsMgr::material( size_t index )                              // |
{
    if( index < materials().count() )
    {
        XMLObject* object = ref_materials()[index];
        if( object -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Material::class_name()) )
            return( static_cast<Material*>(object) );
    }
    return( 0 );
}
const Material* MaterialsMgr::material_const( size_t index ) const            // |
{
    if( index < materials().count() )
    {
        const XMLObject* object = cref_materials().itemAt(index);
        if( 0 != object )
        {
            if( object -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Material::class_name()) )
                return( static_cast<const Material*>(object) );
        }
    }
    return( 0 );
}
Material* MaterialsMgr::getMaterial( size_t index )                           // |
{
    return( material(index) );
}
Material* MaterialsMgr::getMaterial( const QString& namae )                   // |
{
    for( size_t i = 0; i < materials().count(); ++i )
    {
        Material* mtl = material(i);
        if( 0 != mtl && mtl->name() == namae )
            return( mtl );
    }
    return( 0 );
}
const Material* MaterialsMgr::getMaterial_const( const QString& namae ) const // |
{
    for( size_t i = 0; i < materials().count(); ++i )
    {
        const Material* mtl = material_const(i);
        if( 0 != mtl && mtl->name() == namae )
            return( mtl );
    }
    return( 0 );
}
void MaterialsMgr::loadFileMtl( const QString& path )// |
{
    if( path.isEmpty() )
        return;
    QFile file( path );
    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QTextStream input( &file );
        QFileInfo info(file);
        QDir dir(info.path());
        Material* mtl = 0;
        while( !input.atEnd() )
        {
            QString str = input.readLine();
            if( str.isEmpty() )
                continue;
            QStringList components = str.split( " ", QString::SkipEmptyParts );
            QString key = components.front();
            if( key == "#" )
            {
                if( components.size() > 1 )
                    std::cout << "comment: " << str.toStdString() << std::endl;
            }
            else if( key == "newmtl" )
            {
                if( components.size() > 1 )
                {
                    QString material_name = QString("%1/%2").arg(info.baseName()).arg(components[1]);
                    mtl = getMaterial( material_name );
                    if( 0 == mtl )
                    {
                        addMaterial( new Material(material_name) );
                        mtl = getMaterial( material_name );
                        if( 0 != mtl )
                            std::cout << "material... [" << mtl->name().toStdString() << "]" << std::endl;
                    }
                }
            }
            else if( key == "Ka" && 0 != mtl )
            {
                if( components.size() == 4 )
                {
                    float r = components[1].toFloat();
                    float g = components[2].toFloat();
                    float b = components[3].toFloat();
                    mtl -> setAmbientColor( Vector3(r, g, b) );
                }
            }
            else if( key == "Kd" && 0 != mtl )
            {
                if( components.size() == 4 )
                {
                    float r = components[1].toFloat();
                    float g = components[2].toFloat();
                    float b = components[3].toFloat();
                    mtl -> setDiffuseColor( Vector3(r, g, b) );
                }
            }
            else if( key == "Ks" && 0 != mtl )
            {
                if( components.size() == 4 )
                {
                    float r =  components[1].toFloat();
                    float g =  components[2].toFloat();
                    float b =  components[3].toFloat();
                    mtl -> setSpecularColor( Vector3(r, g, b) );
                }
            }
            else if( key == "Ns" && 0 != mtl )
            {
                if( components.size() > 1 )
                    mtl -> setSpecularExponent( components[1].toFloat() );
            }
            else if( key == "d"  && 0 != mtl )
            {
                if( components.size() == 2 )
                    mtl -> setDissolve( components[1].toFloat() );
                else if( components.size() == 3 )
                {
                    mtl -> setDissolve( components[2].toFloat() );
                    mtl -> setHalo( components[1] == "-halo" );
                }
            }
            else if( key == "map_d"  && 0 != mtl )
            {
                if( components.size() > 1 ) /// @note: not supported options
                    mtl -> setDissolveMap( dir.filePath(components.back()) );
            }
            else if( key == "map_Ka" && 0 != mtl )
            {
                if( components.size() > 1 ) /// @note: not supported options
                    mtl -> setAmbientMapColor( dir.filePath(components.back()) );
            }
            else if( key == "map_Kd" && 0 != mtl )
            {
                if( components.size() > 1 ) /// @note: not supported options
                    mtl -> setDiffuseMapColor( dir.filePath(components.back()) );
            }
            else if( key == "map_Ks" && 0 != mtl )
            {
                if( components.size() > 1 ) /// @note: not supported options
                    mtl -> setSpecularMapColor( dir.filePath(components.back()) );
            }
            else if( key == "bump"   && 0 != mtl )
            {
                if( components.size() > 1 ) /// @note: not supported options
                    mtl -> setNormalMap( dir.filePath(components.back()) );
            }
        }
        file.close();
    }
    return;
}
MaterialsMgr::~MaterialsMgr()
{
}



