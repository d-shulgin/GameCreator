#ifndef XML_FIELD_H
#define XML_FIELD_H

#include <QString>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <vector>

#include "xml_word.h"

class XMLObject;
class XMLEnum;
class XMLArray;
class XMLCollection;
class XMLFactory;

class XMLField
{
public:
    XMLField();
    explicit XMLField( bool* );
    explicit XMLField( int* );
    explicit XMLField( unsigned int* );
    explicit XMLField( float* );
    explicit XMLField( QString* );
    explicit XMLField( std::vector<bool>* );
    explicit XMLField( std::vector<int>* );
    explicit XMLField( std::vector<unsigned int>* );
    explicit XMLField( std::vector<float>* );
    explicit XMLField( std::vector<QString>* );
    explicit XMLField( XMLObject* );
    explicit XMLField( XMLEnum* );
    explicit XMLField( XMLArray* );
    explicit XMLField( XMLCollection* );
    ~XMLField();

    bool isNull() const;
    bool isEnum() const;
    bool isObject() const;
    bool isVector() const;
    bool isArray() const;
    bool isCollection() const;

private:
    bool*           _field_bool;
    int*            _field_int;
    unsigned int*   _field_uint;
    float*          _field_float;
    QString*        _field_str;
    std::vector< bool >*            _field_arr_bool;
    std::vector< int >*             _field_arr_int;
    std::vector< unsigned int >*    _field_arr_uint;
    std::vector< float >*           _field_arr_float;
    std::vector< QString >*         _field_arr_str;
    XMLObject*      _field_object;
    XMLEnum*        _field_enum;
    XMLArray*       _field_array;
    XMLCollection*  _field_collection;

public:
    void set( const QString& );
    QString get() const;

public: /// @section: object
    void load_object( QDomElement& );
    bool save_object( QDomDocument&, QDomElement& );

public: /// @section: array
    void load_array( QDomElement& );
    bool save_array( QDomDocument&, QDomElement& );

private: /// @section: vector
    void load_vector( QDomElement& );
    bool save_vector( QDomDocument&, QDomElement& );

public: /// @section: collection
    void load_collection( QDomElement&, const XMLFactory* );
    bool save_collection( QDomDocument&, QDomElement& );
};

#endif // XML_FIELD_H
