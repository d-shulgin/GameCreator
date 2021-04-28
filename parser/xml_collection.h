#ifndef XML_COLLECTION_H
#define XML_COLLECTION_H

#include "xml_word.h"
#include "xml_object.h"

class XMLCollectionU
{
public:
    XMLCollectionU(){}

    virtual size_t count() const { return( 0 ); }
    virtual XMLCollectionU& operator << ( XMLObject* ){ return( *this ); }
};

class XMLCollection : public XMLCollectionU
{
public:
    virtual bool isModify() const { return( false ); }

public:
    XMLCollection();
    virtual ~XMLCollection();

    virtual void Load( QDomElement&, const XMLFactory* );
    virtual bool Save( QDomDocument&, QDomElement& );

public:
    XMLCollection( const XMLCollection& cpy )
    {
        release();
        _objects.reserve( cpy.count() );
        std::vector< XMLObject* >::const_iterator it = cpy._objects.begin();
        while( it != cpy._objects.end() )
        {
            if( (*it) != 0 )
            {
                XMLObject* object = (*it);
                _objects.push_back( object -> clone() );
            }
            ++ it;
        }
    }
    XMLCollection& operator = ( const XMLCollection& cpy )
    {
        if( this != &cpy )
        {
            release();
            _objects.reserve( cpy.count() );
            std::vector< XMLObject* >::const_iterator it = cpy._objects.begin();
            while( it != cpy._objects.end() )
            {
                if( (*it) != 0 )
                {
                    XMLObject* object = (*it);
                    _objects.push_back( object -> clone() );
                }
                ++ it;
            }
        }
        return( *this );
    }

private:
    std::vector< XMLObject* > _objects;

    void release();

public:
    void reset() { release(); }

public:
    virtual size_t count() const { return( _objects.size() ); }
    virtual XMLCollectionU& operator << ( XMLObject* object )
    {
        if( 0 != object )
        {
            _objects.push_back( object );
        }
        return( *this );
    }
    const XMLObject* itemAt( size_t index ) const
    {
        if( index < _objects.size() )
            return( _objects[index] );
        return( 0 );
    }
    XMLObject* operator[] ( size_t index )
    {
        if( index < _objects.size() )
            return( _objects[index] );
        return( 0 );
    }

protected: /// @section: events
    virtual void event_Saved(){ return; }
    virtual void event_Loaded(){ return; }
};

#endif // XML_COLLECTION_H
