#include "xml_object.h"

XMLFactory XMLObject::_factory = XMLFactory();

XMLObject::XMLObject()
{
}
void XMLObject::Load( QDomElement& el_object )
{
    if( xml_class_name().isEmpty() )
        return;
    if( !el_object.isNull()
            && el_object.attribute(XMLWord(XMLID::_class).to_string()) == xml_class_name() )
    {
        int loaded = 0;
        QDomElement el_field = el_object.firstChildElement( XMLWord(XMLID::_field).to_string() );
        while( !el_field.isNull() )
        {
            QString key = el_field.attribute( XMLWord(XMLID::_name).to_string() );
            if( key.isEmpty() )
                key = el_field.attribute( XMLWord(XMLID::_enum).to_string() );
            QDomElement el_array = el_field.firstChildElement( XMLWord(XMLID::_array).to_string() );
            if( el_array.isNull() )
            {
                QDomElement el_collection = el_field.firstChildElement( XMLWord(XMLID::_collection).to_string() );
                if( el_collection.isNull() )
                {
                    QDomElement el_value = el_field.firstChildElement( XMLWord(XMLID::_object).to_string() );
                    if( el_value.isNull() )
                    {
                        QString value = el_field.attribute( XMLWord(XMLID::_value).to_string() );
                        if( _fields.contains(key)
                                && !value.isEmpty()
                                && !_fields[key].isNull() )
                        {
                            loaded ++;
                            _fields[key].set( value );
                        }
                    }
                    else
                    {
                        if( _fields.contains(key)
                                && _fields[key].isObject() )
                        {
                            loaded ++;
                            _fields[key].load_object( el_value );
                        }
                    }
                }
                else
                {
                    if( _fields.contains(key) && _fields[key].isCollection() )
                    {
                        loaded ++;
                        _fields[key].load_collection( el_collection, &XMLObject::factory() );
                    }
                }
            }
            else
            {
                if( _fields.contains(key)
                        && (_fields[key].isArray() || _fields[key].isVector()) )
                {
                    loaded ++;
                    _fields[key].load_array( el_array );
                }
            }
            el_field = el_field.nextSiblingElement( XMLWord(XMLID::_field).to_string() );
        }
        event_Loaded( loaded == _fields.keys().size() );
    }
    return;
}
bool XMLObject::Save( QDomDocument& xml
                      , QDomElement& el_object )
{
    if( xml_class_name().isEmpty() )
        return( false );
    if( !el_object.isNull()
            && el_object.attribute(XMLWord(XMLID::_class).to_string()) == xml_class_name() )
    {
        QStringList keys = _fields.keys();
        // changed fields of xml-structure   |
        {
            QDomElement el_field = el_object.firstChildElement( "field" );
            while( !el_field.isNull() )
            {
                QString key = el_field.attribute( XMLWord(XMLID::_name).to_string() );
                if( key.isEmpty() )
                    key = el_field.attribute( XMLWord(XMLID::_enum).to_string() );
                if( keys.contains(key) )
                {
                    if( _fields[key].isArray() || _fields[key].isVector() )
                    {
                        QDomElement el_array = el_field.firstChildElement( XMLWord(XMLID::_array).to_string() );
                        _fields[key].save_array( xml, el_array );
                        keys.removeOne( key );
                    }
                    else if( _fields[key].isCollection() )
                    {
                        QDomElement el_collection = el_field.firstChildElement( XMLWord(XMLID::_collection).to_string() );
                        _fields[key].save_collection( xml, el_collection );
                        keys.removeOne( key );
                    }
                    else if( _fields[key].isObject() )
                    {
                        QDomElement el_value = el_field.firstChildElement( XMLWord(XMLID::_object).to_string() );
                        _fields[key].save_object( xml, el_value );
                        keys.removeOne( key );
                    }
                    else if( !_fields[key].get().isEmpty() )
                    {
                        el_field.setAttribute( XMLWord(XMLID::_value).to_string()
                                               , _fields[key].get() );
                        keys.removeOne( key );
                    }
                }
                el_field = el_field.nextSiblingElement( "field" );
            }
        }
        // added new fields of xml-structure |
        {
            QStringList::const_iterator it = keys.constBegin();
            while( it != keys.constEnd() )
            {
                QString key = (*it);
                QDomElement el_field = xml.createElement( "field" );
                if( !el_field.isNull() )
                {
                    el_object.appendChild( el_field );
                    if( _fields[key].isEnum() )
                        el_field.setAttribute( XMLWord(XMLID::_enum).to_string(), key );
                    else
                        el_field.setAttribute( XMLWord(XMLID::_name).to_string(), key );
                    if( _fields[key].isArray() || _fields[key].isVector() )
                    {
                        QDomElement el_array = xml.createElement( XMLWord(XMLID::_array).to_string() );
                        if( !el_array.isNull() )
                        {
                            el_field.appendChild( el_array );
                            _fields[key].save_array( xml, el_array );
                        }
                    }
                    else if( _fields[key].isCollection() )
                    {
                        QDomElement el_collection = xml.createElement( XMLWord(XMLID::_collection).to_string() );
                        if( !el_collection.isNull() )
                        {
                            el_field.appendChild( el_collection );
                            _fields[key].save_collection( xml, el_collection );
                        }
                    }
                    else if( _fields[key].isObject() )
                    {
                        QDomElement el_value = xml.createElement( XMLWord(XMLID::_object).to_string() );
                        if( !el_value.isNull() )
                        {
                            el_field.appendChild( el_value );
                            _fields[key].save_object( xml, el_value );
                        }
                    }
                    else
                    {
                        el_field.setAttribute( XMLWord(XMLID::_value).to_string()
                                               , _fields[key].get() );
                    }
                }
                ++it;
            }
        }
        event_Saved();
        return( true );
    }
    return( false );
}
XMLObject::~XMLObject()
{
}


XMLFactory::XMLFactory()
{
}
XMLObject* XMLFactory::registerObject(XMLObject *object)
{
    if( 0 == object )
        return( 0 );
    std::map< std::string, XMLObject* >::const_iterator it = _register_objects.begin();
    while( it != _register_objects.end() )
    {
        std::string key = it -> first;
        if( key == object -> xml_class_name().toStdString() )
            return( object );
        ++ it;
    }
    _register_objects[ object -> xml_class_name().toStdString() ] = object -> create();
    return( object );
}
XMLObject *XMLFactory::create(const std::string &namae) const
{
    std::map< std::string, XMLObject*>::const_iterator it = _register_objects.begin();
    while( it != _register_objects.end() )
    {
        if( it -> first == namae && 0 != it -> second )
            return( it -> second -> create() );
        ++it;
    }
    return( 0 );
}
XMLFactory::~XMLFactory()
{
    std::map< std::string, XMLObject* >::iterator it = _register_objects.begin();
    while( it != _register_objects.end() )
    {
        if( 0 != it -> second )
        {
            XMLObject* object = it -> second;
            delete object;
            it->second = 0;
        }
        ++ it;
    }
}

