/**
 * Author: rfilippone@gmail.com
 */

#ifndef DEFAULTROUTER_H_
#define DEFAULTROUTER_H_

#include "boost/cgi/fcgi.hpp"

#include "IRouter.h"

class DefaultRouter: public IRouter
{
public:
    DefaultRouter(boost::fcgi::request& req);
    virtual ~DefaultRouter();

    virtual std::string getControllerName();
    virtual std::string getActionName();

private:
    std::string m_Url;
    std::string m_Controller;
    std::string m_Action;
};

#endif /* DEFAULTROUTER_H_ */
