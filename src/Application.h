/**
 * Author: rfilippone@gmail.com
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <string>

#include "boost/cgi/fcgi.hpp"

class IBootstrap;

class Application
{
public:
    Application(std::string configuration);

    virtual ~Application();

    //boost::shared_ptr<IBootstrap> bootstrap();
    Application& bootstrap();

    void run();

private:
    int handle_request(boost::fcgi::request& req);

private:
    std::string m_configuration;
    boost::shared_ptr<IBootstrap> m_bootstrap;
};

int entryPoint();


#endif /* APPLICATION_H_ */
