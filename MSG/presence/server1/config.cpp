//
// cofig.cpp
// ~~~~~~~~~~
//
//
#include "stdafx.h"

#include "common_def.hpp"
#include "config.hpp"

namespace presence 
{

Configure& get_conf()
{
	static Configure conf;
	
	return conf;
}

static void load(const YAML::Node& node, std::vector<ServerInfo>& game_servers)
{

	for (int i =0; i < (int)node.size(); i++)
	{
		ServerInfo si;
		node[i]["ip"]			>> si.ip;
		node[i]["port"]			>> si.port;
		node[i]["begin_roomid"]	>> si.begin_roomid;
		node[i]["end_roomid"]	>> si.end_roomid;

		game_servers.push_back(si);
	}

	return;
}

static void load(const YAML::Node& node, std::vector<CategoryInfo>& categories)
{
	for (int i =0; i < (int)node.size(); i++)
	{
		CategoryInfo category;
		node[i]["id"] >> category.id;
		node[i]["name"] >> category.name;

		const YAML::Node& game_servers_node = node[i]["game_servers"];

		load(game_servers_node, category.game_servers);

		categories.push_back(category);
	}

	return;
}

bool Configure::load(const std::string& file_name)
{
	// 디버깅 또는 에러 메시지 출력을 위해 절대 경로 구해 놓음.
	std::string abs_file_path = file_name;	
	boost::filesystem::path org_path(file_name);
	if (org_path.is_absolute() == false)
		abs_file_path = boost::filesystem::current_path().string() + "/" + file_name;						


	try
	{
		std::ifstream ifs(file_name.c_str());

		if (ifs.is_open() == false)
		{
			MSG_LOG() << "file open fail!!! " << std::endl;
			MSG_LOG() << "\t file name \""  << abs_file_path << std::endl;
			return false;
		}


		YAML::Parser parser(ifs);

		YAML::Node doc;		
		parser.GetNextDocument(doc);

		const YAML::Node& presence = doc["presence"];

		presence["bind_ip_for_ug"]			>> bind_ip_for_ug_;
		presence["bind_ip_for_monitoring"]	>> bind_ip_for_monitoring_;

		presence["bind_port_for_ug"]		>> bind_port_for_ug_;
		presence["bind_port_for_monitoring"]>> bind_port_for_monitoring_;

        const YAML::Node& modules = doc["modules"];
		for (int k =0; k < (int)modules.size(); k++)
		{
            ModuleInfo module;
            modules[k]["name"]    >> module.name;
            modules[k]["version"] >> module.version;
            modules[k]["active"]  >> module.active;
            modules_.push_back(module);
        }

		const YAML::Node& services = doc["services"];
		
		for (int k =0; k < (int)services.size(); k++)
		{
			ServiceInfo service;

			services[k]["id"]	>> service.id;
			services[k]["name"] >> service.name;
            // sk68: get the depmods array
            //       then check if any of them are valid module names
            //       if we cannot find the module name in the modules
            //       section, spit out a warning
            services[k]["depmods"] >> service.dep_modules;

            // sk68: directives such as max_user_per_room should really only
            //       be readable/settable when the appropriate (e.g. modroom)
            //       module is used.

			services[k]["max_user_per_room"] >> service.max_user_per_room;

			const YAML::Node& categories_node = services[k]["categories"];

			presence::load(categories_node, service.categories);
			services_.push_back(service);	
		}
		
	}
	catch (std::exception& e)
	{
		last_err_string_ = e.what();
		MSG_LOG() << "yaml file load fail!!! " << last_err_string_ << std::endl;
		MSG_LOG() << "\t file name \""  << abs_file_path << std::endl;
		return false;
	}		

	return true;
};
} // namespace presence
