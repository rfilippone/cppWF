/**
 * Author: rfilippone@gmail.com
 */

#include "RestBaseController.h"


REST_CONTROLLER(RestExampleController)

    void init()
    {
        std::cout << "RestExampleController - Init" << std::endl;
    }

    void indexOp()
    {
        m_resp << "indexOp";
    }

    void getOp()
    {
        m_resp << "getOp";
    }

    void postOp()
    {
        m_resp << "postOp";
    }

    void putOp()
    {
        m_resp << "putOp";
    }

    void deleteOp()
    {
        m_resp << "deleteOp";
    }
};


BIND_REST_CONTROLLER(RestExampleController);
