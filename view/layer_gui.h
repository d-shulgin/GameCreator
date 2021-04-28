#ifndef LAYER_GUI_H
#define LAYER_GUI_H

#include "layer.h"

class LayerGUI : public Layer
{
public:
    static QString class_name() { return( QString("GUI") ); }
    virtual QString xml_class_name() const
    {
        if( Layer::xml_class_name().isEmpty() )
            return( class_name() );
        return( Layer::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( Layer::isModify()
                                            || _modify ); }

public:
    LayerGUI();
    virtual ~LayerGUI();

public:
    LayerGUI( const LayerGUI& cpy )
        : Layer( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
    }
    LayerGUI& operator = ( const LayerGUI& cpy )
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
        return( new LayerGUI() );
    }
    virtual XMLObject* clone() const
    {
        LayerGUI* object = new LayerGUI();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
};

#endif // LAYER_GUI_H
