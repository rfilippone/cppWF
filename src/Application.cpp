/**
 * Author: rfilippone@gmail.com
 */

#include <boost/make_shared.hpp>


#include "Application.h"

//TODO remove
#include <iostream>
#include "MyBootstrap.h"

Application::Application(std::string configuration) :
    m_configuration(configuration),
    m_bootstrap()
{
}

Application::~Application()
{
}

Application& Application::bootstrap()
{
    if (m_bootstrap == NULL)
    {
        m_bootstrap = boost::make_shared<MyBootstrap>();
        m_bootstrap->init();
    }

    return *this;
}


void Application::run()
{
    std::cout << "application run" << std::endl;
}

//boost::shared_ptr<IBootstrap> Application::bootstrap()
//{
//    if (m_bootstrap == NULL)
//    {
//        m_bootstrap = boost::make_shared<MyBootstrap>();
//        m_bootstrap->init();
//    }
//
//    return m_bootstrap;
//}

