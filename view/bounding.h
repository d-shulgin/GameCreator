#ifndef BOUNDING_H
#define BOUNDING_H

class Bounding
{
public:
    explicit Bounding( float = 0.0f, float = 0.0f, float = 0.0f );
    virtual ~Bounding();

public:
    Bounding( const Bounding& cpy )
    {
        _width  = cpy._width;
        _height = cpy._height;
        _length = cpy._length;
        _xMin = cpy._xMin;
        _xMax = cpy._xMax;
        _yMin = cpy._yMin;
        _yMax = cpy._yMax;
        _zMin = cpy._zMin;
        _zMax = cpy._zMax;
    }
    Bounding& operator = ( const Bounding& cpy )
    {
        if( this != &cpy )
        {
            _width  = cpy._width;
            _height = cpy._height;
            _length = cpy._length;
            _xMin = cpy._xMin;
            _xMax = cpy._xMax;
            _yMin = cpy._yMin;
            _yMax = cpy._yMax;
            _zMin = cpy._zMin;
            _zMax = cpy._zMax;
        }
        return( *this );
    }

private:
    float _width; // убрать
    float _height; // убрать
    float _length; // убрать

    float _xMin, _xMax;
    float _yMin, _yMax;
    float _zMin, _zMax;

public:
    float width() const { return( _xMax - _xMin ); }
    float height() const { return( _yMax - _yMin ); }
    float length() const { return( _zMax - _zMin ); }

public: /// @section: operators
    Bounding& operator += ( const Bounding& /*v*/ )
    {
        return( *this );
    }
};

#endif // BOUNDING_H
