/**
 * Author: rfilippone@gmail.com
 */

#ifndef RESTBASECONTROLLER_H_
#define RESTBASECONTROLLER_H_

#include "BaseController.h"

class RestBaseController : public BaseController
{
public:
    RestBaseController(boost::fcgi::request& req,  boost::fcgi::response& resp);
    virtual ~RestBaseController();

    virtual void indexOp() = 0;
    virtual void getOp() = 0;
    virtual void postOp() = 0;
    virtual void putOp() = 0;
    virtual void deleteOp() = 0;
};

#define REST_CONTROLLER(CONTROLLER) \
class CONTROLLER;\
template <> bool ControllerBinder<CONTROLLER>::bound = ControllerBinder<CONTROLLER>::bind(BOOST_STRINGIZE(CONTROLLER));\
class CONTROLLER : public RestBaseController { public: CONTROLLER(boost::fcgi::request& req,  boost::fcgi::response& resp) : RestBaseController(req, resp) {}

#define BIND_REST_CONTROLLER(CONTROLLER) \
BIND_ACTION(CONTROLLER, indexOp);\
BIND_ACTION(CONTROLLER, getOp);\
BIND_ACTION(CONTROLLER, postOp);\
BIND_ACTION(CONTROLLER, putOp);\
BIND_ACTION(CONTROLLER, deleteOp);

#endif /* RESTBASECONTROLLER_H_ */
