#ifndef RENDER_ITEM_H
#define RENDER_ITEM_H

#include "../parser/xml_meta_data.h"
#include "resources/package.h"
#include "shaders/package.h"

class RenderItem : public XMLObject
{
public:
    static QString class_name() { return( QString("RenderItem") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( false ); }

public:
    RenderItem();
    virtual ~RenderItem();

public:
    RenderItem( const RenderItem& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
    }
    RenderItem& operator = ( const RenderItem& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        return;
    }

protected:
    virtual void event_Saved()
    {
        return;
    }
    virtual void event_Loaded( bool )
    {
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new RenderItem() );
    }
    virtual XMLObject* clone() const
    {
        RenderItem* object = new RenderItem();
        (*object) = (*this);
        return( object );
    }

private: /// @section: programs
    static ProgramMgr _programsMgr;

public:
    static ProgramMgr& programsMgr()
    {
        return( _programsMgr );
    }

private: /// @section: textures
    static TexturesMgr _texturesMgr;

public:
    static TexturesMgr& texturesMgr()
    {
        return( _texturesMgr );
    }

private: /// @section: materials
    static MaterialsMgr _materialsMgr;

public:
    static MaterialsMgr& materialsMgr()
    {
        return( _materialsMgr );
    }

private: /// @section: mesh
    static MeshLib _meshLib;

public:
    static MeshLib& meshLib()
    {
        return( _meshLib );
    }

private: /// @section: font
    static FontLib _fontLib;

public:
    static FontLib& fontLib()
    {
        return( _fontLib );
    }
};

#endif // RENDER_ITEM_H
