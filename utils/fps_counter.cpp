#include "fps_counter.h"

FPSCounter::FPSCounter( size_t size )
    : _started( false )
    , _bufferSize( size )
    , _elapsed( 0 )
    , _counter( 0 )
{
}
void FPSCounter::update()
{
    if( isStarted() )
    {
        _counter ++;
        _elapsed += _time.elapsed();
        if( _elapsed >= 1000 )
        {
            float time = static_cast<float>( _elapsed )/1000.0f;
            store_frames( static_cast<float>(_counter)/time );
            _counter = 0;
            _elapsed = 0;
        }
        _time.restart();
    }
    else
    {
        _counter = 0;
        _elapsed = 0;
        _started = true;
        _time.start();
        _frames.clear();
    }
    return;
}
void FPSCounter::store_frames( float current_frames )
{
    if( _frames.size() < _bufferSize )
        _frames.push_back( 0.0f );
    for( size_t i = _frames.size() - 1; i > 0; --i )
        _frames[i] = _frames[i - 1];
    _frames[0] = current_frames;
    return;
}
FPSCounter::~FPSCounter()
{
}
