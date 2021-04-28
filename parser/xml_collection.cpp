#include "xml_collection.h"

XMLCollection::XMLCollection()
    // //////////////////////////////////////////////////// |
{
}
void XMLCollection::Load( QDomElement& el_collection     // |
                          , const XMLFactory* factory )  // |
{
    if( !el_collection.isNull() )
    {
        QDomElement el_object = el_collection.firstChildElement( XMLWord(XMLID::_object).to_string() );
        while( !el_object.isNull() )
        {
            XMLObject* object = factory -> create( el_object.attribute(XMLWord(XMLID::_class).to_string()).toStdString() );
            if( 0 != object )
            {
                _objects.push_back( object );
                object -> Load( el_object );
            }
            el_object = el_object.nextSiblingElement( XMLWord(XMLID::_object).to_string() );
        }
        event_Loaded();
    }
    return;
}
bool XMLCollection::Save( QDomDocument& xml              // |
                          , QDomElement& el_collection ) // |
{
    if( !el_collection.isNull() )
    {
        size_t index = 0;
        QDomElement el_object = el_collection.firstChildElement( XMLWord(XMLID::_object).to_string() );
        while( !el_object.isNull() )
        {
            QDomElement el_removed;
            if( index < count() )
            {
                if( 0 != itemAt(index) )
                    (*this)[index] -> Save( xml, el_object );
                    //itemAt(index) -> Save( xml, el_object );
            }
            else
                el_removed = el_object;

            el_object = el_object.nextSiblingElement( XMLWord(XMLID::_object).to_string() );
            if( el_removed.isNull() )
                index ++;
            else
                el_collection.removeChild( el_removed );
        }
        for( size_t i = index; i < count(); ++i )
        {
            if( 0 != itemAt(i) )
            {
                QDomElement el_object = xml.createElement( XMLWord(XMLID::_object).to_string() );
                el_collection.appendChild( el_object );
                el_object.setAttribute( XMLWord(XMLID::_class).to_string()
                                        , itemAt(i) -> xml_class_name() );
                (*this)[i] -> Save( xml, el_object );
                //itemAt(i) -> Save( xml, el_object );
            }
        }
        event_Saved();
        return( true );
    }
    return( false );
}
void XMLCollection::release()                            // |
{
    std::vector< XMLObject* >::iterator it = _objects.begin();
    while( it != _objects.end() )
    {
        if( (*it) != 0 )
        {
            XMLObject* object = (*it);
            delete object;
        }
        ++ it;
    }
    _objects.clear();
    return;
}
XMLCollection::~XMLCollection()
{
    release();
}
