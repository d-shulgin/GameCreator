#include "render_item.h"

ProgramMgr RenderItem::_programsMgr = ProgramMgr();
TexturesMgr RenderItem::_texturesMgr = TexturesMgr();
MaterialsMgr RenderItem::_materialsMgr = MaterialsMgr();
MeshLib RenderItem::_meshLib = MeshLib();
FontLib RenderItem::_fontLib = FontLib();

RenderItem::RenderItem()
    : XMLObject()
{
    bind_fields();
}
RenderItem::~RenderItem()
{
}

