/**
 * Author: rfilippone@gmail.com
 */

#include "BaseController.h"


CONTROLLER(IndexController)

    void init()
    {
        std::cout << "IndexController - Init" << std::endl;
        m_a = 56;
    }

    void index()
    {
        m_resp << boost::fcgi::content_type("text/html");

        m_resp << "IndexController - Action: index - " << m_a;
    }

    void abc()
    {
        m_resp << boost::fcgi::content_type("text/html");

        m_resp << "ID = " << m_req.id() << "<br/>";

        m_resp << "IndexController - Action: abc - " << m_a << "<br/>";

        m_resp << "URI = " << m_req.uri() << "<br/>";

        m_resp << "query string = " << m_req.query_string() << "<br/>";

        m_resp << "script_name = " << m_req.script_name() << "<br/>";

        m_resp << "script_uri = " << m_req.script_uri() << "<br/>";

        m_resp << "script_url = " << m_req.script_url() << "<br/>";

        m_resp << "path_info = " << m_req.path_info().value << "<br/>";

        m_resp << "--------------------------" << "<br/>";

        boost::fcgi::get_data data =  m_req.get;

        BOOST_FOREACH(boost::fcgi::get_data::value_type pair, data)
        {
            m_resp << pair.first << " = " << pair.second << "<br/>";
        }

        m_resp << "--------------------------" << "<br/>";

        boost::fcgi::env_data env =  m_req.env;

        BOOST_FOREACH(boost::fcgi::env_data::value_type pair, env)
        {
            m_resp << pair.first << " = " << pair.second << "<br/>";
        }


    }

    void def()
    {
        m_resp << boost::fcgi::content_type("text/html");

        m_resp << "IndexController - Action: def - " << m_a;
    }

private:
    int m_a;

};

BIND_ACTION(IndexController, index);
BIND_ACTION(IndexController, abc);
BIND_ACTION(IndexController, def);

