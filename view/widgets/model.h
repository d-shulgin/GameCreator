#ifndef MODEL_H
#define MODEL_H

#include "view.h"
#include "shape.h"

class Model : public View
{
public:
    static QString class_name() { return( QString("Model") ); }
    virtual QString xml_class_name() const
    {
        if( View::xml_class_name().isEmpty() )
            return( class_name() );
        return( View::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( View::isModify() || _modify ); }

public:
    explicit Model( const QString& = QString(), const QString& = QString() );
    virtual ~Model();

public:
    Model( const Model& cpy )
        : View( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _path = cpy._path;
        _shapes = cpy._shapes;
        _vertices = cpy._vertices;
    }
    Model& operator = ( const Model& cpy )
    {
        if( this != &cpy )
        {
            View::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _path = cpy._path;
            _shapes = cpy._shapes;
            _vertices = cpy._vertices;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        View::bind_fields();
        bind_field( "path", &_path );
        bind_field( "shapes", &_shapes );
        return;
    }

protected:
    virtual void event_Saved()
    {
        View::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        View::event_Loaded( success );
        if( success )
        {
            _modify = false;
            createModel();
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Model() );
    }
    virtual XMLObject* clone() const
    {
        Model* object = new Model();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: path of shape
    QString _path;

public:
    const QString& path() const;
    void setPath(const QString& path);

private: /// @section: shapes (non-bind_field)
    XMLCollection _shapes;

protected:
    const Shape* shape_const( size_t ) const;
    void addShape( Shape* shape )
    {
        _shapes << static_cast< XMLObject* >( shape );
        _modify = true;
        return;
    }

public:
    const XMLCollectionU& shapes() const { return( _shapes ); }

private: /// @section: vertices
    Vertices _vertices;

protected:
    virtual void createModel();
    void getTB( int, Vector3*, Vector3* );

public:
    const Vertices& vertices() const { return( _vertices ); }

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
    virtual void drawShadow( QGLFunctions* ) const;

public: /// @section: exception
    class Error
    {
    public:
        enum Id
        {
            none
            , pointer_is_NULL
            , incorrect_vertex_info
            , incorrect_material_name
        };
        QString to_string() const
        {
            QString prefix( "Model : " );
            switch( id() )
            {
            case none: return( QString("none") );
            case pointer_is_NULL: return( prefix.append("pointer is NULL") );
            case incorrect_vertex_info: return( prefix.append("incorrect vertex info") );
            case incorrect_material_name: return( prefix.append("incorrect material name") );
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
class ModelV2 : public View
{
public:
    static QString class_name() { return( QString("ModelV2") ); }
    virtual QString xml_class_name() const
    {
        if( View::xml_class_name().isEmpty() )
            return( class_name() );
        return( View::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( View::isModify() || _modify ); }

public:
    explicit ModelV2( const QString& = QString(), const QString& = QString() );
    virtual ~ModelV2();

public:
    ModelV2( const ModelV2& cpy )
        : View( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _name_mesh = cpy._name_mesh;
    }
    ModelV2& operator = ( const ModelV2& cpy )
    {
        if( this != &cpy )
        {
            View::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _name_mesh = cpy._name_mesh;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        View::bind_fields();
        bind_field( "name_mesh", &_name_mesh );
        return;
    }

protected:
    virtual void event_Saved()
    {
        View::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        View::event_Loaded( success );
        if( success )
        {
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new ModelV2() );
    }
    virtual XMLObject* clone() const
    {
        ModelV2* object = new ModelV2();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: mesh
    QString _name_mesh;

    void bind_material( QGLFunctions*, const QString& ) const;
    void unbind_material( QGLFunctions*, const QString& ) const;
    void bind_data( QGLFunctions* ) const;
    void unbind_data( QGLFunctions* ) const;

public:
    const QString& name_mesh() const { return( _name_mesh ); }

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
    virtual void drawShadow( QGLFunctions* ) const;
};

#endif // MODEL_H
