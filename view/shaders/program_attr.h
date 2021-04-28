#ifndef PROGRAM_ATTR_H
#define PROGRAM_ATTR_H

#include "../../parser/xml_meta_data.h"

class ProgramAttr : public XMLObject
{
public:
    static QString class_name() { return( QString("Attribute") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    ProgramAttr();
    virtual ~ProgramAttr();

public:
    ProgramAttr( const ProgramAttr& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _position = cpy._position;
        _normal = cpy._normal;
        _texturePos = cpy._texturePos;
        _color = cpy._color;
        _tangent = cpy._tangent;
        _bitangent = cpy._bitangent;
    }
    ProgramAttr& operator = ( const ProgramAttr& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _position = cpy._position;
            _normal = cpy._normal;
            _texturePos = cpy._texturePos;
            _color = cpy._color;
            _tangent = cpy._tangent;
            _bitangent = cpy._bitangent;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "position",   &_position );
        bind_field( "normal",     &_normal );
        bind_field( "texturePos", &_texturePos );
        bind_field( "color",      &_color );
        bind_field( "tangent",    &_tangent );
        bind_field( "bitangent",  &_bitangent );
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
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new ProgramAttr() );
    }
    virtual XMLObject* clone() const
    {
        ProgramAttr* object = new ProgramAttr();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: attribute... position
    QString _position;

public:
    const QString& position() const;
    void setPosition( const QString& position );

private: /// @section: attribute... normal
    QString _normal;

public:
    const QString& normal() const;
    void setNormal( const QString& normal );

private: /// @section: attribute... UVcoords of texture
    QString _texturePos;

public:
    const QString& texturePos() const;
    void setTexturePos( const QString& texturePos );

private: /// @section: attribute... color
    QString _color;

public:
    const QString& color() const;
    void setColor( const QString& color );

private: /// @section: attribute... tangent
    QString _tangent;

public:
    const QString& tangent() const;
    void setTangent( const QString& tangent );

private: /// @section: attribute... bitangent
    QString _bitangent;

public:
    const QString& bitangent() const;
    void setBitangent( const QString& bitangent );
};

#endif // PROGRAM_ATTR_H
