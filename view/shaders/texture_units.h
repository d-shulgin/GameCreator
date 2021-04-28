#ifndef TEXTURE_UNITS_H
#define TEXTURE_UNITS_H

#include <QGLFunctions>
#include <map>
#include "../../utils/exception.h"

class TextureUnits
{
    std::vector< GLenum > _units;
    std::map< QString, GLenum > _locked;

public:
    TextureUnits();
    virtual ~TextureUnits();

public:
    const std::vector< GLenum >& values() const { return( _units ); }
    GLenum get( const QString& ) const;
    GLenum lock( const QString& );
    void unlock( const QString& );
    bool check( GLenum unit ) const
    {
        return( unit >= GL_TEXTURE0 && unit <= GL_TEXTURE31 );
    }

public: /// @section: exception
    class Error
    {
    public:
        enum Id
        {
            none
            , incorrect_unit
            , no_available_unit
            , incorrect_lock_key
        };
        QString to_string() const
        {
            QString prefix( "TextureUnits : " );
            switch( id() )
            {
            case none: return( QString("none") );
            case incorrect_unit: return( prefix.append("incorrect value of texture unit") );
            case no_available_unit: return( prefix.append("no available values of texture unit") );
            case incorrect_lock_key: return( prefix.append("incorrect name of key of locked texture unit") );
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

#endif // TEXTURE_UNITS_H
