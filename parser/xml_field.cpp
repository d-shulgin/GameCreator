#include "xml_field.h"
#include "xml_object.h"
#include "xml_enum.h"
#include "xml_array.h"
#include "xml_collection.h"

XMLField::XMLField()
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( bool* v )
    : _field_bool( v )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( int* v )
    : _field_bool( 0 )
    , _field_int( v )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( unsigned int* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( v )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( float* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( v )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( QString* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( v )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( std::vector<bool>* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( v )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( std::vector<int>* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( v )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( std::vector<unsigned int>* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( v )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( std::vector<float>* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( v )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( std::vector<QString>* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( v )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( XMLObject* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( v )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( XMLEnum* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( v )
    , _field_array( 0 )
    , _field_collection( 0 )
{}
XMLField::XMLField( XMLArray* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( v )
    , _field_collection( 0 )
{}
XMLField::XMLField( XMLCollection* v )
    : _field_bool( 0 )
    , _field_int( 0 )
    , _field_uint( 0 )
    , _field_float( 0 )
    , _field_str( 0 )
    , _field_arr_bool( 0 )
    , _field_arr_int( 0 )
    , _field_arr_uint( 0 )
    , _field_arr_float( 0 )
    , _field_arr_str( 0 )
    , _field_object( 0 )
    , _field_enum( 0 )
    , _field_array( 0 )
    , _field_collection( v )
    // /////////////////////////////////////// |
{
}
bool XMLField::isNull() const               // |
{
    return( 0 == _field_bool
            && 0 == _field_int
            && 0 == _field_uint
            && 0 == _field_float
            && 0 == _field_str
            && 0 == _field_arr_bool
            && 0 == _field_arr_int
            && 0 == _field_arr_uint
            && 0 == _field_arr_float
            && 0 == _field_arr_str
            && 0 == _field_object
            && 0 == _field_enum
            && 0 == _field_array
            && 0 == _field_collection );
}
bool XMLField::isEnum() const               // |
{
    return( 0 != _field_enum );
}
bool XMLField::isObject() const             // |
{
    return( 0 != _field_object );
}
bool XMLField::isVector() const             // |
{
    return( 0 != _field_arr_bool
            || 0 != _field_arr_int
            || 0 != _field_arr_uint
            || 0 != _field_arr_float
            || 0 != _field_arr_str );
}
bool XMLField::isArray() const              // |
{
    return( 0 != _field_array );
}
bool XMLField::isCollection() const         // |
{
    return( 0 != _field_collection );
}
void XMLField::set( const QString& value )  // |
{
    if( 0 != _field_bool )
        *_field_bool = ( value.compare("true", Qt::CaseInsensitive) == 0 );
    else if( 0 != _field_int )
        *_field_int = value.toInt();
    else if( 0 != _field_uint )
        *_field_uint = value.toUInt();
    else if( 0 != _field_float )
        *_field_float = value.toFloat();
    else if( 0 != _field_str )
        *_field_str = value;
    else if( 0 != _field_enum )
        _field_enum -> set( value );
    return;
}
QString XMLField::get() const               // |
{
    if( 0 != _field_bool )
        return( *_field_bool ? QString("true"): QString("false") );
    else if( 0 != _field_int )
        return( QString("%1").arg(*_field_int) );
    else if( 0 != _field_uint )
        return( QString("%1").arg(*_field_uint) );
    else if( 0 != _field_float )
        return( QString("%1").arg(*_field_float) );
    else if( 0 != _field_str )
        return( *_field_str );
    else if( 0 != _field_enum )
        return( _field_enum -> get() );
    return( QString() );
}
/// @section: object ///////////////////////////////////// |
void XMLField::load_object( QDomElement& el_object )    // |
{
    if( isObject() )
        _field_object -> Load( el_object );
    return;
}
bool XMLField::save_object( QDomDocument& xml           // |
                            , QDomElement& el_object )  // |
{
    if( isObject() )
    {
        if( el_object.attribute(XMLWord(XMLID::_class).to_string()).isEmpty() )
            el_object.setAttribute( XMLWord(XMLID::_class).to_string()
                                    , _field_object -> xml_class_name() );
        return( _field_object -> Save(xml, el_object) );
    }
    return( false );
}
/// @section: array ////////////////////////////////////// |
void XMLField::load_array( QDomElement& el_array )      // |
{
    if( isVector() )
        load_vector( el_array );
    else if( isArray() )
        _field_array -> Load( el_array );
    return;
}
bool XMLField::save_array( QDomDocument& xml            // |
                           , QDomElement& el_array )    // |
{
    if( isVector() )
        return( save_vector(xml, el_array) );
    else if( isArray() )
        return( _field_array -> Save(xml, el_array) );
    return( false );
}
/// @section: vector ///////////////////////////////////// |
void XMLField::load_vector( QDomElement& el_vector )    // |
{
    if( !el_vector.isNull() )
    {
        QDomElement el_element = el_vector.firstChildElement( XMLWord(XMLID::_element).to_string() );
        while( !el_element.isNull() )
        {
            QString value = el_element.attribute( XMLWord(XMLID::_value).to_string() );
            if( !value.isEmpty() )
            {
                if( 0 != _field_arr_bool )
                    _field_arr_bool -> push_back( value.compare("true", Qt::CaseInsensitive) == 0 );
                else if( 0 != _field_arr_int )
                    _field_arr_int -> push_back( value.toInt() );
                else if( 0 != _field_arr_uint )
                    _field_arr_uint -> push_back( value.toUInt() );
                else if( 0 != _field_arr_float )
                    _field_arr_float -> push_back( value.toFloat() );
                else if( 0 != _field_arr_str )
                    _field_arr_str -> push_back( value );
            }
            el_element = el_element.nextSiblingElement( XMLWord(XMLID::_element).to_string() );
        }
    }
    return;
}
bool XMLField::save_vector( QDomDocument& xml           // |
                            , QDomElement& el_vector )  // |
{
    if( !el_vector.isNull() )
    {
        size_t index = 0;
        QDomElement el_element = el_vector.firstChildElement( XMLWord(XMLID::_element).to_string() );
        while( !el_element.isNull() )
        {
            QDomElement el_removed;
            if( 0 != _field_arr_bool )
            {
                if( index < _field_arr_bool -> size() )
                    el_element.setAttribute( XMLWord(XMLID::_value).to_string()
                                             , ((*_field_arr_bool)[index] ? QString("true")
                                                                          : QString("false")) );
                else
                    el_removed = el_element;
            }
            else if( 0 != _field_arr_int )
            {
                if( index < _field_arr_int -> size() )
                    el_element.setAttribute( XMLWord(XMLID::_value).to_string()
                                             , QString("%1").arg((*_field_arr_int)[index]) );
                else
                    el_removed = el_element;
            }
            else if( 0 != _field_arr_uint )
            {
                if( index < _field_arr_uint -> size() )
                    el_element.setAttribute( XMLWord(XMLID::_value).to_string()
                                             , QString("%1").arg((*_field_arr_uint)[index]) );
                else
                    el_removed = el_element;
            }
            else if( 0 != _field_arr_float )
            {
                if( index < _field_arr_float -> size() )
                    el_element.setAttribute( XMLWord(XMLID::_value).to_string()
                                             , QString("%1").arg((*_field_arr_float)[index]) );
                else
                    el_removed = el_element;
            }
            else if( 0 != _field_arr_str )
            {
                if( index < _field_arr_str -> size() )
                    el_element.setAttribute( XMLWord(XMLID::_value).to_string()
                                             , (*_field_arr_str)[index] );
                else
                    el_removed = el_element;
            }
            el_element = el_element.nextSiblingElement( XMLWord(XMLID::_element).to_string() );
            if( el_removed.isNull() )
                index ++;
            else
                el_vector.removeChild( el_removed );
        }
        size_t size = 0;
        if( 0 != _field_arr_bool )
            size = _field_arr_bool -> size();
        else if( 0 != _field_arr_int )
            size = _field_arr_int -> size();
        else if( 0 != _field_arr_uint )
            size = _field_arr_uint -> size();
        else if( 0 != _field_arr_float )
            size = _field_arr_float -> size();
        else if( 0 != _field_arr_str )
            size = _field_arr_str -> size();
        for( size_t i = index; i < size; ++i )
        {
            QDomElement el_element = xml.createElement( XMLWord(XMLID::_element).to_string() );
            if( !el_element.isNull() )
            {
                el_vector.appendChild( el_element );
                if( 0 != _field_arr_bool )
                    el_element.setAttribute( XMLWord(XMLID::_value).to_string()
                                             , ((*_field_arr_bool)[i] ? QString("true")
                                                                      : QString("false")) );
                else if( 0 != _field_arr_int )
                    el_element.setAttribute( XMLWord(XMLID::_value).to_string()
                                             , QString("%1").arg((*_field_arr_int)[i]) );
                else if( 0 != _field_arr_uint )
                    el_element.setAttribute( XMLWord(XMLID::_value).to_string()
                                             , QString("%1").arg((*_field_arr_uint)[i]) );
                else if( 0 != _field_arr_float )
                    el_element.setAttribute( XMLWord(XMLID::_value).to_string()
                                             , QString("%1").arg((*_field_arr_float)[i]) );
                else if( 0 != _field_arr_str )
                    el_element.setAttribute( XMLWord(XMLID::_value).to_string()
                                             , (*_field_arr_str)[i] );
            }
        }
        return( true );
    }
    return( false );
}
/// @section: collection ///////////////////////////////////////// |
void XMLField::load_collection( QDomElement& el_collection      // |
                                , const XMLFactory* factory )   // |
{
    if( isCollection() && 0 != factory )
        _field_collection -> Load( el_collection, factory );
    return;
}
bool XMLField::save_collection( QDomDocument& xml               // |
                                , QDomElement& el_collection )  // |
{
    if( isCollection() )
        return( _field_collection -> Save(xml, el_collection) );
    return( false );
}
XMLField::~XMLField()
{}









