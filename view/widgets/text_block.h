#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "view.h"

class TextBlock : public View
{
public:
    static QString class_name() { return( QString("TextBlock") ); }
    virtual QString xml_class_name() const
    {
        if( View::xml_class_name().isEmpty() )
            return( class_name() );
        return( View::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( View::isModify() || _modify ); }

public:
    explicit TextBlock( const QString& = QString()
            , const QString& = QString()
            , const QString& = QString() );
    virtual ~TextBlock();

public:
    TextBlock( const TextBlock& cpy )
        : View( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _font = cpy._font;
        _letter = cpy._letter;
        _material = cpy._material;
    }
    TextBlock& operator = ( const TextBlock& cpy )
    {
        if( this != &cpy )
        {
            View::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _font = cpy._font;
            _letter = cpy._letter;
            _material = cpy._material;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        View::bind_fields();
        bind_field( "font", &_font );
        bind_field( "letter", &_letter );
        bind_field( "material", &_material );
        return;
    }

protected:
    virtual void event_Saved()
    {
        View::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        View::event_Loaded( success );
        if( success )
        {
            _modify = false;
            changeLetterData();
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new TextBlock() );
    }
    virtual XMLObject* clone() const
    {
        TextBlock* object = new TextBlock();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: font...
    QString _font;

protected:
    void bind_data( QGLFunctions* ) const;
    void unbind_data( QGLFunctions* ) const;

public:
    const QString& font() const;
    void setFont(const QString& font);

private: /// @section: letter...
    class LetterData
    {
    public:
        explicit LetterData( const QVector2D& offset = QVector2D()
                             , const std::vector< unsigned int >& indices = std::vector< unsigned int >() )
            : _offset ( offset  )
            , _indices( indices )
            // //////////////// |
        {
        }
        ~LetterData(){}

    private: /// @section: offset...
        QVector2D _offset;

    public:
        const QVector2D& offset() const
        {
            return( _offset );
        }
        void setOffset( const QVector2D& offset )
        {
            _offset = offset;
        }
        void setOffset( float x, float y )
        {
            _offset = QVector2D( x, y );
        }

    private: /// @section: indices...
        std::vector< unsigned int > _indices;

    public:
        const std::vector< unsigned int >& indices() const
        {
            return( _indices );
        }
    };

    QString _letter;
    float _letterWidth;
    std::vector< LetterData > _letter_data;

public:
    const QString& letter() const;
    float letterWidth() const { return( _letterWidth ); }
    void setLetter( const QString& letter );

protected:
    void changeLetterData();
    void bind_character(QGLFunctions*, const Font*, size_t, const QVector2D& ) const;
    void unbind_character( QGLFunctions*, const Font* ) const;

private: /// @section: material...
    QString _material;

public:
    const QString& material() const;
    void setMaterial(const QString& material);

protected:
    void bind_material( QGLFunctions* ) const;
    void unbind_material( QGLFunctions* ) const;

public: /// @section: drawable
    virtual void draw( QGLFunctions* ) const;
    virtual void drawShadow( QGLFunctions* ) const;
    virtual void draw( QGLFunctions*, float ) const;
    virtual void drawShadow( QGLFunctions*, float ) const;
};

#endif // TEXT_BLOCK_H
