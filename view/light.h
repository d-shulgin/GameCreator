#ifndef LIGHT_H
#define LIGHT_H

#include "../parser/xml_meta_data.h"
#include "shaders/package.h"
#include "render_item.h"
#include "transform.h"
#include "angle.h"
#include "vector3.h"
#include "shadow.h"

class Light : public RenderItem
{
protected:
    enum { eDirection = 0
           , ePoint = 1
           , eSpot = 2 };

public:
    static QString class_name() { return( QString("Light") ); }
    virtual QString xml_class_name() const
    {
        if( RenderItem::xml_class_name().isEmpty() )
            return( class_name() );
        return( RenderItem::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( RenderItem::isModify() || _modify
                                            || isAnyElementModify() ); }

public:
    Light();
    virtual ~Light();

public:
    Light( const Light& cpy )
        : RenderItem( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _programs = cpy._programs;
        _power = cpy._power;
        _ambientColor = cpy._ambientColor;
        _diffuseColor = cpy._diffuseColor;
        _specularColor = cpy._specularColor;
        _active = cpy._active;
        _shadow = cpy._shadow;
    }
    Light& operator = ( const Light& cpy )
    {
        if( this != &cpy )
        {
            RenderItem::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _programs = cpy._programs;
            _power = cpy._power;
            _ambientColor = cpy._ambientColor;
            _diffuseColor = cpy._diffuseColor;
            _specularColor = cpy._specularColor;
            _active = cpy._active;
            _shadow = cpy._shadow;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        RenderItem::bind_fields();
        bind_field( "program", &_programs );
        bind_field( "active", &_active );
        bind_field( "power", &_power );
        bind_field( "ambientColor",  &_ambientColor );
        bind_field( "diffuseColor",  &_diffuseColor );
        bind_field( "specularColor", &_specularColor );
        bind_field( "shadow", &_shadow );
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
        return( new Light() );
    }
    virtual XMLObject* clone() const
    {
        Light* object = new Light();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < _shadow.count() && !modify; ++i )
            modify = _shadow.itemAt(i) -> isModify();
        return( modify );
    }

private: /// @section: program...
    std::vector< QString > _programs;

protected:
    bool isSupported( const QString& namae ) const
    {
        if( !namae.isEmpty() )
        {
            for( size_t i = 0; i < _programs.size(); ++i )
                if( _programs[i] == namae )
                    return( true );
        }
        return( false );
    }

public:
    void addProgram( const QString& namae )
    {
        if( !namae.isEmpty() )
        {
            _programs.push_back( namae );
            _modify = true;
        }
        return;
    }

private: /// @section: power of light
    float _power;

public:
    float power() const;
    void setPower( float power );

private: /// @section: ambient color
    Vector3 _ambientColor;

public:
    const Vector3& ambientColor() const;
    void setAmbientColor( const Vector3& ambientColor );

private: /// @section: diffuse color
    Vector3 _diffuseColor;

public:
    const Vector3& diffuseColor() const;
    void setDiffuseColor( const Vector3& diffuseColor );

private: /// @section: specular color
    Vector3 _specularColor;

public:
    const Vector3& specularColor() const;
    void setSpecularColor( const Vector3& specularColor );

private: /// @section: shadow texture

private: /// @section: control
    bool _active;

public:
    bool active() const;
    void setActive( bool active );

protected: /// @section: shadow
    XMLCollection _shadow;

public:
    void setShadow( Shadow* shadow )
    {
        size_t amount = _shadow.count();
        _shadow.reset();
        if( 0 != shadow )
        {
            _shadow << static_cast<XMLObject*>( shadow );
            _modify = true;
            return;
        }
        if( amount != _shadow.count() )
            _modify = true;
        return;
    }
    Shadow* shadow();
    const Shadow* shadow_const() const;

public:
    virtual void drawShadow( QGLFunctions*, const Shadow::Callback* ) const;

public: /// @section: initialize
    virtual void initialize( QGLFunctions* );

public: /// @section: bind
    virtual void bind( size_t, ProgramShader*, QGLFunctions* ) const;
};
class LightDirection : public Light
{
public:
    static QString class_name() { return( QString("Direction") ); }
    virtual QString xml_class_name() const
    {
        if( Light::xml_class_name().isEmpty() )
            return( class_name() );
        return( Light::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( Light::isModify()
                                            || _modify ); }
public:
    LightDirection();
    virtual ~LightDirection();

public:
    LightDirection( const LightDirection& cpy )
        : Light( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _direction = cpy._direction;
//        _shadowMainObject = cpy._shadowMainObject;
//        _shadowDistance = cpy._shadowDistance;
    }
    LightDirection& operator = ( const LightDirection& cpy )
    {
        if( this != &cpy )
        {
            Light::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _direction = cpy._direction;
//            _shadowMainObject = cpy._shadowMainObject;
//            _shadowDistance = cpy._shadowDistance;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        Light::bind_fields();
        bind_field( "direction", &_direction );
//        bind_field( "shadow_main_object", &_shadowMainObject );
//        bind_field( "shadow_distance", &_shadowDistance );
        return;
    }

protected:
    virtual void event_Saved()
    {
        Light::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        Light::event_Loaded( success );
        if( success )
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new LightDirection() );
    }
    virtual XMLObject* clone() const
    {
        LightDirection* object = new LightDirection();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: direction
    Vector3 _direction;

public:
    const Vector3& direction() const;
    void setDirection( const Vector3& direction );

public: /// @section: shadow
    void setShadow( ShadowDirection* shadow )
    {
        size_t amount = _shadow.count();
        _shadow.reset();
        if( 0 != shadow )
        {
            shadow -> setDirection( this -> direction() );
            _shadow << static_cast<XMLObject*>( shadow );
            _modify = true;
            return;
        }
        if( amount != _shadow.count() )
            _modify = true;
        return;
    }
    ShadowDirection* shadow();
    virtual void drawShadow( QGLFunctions*, const Shadow::Callback* ) const;
//    QString _shadowMainObject; // central shadow object
//    float _shadowDistance;
//    QMatrix4x4 mtx_projection;
//    QMatrix4x4 mtx_view;
//public:
//    float shadowDistance() const;
//    const QString& shadowMainObject() const;
//    void setShadow( const QString&, float = 1000.0f );
//    virtual void drawShadow( QGLFunctions*, const Light::Callback* ) const;
public:


public: /// @section: bind
    virtual void bind( size_t, ProgramShader*, QGLFunctions* ) const;
};
class LightPoint     : public Light
{
public:
    static QString class_name() { return( QString("Point") ); }
    virtual QString xml_class_name() const
    {
        if( Light::xml_class_name().isEmpty() )
            return( class_name() );
        return( Light::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( Light::isModify()
                                            || _modify ); }

public:
    LightPoint();
    virtual ~LightPoint();

public:
    LightPoint( const LightPoint& cpy )
        : Light( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _position = cpy._position;
    }
    LightPoint& operator = ( const LightPoint& cpy )
    {
        if( this != &cpy )
        {
            Light::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _position = cpy._position;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        Light::bind_fields();
        bind_field( "position", &_position );
        return;
    }

protected:
    virtual void event_Saved()
    {
        Light::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        Light::event_Loaded( success );
        if( success )
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new LightPoint() );
    }
    virtual XMLObject* clone() const
    {
        LightPoint* object = new LightPoint();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: position
    Vector3 _position;

public:
    const Vector3& position() const;
    void setPosition(const Vector3& position);

public: /// @section: bind
    virtual void bind( size_t, ProgramShader*, QGLFunctions* ) const;
};
class LightSpot      : public Light
{
public:
    static QString class_name() { return( QString("Spot") ); }
    virtual QString xml_class_name() const
    {
        if( Light::xml_class_name().isEmpty() )
            return( class_name() );
        return( Light::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( Light::isModify()
                                            || _modify ); }

public:
    LightSpot();
    virtual ~LightSpot();

public:
    LightSpot( const LightSpot& cpy )
        : Light( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _position = cpy._position;
        _direction = cpy._direction;
        _angle = cpy._angle;
        _borderArea = cpy._borderArea;
    }
    LightSpot& operator = ( const LightSpot& cpy )
    {
        if( this != &cpy )
        {
            Light::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _position = cpy._position;
            _direction = cpy._direction;
            _angle = cpy._angle;
            _borderArea = cpy._borderArea;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        Light::bind_fields();
        bind_field( "position", &_position );
        bind_field( "direction", &_direction );
        bind_field( "angle", &_angle );
        bind_field( "borderArea", &_borderArea );
        return;
    }

protected:
    virtual void event_Saved()
    {
        Light::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        Light::event_Loaded( success );
        if( success )
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new LightSpot() );
    }
    virtual XMLObject* clone() const
    {
        LightSpot* object = new LightSpot();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: position
    Vector3 _position;

public:
    const Vector3& position() const;
    void setPosition( const Vector3& position );

private: /// @section: direction
    Vector3 _direction;

public:
    const Vector3& direction() const;
    void setDirection( const Vector3& direction );

private: /// @section: angle (0..90)
    Angle _angle;

public:
    const Angle& angle() const;
    void setAngle(const Angle& angle);

private: /// @section: border area (0..1)
    float _borderArea;

public:
    float borderArea() const;
    void setBorderArea( float borderArea );

public: /// @section: bind
    virtual void bind( size_t, ProgramShader*, QGLFunctions* ) const;
};

#endif // LIGHT_H
