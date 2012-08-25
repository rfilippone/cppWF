/**
 * Author: rfilippone@gmail.com
 */

#include "RestBaseController.h"

RestBaseController::RestBaseController(boost::fcgi::request& req,  boost::fcgi::response& resp):
    BaseController(req, resp)
{
}

RestBaseController::~RestBaseController()
{
}

