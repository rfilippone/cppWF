/**
 * Author: rfilippone@gmail.com
 */

#ifndef BASECONTROLLER_H_
#define BASECONTROLLER_H_

#include "boost/cgi/fcgi.hpp"

#include "Controller.h"

class BaseController : public IController
{
public:
    BaseController(boost::fcgi::request& req,  boost::fcgi::response& resp);
    virtual ~BaseController();

    void _init();

    bool m_initialized;
    boost::fcgi::request& m_req;
    boost::fcgi::response& m_resp;
};

struct ActionInvoker
{
    static void invoke(std::string sController, std::string sAction, boost::fcgi::request& req,  boost::fcgi::response& resp);
};


#define CONTROLLER(CONTROLLER) \
class CONTROLLER;\
template <> bool ControllerBinder<CONTROLLER>::bound = ControllerBinder<CONTROLLER>::bind(BOOST_STRINGIZE(CONTROLLER));\
class CONTROLLER : public BaseController { public: CONTROLLER(boost::fcgi::request& req,  boost::fcgi::response& resp) : BaseController(req, resp) {}

//#define BIND_CONTROLLER(CONTROLLER) template <> bool ControllerBinder<CONTROLLER>::bound = ControllerBinder<CONTROLLER>::bind(BOOST_STRINGIZE(CONTROLLER))

#define BIND_ACTION(CONTROLLER, ACTION) void __##CONTROLLER##__##ACTION##__invoke(boost::shared_ptr<IController> pIC) \
{\
    boost::shared_ptr<CONTROLLER> pC = boost::shared_dynamic_cast<CONTROLLER>(pIC);\
    pC->ACTION();\
}\
static bool __##CONTROLLER##__##ACTION##__bound = ActionBinder::bind(BOOST_STRINGIZE(CONTROLLER), BOOST_STRINGIZE(ACTION), __##CONTROLLER##__##ACTION##__invoke);


#endif /* BASECONTROLLER_H_ */
