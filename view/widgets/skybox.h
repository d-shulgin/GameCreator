#ifndef SKYBOX_H
#define SKYBOX_H

#include "view.h"
#include "vertices.h"

class SkyBox : public View
{
public:
    static QString class_name() { return( QString("SkyBox") ); }
    virtual QString xml_class_name() const
    {
        if( View::xml_class_name().isEmpty() )
            return( class_name() );
        return( View::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( View::isModify() || _modify ); }

public:
    explicit SkyBox( const QString& = QString() );
    explicit SkyBox( const QString&, const QString& = QString() );
    virtual ~SkyBox();

public:
    SkyBox( const SkyBox& cpy )
        : View( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _vertices = cpy._vertices;
        _indices = cpy._indices;
        _picture_name = cpy._picture_name;
    }
    SkyBox& operator = ( const SkyBox& cpy )
    {
        if( this != &cpy )
        {
            View::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _vertices = cpy._vertices;
            _indices = cpy._indices;
            _picture_name = cpy._picture_name;
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
            createBox();
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new SkyBox() );
    }
    virtual XMLObject* clone() const
    {
        SkyBox* object = new SkyBox();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: vertices & indices
    Vertices _vertices;
    std::vector< unsigned int > _indices;

    void createBox();
    void bind_data( QGLFunctions* ) const;

public:
    const Vertices& vertices() const { return( _vertices ); }
    const std::vector< unsigned int >& indices() const { return( _indices ); }

protected: /// @section: picture
    QString _picture_name;

    void bind_picture( QGLFunctions*, const QString&, int = 0 ) const;

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
};

#endif // SKYBOX_H
