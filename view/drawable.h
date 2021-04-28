#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QGLFunctions>

class Drawable
{
public:
    Drawable(){}

    virtual void draw( QGLFunctions* functions ) const = 0;
    virtual void drawShadow( QGLFunctions* functions ) const = 0;
};

#endif // DRAWABLE_H
