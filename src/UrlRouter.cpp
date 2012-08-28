/**
 * Author: rfilippone@gmail.com
 */

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "UrlRouter.h"
#include "IRouter.h"
#include "DefaultRouter.h"
#include "RestRouter.h"
#include "RoutesConfiguration.h"

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
    for (RoutesConfiguration::iteartor route = RoutesConfiguration::begin();
         route != RoutesConfiguration::end();
         ++route)
    {
       if (req.uri().find(route->first) == 0)
       {
           std::cerr << "Route configured: " << route->first << " -> " << route->second << std::endl;

           typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

           boost::char_separator<char> sep(",");
           tokenizer tokens(route->second, sep);

           tokenizer::iterator iter = tokens.begin();

           if (iter != tokens.end())
           {
               std::string sRouter = *iter;
               if (sRouter == "rest")
               {
                   std::cerr << "Using a rest router." << std::endl;
                   return boost::shared_ptr<IRouter>(new RestRouter(req, route));
               }
               else
               {
                   return boost::shared_ptr<IRouter>(new DefaultRouter(req));
               }
           }
           else
           {
               return boost::shared_ptr<IRouter>(new DefaultRouter(req));
           }
       }
    }

    return boost::shared_ptr<IRouter>(new DefaultRouter(req));
}
