/**
 * Author: rfilippone@gmail.com
 */

#ifndef ROUTESCONFIGURATION_H_
#define ROUTESCONFIGURATION_H_

#include <string>

#include <boost/unordered_map.hpp>
#include <boost/property_tree/ptree.hpp>

typedef boost::unordered_map<std::string, std::string> RoutesMap; // name -> value

class RoutesConfiguration
{
public:
    typedef RoutesMap::iterator iteartor;

    RoutesConfiguration();
    virtual ~RoutesConfiguration();

    static std::string get(const std::string& name);

    static void setInstance(RoutesConfiguration* instance);

    static iteartor begin() { return instance().m_routesMap.begin(); }
    static iteartor end() { return instance().m_routesMap.end(); }

protected:
    static RoutesConfiguration& instance();

private:
    static RoutesConfiguration* m_instance;

//move to impl
private:
    void _init(const std::string& fileName);
    std::string _get(const std::string& name);

    std::time_t m_lastTime;
    std::string m_lastFile;

    RoutesMap m_routesMap;
};

#endif /* ROUTESCONFIGURATION_H_ */
