/**
 * Author: rfilippone@gmail.com
 */

#ifndef RESTROUTER_H_
#define RESTROUTER_H_

#include "boost/cgi/fcgi.hpp"

#include "IRouter.h"
#include "RoutesConfiguration.h"

class RestRouter: public IRouter
{
public:
    RestRouter(boost::fcgi::request& req, RoutesConfiguration::iteartor route);
    virtual ~RestRouter();

    virtual std::string getControllerName();
    virtual std::string getActionName();


private:
    std::string m_Url;
    std::string m_Controller;
    std::string m_Action;
};

#endif /* RESTROUTER_H_ */
