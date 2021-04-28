#ifndef XML_ENUM_H
#define XML_ENUM_H

#include <QString>
#include "../utils/exception.h"

class XMLEnum
{
//    QString _string;
public:
    XMLEnum(){}
    virtual ~XMLEnum(){}

    virtual void set( const QString& ){}
    virtual const QString get() const { return( QString() ); }

public:
    XMLEnum( const XMLEnum& )
    {
    }
    XMLEnum& operator = ( const XMLEnum& )
    {
        return( *this );
    }
};
class EnumValue
{
public:
    EnumValue(){}
    explicit EnumValue( const QString& ){}
    virtual ~EnumValue(){}

public:
    virtual QString to_string() const { return(QString()); }
    virtual int to_int() const { return( 0 ); }

public: /// @section: exception
    class Error
    {
    public:
        enum Id
        {
            none
            , unknown_enum_id
        };
        QString to_string() const
        {
            QString prefix( "EnumValue : " );
            switch( id() )
            {
            case none: return( QString("none") );
            case unknown_enum_id: return( prefix.append("unknown enumeration id") );
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
template < typename EnumValue >
class EnumAs: public XMLEnum
{
public:
    EnumAs()
        : XMLEnum()
    {}
    explicit EnumAs( const EnumValue& v )
        : XMLEnum()
        , _value( v )
    {}
    virtual ~EnumAs(){}

public:
    EnumAs( const EnumAs<EnumValue>& cpy )
        : XMLEnum( cpy )
    {
        _value = cpy._value;
    }
    EnumAs<EnumValue>& operator = ( const EnumAs<EnumValue>& cpy )
    {
        if( this != &cpy )
        {
            XMLEnum::operator = ( cpy );
            _value = cpy._value;
        }
        return( *this );
    }

private: /// @section: value
    EnumValue _value;

public:
    virtual void set( const QString& v )
    {
        _value = EnumValue( v );
        return;
    }
    virtual const QString get() const
    {
        return( _value.to_string() );
    }
    int value() const
    {
        return( _value.to_int() );
    }
    const QString to_string() const
    {
        return( _value.to_string() );
    }

public: /// @section: operators boolean
    bool operator == ( const EnumAs<EnumValue>& e ) const
    {
        return( value() == e.value() );
    }
};

#endif // XML_ENUM_H
