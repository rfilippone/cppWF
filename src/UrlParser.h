/**
 * Author: rfilippone@gmail.com
 */

#ifndef URLPARSER_H_
#define URLPARSER_H_

#include "boost/cgi/fcgi/request.hpp"

#include "IUrlParser.h"

class UrlParser : public IUrlParser
{
public:
    UrlParser(boost::fcgi::request& req);
    virtual ~UrlParser();

    std::string getControllerName();
    std::string getActionName();

private:
    std::string m_Url;
    std::string m_Controller;
    std::string m_Action;
};

#endif /* URLPARSER_H_ */
