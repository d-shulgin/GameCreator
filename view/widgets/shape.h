#ifndef SHAPE_H
#define SHAPE_H

#include <QFile>
#include <QTextStream>
#include "view.h"
#include "vertices.h"

class Shape : public RenderItem
{
public:
    static QString class_name() { return( QString("Shape") ); }
    virtual QString xml_class_name() const
    {
        if( RenderItem::xml_class_name().isEmpty() )
            return( class_name() );
        return( RenderItem::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( RenderItem::isModify() || _modify ); }

public:
    explicit Shape( const QString& = QString(), const QString& = QString() );
    virtual ~Shape();

public:
    Shape( const Shape& cpy )
        : RenderItem( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _program = cpy._program;
        _name = cpy._name;
        _indices = cpy._indices;
        _materialName = cpy._materialName;
    }
    Shape& operator = ( const Shape& cpy )
    {
        if( this != &cpy )
        {
            RenderItem::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _program = cpy._program;
            _name = cpy._name;
            _indices = cpy._indices;
            _materialName = cpy._materialName;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        RenderItem::bind_fields();
        bind_field( "name", &_name );
        bind_field( "program", &_program );
        bind_field( "materialName", &_materialName );
        return;
    }

protected:
    virtual void event_Saved()
    {
        RenderItem::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        RenderItem::event_Loaded( success );
        if( success )
        {
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Shape() );
    }
    virtual XMLObject* clone() const
    {
        Shape* object = new Shape();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected: /// @section: program
    QString _program;

protected:
    const QString& program() const { return( _program ); }

public:
    virtual void setProgram( const QString& namae )
    {
        _modify = _modify || (_program != namae);
        _program = namae;
        return;
    }

protected:
    void bind_program( QGLFunctions* ) const;
    void bind_program( QGLFunctions*, const QString& ) const;

private: /// @section: name
    QString _name;

public:
    const QString& name() const;
    void setName(const QString& name);

private: /// @section: indices
    std::vector< GLuint > _indices;
    void bind_data( QGLFunctions*, const Vertices& ) const;

public:
    const std::vector< GLuint >& indices() const { return( _indices ); }
    void add( const std::vector< GLuint >& );

private: /// @section: material
    QString _materialName;

    void bind_material( QGLFunctions* ) const;
    void unbind_material( QGLFunctions* ) const;

public:
    const QString& materialName() const;
    void setMaterialName(const QString& materialName);

public: /// @section: drawable
    virtual void draw( QGLFunctions*, const Vertices& ) const;
    virtual void drawShadow( QGLFunctions*, const Vertices& ) const;
};

#endif // SHAPE_H
