#ifndef PROGRAM_MGR_H
#define PROGRAM_MGR_H

#include <QGLFunctions>

#include "../../parser/xml_meta_data.h"
#include "program_shader.h"
#include "program_attr.h"
#include "program_uniform.h"
#include "texture_units.h"

class ProgramMgr : public XMLObject
{
public:
    static QString class_name() { return( QString("ProgramMgr") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify || isAnyElementModify() ); }

public:
    ProgramMgr();
    virtual ~ProgramMgr();

public:
    ProgramMgr( const ProgramMgr& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _programs = cpy._programs;
        _activated_program = cpy._activated_program;
        _attr = cpy._attr;
        _uniform = cpy._uniform;
        _handle = cpy._handle;
    }
    ProgramMgr& operator = ( const ProgramMgr& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _programs = cpy._programs;
            _activated_program = cpy._activated_program;
            _attr = cpy._attr;
            _uniform = cpy._uniform;
            _handle = cpy._handle;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "programs", &_programs );
        bind_field( "attr", &_attr );
        bind_field( "uniform", &_uniform );
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
        return( new ProgramMgr() );
    }
    virtual XMLObject* clone() const
    {
        ProgramMgr* object = new ProgramMgr();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < programs().count(); ++i )
            modify = cref_programs().itemAt(i) -> isModify();
//        for( size_t i = 0; i < cameras().count() && !modify; ++i )
//            modify = cref_cameras().itemAt(i) -> isModify();
//        for( size_t i = 0; i < views().count() && !modify; ++i )
//            modify = cref_views().itemAt(i) -> isModify();
//        for( size_t i = 0; i < lights().count() && !modify; ++i )
//            modify = cref_lights().itemAt(i) -> isModify();
        return( modify );
    }

private:
    XMLCollection _programs;

    const XMLCollection& cref_programs() const { return( _programs ); }
    XMLCollection& ref_programs() { return( _programs ); }

public:
    const XMLCollectionU& programs() const { return( _programs ); }
    const ProgramShader* program_const( size_t ) const;
    ProgramShader* program( size_t );

public:
    void add( ProgramShader* object )
    {
        _programs << static_cast< XMLObject* >( object );
        _modify = true;
        return;
    }
    ProgramShader* getProgram();
    ProgramShader* getProgram( size_t );
    ProgramShader* getProgram( const QString& );

public: /// @section: compile
    void compileAll( QGLFunctions* );

private: /// @section: bind
    QString _activated_program;

public:
    const QString& activated_program() const { return( _activated_program ); }
    void bind( QGLFunctions*, QString );
    void unbind( ProgramShader* , QGLFunctions* );

private: /// @section: attribute
    ProgramAttr _attr;

public:
    const ProgramAttr& attr() const { return( _attr ); }
    ProgramAttr& ref_attr() { return( _attr ); }

private: /// @section: uniform
    ProgramUniform _uniform;

public:
    const ProgramUniform& uniform() const { return( _uniform ); }
    ProgramUniform& ref_uniform() { return( _uniform ); }

private: /// @section: texture units
    TextureUnits _units;

public:
    const TextureUnits& textureUnits() const { return( _units ); }
    TextureUnits& ref_textureUnits() { return( _units ); }

public: /// @section: callback
    class Callback
    {
    public:
        Callback(){}

        virtual void event_ProgramDeactivated( ProgramShader*, QGLFunctions* ) const = 0;
        virtual void event_ProgramActivated( ProgramShader*, QGLFunctions* ) const = 0;
        virtual QString event_DefaultProgram() const = 0;
    };

    void setCallback( const Callback* h ){ _handle = h; }

private:
    const Callback* _handle;

public: /// @section: exception
    class Error
    {
    public:
        enum Id
        {
            none
            , pointer_is_NULL
        };
        QString to_string() const
        {
            QString prefix( "ProgramMgr : " );
            switch( id() )
            {
            case none: return( QString("none") );
            case pointer_is_NULL: return( prefix.append("pointer is NULL") );
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

#endif // PROGRAM_MGR_H
