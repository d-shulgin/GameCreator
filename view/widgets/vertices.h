#ifndef VERTICES_H
#define VERTICES_H

#include <vector>
#include <QVector2D>
#include <QVector3D>
#include "../color.h"
#include "../vector3.h"

class Vertices
{
public:
    Vertices()
        : _count( 0 )
    {}

    class VertexData
    {
    public:
        VertexData()
        {
            _data.x = _data.y = _data.z = 0.0f;
            _data.tx = _data.ty = 0.0f;
            _data.nx = _data.ny = 0.0f; _data.nz = 1.0f;
            _data.r = _data.g = _data.b = 0.0f; _data.a = 1.0f;
            _data.tan_x = _data.tan_y = _data.tan_z = 0.0f;
            _data.btan_x = _data.btan_y = _data.btan_z = 0.0f;
        }
        explicit VertexData( float x, float y
                             , float tx, float ty
                             , float r, float g, float b, float a )
        {
            _data.x = _data.y = _data.z = 0.0f;
            _data.tx = _data.ty = 0.0f;
            _data.nx = _data.ny = 0.0f; _data.nz = 1.0f;
            _data.r = _data.g = _data.b = 0.0f; _data.a = 1.0f;

            _data.x = x; _data.y = y;
            _data.tx = tx; _data.ty = ty;
            _data.r = r; _data.g = g; _data.b = b; _data.a = a;
            _data.tan_x = _data.tan_y = _data.tan_z = 0.0f;
            _data.btan_x = _data.btan_y = _data.btan_z = 0.0f;
        }
        explicit VertexData( float x, float y, float z
                             , float tx, float ty
                             , float nx, float ny, float nz
                             , float r, float g, float b, float a )
        {
            _data.x = x; _data.y = y; _data.z = z;
            _data.tx = tx; _data.ty = ty;
            _data.nx = nx; _data.ny = ny; _data.nz = nz;
            _data.r = r; _data.g = g; _data.b = b; _data.a = a;
            _data.tan_x = _data.tan_y = _data.tan_z = 0.0f;
            _data.btan_x = _data.btan_y = _data.btan_z = 0.0f;
        }
        explicit VertexData( float x, float y, float z
                             , float tx, float ty
                             , float nx, float ny, float nz
                             , float tnx, float tny, float tnz
                             , float btx, float bty, float btz
                             , float r, float g, float b, float a )
        {
            _data.x = x; _data.y = y; _data.z = z;
            _data.tx = tx; _data.ty = ty;
            _data.nx = nx; _data.ny = ny; _data.nz = nz;
            _data.r = r; _data.g = g; _data.b = b; _data.a = a;
            _data.tan_x = tnx; _data.tan_y = tny; _data.tan_z = tnz;
            _data.btan_x = btx; _data.btan_y = bty; _data.btan_z = btz;
        }
        explicit VertexData( const QVector3D& p
                             , const QVector2D& t
                             , const QVector3D& n
                             , const QVector4D& c )
        {
            _data.x = p.x(); _data.y = p.y(); _data.z = p.z();
            _data.tx = t.x(); _data.ty = t.y();
            _data.nx = n.x(); _data.ny = n.y(); _data.nz = n.z();
            _data.r = c.x(); _data.g = c.y(); _data.b = c.z(); _data.a = c.w();
            _data.tan_x = _data.tan_y = _data.tan_z = 0.0f;
            _data.btan_x = _data.btan_y = _data.btan_z = 0.0f;
        }

