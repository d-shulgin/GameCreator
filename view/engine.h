#ifndef ENGINE_H
#define ENGINE_H

#include "../parser/xml_meta_data.h"
#include "scene.h"
#include "layer.h"
#include "layer3d.h"
#include "layer_gui.h"
#include "resources/package.h"
#include "shaders/package.h"
#include "widgets/package.h"

class Engine
{
public:
    Engine();

    static void initialize()
    {
        // resources .......................
        registerObject< MeshLib         >();
        registerObject< Mesh            >();
        registerObject< MeshShape       >();
        registerObject< MaterialsMgr    >();
        registerObject< Material        >();
        registerObject< TexturesMgr     >();
        registerObject< Texture         >();
        registerObject< TextureCoord    >();
        registerObject< Picture         >();
        registerObject< FontLib         >();
        registerObject< Font            >();
        registerObject< FontData        >();
        registerObject< FontTextureSize >();
        registerObject< CharData        >();
        registerObject< CharTextureArea >();
        // shaders ...........................
        registerObject< ProgramMgr        >();
        registerObject< ProgramShader     >();
        registerObject< Shader            >();
        registerObject< ProgramAttr       >();
        registerObject< ProgramUniform    >();
        registerObject< ProgramLight      >();
        registerObject< ProgramMaterial   >();
        registerObject< ProgramShadowData >();
        // base .......................
        registerObject< Vector3    >();
        registerObject< Angle      >();
        registerObject< Color      >();
        registerObject< Resolution >();
        registerObject< Position   >();
        registerObject< Rotate     >();
        registerObject< Scale      >();
        registerObject< Transform  >();
        // scene ......................
        registerObject< Scene      >();
        registerObject< RenderItem >();
        // layer ....................
        registerObject< Layer    >();
        registerObject< LayerGUI >();
        registerObject< Layer3D  >();
        // camera ......................
        registerObject< Camera      >();
        registerObject< Ortho       >();
        registerObject< Perspective >();
        registerObject< Eye         >(); // perspective with look_at method
        // light ..........................
        registerObject< Light          >();
        registerObject< LightDirection >();
        registerObject< LightPoint     >();
        registerObject< LightSpot      >();
        // shadow ..........................
        registerObject< Shadow          >();
        registerObject< ShadowDirection >();
        // view ....................
        registerObject< View      >();
        registerObject< SkyBox    >();
        registerObject< Group     >();
        registerObject< Sprite    >();
        registerObject< SpriteDbg >();
        registerObject< Box       >();
        registerObject< Shape     >();
        registerObject< Model     >();
        registerObject< ModelV2   >();
        registerObject< Text      >();
        registerObject< TextBlock >();
        return;
    }

    template< class T >
    static void registerObject()
    {
        T* object = static_cast<T*>( XMLObject::factory().registerObject(new T()) );
        if( 0 != object )
            delete object;
        return;
    }
};

#endif // ENGINE_H
