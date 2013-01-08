
// X(DOMAIN,NAME,ORDER) 
#define for_each_UserGateServer_Client(X)\
		X(UserGateServer_Client,ug2x_echo,2)\
		X(UserGateServer_Client,ans_ug_error,3)\
		X(UserGateServer_Client,ug2x_client_version,4)\
  


// X(DOMAIN,NAME,ORDER) 
#define for_each_Client_UserGateServer(X)\
		X(Client_UserGateServer,x2ug_echo,2)\
		X(Client_UserGateServer,x2ug_get_client_version,3)\
  


		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.6_ug_admin.usd
		#define for_each_UserGateServer_Client___ug2x_echo(X)\
		X(ug2x_echo,0,int32,type)\
		X(ug2x_echo,1,string,msg)\
		X(ug2x_echo,2,int32,client_time_msec)\
		X(ug2x_echo,3,int64,ug_time_msec)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.6_ug_admin.usd
		#define for_each_UserGateServer_Client___ans_ug_error(X)\
		X(ans_ug_error,0,int32,sys_error_id)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.6_ug_admin.usd
		#define for_each_UserGateServer_Client___ug2x_client_version(X)\
		X(ug2x_client_version,0,string,version)\


  


		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.6_ug_admin.usd
		#define for_each_Client_UserGateServer___x2ug_echo(X)\
		X(x2ug_echo,0,int32,type)\
		X(x2ug_echo,1,string,msg)\
		X(x2ug_echo,2,int32,client_time_msec)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.6_ug_admin.usd
		#define for_each_Client_UserGateServer___x2ug_get_client_version(X)\
		X(x2ug_get_client_version,0,string,version)\


  

