/**
 * Author: rfilippone@gmail.com
 */

#include "Application.h"

int entryPoint()
{
    boost::shared_ptr<Application> app(new Application("../configs/application.ini"));
    app->bootstrap().run();

    return 0;
}
