/**
 * Author: rfilippone@gmail.com
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <boost/exception/all.hpp>

// error infos
typedef boost::error_info<struct tag_msg_info, std::string> msg_info;

// possible errors
struct exception_base: virtual std::exception, virtual boost::exception { };
struct controller_not_found : virtual exception_base { };
struct action_not_found : virtual exception_base { };


#endif /* EXCEPTION_H_ */
