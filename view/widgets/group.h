#ifndef GROUP_H
#define GROUP_H

#include "view.h"

class Group : public View
{
public:
    static QString class_name() { return( QString("Group") ); }
    virtual QString xml_class_name() const
    {
        if( View::xml_class_name().isEmpty() )
            return( class_name() );
        return( View::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( View::isModify() || _modify
                                            || isAnyElementModify() ); }

public:
    explicit Group( const QString& = QString() );
    virtual ~Group();

public:
    Group( const Group& cpy )
        : View( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _children = cpy._children;
    }
    Group& operator = ( const Group& cpy )
    {
        if( this != &cpy )
        {
            View::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _children = cpy._children;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        View::bind_fields();
        bind_field( "children", &_children );
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
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Group() );
    }
    virtual XMLObject* clone() const
    {
        Group* object = new Group();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < children().count() && !modify; ++i )
            modify = cref_children().itemAt(i) -> isModify();
        return( modify );
    }

private: /// @section: children
    XMLCollection _children;

protected:
    XMLCollection& ref_children() { return( _children ); }
    const XMLCollection& cref_children() const { return( _children ); }

public:
    const XMLCollectionU& children() const { return( _children ); }
    View* child( size_t );
    const View* child_const( size_t ) const;

public:
    Group& addChild( View* object )
    {
        _children << static_cast<XMLObject*>( object );
        _modify = true;
        return( *this );
    }
    View* getChild( const QString&, const QString& = QString() );

public: /// @section: global matrix
    virtual void setGlobalMtx( const QMatrix4x4& mtx )
    {
        View::setGlobalMtx( mtx );
        QMatrix4x4 mtx_model = global_matrix() * transform().matrix();
        for( size_t i = 0; i < children().count(); ++i )
        {
            child(i) -> setGlobalMtx( mtx_model );
        }
        return;
    }

protected: /// @section: trnasformation
    virtual void onTransformModify( bool is_modified )
    {
        if( is_modified )
        {
            QMatrix4x4 mtx_model = global_matrix() * transform().matrix();
            for( size_t i = 0; i < children().count(); ++i )
            {
                child(i) -> setGlobalMtx( mtx_model );
            }
        }
        return;
    }

public: /// @section: bounding
    virtual Bounding bounding() const;

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
    virtual void drawShadow( QGLFunctions* ) const;
};

#endif // GROUP_H
