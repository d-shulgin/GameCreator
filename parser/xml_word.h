#ifndef XML_WORD_H
#define XML_WORD_H

#include <QString>

class XMLID
{
public:
    enum val { unknown
              , _name
              , _enum
              , _value
              , _object
              , _field
              , _class
              , _array
              , _element
              , _collection
            };
    XMLID(){}
};

class XMLWord
{
private:
    XMLID::val _id;

public:
    XMLWord()
        : _id( XMLID::unknown )
    {}
    explicit XMLWord( XMLID::val v )
        : _id( v )
    {}

    XMLID::val id() const { return( _id ); }
    QString to_string()
    {
        switch ( id() )
        {
        case XMLID::unknown:     return( QString() );
        case XMLID::_name:       return( QString("var") );
        case XMLID::_enum:       return( QString("enum") );
        case XMLID::_value:      return( QString("value") );
        case XMLID::_object:     return( QString("object") );
        case XMLID::_field:      return( QString("field") );
        case XMLID::_class:      return( QString("class") );
        case XMLID::_array:      return( QString("array") );
        case XMLID::_element:    return( QString("element") );
        case XMLID::_collection: return( QString("collectiont") );
        default:
            break;
        }
        return( QString() );
    }
};

#endif // XML_WORD_H
