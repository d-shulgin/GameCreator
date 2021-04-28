#ifndef FONT_H
#define FONT_H

#include <QGLFunctions>
#include "../../parser/xml_meta_data.h"
#include "../widgets/vertices.h"
#include "srcFont/font_data.h"

class Char : public XMLObject
{
public:
    static QString class_name() { return( QString("Char") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    explicit Char( const QString& = QString()
            , const std::vector< unsigned int >& = std::vector<unsigned int>() );
    virtual ~Char();

public:
    Char( const Char& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _code = cpy._code;
        _indices = cpy._indices;
    }
    Char& operator = ( const Char& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _code = cpy._code;
            _indices = cpy._indices;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "code", &_code );
        bind_field( "indices", &_indices );
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
        return( new Char() );
    }
    virtual XMLObject* clone() const
    {
        Char* object = new Char();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: code...
    QString _code;

public:
    const QString& code() const;
    void setCode( const QString& code );

private: /// @section: indices...
    std::vector< unsigned int > _indices;

public:
    const std::vector<unsigned int>& indices() const;
    void setIndices( const std::vector<unsigned int>& indices );
};
class Font : public XMLObject
{
public:
    static QString class_name() { return( QString("Font") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }
public:
    explicit Font( const QString& = QString(), const QString& = QString() );
    virtual ~Font();

public:
    Font( const Font& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _name = cpy._name;
        _filepath = cpy._filepath;
        _filepathPNG = cpy._filepathPNG;
        _data = cpy._data;
        _VBO = cpy._VBO;
        _EBO = cpy._EBO;
        _characters = cpy._characters;
    }
    Font& operator = ( const Font& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _name = cpy._name;
            _filepath = cpy._filepath;
            _filepathPNG = cpy._filepathPNG;
            _data = cpy._data;
            _VBO = cpy._VBO;
            _EBO = cpy._EBO;
            _characters = cpy._characters;
        }
        return( *this );
    }

public:
    void load( QGLFunctions* );
    bool is_loaded() const
    {
        return( 0 != _VBO && 0 != _EBO );
    }
    void release( QGLFunctions* );

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "name",     &_name );
        bind_field( "filepath", &_filepath );
        bind_field( "characters", &_characters );
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
        return( new Font() );
    }
    virtual XMLObject* clone() const
    {
        Font* object = new Font();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: name...
    QString _name;

public:
    const QString& name() const;
    void setName( const QString& namae );

private: /// @section: path...
    QString _filepath;
    QString _filepathPNG;

public:
    const QString& filepath() const;
    const QString& filepathPNG() const;
    void setFilepath( const QString& filepath );

private: /// @section: data
    FontData _data;

public:
    const FontData& data() const { return( _data ); }

private: /// @section: VBO & EBO
    GLuint _VBO;
    GLuint _EBO;

    void createVBO( QGLFunctions*, const Vertices& );
    void createEBO( QGLFunctions* );

public:
    void bind( QGLFunctions* ) const;
    void unbind( QGLFunctions* ) const;

private: /// @section: character set...
    XMLCollection _characters; /// @todo: need std::map< QString, Char >

protected:
    XMLCollection& ref_characters() { return( _characters ); }
    const XMLCollection& cref_characters() const { return( _characters ); }

public:
    const XMLCollectionU& characters() const { return( _characters ); }
    const Char* symbol( size_t ) const;
    const Char* symbol( const QString& ) const;
    void bindChar( QGLFunctions*, const std::vector<unsigned int>& ) const;
    void unbindChar( QGLFunctions* ) const;

public: /// @section: exception
    class Error
    {
    public:
        enum Id
        {
            none
            , pointer_is_NULL
            , incorrect_VBO
            , incorrect_EBO
        };
        QString to_string() const
        {
            QString prefix( "Font : " );
            switch( id() )
            {
            case none: return( QString("none") );
            case pointer_is_NULL: return( prefix.append("pointer is NULL") );
            case incorrect_VBO: return( prefix.append("incorrect VBO guid") );
            case incorrect_EBO: return( prefix.append("incorrect EBO guid") );
            default:
                break;
            }
            return( QString("unknown") );
        }

    private:
        Id _id;
        QString _str;

    public:
        Error()
            : _id( none )
        {}
        explicit Error( Id id )
            : _id( id )
        {}
        explicit Error( Id id, const QString& s )
            : _id( id )
            , _str( s )
        {}
        ~Error()
        {}

    public:
        Error( const Error& cpy )
        {
            _id  = cpy._id;
            _str = cpy._str;
        }
        Error& operator = ( const Error& cpy )
        {
            if( this != &cpy )
            {
                _id  = cpy._id;
                _str = cpy._str;
            }
            return( *this );
        }

    public:
        Id id() const { return( _id ); }
        const QString& str() const { return( _str ); }
    };
    class Exception : public IException
    {
    public:
        Exception() throw()
            : IException()
        {
            create_desc();
        }
        explicit Exception( Error::Id id ) throw()
            : IException()
            , _error( Error(id) )
        {
            create_desc();
        }
        explicit Exception( Error::Id id, const QString& str ) throw()
            : IException()
            , _error( Error(id, str) )
        {
            create_desc();
        }
        virtual ~Exception() throw()
        {}

    public:
        Exception( const Exception& cpy ) throw()
        {
            _error = cpy._error;
            create_desc();
        }
        Exception& operator = ( const Exception& cpy ) throw()
        {
            if( this != &cpy )
            {
                _error = cpy._error;
                create_desc();
            }
            return( *this );
        }

    private:
        Error _error;

    public:
        const Error& error() const throw()
        {
            return( _error );
        }
        virtual int error_id() const throw() { return( error().id() ); }
        virtual QString description() const throw()
        {
            if( error().str().isEmpty() )
                return( error().to_string() );
            return( error().to_string().append(": ").append(error().str()) );
        }
    };
};

#endif // FONT_H
