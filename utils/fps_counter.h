#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <QTime>

class FPSCounter
{
public:
    explicit FPSCounter( size_t size = 10 );
    virtual ~FPSCounter();

    void update();

private:
    bool   _started;
    size_t _bufferSize;

private: /// @section: time
    int _elapsed;
    QTime _time;

protected:
    bool isStarted() const { return( _started ); }

private: /// @section: frames
    std::vector< float > _frames;
    unsigned int _counter;

protected:
    void store_frames( float );

public:
    const std::vector<float>& frames() const { return( _frames ); }
};

#endif // FPS_COUNTER_H
