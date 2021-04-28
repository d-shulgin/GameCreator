#include "program_mgr.h"

ProgramMgr::ProgramMgr()
    : XMLObject()
    , _modify( false )
    , _handle( 0 )
    // //////////////////////////////////////////////////////////////// |
{
    bind_fields();
}
const ProgramShader* ProgramMgr::program_const( size_t index ) const // |
{
    if( index < programs().count() )
    {
        if( cref_programs().itemAt(index) -> xml_class_name().split(".", QString::SkipEmptyParts).contains(ProgramShader::class_name()) )
            return( static_cast<const ProgramShader*>(cref_programs().itemAt(index)) );
    }
    return( 0 );
}
ProgramShader* ProgramMgr::program( size_t index )                   // |
{
    if( index < programs().count() )
    {
        if( ref_programs()[index] -> xml_class_name().split(".", QString::SkipEmptyParts).contains(ProgramShader::class_name()) )
            return( static_cast<ProgramShader*>(ref_programs()[index]) );
    }
    return( 0 );
}
ProgramShader* ProgramMgr::getProgram()                              // |
{
    if( !activated_program().isEmpty() )
    {
        for( size_t i = 0; i < programs().count(); ++i )
        {
            if( program(i) -> name() == activated_program() )
                return( program(i) );
        }
    }
    return( 0 );
}
ProgramShader* ProgramMgr::getProgram( size_t index )                // |
{
    return( program(index) );
}
ProgramShader* ProgramMgr::getProgram( const QString& namae )        // |
{
    for( size_t i = 0; i < programs().count(); ++i )
    {
        if( program(i) -> name() == namae )
            return( program(i) );
    }
    return( 0 );
}
/// @section: compile /////////////////////////////////// |
void ProgramMgr::compileAll( QGLFunctions* functions ) // |
{
    for( size_t i = 0; i < programs().count(); ++i )
        program(i) -> link( functions );
    return;
}
/// @section: bind ////////////////////////////////////// |
void ProgramMgr::bind( QGLFunctions* functions         // |
                       , QString namae )               // |
{
    if( _activated_program == namae )
    {
        if( namae.isEmpty() && 0 != _handle )
            namae = _handle -> event_DefaultProgram();
        else
            return;
    }
    if( !_activated_program.isEmpty() && !namae.isEmpty() )
    {
        ProgramShader* program = getProgram();
        unbind( program, functions );
    }
    if( !namae.isEmpty() )
    {
        for( size_t i = 0; i < programs().count(); ++i )
        {
            if( this -> program(i) -> name() == namae )
            {
                _activated_program = namae;
                functions -> glUseProgram( this -> program(i) -> glID() );
                if( 0 != _handle )
                    _handle -> event_ProgramActivated( this -> program(i), functions );
                break;
            }
        }
    }
    return;
}
void ProgramMgr::unbind( ProgramShader* program        // |
                         , QGLFunctions* functions )   // |
{
    if( 0 != program && 0 != functions )
    {
        if( 0 != _handle )
            _handle -> event_ProgramDeactivated( program, functions );
        functions -> glUseProgram( 0 );
        _activated_program = QString();
    }
    return;
}
ProgramMgr::~ProgramMgr()
{
}

