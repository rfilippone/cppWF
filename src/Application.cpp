/**
 * Author: rfilippone@gmail.com
 */

#include <boost/make_shared.hpp>


#include "Application.h"
#include "Configuration.h"
#include "UrlRouter.h"
#include "IRouter.h"
#include "BaseController.h"

//TODO remove
#include <iostream>
#include "MyBootstrap.h"


int main()
{
    return entryPoint();
}


Application::Application(std::string configuration) :
    m_configuration(configuration),
    m_bootstrap()
{
    Configuration::setFile(m_configuration);
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
    std::cerr << "application run" << std::endl;

    //Make a `service` (more about this in other examples).
    boost::fcgi::service s;

    // Make an `acceptor` for accepting requests through.
    boost::fcgi::acceptor a(s);

    int status(0);
    do
    {
        status = a.accept(boost::bind(&Application::handle_request, this, _1));
    } while (!status);
}

int Application::handle_request(boost::fcgi::request& req)
{
    // Construct a `response` object (makes writing/sending responses easier).
    boost::fcgi::response resp;

    try
    {
        // Load in the request data so we can access it easily.
        req.load(boost::fcgi::parse_all);

        boost::shared_ptr<UrlRouter> pUrlRouter(new UrlRouter());
        boost::shared_ptr<IRouter> pRouter = pUrlRouter->getRouter(req);

        std::string sController = pRouter->getControllerName();
        std::string sAction = pRouter->getActionName();

        ActionInvoker::invoke(sController, sAction, req, resp);
    }
    catch (controller_not_found& e) {
        std::cerr << boost::diagnostic_information(e) << std::endl;

        resp.reset();
        resp.set_header("Status", "404");

        resp << "Controller not found.\n";
        resp << boost::diagnostic_information(e);
    }
    catch (action_not_found& e) {
        std::cerr << boost::diagnostic_information(e) << std::endl;

        resp.reset();
        resp.set_header("Status", "404");

        resp << "Action not found.\n";
        resp << boost::diagnostic_information(e);
    }
    catch (exception_base& e) {
        std::cerr << boost::diagnostic_information(e) << std::endl;

        resp.reset();
        resp.set_header("Status", "500");

        resp << "Base Exception.\n";
        resp << boost::diagnostic_information(e);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;

        resp.reset();
        resp.set_header("Status", "500");

        resp << "Exception.\n";
        resp << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;

        resp.reset();
        resp.set_header("Status", "500");

        resp << "Unknown Exception.\n";
    }

    // This function finishes up. The optional third argument
    // is the program status (default: 0).
    return boost::fcgi::commit(req, resp);
}

