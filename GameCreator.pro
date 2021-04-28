#-------------------------------------------------
#
# Project created by QtCreator 2020-05-05T11:28:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += opengl xml

TARGET = GameCreator
TEMPLATE = app


SOURCES += main.cpp\
        main_window.cpp \
    render.cpp \
    editors/scene_view.cpp \
    parser/xml_array.cpp \
    parser/xml_enum.cpp \
    parser/xml_field.cpp \
    parser/xml_object.cpp \
    parser/xml_word.cpp \
    view/camera.cpp \
    view/transform.cpp \
    parser/xml_collection.cpp \
    view/vector3.cpp \
    view/angle.cpp \
    view/layer.cpp \
    view/engine.cpp \
    view/resolution.cpp \
    view/widgets/view.cpp \
    view/widgets/group.cpp \
    view/layer_gui.cpp \
    view/widgets/sprite.cpp \
    view/widgets/vertices.cpp \
    view/scene.cpp \
    view/bounding.cpp \
    view/color.cpp \
    view/layer3d.cpp \
    view/widgets/box.cpp \
    view/light.cpp \
    view/widgets/skybox.cpp \
    view/resources/texture.cpp \
    view/resources/picture.cpp \
    view/resources/textures_mgr.cpp \
    view/shaders/program_mgr.cpp \
    view/shaders/program_shader.cpp \
    view/shaders/shader.cpp \
    view/widgets/shape.cpp \
    view/resources/material.cpp \
    view/resources/materials_mgr.cpp \
    view/widgets/model.cpp \
    view/render_item.cpp \
    view/shaders/program_attr.cpp \
    view/shaders/program_uniform.cpp \
    view/shaders/program_light.cpp \
    view/shaders/program_material.cpp \
    view/shadow.cpp \
    view/resources/mesh_lib.cpp \
    view/resources/mesh.cpp \
    view/shaders/program_shadow.cpp \
    view/shaders/texture_units.cpp \
    view/resources/font_lib.cpp \
    view/resources/font.cpp \
    view/resources/srcFont/char_data.cpp \
    view/resources/srcFont/font_data.cpp \
    view/resources/srcFont/font_texture_size.cpp \
    view/widgets/text.cpp \
    view/widgets/text_block.cpp \
    utils/fps_counter.cpp

HEADERS  += main_window.h \
    render.h \
    editors/scene_view.h \
    parser/xml_array.h \
    parser/xml_enum.h \
    parser/xml_field.h \
    parser/xml_meta_data.h \
    parser/xml_object.h \
    parser/xml_word.h \
    utils/exception.h \
    view/camera.h \
    view/transform.h \
    parser/xml_collection.h \
    view/vector3.h \
    view/angle.h \
    view/layer.h \
    view/drawable.h \
    view/engine.h \
    view/resolution.h \
    view/resizeable.h \
    view/widgets/view.h \
    view/widgets/package.h \
    view/widgets/group.h \
    view/layer_gui.h \
    view/widgets/sprite.h \
    view/widgets/vertices.h \
    view/scene.h \
    view/bounding.h \
    view/color.h \
    view/layer3d.h \
    view/widgets/box.h \
    view/light.h \
    view/widgets/skybox.h \
    view/resources/texture.h \
    view/resources/package.h \
    view/resources/picture.h \
    view/resources/textures_mgr.h \
    view/shaders/program_mgr.h \
    view/shaders/program_shader.h \
    view/shaders/shader.h \
    view/shaders/package.h \
    view/widgets/shape.h \
    view/resources/material.h \
    view/resources/materials_mgr.h \
    view/widgets/model.h \
    view/render_item.h \
    view/shaders/program_attr.h \
    view/shaders/program_uniform.h \
    view/shaders/program_light.h \
    view/shaders/program_material.h \
    view/shadow.h \
    view/resources/mesh_lib.h \
    view/resources/mesh.h \
    view/shaders/program_shadow.h \
    view/shaders/texture_units.h \
    view/resources/font_lib.h \
    view/resources/font.h \
    view/resources/srcFont/char_data.h \
    view/resources/srcFont/font_data.h \
    view/resources/srcFont/font_texture_size.h \
    view/widgets/text.h \
    view/widgets/text_block.h \
    utils/fps_counter.h

FORMS    += main_window.ui \
    editors/scene_view.ui

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    models.qrc

OTHER_FILES +=
