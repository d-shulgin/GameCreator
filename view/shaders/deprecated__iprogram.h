#ifndef PROGRAM_H
#define PROGRAM_H

#include "../../parser/xml_meta_data.h"

class IProgram : public XMLObject
{
public:
    static QString class_name() { return( QString("Program") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    explicit IProgram( const QString& = QString() );
    virtual ~IProgram();

public:
    IProgram( const IProgram& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _name = cpy._name;
    }
    IProgram& operator = ( const IProgram& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _name = cpy._name;

        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "name", &_name );
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
        return( new IProgram() );
    }
    virtual XMLObject* clone() const
    {
        IProgram* object = new IProgram();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: name
    QString _name;

public:
    const QString& name() const { return( _name ); }
    void setName( const QString& namae )
    {
        QString origin = name();
        _name = namae;
        _modify = _modify || (origin != name());
        return;
    }
};

#endif // PROGRAM_H
