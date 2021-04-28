#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <exception>

class IException : public std::exception
{
public:
    IException() throw()
    {
        _error_id = 0;
        _desc[0] = 0;
    }
    virtual ~IException() throw()
    {}

private:
    int  _error_id;
    char _desc[256];
    QString _description;

protected:
    void create_desc() throw()
    {
        _error_id = error_id();
        _description = description();
        _desc[0] = 0;
        ::snprintf( _desc, 256, "%s", description().toStdString().c_str() );
        return;
    }

public:
    virtual const char* what() const throw()
    {
        return( _desc );
    }
    virtual int error_id() const throw() { return( _error_id ); }
    virtual QString description() const throw() { return( _description ); }
};

#endif // EXCEPTION_H
