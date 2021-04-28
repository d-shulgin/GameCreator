#include "program_shader.h"

ProgramShader::ProgramShader( const QString& namae )
    : XMLObject()
    , _modify( false )
    , _name( namae )
    , _gl_program( 0 )
{
    bind_fields();
}
const Shader* ProgramShader::shader_const( size_t index ) const
{
    if( index < shaders().count() )
    {
        if( cref_shaders().itemAt(index) -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Shader::class_name()) )
            return( static_cast<const Shader*>(cref_shaders().itemAt(index)) );
    }
    return( 0 );
}
Shader*ProgramShader::shader( size_t index )
{
    if( index < shaders().count() )
    {
        if( ref_shaders()[index] -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Shader::class_name()) )
            return( static_cast<Shader*>(ref_shaders()[index]) );
    }
    return( 0 );
}
void ProgramShader::link( QGLFunctions* functions )
{
    if( is_linked() )
        return;
    if( 0 == functions )
        return;
    for( size_t i = 0; i < shaders().count(); ++i )
        if( !shader(i) -> compile(functions) )
            return;
    _gl_program = functions -> glCreateProgram();
    if( 0 != _gl_program )
    {
        for( size_t i = 0; i < shaders().count(); ++i )
            functions -> glAttachShader( _gl_program, shader_const(i) -> glId() );
        functions -> glLinkProgram( _gl_program );
        GLint status = 0;
        functions -> glGetProgramiv( _gl_program, GL_LINK_STATUS, &status );
        if( 0 == status )
            release( functions );
    }
    return;
}
void ProgramShader::release( QGLFunctions* functions )
{
    if( 0 != functions && is_linked() )
    {
        functions -> glDeleteProgram( _gl_program );
        _gl_program = 0;
    }
    return;
}
bool ProgramShader::is_linked() const
{
    return( 0 != _gl_program );
}
/// @section: uniform //////////////////////////////////////////////////// |
int ProgramShader::uniformLoc( QGLFunctions* functions                  // |
                               , const QString& namae ) const           // |
{
    if( is_linked() && !namae.isEmpty() && 0 != functions )
    {
        int result = functions -> glGetUniformLocation(_gl_program, namae.toStdString().c_str());
        return( result );
    }
    return( 0 );
}
void ProgramShader::setUniformValue( QGLFunctions* functions            // |
                                     , int loc                          // |
                                     , int value ) const                // |
{
    if( is_linked() && -1 != loc && 0 != functions )
        functions -> glUniform1i( loc, GLint(value) );
    return;
}
void ProgramShader::setUniformValue( QGLFunctions* functions            // |
                                     , int loc                          // |
                                     , unsigned int value ) const       // |
{
    if( is_linked() && -1 != loc && 0 != functions )
        functions -> glUniform1i( loc, GLint(value) );
    return;
}
void ProgramShader::setUniformValue( QGLFunctions* functions            // |
                                     , int loc                          // |
                                     , float value ) const              // |
{
    if( is_linked() && -1 != loc && 0 != functions )
        functions -> glUniform1f( loc, value );
    return;
}
void ProgramShader::setUniformValue( QGLFunctions* functions            // |
                                     , int loc                          // |
                                     , bool value ) const               // |
{
    if( is_linked() && -1 != loc && 0 != functions )
        functions -> glUniform1i( loc, (value ? 1 : 0) );
    return;
}
void ProgramShader::setUniformValue( QGLFunctions* functions            // |
                                     , int loc                          // |
                                     , const QVector4D& value ) const   // |
{
    if( is_linked() && -1 != loc && 0 != functions )
        functions -> glUniform4f( loc, value.x(), value.y(), value.z(), value.w() );
    return;
}
void ProgramShader::setUniformValue( QGLFunctions* functions            // |
                                     , int loc                          // |
                                     , const QVector3D& value ) const   // |
{
    if( is_linked() && -1 != loc && 0 != functions )
        functions -> glUniform3f( loc, value.x(), value.y(), value.z() );
    return;
}
void ProgramShader::setUniformValue( QGLFunctions* functions            // |
                                     , int loc                          // |
                                     , const QVector2D& value ) const   // |
{
    if( is_linked() && -1 != loc && 0 != functions )
        functions -> glUniform2f( loc, value.x(),value.y() );
    return;
}
void ProgramShader::setUniformValue( QGLFunctions* functions            // |
                                     , int loc                          // |
                                     , const QMatrix4x4& matrix ) const // |
{
    if( is_linked() && -1 != loc && 0 != functions )
        functions -> glUniformMatrix4fv( loc, 1, GL_FALSE
                                         , static_cast<const GLfloat*>(matrix.constData()) );
    return;
}
/// @section: attribute ////////////////////////////////////////// |
int ProgramShader::attributeLoc( QGLFunctions* functions        // |
                                 , const QString& namae ) const // |
{
    if( is_linked() && !namae.isEmpty() && 0 != functions )
    {
        int result = functions -> glGetAttribLocation(_gl_program, namae.toStdString().c_str());
        return( result );
    }
    return( 0 );
}
ProgramShader::~ProgramShader()
{
}


