/*
* Author: rfilippone@gmail.com
*/

#ifndef IROUTER_H_
#define IROUTER_H_

#include <string>

class IRouter
{
public:
    virtual ~IRouter() {}

    virtual std::string getControllerName() = 0;
    virtual std::string getActionName() = 0;
};

#endif /* IROUTER_H_ */
