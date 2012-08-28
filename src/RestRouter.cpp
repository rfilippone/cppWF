/**
 * Author: rfilippone@gmail.com
 */

#include "RestRouter.h"

RestRouter::RestRouter(boost::fcgi::request& req, RoutesConfiguration::iteartor route) :
    m_Url(req.env["REDIRECT_URL"]),
    m_Controller("index"),
    m_Action("index")
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

    boost::char_separator<char> sep(",");
    tokenizer tokens(route->second, sep);

    tokenizer::iterator iter = tokens.begin();
    if (iter != tokens.end())
    {
        iter++;
        if (iter!= tokens.end())
        {
            m_Controller = *iter;
        }
    }

    if (req.method() == "GET")
    {
        if (m_Url == route->first) // no specific resorce do a list
        {
            m_Action = "indexOp";
        }
        else
        {
            m_Action = "getOp";
        }

    }
    else if (req.method() == "POST")
    {
        m_Action = "postOp";
    }
    else if (req.method() == "PUT")
    {
        m_Action = "putOp";
    }
    else if (req.method() == "delete")
    {
        m_Action = "deleteOp";
    }
    else
    {
        m_Action = "index";
    }
}

RestRouter::~RestRouter()
{
}

std::string RestRouter::getControllerName()
{
    return m_Controller;
}

std::string RestRouter::getActionName()
{
    return m_Action;
}

