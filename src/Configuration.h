/**
 * Author: rfilippone@gmail.com
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>

#include <boost/unordered_map.hpp>
#include <boost/property_tree/ptree.hpp>

typedef boost::unordered_map<std::string, std::string> ParametersMap; // name -> value
typedef std::pair<std::string,  ParametersMap> SectionMap; // parent -> map
typedef boost::unordered_map<std::string, SectionMap > ConfigurationMap; // section name -> section map


class Configuration
{
public:
    Configuration();
    virtual ~Configuration();

    static std::string get(const std::string& name);

    static void setInstance(Configuration* instance);

    static const std::string APPLICATION_ENV_VAR;

protected:
    static Configuration& instance();

private:
    static Configuration* m_instance;

//move to impl
private:
    void _init(const std::string& fileName);
    std::string _get(const std::string& name);
    void _load_ini(SectionMap& sectionMap, const boost::property_tree::ptree& pt);

    std::time_t m_lastTime;

    ConfigurationMap m_configurationMap;
    ParametersMap m_parametersMap;
};

#endif /* CONFIGURATION_H_ */
