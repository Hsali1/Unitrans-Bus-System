//

#ifndef _ECS36B_EXCEPTION_
#define _ECS36B_EXCEPTION_

#include <exception>

class another
{
private:
  int x;
protected:
public:
};

class ecs36b_Exception : public another, std::exception
{
private:
    const char* errorMessage;

public:
    ecs36b_Exception(const char* error) : errorMessage(error) {}
    virtual ~ecs36b_Exception() throw() {}
    virtual const char* what() const throw() { return errorMessage; }
};

#endif /* _ECS36B_EXCEPTION_ */
