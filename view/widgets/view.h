#ifndef VIEW_H
#define VIEW_H

#include "../../parser/xml_meta_data.h"
#include "../drawable.h"
#include "../render_item.h"
#include "../transform.h"
#include "../bounding.h"
#include "../shaders/package.h"
#include "../resources/package.h"

class View : public RenderItem
        , public Drawable
{
public:
    static QString class_name() { return( QString("View") ); }
    virtual QString xml_class_name() const
    {
        if( RenderItem::xml_class_name().isEmpty() )
            return( class_name() );
        return( RenderItem::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( RenderItem::isModify() || _modify
                                            || transform().isModify() ); }

public:
    class ShadowFilter : public EnumValue
    {
    public:
        enum id{ none
                 , PCF

                 , _first = none
                 , _last  = PCF
               };
        static int count() { return( last() - first() + 1 ); }
        static int first() { return( _first ); }
        static int last()  { return( _last ); }
        static QString to_string( int v )
        {
            return( to_string(id(v)) );
        }
        static QString to_string( id v )
        {
            switch( v )
            {
            case none: return( QString("none") );
            case PCF: return( QString("PCF") );
            default:
                break;
            }
            throw( Exception(Error::unknown_enum_id, "for View::ShadowFilter") );
        }

    public:
        ShadowFilter()
            : EnumValue()
            , _id( none )
        {}
        explicit ShadowFilter( const QString& v )
            : EnumValue( v )
        {
            for( int index = first(); index <= last(); ++index )
            {
                if( to_string(index) == v )
                {
                    _id = id(index);
                    return;
                }
            }
            throw( Exception(Error::unknown_enum_id, "for View::ShadowFilter") );
        }
        explicit ShadowFilter( id v )
            : EnumValue()
            , _id( v )
        {
        }
        virtual ~ShadowFilter()
        {}

    private:
        id _id;

    public:
        virtual QString to_string() const
        {
            return( to_string(_id) );
        }
        virtual int to_int() const
        {
            switch( _id )
            {
            case none : return( 0 );
            case PCF: return( 1 );
            default:
                break;
            }
            return( 0 );
        }
    };

public:
    explicit View( const QString& = QString() );
    virtual ~View();

public:
    View( const View& cpy )
        : RenderItem( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _program = cpy._program;
        _name = cpy._name;
        _mtx_global = cpy._mtx_global;
        _transform = cpy._transform;
        _visibility = cpy._visibility;
        _shadowEnable = cpy._shadowEnable;
        _shadowFilter = cpy._shadowFilter;
    }
    View& operator = ( const View& cpy )
    {
        if( this != &cpy )
        {
            RenderItem::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _program = cpy._program;
            _name = cpy._name;
            _mtx_global = cpy._mtx_global;
            _transform = cpy._transform;
            _visibility = cpy._visibility;
            _shadowEnable = cpy._shadowEnable;
            _shadowFilter = cpy._shadowFilter;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        RenderItem::bind_fields();
        bind_field( "name", &_name );
        bind_field( "program", &_program );
        bind_field( "transform", &_transform );
        bind_field( "visibility", &_visibility );
        bind_field( "shadowEnable", &_shadowEnable );
        bind_field( "shadowFilter", &_shadowFilter );
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
        return( new View() );
    }
    virtual XMLObject* clone() const
    {
        View* object = new View();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected: /// @section: program
    QString _program;

protected:
    const QString& program() const { return( _program ); }
    bool isSupported( const QString& namae ) const
    {
        if( !namae.isEmpty() )
            return( _program == namae );
        return( false );
    }

public:
    virtual void setProgram( const QString& namae )
    {
        _modify = _modify || (_program != namae);
        _program = namae;
        return;
    }

protected:
    void bind_program( QGLFunctions* ) const;
    void bind_program( QGLFunctions*, const QString& ) const;

protected: /// @section: name
    QString _name;

public:
    const QString& name() const { return( _name ); }
    void setName( const QString& namae )
    {
        QString origin = name();
        _name = namae;
        _modify = _modify || (origin != name());
        return;
    }

protected: /// @section: global matrix
    QMatrix4x4 _mtx_global;

public:
    const QMatrix4x4& global_matrix() const { return( _mtx_global ); }
    virtual void setGlobalMtx( const QMatrix4x4& mtx )
    {
        _mtx_global = mtx;
    }

protected: /// @section: trnasformation
    Transform  _transform;

    virtual void onTransformModify( bool ){ return; }

public:
    const Transform& transform() const { return( _transform ); }
    void transform_Modify( const Transform& t )
    {
        Transform origin = transform();
        _transform = t;
        bool transform_modify = (origin != transform());
        _modify = _modify || transform_modify;
        onTransformModify( transform_modify );
        return;
    }
    void transform_Modify( const Position& p )
    {
        Position origin = transform().position();
        _transform.setPosition( p );
        if( origin != transform().position() )
            onTransformModify( true );
        return;
    }
    void transform_Modify( const Rotate& r )
    {
        Rotate origin = transform().rotate();
        _transform.setRotate( r );
        if( origin != transform().rotate() )
            onTransformModify( true );
        return;
    }
    void transform_Modify( const Scale& s )
    {
        Scale origin = transform().scale();
        _transform.setScale( s );
        if( origin != transform().scale() )
            onTransformModify( true );
        return;
    }
    Vector3 getGlobalPos() const
    {
        QMatrix4x4 mtx_model = global_matrix() * transform().matrix();
        return( Vector3(mtx_model.column(3).toVector3D()) );
    }

protected: /// @section: model matrix
    virtual void bind_modelMtx( QGLFunctions* ) const;

protected: /// @section: visibility
    bool _visibility;

public:
    bool visibility() const { return( _visibility ); }
    void setVisibility( bool v )
    {
        _modify = _modify || (v != visibility());
        _visibility = v;
        return;
    }

private: /// @section: shadow
    bool _shadowEnable;

public:
    bool shadowEnable() const
    {
        return( _shadowEnable );
    }
    void setShadowEnable( bool shadow )
    {
        _modify = _modify || (shadow != this -> shadowEnable());
        _shadowEnable = shadow;
        return;
    }

private: /// @section: shadow Percentage Closer Filtering
    EnumAs< ShadowFilter > _shadowFilter;

protected:
    virtual void bind_shadowFiltering( QGLFunctions* ) const;

public:
    const EnumAs<ShadowFilter>& shadowFilter() const { return( _shadowFilter ); }
    void setShadowFilter( View::ShadowFilter::id id )
    {
        _modify = _modify || ( EnumAs<ShadowFilter>(ShadowFilter(id)).value() != shadowFilter().value() );
        _shadowFilter = EnumAs<ShadowFilter>(ShadowFilter(id));
        return;
    }

public: /// @section: bounding
    virtual Bounding bounding() const { return( Bounding() ); }

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
    virtual void drawShadow( QGLFunctions* ) const;
};

#endif // VIEW_H
