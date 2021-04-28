#ifndef RESIZEABLE_H
#define RESIZEABLE_H

class Resizeable
{
public:
    Resizeable(){}

    virtual void resize( int, int ) = 0;
};

#endif // RESIZEABLE_H
