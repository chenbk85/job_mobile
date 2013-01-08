#include "stdafx.h"
#define _WIN32_WINNT 0x0500

#include "dialog.h"
#include "resource.h"
#include "stdafx.h"
#include "struct.h"
#include <windows.h>

HWND hDlg = NULL;
WNDPROC	OriginalEditProc = NULL;

BOOL APIENTRY DlgProc (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EditProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
extern jIConnection* g_pClientCon, *g_pHostServerCon;
extern jINetPort* g_pHostServer;
extern jNetPortCallback g_HostServerCB, g_HostClientCB;
void InitializeDialog()
{
	hDlg = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG),NULL,(DLGPROC)DlgProc);

	SetLayeredWindowAttributes(hDlg,0x00000000,60,LWA_ALPHA);
}

BOOL APIENTRY DlgProc (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg) 
	{
        case WM_INITDIALOG:
			{
				if(g_pGameServer)
				{
					HWND d = GetDlgItem(hdlg,IDC_EDIT_CHAT);
					OriginalEditProc = (WNDPROC)SetWindowLong (d,GWL_WNDPROC,LONG(EditProc));
					cstr sz ;
					if(g_pGameServer->IsServerMode())
					{
						assert(!g_pHostServer);
						sz =  "RestartServer" ;
					}
					else
					{
						if(g_pHostServer)
						{
							sz = "ConnectToServer & HostSerer";
						}
						else
						{
							sz = "ConnectToServer";
						}
					}
					SetDlgItemText(hdlg,IDC_BUTTON_CONNECT,sz);
					SetWindowText(hdlg , g_pGameServer->GetNetLogicNode()->Get_cstr() );
					fname_t buf;
					SetDlgItemText(hdlg,IDC_EDIT_CONNECT_IP,g_pGameServer->GetNetLogicNode()->GetAttribute("IP"));
					sprintf(buf, "%d", g_pGameServer->GetPort() );
					SetDlgItemText(hdlg,IDC_EDIT_CONNECT_PORT,buf);
				}
				else
				{
					HWND d = GetDlgItem(hdlg,IDC_EDIT_CHAT);
					OriginalEditProc = (WNDPROC)SetWindowLong (d,GWL_WNDPROC,LONG(EditProc));
					cstr sz ;
					if(g_pHostServer->IsServerMode())
					{
						assert(0);
						return 1;
					}
					else
					{
						sz = "ConnectTo HostSerer";
					}
					SetDlgItemText(hdlg,IDC_BUTTON_CONNECT,sz);
					SetWindowText(hdlg , g_pHostServer->GetNetLogicNode()->Get_cstr() );
					fname_t buf;
					SetDlgItemText(hdlg,IDC_EDIT_CONNECT_IP,g_pHostServer->GetNetLogicNode()->GetAttribute("IP"));
					sprintf(buf, "%d", g_pHostServer->GetPort() );
					SetDlgItemText(hdlg,IDC_EDIT_CONNECT_PORT,buf);
				}
			}
            return (TRUE);
  
        case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case IDC_BUTTON_CONNECT:
				if(g_pGameServer->IsServerMode() ) return 0;
				if(g_pClientCon)
				{
					g_pGameServer->Disconnect(g_pClientCon);
				}
				g_pClientCon = g_pGameServer->StartService(g_ClientCB);

				if(g_pHostServerCon)
				{
					g_pHostServer->Disconnect(g_pHostServerCon);
				}
				g_pHostServerCon = g_pHostServer->StartService(g_HostClientCB);
				break;
			case IDC_BUTTON_START_SERVER:
				if(!g_pGameServer->IsServerMode() ) return 0;
				g_pGameServer->StartService(g_ServerCB);
				break;

			}

			break;
		case WM_CLOSE:
			DestroyWindow(hdlg);
			PostQuitMessage(0);
			return TRUE;
    }
    return (FALSE);
}

LRESULT CALLBACK EditProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char txt[128];
	switch(message)
	{
		case WM_GETDLGCODE: return DLGC_WANTALLKEYS;
		case WM_KEYDOWN:
			switch(LOWORD(wParam))
			{
				case VK_RETURN:
					{
						if(g_pHostServer)
						{
							HWND parent = GetParent(hWnd);
							GetDlgItemText(parent,IDC_EDIT_CHAT,txt,100);

							static jIE* peChat = g_pHostServer->FindProtocal(TEXT("ChatMsg"));
							peChat->Find(TEXT("TEXT"))->Set_cstr(txt);

							if(g_pHostServerCon)  // client mode
							{
								g_pHostServerCon->Send(peChat);
							}
							else // server mode
							{
								jIConnection* pCon  = g_pHostServer->GotoBegin();
								for( ; pCon ;pCon = g_pHostServer->Next())
								{
									pCon->Send(peChat);
								}
							}

						}
						if(g_pGameServer )
						{
							HWND parent = GetParent(hWnd);
							GetDlgItemText(parent,IDC_EDIT_CHAT,txt,100);

							static jIE* peChat = g_pGameServer->FindProtocal(TEXT("ChatMsg"));
							peChat->Find(TEXT("TEXT"))->Set_cstr(txt);

							if(g_pClientCon)  // client mode
							{
								g_pClientCon->Send(peChat);
							}
							else // server mode
							{
								jIConnection* pCon  = g_pGameServer->GotoBegin();
								for( ; pCon ;pCon = g_pGameServer->Next())
								{
									pCon->Send(peChat);
								}
							}
						}

					}
					return 1;
			}
			break;
	}
	return CallWindowProc(OriginalEditProc,hWnd,message,wParam,lParam);
}