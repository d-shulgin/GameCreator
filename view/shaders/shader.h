#ifndef SHADER_H
#define SHADER_H

#include <GL/gl.h>
#include <QGLFunctions>
#include <QGLShaderProgram>
#include <QFile>
#include <QTextStream>
#include "../../parser/xml_meta_data.h"

class Shader : public XMLObject
{
public:
    static QString class_name() { return( QString("Shader") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    class Type: public EnumValue
    {
    public:
        enum id{ vertex
                 , fragment
                 , tess_control
                 , tess_evaluation

                 , _first = vertex
                 , _last  = tess_evaluation
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
            case vertex : return( QString("vertex") );
            case fragment : return( QString("fragment") );
            default:
                break;
            }
            throw( Exception(Error::unknown_enum_id, "for Shader::Type") );
        }

    public:
        Type()
            : EnumValue()
            , _id( vertex )
        {}
        explicit Type( const QString& v )
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
            throw( Exception(Error::unknown_enum_id, "for Shader::Type") );
        }
        explicit Type( id v )
            : EnumValue()
            , _id( v )
        {
        }
        virtual ~Type()
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
            case vertex  : return( int(GL_VERTEX_SHADER) );
            case fragment: return( int(GL_FRAGMENT_SHADER) );
            case tess_control: return( int(GL_TESS_CONTROL_SHADER) );
            case tess_evaluation: return( int(GL_TESS_EVALUATION_SHADER) );
            default:
                break;
            }
            return( int(GL_VERTEX_SHADER) );
        }
    };

public:
    explicit Shader( Type::id = Type::vertex, const QString& = QString() );
    virtual ~Shader();

public:
    Shader( const Shader& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _path = cpy._path;
        _type = cpy._type;
        if( is_compiled() )
            throw( Exception(Error::already_compiled, "contructor copy") );
        _gl_shader = cpy._gl_shader;
    }
    Shader& operator = ( const Shader& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _path = cpy._path;
            _type = cpy._type;
            if( is_compiled() )
                throw( Exception(Error::already_compiled, "operator = ") );
            _gl_shader = cpy._gl_shader;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "path", &_path );
        bind_field( "type", &_type );
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
        return( new Shader() );
    }
    virtual XMLObject* clone() const
    {
        Shader* object = new Shader();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: path of code
    QString _path;

public:
    const QString& path() const { return( _path ); }

private: /// @section: type of shader
    EnumAs< Type > _type;

public:
    const EnumAs< Type >& type() const { return( _type ); }

private: /// @section: compile
    GLuint  _gl_shader;

    void compileSrc( QGLFunctions*, const char* );

public:
    GLuint glId() const { return( _gl_shader ); }
    bool compile( QGLFunctions* );
    void release( QGLFunctions* );
    bool is_compiled() const;

public: /// @section: exception
    class Error
    {
    public:
        enum Id
        {
            none
            , pointer_is_NULL
            , already_compiled
        };
        QString to_string() const
        {
            QString prefix( "Shader : " );
            switch( id() )
            {
            case none: return( QString("none") );
            case pointer_is_NULL: return( prefix.append("pointer is NULL") );
            case already_compiled: return( prefix.append("already compiled") );
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

#endif // SHADER_H
