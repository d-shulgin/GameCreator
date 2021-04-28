#include "mesh_lib.h"

MeshLib::MeshLib()
    : XMLObject()
    , _modify( false )
{
    bind_fields();
}
/// @section: meshes ////////////////////////////// |
void MeshLib::load( const QString& namae         // |
                    , const QString& path )      // |
{
    Mesh* mesh = getMesh( namae );
    if( 0 == mesh )
    {
        _meshes << static_cast< XMLObject* >( new Mesh(namae, path) );
        _modify = true;
    }
    return;
}
void MeshLib::upload( QGLFunctions* functions )  // |
{
    if( 0 != functions )
    {
        for( size_t i = 0; i < meshes().count(); ++i )
        {
            Mesh* o_mesh = mesh(i);
            if( 0 != o_mesh )
                o_mesh -> load( functions );
        }
    }
    return;
}
void MeshLib::release( QGLFunctions* functions ) // |
{
    if( 0 != functions )
    {
        for( size_t i = 0; i < meshes().count(); ++i )
        {
            Mesh* o_mesh = mesh(i);
            if( 0 != o_mesh )
                o_mesh -> release( functions );
        }
        ref_meshes().reset();
    }
    return;
}
Mesh* MeshLib::mesh( size_t index )              // |
{
    if( index < meshes().count() )
    {
        XMLObject* object = ref_meshes()[index];
        if( 0 != object
                && object->xml_class_name().split(".", QString::SkipEmptyParts).contains(Mesh::class_name()) )
            return( static_cast<Mesh*>(object) );
    }
    return( 0 );
}
Mesh* MeshLib::getMesh( const QString& namae )   // |
{
    for( size_t i = 0; i < meshes().count(); ++i )
    {
        Mesh* o_mesh = mesh(i);
        if( 0 != o_mesh && o_mesh->name() == namae )
            return( o_mesh );
    }
    return( 0 );
}
MeshLib::~MeshLib()
{
}

