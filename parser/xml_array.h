#ifndef XML_ARRAY_H
#define XML_ARRAY_H

#include "xml_word.h"
#include "xml_object.h"

class XMLArray
{
public:
    XMLArray();
    virtual ~XMLArray();

    virtual bool isModify() const { return( false ); }

    virtual void Load( QDomElement& );
    virtual bool Save( QDomDocument&, QDomElement& );

public:
    XMLArray( const XMLArray& /*cpy*/ )
    {
    }
    XMLArray& operator = ( const XMLArray& /*cpy*/ )
    {
        return( *this );
    }

    size_t count() const { return( count_objects() ); }

protected:
    virtual size_t count_objects() const { return( 0 ); }
    virtual XMLObject* add_object(){ return( 0 ); }
    virtual const XMLObject* object( size_t ) const { return( 0 ); }
    virtual XMLObject* get_object( size_t ){ return( 0 ); }

protected:
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < count_objects() && !modify; ++i )
        {
            if( object(i) != 0 )
                modify = object(i) -> isModify();
        }
        return( modify );
    }

protected: /// @section: events
    virtual void event_Saved(){ return; }
    virtual void event_Loaded(){ return; }
};

#endif // XML_ARRAY_H
