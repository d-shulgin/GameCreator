#ifndef SCENE_H
#define SCENE_H

#include "../parser/xml_meta_data.h"
#include "drawable.h"
#include "resizeable.h"
#include "layer.h"

class Scene : public XMLObject, Drawable, Resizeable
{
public:
    static QString class_name() { return( QString("Scene") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify || isAnyElementModify() ); }

public:
    Scene();
    virtual ~Scene();

public:
    Scene( const Scene& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _layers = cpy._layers;
        _dbg_layer = cpy._dbg_layer;
    }
    Scene& operator = ( const Scene& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _layers = cpy._layers;
            _dbg_layer = cpy._dbg_layer;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "layers", &_layers );
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
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Scene() );
    }
    virtual XMLObject* clone() const
    {
        Scene* object = new Scene();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected:
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < layers().count() && !modify; ++i )
            modify = cref_layers().itemAt(i) -> isModify();
        return( modify );
    }

private: /// @section: layers
    XMLCollection _layers;

protected:
    XMLCollection& ref_layers() { return( _layers ); }
    const XMLCollection& cref_layers() const { return( _layers ); }

public:
    const XMLCollectionU& layers() const { return( _layers ); }
    Scene& addLayer( Layer* layer )
    {
        _layers << static_cast<XMLObject*>( layer );
        _modify = true;
        return( *this );
    }
    Layer* layer( size_t );
    const Layer* layer_const( size_t ) const;

public: /// @section: drawable
    virtual void prepareDraw();
    virtual void draw( QGLFunctions* ) const;
    virtual void drawShadow( QGLFunctions* ) const;

private: /// @section: resizeable
    int _width;
    int _height;

public:
    int width() const { return( _width ); }
    int height() const { return( _height ); }
    virtual void resize( int, int );

public: /// @section: initialize
    virtual void initialize( QGLFunctions* );

private: /// @section: debug
    XMLCollection _dbg_layer;

public:
    Scene& attachDbgLayer( Layer* layer )
    {
        detachDbgLayer();
        _dbg_layer << static_cast< XMLObject* >( layer );
        return( *this );
    }
    Scene& detachDbgLayer()
    {
        _dbg_layer.reset();
        return( *this );
    }
    Layer* dbg_layer();
    const Layer* dbg_layer_const() const;

public: /// @todo: tmp idea

    class Callback
    {
    public:
        Callback(){}

        virtual void event_A() = 0;
        virtual void event_B() = 0;
    };
    void attach_Handler( Callback* ){}

/*
 * class MyObject: public AnyObject, Scene::Callback
 * {
 * public:
 * ...
 *      virtual void event_A(){}
 *      virtual void event_B(){}
 * ...
 * };
*/
};

#endif // SCENE_H
