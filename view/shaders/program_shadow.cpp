#include "program_shadow.h"

ProgramShadowData::ProgramShadowData()
    : XMLObject()
    , _modify( false )
    , _enable       ( "u_shadow.enable" )
    , _projectionMtx( "u_shadow.projectionMtx" )
    , _viewMtx      ( "u_shadow.viewMtx" )
{
    bind_fields();
}
/// @section: uniform... enable ///////////////////////////// |
const QString& ProgramShadowData::enable() const           // |
{
    return( _enable );
}
void ProgramShadowData::setEnable( const QString& enable ) // |
{
    _modify = _modify || (enable != this -> enable());
    _enable = enable;
    return;
}
/// @section: uniform... projectionMtx //////////////////////////////////// |
const QString& ProgramShadowData::projectionMtx() const                  // |
{
    return( _projectionMtx );
}
void ProgramShadowData::setProjectionMtx( const QString& projectionMtx ) // |
{
    _modify = _modify || (projectionMtx != this -> projectionMtx());
    _projectionMtx = projectionMtx;
    return;
}
/// @section: uniform... viewMtx ////////////////////////////// |
const QString& ProgramShadowData::viewMtx() const            // |
{
    return( _viewMtx );
}
void ProgramShadowData::setViewMtx( const QString& viewMtx ) // |
{
    _modify = _modify || (viewMtx != this -> viewMtx());
    _viewMtx = viewMtx;
    return;
}
/// @section: initialize ////////////////////////////////////////////////////// |
QString ProgramShadowData::locName( size_t index                             // |
                                    , const QString& namae ) const           // |
{
    if( !namae.isEmpty() )
    {
        QStringList items = namae.split( ".", QString::SkipEmptyParts );
        if( items.count() == 2 )
        {
            return( QString("%1[%2].%3").arg(items[0]).arg(index).arg(items[1]) );
        }
    }
    return( QString() );
}
void ProgramShadowData::initEnable( size_t index                             // |
                                    , QGLFunctions* functions                // |
                                    , ProgramShader* program                 // |
                                    , bool value ) const                     // |
{
    QString locName = this -> locName( index, enable() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value );
    }
    return;
}
void ProgramShadowData::initProjectionMtx( size_t index                      // |
                                           , QGLFunctions* functions         // |
                                           , ProgramShader* program          // |
                                           , const QMatrix4x4& value ) const // |
{
    QString locName = this -> locName( index, projectionMtx() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value );
    }
    return;
}
void ProgramShadowData::initViewMtx( size_t index                            // |
                                     , QGLFunctions* functions               // |
                                     , ProgramShader* program                // |
                                     , const QMatrix4x4& value ) const       // |
{
    QString locName = this -> locName( index, viewMtx() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value );
    }
    return;
}
ProgramShadowData::~ProgramShadowData()
{
}

