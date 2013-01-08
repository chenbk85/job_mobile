
#include "stdafx.h"

#include "config.hpp"
#include "backend_handler.hpp"

namespace presence
{

//=================================================================
// BackEnd singleton 구현.
//=================================================================
BackEnd& get_backend()
{
    static BackEnd be_;
    return be_;
}

BackEnd::BackEnd()
{
}

void BackEnd::start()
{
}

int BackEnd::init(std::vector<BackEndModule *> * modules)
{
    // we should initialize resources here
    std::string config_file = presence::default_config_name;

	bool is_ok = presence::the_configure.load(config_file);
	if (is_ok == false)
		return -1;

    // for each module in modules, initialize + addContent
    for (std::vector<BackEndModule *>::iterator iter = modules->begin();
        iter != modules->end(); ++iter)
    {
        initialize(**iter);
        addContent(**iter);
    }

    // now load services
	for (std::vector<presence::ServiceInfo>::const_iterator iter = presence::the_configure.services().begin();
		iter != presence::the_configure.services().end();
		iter++)
	{
		presence::SpGameService svc = presence::GameService::create_service(*iter, modules);
		if (svc)
			service_[svc->id()] = svc;
		else
			return -1;
	}
    return 0;
}

// initialize each module
int BackEnd::initialize(BackEndModule & bem)
{
    int result = bem.init_func();
    return result;
}

boost::shared_ptr<presence::SKSK> BackEnd::get_entry_point(ServiceID id)
{
    std::map<presence::ServiceID, boost::shared_ptr<presence::GameService> >::const_iterator svc = service_.find(id);
    //sk68: TODO: svc NULL check
    if (svc != service_.end())
    {
        return svc->second->entry_point;
    }
    else
        return boost::shared_ptr<presence::SKSK>();
}

// add ContentHandler to existing set.
// duplicates (i.e. same content-type, module version) are
// considered error
void BackEnd::addContent(BackEndModule & bem)
{
    ContentHandler cHandler;
    cHandler.op1 = 0;   // need to convert id to integer
    cHandler.handlers.insert(std::pair<int, const handler_rec*>(0, bem.handlers));
    // add to server_handlers
    server_handlers.insert(std::pair<int, ContentHandler>(0, cHandler));
}

presence::SpGameService BackEnd::get_service(presence::ServiceID svcid)
{
	presence::SpGameService game_service;

	//  서비스 아이디가 올바른 값인지 알아본다
	std::map<presence::ServiceID, presence::SpGameService>::const_iterator iter = service_.find(svcid);
	if (iter == service_.end())
	{
		// 에러 로그 남기시오.
		return game_service;		
	}

	return iter->second;
}

}
