#include "iprogram.h"

IProgram::IProgram( const QString& name )
    : XMLObject()
    , _modify( false )
    , _name( name )
{
    bind_fields();
}
IProgram::~IProgram()
{
}
