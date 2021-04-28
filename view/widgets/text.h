#ifndef TEXT_H
#define TEXT_H

#include "view.h"
#include "text_block.h"

class Text : public View
{
public:
    static QString class_name() { return( QString("Text") ); }
    virtual QString xml_class_name() const
    {
        if( View::xml_class_name().isEmpty() )
            return( class_name() );
        return( View::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( View::isModify() || _modify ); }

public:
    explicit Text( const QString& = QString() );
    virtual ~Text();

public:
    Text( const Text& cpy )
        : View( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
    }
    Text& operator = ( const Text& cpy )
    {
        if( this != &cpy )
        {
            View::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        View::bind_fields();
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
        return( new Text() );
    }
    virtual XMLObject* clone() const
    {
        Text* object = new Text();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: blocks...
    XMLCollection _blocks;

protected:
    XMLCollection& ref_blocks() { return( _blocks ); }
    const XMLCollection& cref_blocks() const { return( _blocks ); }

public:
    const XMLCollectionU& blocks() const { return( _blocks ); }
    TextBlock* block( size_t );
    const TextBlock* block_const( size_t ) const;
    void addBlock( TextBlock* );

public: /// @section: global matrix
    virtual void setGlobalMtx( const QMatrix4x4& mtx )
    {
        View::setGlobalMtx( mtx );
        QMatrix4x4 mtx_model = global_matrix() * transform().matrix();
        for( size_t i = 0; i < blocks().count(); ++i )
        {
            block(i) -> setGlobalMtx( mtx_model );
        }
        return;
    }

protected: /// @section: trnasformation
    virtual void onTransformModify( bool is_modified )
    {
        if( is_modified )
        {
            QMatrix4x4 mtx_model = global_matrix() * transform().matrix();
            for( size_t i = 0; i < blocks().count(); ++i )
            {
                block(i) -> setGlobalMtx( mtx_model );
            }
        }
        return;
    }

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
    virtual void drawShadow( QGLFunctions* ) const;
};

#endif // TEXT_H
