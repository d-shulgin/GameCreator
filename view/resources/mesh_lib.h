#ifndef MESH_LIB_H
#define MESH_LIB_H

#include "../../parser/xml_meta_data.h"
#include "mesh.h"

class MeshLib : public XMLObject
{
public:
    static QString class_name() { return( QString("MeshLib") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify || isAnyElementModify() ); }

public:
    MeshLib();
    virtual ~MeshLib();

public:
    MeshLib( const MeshLib& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _meshes = cpy._meshes;
    }
    MeshLib& operator = ( const MeshLib& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _meshes = cpy._meshes;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "meshes", &_meshes );
        return;
    }

protected:
    virtual void event_Saved()
    {
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        if( success )
        {
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new MeshLib() );
    }
    virtual XMLObject* clone() const
    {
        MeshLib* object = new MeshLib();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected:
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < meshes().count() && !modify; ++i )
            modify = cref_meshes().itemAt(i) -> isModify();
        return( modify );
    }

private: /// @section: meshes
    XMLCollection _meshes;

protected:
    XMLCollection& ref_meshes() { return( _meshes ); }
    const XMLCollection& cref_meshes() const { return( _meshes ); }

public:
    void load( const QString&, const QString& );
    void upload( QGLFunctions* );
    void release( QGLFunctions* );
    const XMLCollectionU& meshes() const { return( _meshes ); }
    Mesh* mesh( size_t );
    Mesh* getMesh( const QString& );
};

#endif // MESH_LIB_H
