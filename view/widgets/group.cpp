#include "group.h"

Group::Group( const QString& namae )
    : View( namae )
    , _modify( false )
    // ///////////// |
{
    bind_fields();
}
/// @section: children /////////////////////////////////// |
View* Group::child( size_t index )                      // |
{
    if( index < children().count() )
    {
        if( ref_children()[index] -> xml_class_name().split(".", QString::SkipEmptyParts).contains(View::class_name()) )
            return( static_cast<View*>(ref_children()[index]) );
    }
    return( 0 );
}
const View* Group::child_const( size_t index ) const    // |
{
    if( index < children().count() )
    {
        if( cref_children().itemAt(index) -> xml_class_name().split(".", QString::SkipEmptyParts).contains(View::class_name()) )
            return( static_cast<const View*>(cref_children().itemAt(index)) );
    }
    return( 0 );
}
View* Group::getChild( const QString& namae             // |
                       , const QString& result_parent ) // |
{
    QString result;
    View* found = 0;
    for( size_t i = 0; i < children().count(); ++i )
    {
        QString child_name = child_const(i) -> name();
        result = result_parent + (result_parent.isEmpty() || child_name.isEmpty() ? "" : ".") + child_name;
        if( result == namae )
            return( child(i) );
        else if( result.isEmpty() || namae.left(result.length()) == result )
        {
            Group* group = XMLObject::ptr_cast< Group >( ref_children()[i] );
            if( 0 != group )
                found = group -> getChild( namae, result );
        }
        if( 0 != found )
            return( found );
    }
    return( 0 );
}
/// @section: bounding //////////// |
Bounding Group::bounding() const // |
{
    Bounding result = View::bounding();
    for( size_t i = 0; i < children().count(); ++i )
    {
        result += child_const(i) -> bounding(); /// @todo: 20.05.2020 - необходимо учесть матрицу трансформации для объекта
    }
    return( result );
}
/// @section: drawable /////////////////////////////////// |
void Group::draw( QGLFunctions* functions ) const       // |
{
    if( !visibility() )
        return;
    QString store_program = programsMgr().activated_program();
    View::draw( functions );
    for( size_t i = 0; i < children().count(); ++i )
    {
        child_const(i) -> draw( functions );
    }
    bind_program( functions, store_program );
    return;
}
void Group::drawShadow( QGLFunctions* functions ) const // |
{
    if( !visibility() )
        return;
    View::drawShadow( functions );
    for( size_t i = 0; i < children().count(); ++i )
    {
        child_const(i) -> drawShadow( functions );
    }
    return;
}
Group::~Group()
{
}
