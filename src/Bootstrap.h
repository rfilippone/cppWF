/**
 * Author: rfilippone@gmail.com
 */

#ifndef BOOTSTRAP_H_
#define BOOTSTRAP_H_

class IBootstrap
{
public:

    virtual ~IBootstrap() {}
    virtual void init() = 0;
};

#endif /* BOOTSTRAP_H_ */
