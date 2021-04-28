#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include <QGLFunctions>
#include "../../parser/xml_meta_data.h"
#include "picture.h"

//class Render;
class Texture : public XMLObject
{
public:
    static QString class_name() { return( QString("Texture") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    class WrapMode : public EnumValue
    {
    public:
        enum id{ repeat
                 , mirrored_repeat
                 , clam
                 , clamp_to_edge
                 , clamp_to_border

                 , _first = repeat
                 , _last  = clamp_to_border
               };
        static int count() { return( last() - first() + 1 ); }
        static int first() { return( _first ); }
        static int last()  { return( _last ); }
        static QString to_string( int v )
        {
            return( to_string(id(v)) );
        }
        static QString to_string( id v )
        {
            switch( v )
            {
            case repeat               : return( QString("repeat") );
            case mirrored_repeat      : return( QString("mirrored_repeat") );
            case clam                 : return( QString("clam") );
            case clamp_to_edge        : return( QString("clamp_to_edge") );
            case clamp_to_border      : return( QString("clamp_to_border") );
            default:
                break;
            }
            throw( Exception(Error::unknown_enum_id, "for Texture::WrapMode") );
        }

    public:
        WrapMode()
            : EnumValue()
            , _id( repeat )
        {}
        explicit WrapMode( const QString& v )
            : EnumValue( v )
        {
            for( int index = first(); index <= last(); ++index )
            {
                if( to_string(index) == v )
                {
                    _id = id(index);
                    return;
                }
            }
            throw( Exception(Error::unknown_enum_id, "for Texture::WrapMode") );
        }
        explicit WrapMode( id v )
            : EnumValue()
            , _id( v )
        {
        }
        virtual ~WrapMode()
        {}

    private:
        id _id;

    public:
        virtual QString to_string() const
        {
            return( to_string(_id) );
        }
        virtual int to_int() const
        {
            switch( _id )
            {
            case repeat               : return( int(GL_REPEAT) );
            case mirrored_repeat      : return( int(GL_MIRRORED_REPEAT) );
            case clam                 : return( int(GL_CLAMP) );
            case clamp_to_edge        : return( int(GL_CLAMP_TO_EDGE) );
            case clamp_to_border      : return( int(GL_CLAMP_TO_BORDER) );
            default:
                break;
            }
            return( int(GL_REPEAT) );
        }
    };
    class Filter : public EnumValue
    {
    public:
        enum id{ linear
                 , nearest

                 , _first = linear
                 , _last  = nearest
               };
        static int count() { return( last() - first() + 1 ); }
        static int first() { return( _first ); }
        static int last()  { return( _last ); }
        static QString to_string( int v )
        {
            return( to_string(id(v)) );
        }
        static QString to_string( id v )
        {
            switch( v )
            {
            case linear : return( QString("linear") );
            case nearest : return( QString("nearest") );
            default:
                break;
            }
            throw( Exception(Error::unknown_enum_id, "for Texture::Filter") );
        }

    public:
        Filter()
            : EnumValue()
            , _id( linear )
        {}
        explicit Filter( const QString& v )
            : EnumValue( v )
        {
            for( int index = first(); index <= last(); ++index )
            {
                if( to_string(index) == v )
                {
                    _id = id(index);
                    return;
                }
            }
            throw( Exception(Error::unknown_enum_id, "for Texture::Filter") );
        }
        explicit Filter( id v )
            : EnumValue()
            , _id( v )
        {
        }
        virtual ~Filter()
        {}

    private:
        id _id;

    public:
        virtual QString to_string() const
        {
            return( to_string(_id) );
        }
        virtual int to_int() const
        {
            switch( _id )
            {
            case linear : return( int(GL_LINEAR) );
            case nearest : return( int(GL_NEAREST) );
            default:
                break;
            }
            return( int(GL_LINEAR) );
        }
    };

public:
    explicit Texture( /*Render* = 0, */const QString& filepath = QString(), bool = false );
    explicit Texture( /*Render*, */const QString&
                      , Filter::id, Filter::id
                      , WrapMode::id, WrapMode::id, bool = false );
    virtual ~Texture();

public:
    void loadTexture( /*Render* */);

public:
    Texture( const Texture& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _id = cpy._id;
        _filepath = cpy._filepath;
        _mirrowed = cpy._mirrowed;
//        _render = cpy._render;
        _width = cpy._width;
        _height = cpy._height;
        _wrap_s = cpy._wrap_s;
        _wrap_t = cpy._wrap_t;
        _min_filter = cpy._min_filter;
        _mag_filter = cpy._mag_filter;
        _pictures = cpy._pictures;
    }
    Texture& operator = ( const Texture& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _id = cpy._id;
            _filepath = cpy._filepath;
            _mirrowed = cpy._mirrowed;
//            _render = cpy._render;
            _width = cpy._width;
            _height = cpy._height;
            _wrap_s = cpy._wrap_s;
            _wrap_t = cpy._wrap_t;
            _min_filter = cpy._min_filter;
            _mag_filter = cpy._mag_filter;
            _pictures = cpy._pictures;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "pictures", &_pictures );
        bind_field( "file", &_filepath );
        bind_field( "mirrowed", &_mirrowed );
        bind_field( "wrap_s", &_wrap_s );
        bind_field( "wrap_t", &_wrap_t );
        bind_field( "min_filter", &_min_filter );
        bind_field( "mag_filter", &_mag_filter );
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
            loadTexture();
            for( size_t i = 0; i < pictures().count(); ++i )
            {
                picture(i)->setParent( this );
            }
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Texture() );
    }
    virtual XMLObject* clone() const
    {
        Texture* object = new Texture();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: id
    GLuint  _id;
    QString _filepath;
    bool _mirrowed;
//    Render* _render;

//    Render* render() { return( _render ); }

public:
    GLuint id() const { return( _id ); }
    const QString& filepath() const { return( _filepath ); }
    bool mirrowed() const { return( _mirrowed ); }
    void release()
    {
        if( id() != 0 )
            glDeleteTextures( 1, &_id );
        _id = 0;
        return;
    }

private: /// @section: width/height
    int _width;
    int _height;

public:
    int width() const { return( _width ); }
    int height() const { return( _height ); }

private: /// @section: texture params
    EnumAs< WrapMode >  _wrap_s;
    EnumAs< WrapMode >  _wrap_t;

public:
    const EnumAs< WrapMode >& wrapS() const { return( _wrap_s ); }
    const EnumAs< WrapMode >& wrapT() const { return( _wrap_t ); }

private: /// @section: texture filters
    EnumAs< Filter > _min_filter;
    EnumAs< Filter > _mag_filter;

public:
    const EnumAs< Filter >& minFilter() const { return( _min_filter ); }
    const EnumAs< Filter >& magFilter() const { return( _mag_filter ); }

private: /// @section: pictures
    XMLCollection _pictures;

protected:
    XMLCollection& ref_pictures() { return( _pictures ); }
    const XMLCollection& cref_pictures() const { return( _pictures ); }

public:
    const XMLCollectionU& pictures() const { return( _pictures ); }
    Picture* picture( size_t );
    const Picture* picture_const( size_t ) const;

public:
    void addPicture( Picture* p )
    {
        _pictures << static_cast<XMLObject*>( p );
        p -> setParent( this );
        _modify = true;
        return;
    }
    Picture* getPicture( size_t );
    Picture* getPicture( const QString& );
};

#endif // TEXTURE_H
