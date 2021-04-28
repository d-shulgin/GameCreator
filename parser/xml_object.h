#ifndef XML_OBJECT_H
#define XML_OBJECT_H

#include <QString>
#include <QMap>
#include <QList>
#include <QStringList>
#include <QtXml/QDomDocument>

#include "xml_word.h"
#include "xml_field.h"

#include <map>
#include <string>
#include <iostream>

class XMLObject;
class XMLFactory
{
public:
    XMLFactory();
    ~XMLFactory();

public:
    XMLObject* registerObject( XMLObject* object );
    XMLObject* create( const std::string& namae ) const;

private:
    std::map< std::string, XMLObject* > _register_objects;
};

class XMLObject
{
public:
    XMLObject();
    virtual ~XMLObject();

    virtual QString xml_class_name() const { return( QString() ); }
    virtual bool isModify() const { return( false ); }

    virtual void Load( QDomElement& );
    virtual bool Save( QDomDocument&, QDomElement& );

public:
    XMLObject( const XMLObject& /*cpy*/ )
    {
        unbind_fields();
    }
    XMLObject& operator = ( const XMLObject& cpy )
    {
        if( this != &cpy )
        {
            unbind_fields();
        }
        return( *this );
    }

private: /// @section: fields
    QMap< QString, XMLField > _fields;

protected:
    template< typename Ptr >
    XMLObject& bind_field( const QString& key, Ptr* ptr_of_field_class )
    {
        if( !_fields.contains(key) )
            _fields[key] = XMLField( ptr_of_field_class );
        return( *this );
    }
    void unbind_fields()
    {
        _fields.clear();
    }
    virtual void bind_fields()
    {
        return;
    }

protected: /// @section: events
    virtual void event_Saved(){ return; }
    virtual void event_Loaded( bool /*success*/ ){ return; }

protected: /// @section: factory
    static XMLFactory _factory;

public:
    virtual XMLObject* create() const = 0;
    virtual XMLObject* clone() const = 0;

public:
    static XMLFactory& factory() { return( _factory ); }

public: /// @section: object_cast
    template< class T, class O >
    static T* ptr_cast( O* object )
    {
        if( 0 != object )
        {
            XMLObject* ptr_object = static_cast< XMLObject* >( object );
            if( ptr_object -> xml_class_name().split(".", QString::SkipEmptyParts)
                    .contains(T::class_name()) )
                return( static_cast<T*>(ptr_object) );
        }
        return( 0 );
    }
};

#endif // XML_OBJECT_H
