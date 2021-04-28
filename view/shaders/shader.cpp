#include "shader.h"

Shader::Shader( Type::id id, const QString& path )
    : XMLObject()
    , _modify( false )
    , _path( path )
    , _type( EnumAs<Type>(Type(id)) )
    , _gl_shader( 0 )
{
    bind_fields();
}
void Shader::compileSrc( QGLFunctions* functions, const char* src )
{
    _gl_shader = functions -> glCreateShader( GLenum(type().value()) );
    if( 0 != _gl_shader )
    {
        functions -> glShaderSource ( _gl_shader, 1, &src, 0 );
        functions -> glCompileShader( _gl_shader );
        GLint status = 0;
        functions -> glGetShaderiv( _gl_shader, GL_COMPILE_STATUS, &status );
        if( 0 == status )
        {
            GLint maxLength = 0;
            functions -> glGetShaderiv( _gl_shader, GL_INFO_LOG_LENGTH, &maxLength);
            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            functions -> glGetShaderInfoLog( _gl_shader, maxLength, &maxLength, &errorLog[0]);
            for( size_t i = 0; i < static_cast<size_t>(maxLength) && i < errorLog.size(); ++i )
                std::cout << errorLog[i];
            std::cout << "<---- LOG END" << std::endl;

            std::cout << "program:" << std::endl;
            std::cout << src << "<----END" << std::endl;
            release( functions );
        }
    }
    return;
}
bool Shader::compile( QGLFunctions* functions )
{
    if( is_compiled() )
        return( true );
    if( 0 == functions )
        return( false );
    std::string sources;
    QFile file( path() );
    if( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        QTextStream stream( &file );
        sources = stream.readAll().toStdString();
        file.close();
    }
    if( !sources.empty() )
        compileSrc( functions, sources.c_str() );
    return( is_compiled() );
}
void Shader::release( QGLFunctions* functions )
{
    if( 0 != functions && is_compiled() )
    {
        functions -> glDeleteShader( _gl_shader );
        _gl_shader = 0;
    }
    return;
}
bool Shader::is_compiled() const
{
    return( 0 != _gl_shader );
}
Shader::~Shader()
{
}

