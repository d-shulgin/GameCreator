#ifndef TEXTURES_MGR_H
#define TEXTURES_MGR_H

#include "../../parser/xml_meta_data.h"
#include "texture.h"

class TexturesMgr : public XMLObject
{
public:
    static QString class_name() { return( QString("TexturesMgr") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify || isAnyElementModify() ); }
public:
    explicit TexturesMgr( /*Render* = 0 */);
    virtual ~TexturesMgr();

    void load( const QString& namae, const QString& path );

public:
    TexturesMgr( const TexturesMgr& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
//        _render = cpy._render;
        _textures = cpy._textures;
    }
    TexturesMgr& operator = ( const TexturesMgr& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
//            _render = cpy._render;
            _textures = cpy._textures;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "textures", &_textures );
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
//            for( size_t i = 0; i < textures().count(); ++i )
//            {
//                texture(i) -> loadTexture( render() );
//            }
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new TexturesMgr() );
    }
    virtual XMLObject* clone() const
    {
        TexturesMgr* object = new TexturesMgr();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected:
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < textures().count() && !modify; ++i )
            modify = cref_textures().itemAt(i) -> isModify();
        return( modify );
    }

private: /// @section: textures
    XMLCollection _textures;

protected:
    XMLCollection& ref_textures() { return( _textures ); }
    const XMLCollection& cref_textures() const { return( _textures ); }

public:
    const XMLCollectionU& textures() const { return( _textures ); }
    Texture* texture( size_t );
    const Texture* texture_const( size_t ) const;

public:
    void addTexture( Texture* t )
    {
        _textures << static_cast< XMLObject* >( t );
        _modify = true;
        return;
    }
    Picture* getPicture( const QString& );
    Texture* getTexture( const QString& );
};

#endif // TEXTURES_MGR_H
