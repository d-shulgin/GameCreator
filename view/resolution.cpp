#include "resolution.h"

Resolution::Resolution( unsigned int width
                        , unsigned int height )
    : XMLObject()
    , _modify( false )
    , _width( width )
    , _height( height )
{
    bind_fields();
}
Resolution::~Resolution()
{
}
