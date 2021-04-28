#ifndef MATERIALS_MGR_H
#define MATERIALS_MGR_H

#include <QFile>
#include <QTextStream>
#include "../../parser/xml_meta_data.h"
#include "material.h"
#include "textures_mgr.h"

class MaterialsMgr : public XMLObject
{
public:
    static QString class_name() { return( QString("MaterialsMgr") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify || isAnyElementModify() ); }

public:
    MaterialsMgr();
    virtual ~MaterialsMgr();

public:
    MaterialsMgr( const MaterialsMgr& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
    }
    MaterialsMgr& operator = ( const MaterialsMgr& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
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
        return( new MaterialsMgr() );
    }
    virtual XMLObject* clone() const
    {
        MaterialsMgr* object = new MaterialsMgr();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected:
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < materials().count() && !modify; ++i )
            modify = cref_materials().itemAt(i) -> isModify();
        return( modify );
    }

private: /// @section: materials
    XMLCollection _materials;

protected:
    const XMLCollection& cref_materials() const { return( _materials ); }
    XMLCollection& ref_materials() { return( _materials ); }

public:
    const XMLCollectionU& materials() const { return( _materials ); }
    Material* material( size_t );
    const Material* material_const( size_t ) const;

public:
    void addMaterial( Material* mtl )
    {
        _materials << static_cast< XMLObject* >( mtl );
        _modify = true;
        return;
    }
    Material* getMaterial( size_t );
    Material* getMaterial( const QString& );
    const Material* getMaterial_const( const QString& ) const;
    void loadFileMtl( const QString&/*, TexturesMgr**/ );
};

#endif // MATERIALS_MGR_H
