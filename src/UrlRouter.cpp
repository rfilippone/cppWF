/**
 * Author: rfilippone@gmail.com
 */

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "UrlRouter.h"
#include "IRouter.h"
#include "DefaultRouter.h"

UrlRouter::UrlRouter()
{
    // TODO Auto-generated constructor stub

}

UrlRouter::~UrlRouter()
{
    // TODO Auto-generated destructor stub
}

boost::shared_ptr<IRouter> UrlRouter::getRouter(boost::fcgi::request& req)
{
    return boost::shared_ptr<IRouter>(new DefaultRouter(req));
}
