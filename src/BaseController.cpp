/**
 * Author: rfilippone@gmail.com
 */

#include <boost/make_shared.hpp>

#include "BaseController.h"

BaseController::BaseController(boost::fcgi::request& req,  boost::fcgi::response& resp):
    m_initialized(false),
    m_req(req),
    m_resp(resp)
{
}

BaseController::~BaseController()
{
}

void BaseController::_init()
{
    std::cout << "BaseController - _init" << std::endl;
    if (!m_initialized)
    {
        m_initialized = true;
        init();
    }
}

void ActionInvoker::invoke(std::string sController, std::string sAction, boost::fcgi::request& req,  boost::fcgi::response& resp)
{
    boost::shared_ptr<IController> pIC = IController::getController(sController, req, resp);
    pIC->_init();

    IController::getAction(sController+ "." + sAction)(pIC);
}

