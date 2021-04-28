#ifndef LAYER3D_H
#define LAYER3D_H

#include "layer.h"

class Layer3D : public Layer
{
public:
    static QString class_name() { return( QString("3D") ); }
    virtual QString xml_class_name() const
    {
        if( Layer::xml_class_name().isEmpty() )
            return( class_name() );
        return( Layer::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( Layer::isModify()
                                            || _modify ); }

public:
    Layer3D();
    virtual ~Layer3D();

public:
    Layer3D( const Layer3D& cpy )
        : Layer( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
    }
    Layer3D& operator = ( const Layer3D& cpy )
    {
        if( this != &cpy )
        {
            Layer::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        Layer::bind_fields();
        return;
    }

protected:
    virtual void event_Saved()
    {
        Layer::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        Layer::event_Loaded( success );
        if( success )
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Layer3D() );
    }
    virtual XMLObject* clone() const
    {
        Layer3D* object = new Layer3D();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
    virtual void drawShadow( QGLFunctions* ) const;
};

#endif // LAYER3D_H