        union
        {
            float _buffer[18];
            struct
            {
                float x, y, z;
                float tx, ty;
                float nx, ny, nz;
                float r, g, b, a;
                float tan_x, tan_y, tan_z;
                float btan_x, btan_y, btan_z;
            };
        } _data;
        static int stride() { return( sizeof(float)*size() ); }
        static int sizePosition() { return(3); }
        static int sizeUVCoords() { return(2); }
        static int sizeNormal() { return(3); }
        static int sizeColor() { return(4); }
        static int sizeTangent() { return(3); }
        static int sizeBiTangent() { return(3); }
        static int size(){ return( sizePosition()
                                   + sizeUVCoords()
                                   + sizeNormal()
                                   + sizeColor()
                                   + sizeTangent()
                                   + sizeBiTangent() ); }
        static int offsetPosition() { return( 0 ); }
        static int offsetUVCoords() { return( offsetPosition() + sizePosition() ); }
        static int offsetNormal() { return( offsetUVCoords() + sizeUVCoords() ); }
        static int offsetColor() { return( offsetNormal() + sizeNormal() ); }
        static int offsetTangent() { return( offsetColor() + sizeColor() ); }
        static int offsetBiTangent() { return( offsetTangent() + sizeTangent() ); }
    };

private: /// @section: buffer
    int _count;
    std::vector< float > _buffer;

public:
    int count() const { return( _count ); }
    const std::vector< float >& buffer() const { return( _buffer ); }
    Vertices& reset()
    {
        _buffer.clear();
        _count = 0;
        return(*this);
    }
    Vertices& operator << ( const VertexData& v )
    {
        _buffer.insert( _buffer.end(), v._data._buffer, v._data._buffer + VertexData::size() );
        _count ++;
        return( *this );
    }
    Vertices& changeColor( const Color& color )
    {
        enum { eRed, eGreen, eBlue, eAlpha };
        for( int i = 0; i < count(); ++i )
        {
            _buffer[i*VertexData::size() + VertexData::offsetColor() + eRed  ] = color.red();
            _buffer[i*VertexData::size() + VertexData::offsetColor() + eGreen] = color.green();
            _buffer[i*VertexData::size() + VertexData::offsetColor() + eBlue ] = color.blue();
            _buffer[i*VertexData::size() + VertexData::offsetColor() + eAlpha] = color.alpha();
        }
        return( *this );
    }
    Vector3 position( int index ) const
    {
        int i = index*VertexData::size() + VertexData::offsetPosition();
        if( static_cast<size_t>(i + 2) < _buffer.size() )
        {
            float x = _buffer[i + 0];
            float y = _buffer[i + 1];
            float z = _buffer[i + 2];
            return( Vector3(x, y, z) );
        }
        return( Vector3() );
    }
    QVector2D UVcoords( int index ) const
    {
        int i = index*VertexData::size() + VertexData::offsetUVCoords();
        if( static_cast<size_t>(i + 2) < _buffer.size() )
        {
            float x = _buffer[i + 0];
            float y = _buffer[i + 1];
            return( QVector2D(x, y) );
        }
        return( QVector2D() );
    }
    Vector3 normal( int index ) const
    {
        int i = index*VertexData::size() + VertexData::offsetNormal();
        if( static_cast<size_t>(i + 2) < _buffer.size() )
        {
            float x = _buffer[i + 0];
            float y = _buffer[i + 1];
            float z = _buffer[i + 2];
            return( Vector3(x, y, z) );
        }
        return( Vector3() );
    }
    Vertices& setTangent( int index, const Vector3& tangent )
    {
        int i = index*VertexData::size() + VertexData::offsetTangent();
        if( static_cast<size_t>(i + 2) < _buffer.size() )
        {
            _buffer[i + 0] = tangent.x();
            _buffer[i + 1] = tangent.y();
            _buffer[i + 2] = tangent.z();
        }
        return( *this );
    }
    Vector3 tangent( int index ) const
    {
        int i = index*VertexData::size() + VertexData::offsetTangent();
        if( static_cast<size_t>(i + 2) < _buffer.size() )
        {
            float x = _buffer[i + 0];
            float y = _buffer[i + 1];
            float z = _buffer[i + 2];
            return( Vector3(x, y, z) );
        }
        return( Vector3() );
    }
    Vertices& setBiTangent( int index, const Vector3& bitangent )
    {
        int i = index*VertexData::size() + VertexData::offsetBiTangent();
        if( static_cast<size_t>(i + 2) < _buffer.size() )
        {
            _buffer[i + 0] = bitangent.x();
            _buffer[i + 1] = bitangent.y();
            _buffer[i + 2] = bitangent.z();
        }
        return( *this );
    }
    Vector3 bitangent( int index ) const
    {
        int i = index*VertexData::size() + VertexData::offsetBiTangent();
        if( static_cast<size_t>(i + 2) < _buffer.size() )
        {
            float x = _buffer[i + 0];
            float y = _buffer[i + 1];
            float z = _buffer[i + 2];
            return( Vector3(x, y, z) );
        }
        return( Vector3() );
    }
};

typedef Vertices::VertexData Vertex;

#endif // VERTICES_H
