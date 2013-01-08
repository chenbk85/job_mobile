//
// config.hpp
// ~~~~~~~~~~
//
// 설정 파일("presence_config.yaml") 정보를 접근하기 위한 기능
//
// 최초 작성 : 2012.07.30. kts123@neowiz.com
// ~~~~~~~~~~
//
#ifndef PRESENCE_CONFIG_HPP
#define PRESENCE_CONFIG_HPP

#include <vector>
#include <string>

namespace presence {

struct ModuleInfo
{
	std::string name;				
	int		version;
    bool    active;
};

// game server 정보
// channel 에 해당함
struct ServerInfo
{
	// 클라이언트가 접속할 게임 서버의 외부 아이피/포트
	std::string ip;				
	int		port;

	// 서비스할 방 범위. 
	// [begin_roomid, end_roomid)
	int		begin_roomid;	
	int		end_roomid;		
};

// 속해 있는 카테고리 (채널 묶음에 해당함)
// instance example) 자유채널, 10원 채널, 100원 채널, ...
struct CategoryInfo 
{	
	int			id;
	std::string name;
	std::vector<ServerInfo> game_servers;
};

// 개별 게임에 해당함
// instance example) 맞고, 포커, 야구, ...
struct ServiceInfo
{
	// 서비스 아이디
	int			id;

	// 서비스 이름
	std::string  name;

	// 룸당 최대 인원
	int		max_user_per_room;

	// 카테고리 리스트
	std::vector<CategoryInfo>	categories;

    // modules used (for the time being, just one)
    std::vector<std::string> dep_modules;
};

static const char* const default_config_name = "../yaml/presence_config.yaml";

class Configure
{	
public:
	// Yaml 파일로부터 설정값을 로드함.
	bool load (const std::string& file_name);

	// gets 
	const std::string& bind_ip_for_ug() const { return bind_ip_for_ug_;};
	int	bind_port_for_ug() const { return bind_port_for_ug_;};
	const std::string& bind_ip_for_monitoring() const { return bind_ip_for_monitoring_;};
	int bind_port_for_monitoring() const { return bind_port_for_monitoring_;}
	const std::vector<ServiceInfo>& services() const { return services_;};

private:
	// Presence 서버가 ug 컨넥션을 받기 위해 바인드할 ip/port
	std::string	bind_ip_for_ug_;			
	int			bind_port_for_ug_;

	// Presence 서버가 모니터링 컨넥션을 받기 위해 바인드할 ip/port
	std::string	bind_ip_for_monitoring_;			
	int			bind_port_for_monitoring_;

    std::vector<ModuleInfo> modules_;
	std::vector<ServiceInfo> services_;
		
	// 에러 스트링
	// bool 타입의 false를 리턴하는 경우 에러 메시지를 저장해 놓기 위한 변수.
	std::string		last_err_string_;
};	

// 싱글톤.
extern Configure& get_conf();

#define the_configure get_conf()

} // namespace presence
#endif // PRESENCE_CONFIG_HPP
