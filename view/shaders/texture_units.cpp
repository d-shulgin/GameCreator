#include "texture_units.h"

TextureUnits::TextureUnits()
    // //////////////////////////////////////////////// |
{
    _units.reserve( 32 );
    _units.push_back( GL_TEXTURE0 );
    _units.push_back( GL_TEXTURE1 );
    _units.push_back( GL_TEXTURE2 );
    _units.push_back( GL_TEXTURE3 );
    _units.push_back( GL_TEXTURE4 );
    _units.push_back( GL_TEXTURE5 );
    _units.push_back( GL_TEXTURE6 );
    _units.push_back( GL_TEXTURE7 );
    _units.push_back( GL_TEXTURE8 );
    _units.push_back( GL_TEXTURE9 );
    _units.push_back( GL_TEXTURE10 );
    _units.push_back( GL_TEXTURE11 );
    _units.push_back( GL_TEXTURE12 );
    _units.push_back( GL_TEXTURE13 );
    _units.push_back( GL_TEXTURE14 );
    _units.push_back( GL_TEXTURE15 );
    _units.push_back( GL_TEXTURE16 );
    _units.push_back( GL_TEXTURE17 );
    _units.push_back( GL_TEXTURE18 );
    _units.push_back( GL_TEXTURE19 );
    _units.push_back( GL_TEXTURE20 );
    _units.push_back( GL_TEXTURE21 );
    _units.push_back( GL_TEXTURE22 );
    _units.push_back( GL_TEXTURE23 );
    _units.push_back( GL_TEXTURE24 );
    _units.push_back( GL_TEXTURE25 );
    _units.push_back( GL_TEXTURE26 );
    _units.push_back( GL_TEXTURE27 );
    _units.push_back( GL_TEXTURE28 );
    _units.push_back( GL_TEXTURE29 );
    _units.push_back( GL_TEXTURE30 );
    _units.push_back( GL_TEXTURE31 );
}
GLenum TextureUnits::get( const QString& key ) const // |
{
    std::map<QString, GLenum>::const_iterator it = _locked.find( key );
    if( it == _locked.end() )
        throw( Exception(Error::incorrect_lock_key, "get") );
    return( it -> second );
}
GLenum TextureUnits::lock( const QString& key )      // |
{
    std::map<QString, GLenum>::iterator it = _locked.find( key );
    if( it != _locked.end() )
        return( it -> second );
    if( values().empty() )
        throw( Exception(Error::no_available_unit, "lock") );
    _locked[key] = _units.front();
    _units.erase( _units.begin() );
    return( _locked[key] );
}
void TextureUnits::unlock( const QString& key )      // |
{
    GLenum unit = 0;
    std::map<QString, GLenum>::iterator it = _locked.find( key );
    if( it != _locked.end() )
    {
        unit = it -> second;
        _locked.erase(it);
    }
    if( check(unit) )
    {
        _units.push_back( unit );
        std::sort(_units.begin(), _units.end());
    }
    else
        throw( Exception(Error::incorrect_unit, "unlock") );
    return;
}
TextureUnits::~TextureUnits()
{
}



