/**
 * Author: rfilippone@gmail.com
 */

#include <iostream>
#include <vector>

#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

#include "RoutesConfiguration.h"


RoutesConfiguration* RoutesConfiguration::m_instance = NULL;

RoutesConfiguration::RoutesConfiguration()
{

}

RoutesConfiguration::~RoutesConfiguration()
{
    delete m_instance;
}

std::string RoutesConfiguration::get(const std::string& name)
{
    return instance()._get(name);
}

void RoutesConfiguration::setInstance(RoutesConfiguration* instance)
{
    m_instance = instance;
}


RoutesConfiguration& RoutesConfiguration::instance()
{
    if (m_instance == NULL)
    {
        m_instance = new RoutesConfiguration();
        m_instance->_init("../configs/routes.ini");
    }
    return *m_instance;
}

void RoutesConfiguration::_init(const std::string& fileName)
{
    boost::filesystem::path config(boost::filesystem::current_path() / fileName);

    if (boost::filesystem::exists(config))
    {
        std::cerr << "***** loading routes configuration" << std::endl;

        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini(config.string(), pt);

        BOOST_FOREACH(boost::property_tree::ptree::value_type route, pt)
        {
            m_routesMap.insert(std::make_pair(route.first, route.second.data()));
        }
    }
}

std::string RoutesConfiguration::_get(const std::string& name)
{
    RoutesMap::iterator entry = m_routesMap.find(name);
    if (entry == m_routesMap.end())
    {
        throw std::invalid_argument("Unknown routes name " + name);
    }
    else
    {
        return entry->second;
    }

    return "";
}

