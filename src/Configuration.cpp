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

#include "Configuration.h"


Configuration* Configuration::m_instance = NULL;

Configuration::Configuration()
{

}

Configuration::~Configuration()
{
    delete m_instance;
}

std::string Configuration::get(const std::string& name)
{
    return instance()._get("", name);
}

void Configuration::setInstance(Configuration* instance)
{
    m_instance = instance;
}


Configuration& Configuration::instance()
{
    if (m_instance == NULL)
    {
        std::cerr << "***** loading configuration" << std::endl;
        m_instance = new Configuration();
        m_instance->_init("../configs/application.ini");
    }
    return *m_instance;
}


void Configuration::_load_ini(SectionMap& sectionMap, const boost::property_tree::ptree& pt)
{
    BOOST_FOREACH(boost::property_tree::ptree::value_type v, pt)
    {
        if (v.second.data() != "")
        {
            sectionMap.second.insert(std::make_pair(v.first, v.second.data()));
        }
        else
        {
            std::string sn = v.first; // section name
            boost::erase_all(sn, " ");

            std::vector<std::string> strs;
            boost::split(strs, sn, boost::is_any_of(":"));

            std::string parent("");
            if (strs.size() == 2)
            {
                parent = strs[1];
            }
            else if (strs.size() != 1)
            {
                throw std::invalid_argument("Wrong configuration section name" + v.first);
            }

            ParametersMap parametersMap;
            SectionMap subSectionMap(std::make_pair(parent, parametersMap)); //parent is root section
            _load_ini(subSectionMap, v.second);

            configurationMap.insert(std::make_pair(strs[0],subSectionMap));
        }
    }
}


void Configuration::_init(const std::string& fileName)
{
    boost::filesystem::path config(boost::filesystem::current_path() / fileName);

    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(config.string(), pt);

    ParametersMap parametersMap;
    SectionMap sectionMap(std::make_pair("~", parametersMap)); //no parent
    _load_ini(sectionMap, pt);

    configurationMap.insert(std::make_pair("",sectionMap)); // root section
}


std::string Configuration::_get(const std::string& sectionName, const std::string& name)
{
    ConfigurationMap::iterator section = configurationMap.find(sectionName);
    if (section == configurationMap.end())
    {
        throw std::invalid_argument("Unknown configuration section name " + sectionName);
    }

    ParametersMap::iterator entry = section->second.second.find(name);
    if (entry == section->second.second.end())
    {
        if (section->second.first == "~")
        {
            throw std::invalid_argument("Unknown configuration parameters name " + name);
        }
        else
        {
            return _get(section->second.first, name);
        }
    }
    else
    {
        return entry->second;
    }

    return "";
}
