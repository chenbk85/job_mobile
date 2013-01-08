#include <stddef.h>
#include <iostream>
#include <map>
#include <vector>

#include "backend.hpp"
#include "game_service.hpp"

namespace presence
{

struct ContentHandler
{
    int op1;   // content-type
    std::map<int,const handler_rec*> handlers; // specific op + corresponding handler
};

class BackEnd
{
public:
    BackEnd();
    void start();
    int init(std::vector<BackEndModule *> * modules = NULL);
    int initialize(BackEndModule &bem);
    boost::shared_ptr<presence::GameService> get_service(presence::ServiceID svcid);

    boost::shared_ptr<presence::SKSK> get_entry_point(ServiceID id);

private:
    std::map<int,ContentHandler> server_handlers;
    void addContent(BackEndModule &bem);
    std::map<presence::ServiceID, boost::shared_ptr<presence::GameService> > service_;
};

extern BackEnd& get_backend();

}//namespace presence
