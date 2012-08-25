/**
 * Author: rfilippone@gmail.com
 */

#include "DefaultRouter.h"

DefaultRouter::DefaultRouter(boost::fcgi::request& req) :
    m_Url(req.env["REDIRECT_URL"]),
    m_Controller("index"),
    m_Action("index")
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

    boost::char_separator<char> sep("/");
    tokenizer tokens(m_Url, sep);

    tokenizer::iterator iter = tokens.begin();
    if (iter != tokens.end())
    {
        m_Controller = *iter;
        iter++;
    }
    if (iter!= tokens.end())
    {
        m_Action = *iter;
    }
}

DefaultRouter::~DefaultRouter()
{
}

std::string DefaultRouter::getControllerName()
{
    return m_Controller;
}

std::string DefaultRouter::getActionName()
{
    return m_Action;
}

