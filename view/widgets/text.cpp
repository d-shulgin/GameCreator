#include "text.h"

Text::Text( const QString& namae )
    : View( namae )
    , _modify( false )
{
    bind_fields();
}
/// @section: blocks... /////////////////////////////////// |
TextBlock* Text::block( size_t index )                   // |
{
    if( index < blocks().count() )
    {
        if( ref_blocks()[index] -> xml_class_name()
                .split(".", QString::SkipEmptyParts)
                .contains(TextBlock::class_name()) )
            return( static_cast<TextBlock*>(ref_blocks()[index]) );
    }
    return( 0 );
}
const TextBlock* Text::block_const( size_t index ) const // |
{
    if( index < blocks().count() )
    {
        if( cref_blocks().itemAt(index) -> xml_class_name()
                .split(".", QString::SkipEmptyParts)
                .contains(TextBlock::class_name()) )
            return( static_cast<const TextBlock*>(cref_blocks().itemAt(index)) );
    }
    return( 0 );
}
void Text::addBlock( TextBlock* block )                  // |
{
    _blocks << static_cast< XMLObject* >( block );
    _modify = true;
}
/// @section: drawable ////////////////////////////////// |
void Text::draw( QGLFunctions* functions ) const       // |
{
    if( !visibility() )
        return;
    QString store_program = programsMgr().activated_program();
    View::draw( functions );
    float offsetX = 0.0f;
    for( size_t i = 0; i < blocks().count(); ++i )
    {
        block_const(i) -> draw( functions, offsetX );
        offsetX += block_const(i) -> letterWidth();
    }
    bind_program( functions, store_program );
    return;
}
void Text::drawShadow( QGLFunctions* functions ) const // |
{
}
Text::~Text()
{
}
