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

    virtual void getOp() = 0;
    virtual void postOp() = 0;
    virtual void putOp() = 0;
    virtual void deleteOp() = 0;
};

#endif /* RESTBASECONTROLLER_H_ */
