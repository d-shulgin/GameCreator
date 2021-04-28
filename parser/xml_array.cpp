#include "xml_array.h"

XMLArray::XMLArray()
{
}
void XMLArray::Load( QDomElement& el_array )
{
    if( !el_array.isNull() )
    {
        QDomElement el_element = el_array.firstChildElement( XMLWord(XMLID::_element).to_string() );
        while( !el_element.isNull() )
        {
            QDomElement el_object = el_element.firstChildElement( XMLWord(XMLID::_object).to_string() );
            if( !el_object.isNull() )
            {
                XMLObject* object = add_object();
                if( 0 != object )
                    object -> Load( el_object );
            }
            el_element = el_element.nextSiblingElement( XMLWord(XMLID::_element).to_string() );
        }
        event_Loaded();
    }
    return;
}
bool XMLArray::Save( QDomDocument& xml
                     , QDomElement& el_array )
{
    if( !el_array.isNull() )
    {
        size_t index = 0;
        QDomElement el_element = el_array.firstChildElement( XMLWord(XMLID::_element).to_string() );
        while( !el_element.isNull() )
        {
            QDomElement el_removed;
            if( index < count_objects() )
            {
                if( 0 != object(index) )
                {
                    QDomElement el_object = el_element.firstChildElement( XMLWord(XMLID::_object).to_string() );
                    if( el_object.isNull() )
                    {
                        el_object = xml.createElement( XMLWord(XMLID::_object).to_string() );
                        el_element.appendChild( el_object );
                        el_object.setAttribute( XMLWord(XMLID::_class).to_string()
                                                , object(index) -> xml_class_name() );
                    }
                    get_object(index) -> Save(xml, el_object);
                }
            }
            else
            {
                el_removed = el_element;
            }
            el_element = el_element.nextSiblingElement( XMLWord(XMLID::_element).to_string() );
            if( el_removed.isNull() )
                index ++;
            else
                el_array.removeChild( el_removed );
        }
        for( size_t i = index; i < count_objects(); ++i )
        {
            QDomElement el_element = xml.createElement( XMLWord(XMLID::_element).to_string() );
            if( !el_element.isNull() )
            {
                el_array.appendChild( el_element );
                if( 0 != object(i) )
                {
                    QDomElement el_object = xml.createElement( XMLWord(XMLID::_object).to_string() );
                    el_element.appendChild( el_object );
                    el_object.setAttribute( XMLWord(XMLID::_class).to_string()
                                            , object(i) -> xml_class_name() );
                    get_object(i) -> Save( xml, el_object );
                }
            }
        }
        event_Saved();
        return( true );
    }
    return( false );
}
XMLArray::~XMLArray()
{
}
