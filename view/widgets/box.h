#ifndef BOX_H
#define BOX_H

#include "view.h"
#include "vertices.h"

class Box : public View
{
public:
    static QString class_name() { return( QString("Box") ); }
    virtual QString xml_class_name() const
    {
        if( View::xml_class_name().isEmpty() )
            return( class_name() );
        return( View::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( View::isModify() || _modify ); }

public:
    explicit Box( const QString& = QString() );
    explicit Box( float, float, float, const QString&, const QString& = QString() );
    virtual ~Box();

public:
    Box( const Box& cpy )
        : View( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _width = cpy._width;
        _height = cpy._height;
        _length = cpy._length;
        _vertices = cpy._vertices;
        _indices = cpy._indices;
        _picture_name = cpy._picture_name;
    }
    Box& operator = ( const Box& cpy )
    {
        if( this != &cpy )
        {
            View::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _width = cpy._width;
            _height = cpy._height;
            _length = cpy._length;
            _vertices = cpy._vertices;
            _indices = cpy._indices;
            _picture_name = cpy._picture_name;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        View::bind_fields();
        bind_field( "width",  &_width );
        bind_field( "height", &_height );
        bind_field( "length", &_length );
        return;
    }

protected:
    virtual void event_Saved()
    {
        View::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        View::event_Loaded( success );
        if( success )
        {
            _modify = false;
            createBox();
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Box() );
    }
    virtual XMLObject* clone() const
    {
        Box* object = new Box();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private:
    float _width;

public:
    float width() const { return( _width ); }

private:
    float _height;

public:
    float height() const { return( _height ); }

private:
    float _length;

public:
    float length() const { return( _length ); }

private: /// @section: vertices & indices
    Vertices _vertices;
    std::vector< unsigned int > _indices;

    void createBox();
    void bind_data( QGLFunctions* ) const;

public:
    const Vertices& vertices() const { return( _vertices ); }
    const std::vector< unsigned int >& indices() const { return( _indices ); }

protected: /// @section: picture
    QString _picture_name;

    void bind_picture( QGLFunctions*, const QString&, int = 0 ) const;

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
};

#endif // BOX_H
