/**
 * Author: rfilippone@gmail.com
 */

#ifndef IURLPARSER_H_
#define IURLPARSER_H_

#include <string>

class IUrlParser
{
public:
    virtual ~IUrlParser() {}

    virtual std::string getControllerName() = 0;
    virtual std::string getActionName() = 0;
};

#endif /* IURLPARSER_H_ */
