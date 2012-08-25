/**
 * Author: rfilippone@gmail.com
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream>
#include <map>
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>

#include "Exception.h"

class IController;

typedef boost::function<void (boost::shared_ptr<IController>)> ControllerAction;
typedef boost::function<boost::shared_ptr<IController>(boost::fcgi::request& req,  boost::fcgi::response& resp)> ControllerFactory;

class IController
{
public:
    static boost::shared_ptr<IController> getController(std::string name, boost::fcgi::request& req,  boost::fcgi::response& resp)
    {
        ControllerFactory factory = IController::getControllerFactoryMap()[name];
        if (factory == NULL)
        {
            BOOST_THROW_EXCEPTION(controller_not_found() << msg_info("Controller " + name + " not registered"));
        }
        return factory(req, resp);
    }

    static std::string getControllerUrl(const std::string& controllerName)
    {
        std::string name = controllerName;
        if (!boost::algorithm::find_first(name , "Controller"))
        {
            throw std::invalid_argument(name + " is not a valid controller name");
        }
        boost::algorithm::to_lower(name);
        boost::algorithm::replace_first(name, "controller", "");

        return name;
    }

    static ControllerAction getAction(const std::string& actionName)
    {
        ControllerAction action = IController::getInvokerMap()[actionName];
        if (action == NULL)
        {
            BOOST_THROW_EXCEPTION(action_not_found() << msg_info("No action registered for: " + actionName));
        }
        return action;
    }

    virtual ~IController() {}
    virtual void init() = 0;
    virtual void _init() = 0;

private:
    static std::map<std::string, ControllerFactory >& getControllerFactoryMap()
    {
        static std::map<std::string, ControllerFactory > controllerFactoryMap;
        return controllerFactoryMap;
    }

    static std::map<std::string, ControllerAction>& getInvokerMap()
    {
        static std::map<std::string, ControllerAction> invokerMap;
        return invokerMap;
    }

    template<typename T> friend class ControllerBinder;
    friend class ActionBinder;
};


template<typename T> struct ControllerBinder
{
    static bool bound;

    static bool bind (const std::string& name)
    {
        std::string controllerUrl = IController::getControllerUrl(name);

        IController::getControllerFactoryMap()[controllerUrl] = boost::factory<boost::shared_ptr<T> >();
        return true;
    }
};


struct ActionBinder
{
    static bool bind (const std::string& name, const std::string& actionName, ControllerAction action)
    {
        std::string controllerUrl = IController::getControllerUrl(name) + "." + actionName;

        IController::getInvokerMap()[controllerUrl] = action;
        return true;
    }
};

#endif /* CONTROLLER_H_ */
