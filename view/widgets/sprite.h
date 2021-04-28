#ifndef SPRITE_H
#define SPRITE_H

#include "view.h"
#include "vertices.h"

class Sprite : public View
{
public:
    static QString class_name() { return( QString("Sprite") ); }
    virtual QString xml_class_name() const
    {
        if( View::xml_class_name().isEmpty() )
            return( class_name() );
        return( View::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( View::isModify()
                                            || _modify ); }

public:
    explicit Sprite( const QString& = QString() );
    explicit Sprite( float, float, const QString&, const QString& = QString() );
    virtual ~Sprite();

public:
    Sprite( const Sprite& cpy )
        : View( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _width = cpy._width;
        _height = cpy._height;
        _vertices = cpy._vertices;
        _indices = cpy._indices;
        _picture_name = cpy._picture_name;
    }
    Sprite& operator = ( const Sprite& cpy )
    {
        if( this != &cpy )
        {
            View::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _width = cpy._width;
            _height = cpy._height;
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
        bind_field( "width",        &_width  );
        bind_field( "height",       &_height );
        bind_field( "picture_name", &_picture_name );
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
            createQuad();
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Sprite() );
    }
    virtual XMLObject* clone() const
    {
        Sprite* object = new Sprite();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected: /// @section: width
    float _width;

public:
    float width() const { return( _width ); }

protected: /// @section: height
    float _height;

public:
    float height() const { return( _height ); }

protected: /// @section: data of vertices
    Vertices _vertices;
    std::vector< unsigned int > _indices;

    void createQuad();
    void bind_data( QGLFunctions* ) const;

public:
    const Vertices& vertices() const { return( _vertices ); }
    const std::vector< unsigned int >& indices() const { return( _indices ); }

public:
    void setColor( const Color& );

protected: /// @section: picture
    QString _picture_name;

    virtual void bind_picture( QGLFunctions*, const QString&, int = 0 ) const;

private: /// @section: bounding
    Bounding _bounding;

public:
    virtual Bounding bounding() const { return( _bounding ); }

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
};
class SpriteDbg : public Sprite
{
public:
    static QString class_name() { return( QString("SpriteDebug") ); }
    virtual QString xml_class_name() const
    {
        if( Sprite::xml_class_name().isEmpty() )
            return( class_name() );
        return( Sprite::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( Sprite::isModify()
                                            || _modify ); }

public:
    explicit SpriteDbg( const QString& = QString() );
    explicit SpriteDbg( float, float, GLuint, const QString& = QString() );
    virtual ~SpriteDbg();

public:
    SpriteDbg( const SpriteDbg& cpy )
        : Sprite( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _texture_id = cpy._texture_id;
    }
    SpriteDbg& operator = ( const SpriteDbg& cpy )
    {
        if( this != &cpy )
        {
            Sprite::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _texture_id = cpy._texture_id;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        View::bind_fields();
        return;
    }

protected:
    virtual void event_Saved()
    {
        Sprite::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        Sprite::event_Loaded( success );
        if( success )
        {
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new SpriteDbg() );
    }
    virtual XMLObject* clone() const
    {
        SpriteDbg* object = new SpriteDbg();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: texture id
    GLuint _texture_id;

public:
    GLuint texture_id() const;
    void setTexture_id( const GLuint& texture_id );

protected: /// @section: picture
    virtual void bind_picture( QGLFunctions*, const QString&, int = 0 ) const;
};

#endif // SPRITE_H
