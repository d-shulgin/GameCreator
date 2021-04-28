#include "angle.h"

Angle::Angle()
    : XMLObject()
    , _modify( false )
    , _radians( 0.0f )
{
    bind_fields();
}
Angle::Angle( float v, Angle::eType t )
    : XMLObject()
    , _modify( false )
    , _radians( t == radians_unit ? v : (t == degrees_unit ? v*M_PI/180.0f : v) )
{
    bind_fields();
}
Angle::~Angle()
{
}
