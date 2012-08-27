/**
 * Author: rfilippone@gmail.com
 */

#include <iostream>
#include <map>

#include "boost/cgi/fcgi.hpp"

#include "Configuration.h"
#include "Application.h"
#include "BaseController.h"
#include "UrlRouter.h"
#include "IRouter.h"




int handle_request(boost::fcgi::request& req)
{
    std::cerr << "cwd: " << boost::filesystem::current_path() << std::endl;

    std::cerr << "lookup: " << Configuration::get("n2") << std::endl;

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
        resp << req.uri() << "\n";
        resp << req.query_string() << "\n";

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


int main()
{
//    boost::shared_ptr<Application> app(new Application("wnndqwin"));
//    app->bootstrap().run();


    // Make a `service` (more about this in other examples).
    boost::fcgi::service s;

    // Make an `acceptor` for accepting requests through.
    boost::fcgi::acceptor a(s);

    int status(0);
    do
    {
        status = a.accept(&handle_request);
    } while (!status);

	return 0;
}
