/**
 * Author: rfilippone@gmail.com
 */


#ifndef URLROUTER_H_
#define URLROUTER_H_

#include "boost/cgi/fcgi.hpp"

class IRouter;

class UrlRouter
{
public:
    UrlRouter();
    virtual ~UrlRouter();

    boost::shared_ptr<IRouter> getRouter(boost::fcgi::request& req);
};

#endif /* URLROUTER_H_ */
