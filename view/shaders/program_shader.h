#ifndef PROGRAM_SHADER_H
#define PROGRAM_SHADER_H

#include <GL/gl.h>
#include <QGLFunctions>
#include <QGLShaderProgram>

#include "../../parser/xml_meta_data.h"
#include "shader.h"

class ProgramShader : public XMLObject
{
public:
    static QString class_name() { return( QString("ProgramShader") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify || isAnyElementModify() ); }
public:
    explicit ProgramShader( const QString& = QString() );
    virtual ~ProgramShader();

public:
    ProgramShader( const ProgramShader& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _name = cpy._name;
        _shaders = cpy._shaders;
        if( is_linked() )
            throw( Exception(Error::already_linked, "constructor copy") );
        _gl_program = cpy._gl_program;
    }
    ProgramShader& operator = ( const ProgramShader& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _name = cpy._name;
            _shaders = cpy._shaders;
            if( is_linked() )
                throw( Exception(Error::already_linked, "operator =") );
            _gl_program = cpy._gl_program;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "name", &_name );
        bind_field( "shaders", &_shaders );
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
        return( new ProgramShader() );
    }
    virtual XMLObject* clone() const
    {
        ProgramShader* object = new ProgramShader();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < shaders().count() && !modify; ++i )
            modify = cref_shaders().itemAt(i) -> isModify();
        return( modify );
    }

private: /// @section: namae
    QString _name;

public:
    const QString& name() const { return( _name ); }

private: /// @section: shaders
    XMLCollection _shaders;

    XMLCollection& ref_shaders() { return( _shaders ); }
    const XMLCollection& cref_shaders() const { return( _shaders ); }

public:
    void attach( Shader* object )
    {
        _shaders << static_cast< XMLObject* >( object );
        _modify = true;
        return;
    }

public:
    const XMLCollectionU& shaders() const { return( _shaders ); }
    const Shader* shader_const( size_t ) const;

protected:
    Shader* shader( size_t );

private: /// @section: link
    GLuint _gl_program;

public:
    GLuint glID() const { return( _gl_program ); }
    void link( QGLFunctions* );
    void release( QGLFunctions* );
    bool is_linked() const;

public: /// @section: uniform
    int uniformLoc( QGLFunctions* functions, const QString& namae ) const;
    void setUniformValue( QGLFunctions*, int, int ) const;
    void setUniformValue( QGLFunctions*, int, unsigned int ) const;
    void setUniformValue( QGLFunctions*, int, float ) const;
    void setUniformValue( QGLFunctions*, int, bool ) const;
    void setUniformValue( QGLFunctions*, int, const QVector4D& ) const;
    void setUniformValue( QGLFunctions*, int, const QVector3D& ) const;
    void setUniformValue( QGLFunctions*, int, const QVector2D& ) const;
    void setUniformValue( QGLFunctions*, int, const QMatrix4x4& ) const;

public: /// @section: attribute
    int attributeLoc( QGLFunctions* functions, const QString& namae ) const;

public: /// @section: exception
    class Error
    {
    public:
        enum Id
        {
            none
            , pointer_is_NULL
            , already_linked
        };
        QString to_string() const
        {
            QString prefix( "ProgramShader : " );
            switch( id() )
            {
            case none: return( QString("none") );
            case pointer_is_NULL: return( prefix.append("pointer is NULL") );
            case already_linked: return( prefix.append("already linked") );
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

#endif // PROGRAM_SHADER_H
