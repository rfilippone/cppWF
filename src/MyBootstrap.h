/**
 * Author: rfilippone@gmail.com
 */

#ifndef MYBOOTSTRAP_H_
#define MYBOOTSTRAP_H_

#include "Bootstrap.h"

class MyBootstrap : public IBootstrap
{
public:
    MyBootstrap();
    virtual ~MyBootstrap();

    void init();
};

#endif /* MYBOOTSTRAP_H_ */
