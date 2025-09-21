#include "config_loader.h"
#include "global.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace Config {
    void load_config(const std::string &filename) {
        using boost::property_tree::ptree;
        ptree pt;
        boost::property_tree::read_json(filename, pt);

        Global::input_path = pt.get<std::string>("input_path");
        Global::dataset = pt.get<std::string>("dataset");
        Global::minutils_percentage = pt.get<double>("minutils_percentage");
        Global::algorithm = pt.get<std::string>("algorithm");

        std::string sev = pt.get<std::string>("severity", "info");
        if (sev == "debug") Global::severity = boost::log::trivial::debug;
        else if (sev == "info") Global::severity = boost::log::trivial::info;
        else if (sev == "warning") Global::severity = boost::log::trivial::warning;
        else if (sev == "error") Global::severity = boost::log::trivial::error;
        else Global::severity = boost::log::trivial::info; // default
    }
}
