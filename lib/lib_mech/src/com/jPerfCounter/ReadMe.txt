http://legendfinger.com/449


DLL 공유 섹션 만드는 방법

#pragma data_seg("SHARED")

char shared_buffer[1024] = {0};

#pragma data_seg()

 

#pragma comment(linker, "/subsystem:SHARED,RWS")

 
 http://support.microsoft.com/kb/300702/ko
 
 원격 컴퓨터에서 성능 카운터를 볼 수 있으려면 모니터링할 원격 컴퓨터에 다음 권한이 있어야 합니다. 
systemroot가 NTFS 파티션에 있는 경우 적어도 다음 두 파일에 대한 읽기 권한이 있어야 합니다. 
%SystemRoot%\System32\Perfc009.dat
%SystemRoot%\System32\Perfh009.dat
원격 컴퓨터의 다음 레지스트리 키에 대해 최소한 읽기 권한이 있어야 합니다. 
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SecurePipeServers\winreg
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Perflib
원격 컴퓨터의 다음 레지스트리 키에 대해 모든 권한이 있어야 합니다. 
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\servicename\performance
여기서 servicename은 모니터링할 원격 컴퓨터의 서비스 이름입니다.


