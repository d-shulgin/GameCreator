#ifndef MESH_H
#define MESH_H

#include <QGLFunctions>
#include "../../parser/xml_meta_data.h"
#include "../widgets/vertices.h"

class MeshShape : public XMLObject
{
public:
    static QString class_name() { return( QString("MeshShape") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    explicit MeshShape( GLuint = 0, GLsizei = 0, const QString& = QString() );
    virtual ~MeshShape();

    void release( QGLFunctions* );

public:
    MeshShape( const MeshShape& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _EBO = cpy._EBO;
        _material = cpy._material;
        _size = cpy._size;
    }
    MeshShape& operator = ( const MeshShape& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _EBO = cpy._EBO;
            _material = cpy._material;
            _size = cpy._size;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
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
        {
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new MeshShape() );
    }
    virtual XMLObject* clone() const
    {
        MeshShape* object = new MeshShape();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: EBO
    GLuint _EBO;

public:
    void bind( QGLFunctions* ) const;
    void unbind( QGLFunctions* ) const;

private: /// @section: material
    QString _material;

public:
    const QString& material() const { return( _material ); }

private: /// @section: size
    GLsizei _size;

public:
    GLsizei size() const { return(_size); }
};
class Mesh : public XMLObject
{
public:
    static QString class_name() { return( QString("Mesh") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    explicit Mesh( const QString& = QString(), const QString& = QString() );
    virtual ~Mesh();

public:
    void load( QGLFunctions* );
    void release( QGLFunctions* );
    bool is_loaded() const;

public:
    Mesh( const Mesh& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _name = cpy._name;
        _filepath = cpy._filepath;
        _VBO = cpy._VBO;
        _shapes = cpy._shapes;
    }
    Mesh& operator = ( const Mesh& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _name = cpy._name;
            _filepath = cpy._filepath;
            _VBO = cpy._VBO;
            _shapes = cpy._shapes;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "name",     &_name );
        bind_field( "filepath", &_filepath );
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
        {
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Mesh() );
    }
    virtual XMLObject* clone() const
    {
        Mesh* object = new Mesh();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: name
    QString _name;

public:
    const QString& name() const;
    void setName(const QString& name);

private: /// @section: filepath
    QString _filepath;

public:
    const QString& filepath() const;
    void setFilepath(const QString& filepath);

private: /// @section: VBO
    GLuint _VBO;

    void createVBO( QGLFunctions*, const Vertices& );
    GLuint createEBO( QGLFunctions*, const std::vector<unsigned int>& );

public:
    void bind( QGLFunctions* ) const;
    void unbind( QGLFunctions* ) const;

private: /// @section: shapes
    XMLCollection _shapes;

    void addShape( MeshShape* );

public:
    const XMLCollectionU& shapes() const { return( _shapes ); }
    MeshShape* shape( size_t );

public: /// @section: exception
    class Error
    {
    public:
        enum Id
        {
            none
            , pointer_is_NULL
            , incorrect_vertex_info
            , incorrect_material
            , incorrect_material_name
            , incorrect_frame_structure
            , incorrect_VBO
            , incorrect_EBO
        };
        QString to_string() const
        {
            QString prefix( "Mesh : " );
            switch( id() )
            {
            case none: return( QString("none") );
            case pointer_is_NULL: return( prefix.append("pointer is NULL") );
            case incorrect_vertex_info: return( prefix.append("incorrect vertex info") );
            case incorrect_material: return( prefix.append("incorrect material file name") );
            case incorrect_material_name: return( prefix.append("incorrect material name") );
            case incorrect_frame_structure: return( prefix.append("incorrect frame structure (3 or 4 vertices structure supported)") );
            case incorrect_VBO: return( prefix.append("incorrect VBO guid") );
            case incorrect_EBO: return( prefix.append("incorrect EBO guid") );
            default:
                break;
            }
            return( QString("unknown") );
        }

    private:
        Id _id;
        QString _str;

    public:
        Error()
            : _id( none )
        {}
        explicit Error( Id id )
            : _id( id )
        {}
        explicit Error( Id id, const QString& s )
            : _id( id )
            , _str( s )
        {}
        ~Error()
        {}

    public:
        Error( const Error& cpy )
        {
            _id  = cpy._id;
            _str = cpy._str;
        }
        Error& operator = ( const Error& cpy )
        {
            if( this != &cpy )
            {
                _id  = cpy._id;
                _str = cpy._str;
            }
            return( *this );
        }

    public:
        Id id() const { return( _id ); }
        const QString& str() const { return( _str ); }
    };
    class Exception : public IException
    {
    public:
        Exception() throw()
            : IException()
        {
            create_desc();
        }
        explicit Exception( Error::Id id ) throw()
            : IException()
            , _error( Error(id) )
        {
            create_desc();
        }
        explicit Exception( Error::Id id, const QString& str ) throw()
            : IException()
            , _error( Error(id, str) )
        {
            create_desc();
        }
        virtual ~Exception() throw()
        {}

    public:
        Exception( const Exception& cpy ) throw()
        {
            _error = cpy._error;
            create_desc();
        }
        Exception& operator = ( const Exception& cpy ) throw()
        {
            if( this != &cpy )
            {
                _error = cpy._error;
                create_desc();
            }
            return( *this );
        }

    private:
        Error _error;

    public:
        const Error& error() const throw()
        {
            return( _error );
        }
        virtual int error_id() const throw() { return( error().id() ); }
        virtual QString description() const throw()
        {
            if( error().str().isEmpty() )
                return( error().to_string() );
            return( error().to_string().append(": ").append(error().str()) );
        }
    };
};

#endif // MESH_H
