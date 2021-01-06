/*

	SA:MP Multiplayer Modification
	Copyright 2004-2005 SA:MP Team

	file:
		gamemodes.cpp
	desc:
		GameMode Event Executive.

    Version: $Id: gamemodes.cpp,v 1.27 2006/04/19 11:57:59 spookie Exp $

*/

#include "main.h"

#define CHECK_INIT() { if (!m_bInitialised) return 0; };

char szGameModeFileName[256];
 
#pragma region CGameMode
CGameMode::CGameMode() {
	this->m_bInitialised = false;
	this->m_bSleeping = false;
	this->m_fSleepTime = 0.0f;
	this->m_gtType = GAMEMODE_TYPE::NONE;
}
CGameMode::~CGameMode()
{
}
CGameMode* CGameMode::Create(char* pFileName)
{
	//The check to assign a proper GameMode object is to check the character after the last '.' character.
	//For example if the pFileName ends with .amx then return CGameModeAMX
	//On the other hand if it ends with .dll then return CGameModeDLL
	//And so on if there are multiple types
#ifdef WIN32
	if (strcmp(PathFindExtension(pFileName), ".dll") == 0) {
		return new CGameModeDLL();
	}
#endif

	return new CGameModeAMX();
}
bool CGameMode::Load(char* pFileName)
{
	// TODO: Perform check if the current gamemode filename is a DLL or AMX file
	return false;
}
void CGameMode::Unload()
{
}
void CGameMode::Frame(float fElapsedTime)
{
}
int CGameMode::CallPublic(char* szFuncName)
{
	return 0;
}
int CGameMode::OnPlayerConnect(cell playerid)
{
	return 0;
}
int CGameMode::OnPlayerDisconnect(cell playerid, cell reason)
{
	return 0;
}
int CGameMode::OnPlayerSpawn(cell playerid)
{
	return 0;
}
int CGameMode::OnPlayerDeath(cell playerid, cell killerid, cell reason)
{
	return 0;
}
int CGameMode::OnVehicleSpawn(cell vehicleid)
{
	return 0;
}
int CGameMode::OnVehicleDeath(cell vehicleid, cell killerid)
{
	return 0;
}
int CGameMode::OnPlayerText(cell playerid, unsigned char* szText)
{
	return 0;
}
int CGameMode::OnPlayerCommandText(cell playerid, unsigned char* szCommandText)
{
	return 0;
}
int CGameMode::OnPlayerInfoChange(cell playerid)
{
	return 0;
}
int CGameMode::OnPlayerRequestClass(cell playerid, cell classid)
{
	return 0;
}
int CGameMode::OnPlayerRequestSpawn(cell playerid)
{
	return 0;
}
int CGameMode::OnPlayerEnterVehicle(cell playerid, cell vehicleid, cell ispassenger)
{
	return 0;
}
int CGameMode::OnPlayerExitVehicle(cell playerid, cell vehicleid)
{
	return 0;
}
int CGameMode::OnPlayerStateChange(cell playerid, cell newstate, cell oldstate)
{
	return 0;
}
int CGameMode::OnPlayerEnterCheckpoint(cell playerid)
{
	return 0;
}
int CGameMode::OnPlayerLeaveCheckpoint(cell playerid)
{
	return 0;
}
int CGameMode::OnPlayerEnterRaceCheckpoint(cell playerid)
{
	return 0;
}
int CGameMode::OnPlayerLeaveRaceCheckpoint(cell playerid)
{
	return 0;
}
int CGameMode::OnRconCommand(char* szCommand)
{
	return 0;
}
int CGameMode::OnObjectMoved(cell objectid)
{
	return 0;
}
int CGameMode::OnPlayerObjectMoved(cell playerid, cell objectid)
{
	return 0;
}
int CGameMode::OnPlayerPickedUpPickup(cell playerid, cell pickupid)
{
	return 0;
}
int CGameMode::OnPlayerExitedMenu(cell playerid)
{
	return 0;
}
int CGameMode::OnPlayerSelectedMenuRow(cell playerid, cell row)
{
	return 0;
}
int CGameMode::OnVehicleRespray(cell playerid, cell vehicleid, cell color1, cell color2)
{
	return 0;
}
int CGameMode::OnVehicleMod(cell playerid, cell vehicleid, cell componentid)
{
	return 0;
}
int CGameMode::OnEnterExitModShop(cell playerid, cell enterexit, cell interiorid)
{
	return 0;
}
int CGameMode::OnVehiclePaintjob(cell playerid, cell vehicleid, cell paintjobid)
{
	return 0;
}
int CGameMode::OnPlayerInteriorChange(cell playerid, cell newid, cell oldid)
{
	return 0;
}
int CGameMode::OnPlayerKeyStateChange(cell playerid, cell newkeys, cell oldkeys)
{
	return 0;
}
int CGameMode::OnPlayerUpdate(cell playerid)
{
	return 0;
}
int CGameMode::OnIncomingConnection(cell playerid, char* ip, cell port)
{
	return 0;
}
int CGameMode::OnPlayerClickMap(cell playerid, float fX, float fY, float fZ)
{
	return 0;
}
int CGameMode::OnTrailerUpdate(cell playerid, cell vehicleid)
{
	return 0;
}
int CGameMode::OnRconLoginAttempt(char* szIP, char* szPassword, cell success)
{
	return 0;
}
void CGameMode::OnPlayerBeginTyping(cell playerid)
{
}
void CGameMode::OnPlayerEndTyping(cell playerid)
{
}
int CGameMode::OnPlayerStunt(cell playerid, cell vehicleid)
{
	return 0;
}
void CGameMode::OnClientCheckResponse(cell playerid, cell type, cell address, cell checksum)
{
}
void CGameMode::OnVehicleSirenStateChange(cell playerid, cell vehicleid, cell newstate)
{
}
void CGameMode::OnVehicleDamageStatusUpdate(cell vehicleid, cell playerid)
{
}
#pragma endregion
#pragma region CGameModeAMX
//----------------------------------------------------------------------------------

CGameModeAMX::CGameModeAMX()
{
	m_bInitialised = false;
	m_bSleeping = false;
	//m_pScriptTimers = new CScriptTimers;
}

//----------------------------------------------------------------------------------

CGameModeAMX::~CGameModeAMX()
{
	Unload();
	//SAFE_DELETE(m_pScriptTimers);
	/*if (m_pScriptTimers)
	{
		m_pScriptTimers->EndGMTimers();
		//m_pScriptTimers = null;
	}*/
}

//----------------------------------------------------------------------------------
void PrintMissingNatives(AMX* amx, const char* szScriptName);

bool CGameModeAMX::Load(char* pFileName)
{
	if (m_bInitialised)
		Unload();

	FILE* f = fopen(pFileName, "rb");
	if (!f) return false;
	fclose(f);

	memset((void*)&m_amx, 0, sizeof(AMX));
	m_fSleepTime = 0.0f;
	strcpy(szGameModeFileName, pFileName);

	int err = aux_LoadProgram(&m_amx, szGameModeFileName);
	if (err != AMX_ERR_NONE)
	{
		AMXPrintError(this, &m_amx, err);
		logprintf("Failed to load '%s' script.", szGameModeFileName);
		return false;
	}

	amx_CoreInit(&m_amx);
	amx_FloatInit(&m_amx);
	amx_StringInit(&m_amx);
	amx_FileInit(&m_amx);
	amx_TimeInit(&m_amx);
	amx_CustomInit(&m_amx);
	amx_sampDbInit(&m_amx);

	pPlugins->DoAmxLoad(&m_amx);

	PrintMissingNatives(&m_amx, pFileName);

	m_bInitialised = true;

	// Execute OnGameModeInit callback, if it exists!
	int tmp;
	if (!amx_FindPublic(&m_amx, "OnGameModeInit", &tmp)) 
		amx_Exec(&m_amx, (cell*)&tmp, tmp);
	pNetGame->GetFilterScripts()->OnGameModeInit();
	// ----------------------------------------------

	cell ret = 0;
	err = amx_Exec(&m_amx, &ret, AMX_EXEC_MAIN);
	if (err == AMX_ERR_SLEEP)
	{
		m_bSleeping = true;
		m_fSleepTime = ((float)ret / 1000.0f);
	}
	else if (err != AMX_ERR_NONE)
	{
		m_bSleeping = false;
		AMXPrintError(this, &m_amx, err);
	}

	return true;
}
//----------------------------------------------------------------------------------

void CGameModeAMX::Unload()
{
	// Execute OnGameModeExit callback, if it exists!
	int tmp;
	if (!amx_FindPublic(&m_amx, "OnGameModeExit", &tmp))
		amx_Exec(&m_amx, (cell*)&tmp, tmp);
	// ----------------------------------------------

	// Call in filterscripts
	pNetGame->GetFilterScripts()->OnGameModeExit();
	pNetGame->GetTimers()->DeleteForMode(&m_amx);

	if (m_bInitialised)
	{
		aux_FreeProgram(&m_amx);
		pPlugins->DoAmxUnload(&m_amx);
		amx_sampDbCleanup(&m_amx);
		amx_TimeCleanup(&m_amx);
		amx_FileCleanup(&m_amx);
		amx_StringCleanup(&m_amx);
		amx_FloatCleanup(&m_amx);
		amx_CoreCleanup(&m_amx);
	}
	m_bInitialised = false;
	m_bSleeping = false;
}

//----------------------------------------------------------------------------------

void CGameModeAMX::Frame(float fElapsedTime)
{
	if (!m_bInitialised)
		return;

	//if (m_pScriptTimers)
		//m_pScriptTimers->Process((DWORD)(fElapsedTime * 1000.0f));

	if (!m_bSleeping)
		return;

	if (m_fSleepTime > 0.0f)
	{
		m_fSleepTime -= fElapsedTime;
	}
	else
	{
		cell ret;
		int err = amx_Exec(&m_amx, &ret, AMX_EXEC_CONT);
		if (err == AMX_ERR_SLEEP)
		{
			m_bSleeping = true;
			m_fSleepTime = ((float)ret / 1000.0f);
		}
		else
		{
			m_bSleeping = false;
			AMXPrintError(this, &m_amx, err);
		}
	}
}

//----------------------------------------------------------------------------------

int CGameModeAMX::CallPublic(char* szFuncName)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, szFuncName, &idx))
		amx_Exec(&m_amx, &ret, idx);
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerConnect(playerid);
int CGameModeAMX::OnPlayerConnect(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerConnect", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerDisconnect(playerid, reason);
int CGameModeAMX::OnPlayerDisconnect(cell playerid, cell reason)
{
	//CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerDisconnect", &idx))
	{
		amx_Push(&m_amx, reason);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerSpawn(playerid);
int CGameModeAMX::OnPlayerSpawn(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerSpawn", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerDeath(playerid, killerid, reason);
int CGameModeAMX::OnPlayerDeath(cell playerid, cell killerid, cell reason)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerDeath", &idx))
	{
		amx_Push(&m_amx, reason);
		amx_Push(&m_amx, killerid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnVehicleSpawn(vehicleid);
int CGameModeAMX::OnVehicleSpawn(cell vehicleid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnVehicleSpawn", &idx))
	{
		amx_Push(&m_amx, vehicleid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnVehicleDeath(vehicleid, killerid);
int CGameModeAMX::OnVehicleDeath(cell vehicleid, cell killerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnVehicleDeath", &idx))
	{
		amx_Push(&m_amx, killerid);
		amx_Push(&m_amx, vehicleid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerText(playerid, text[]);
int CGameModeAMX::OnPlayerText(cell playerid, unsigned char * szText)
{
	CHECK_INIT();

	int idx;
	cell ret = 1;	// DEFAULT TO 1!
	int orig_strlen = strlen((char*)szText) + 1;

	if (!amx_FindPublic(&m_amx, "OnPlayerText", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&m_amx, &amx_addr, &phys_addr, (char*)szText, 0, 0);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
		amx_GetString((char*)szText, phys_addr, 0, orig_strlen);
		amx_Release(&m_amx, amx_addr);
	}

	if (ret && pNetGame->GetPlayerPool()->GetSlotState(playerid)) {
		pNetGame->GetPlayerPool()->GetAt(playerid)->Say(szText, strlen((char*)szText));
	}

	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerCommandText(playerid, cmdtext[]);
int CGameModeAMX::OnPlayerCommandText(cell playerid, unsigned char * szCommandText)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;
	int orig_strlen = strlen((char*)szCommandText);

	if(!pNetGame->GetPlayerPool()->GetSlotState(playerid))
		return (int)ret;

	if (!amx_FindPublic(&m_amx, "OnPlayerCommandText", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&m_amx, &amx_addr, &phys_addr, (char*)szCommandText, 0, 0);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
		amx_Release(&m_amx, amx_addr);
	}

	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerInfoChange(playerid);
int CGameModeAMX::OnPlayerInfoChange(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerInfoChange", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerRequestClass(playerid, classid);
int CGameModeAMX::OnPlayerRequestClass(cell playerid, cell classid)
{
	CHECK_INIT();

	int idx;
	cell ret = 1;	// DEFAULT TO 1!
	
	//if(!pNetGame->GetPlayerPool()->GetSlotState((BYTE)playerid))
		//return (int)ret;

	if (!amx_FindPublic(&m_amx, "OnPlayerRequestClass", &idx))
	{
		amx_Push(&m_amx, classid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerRequestSpawn(playerid);
int CGameModeAMX::OnPlayerRequestSpawn(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 1;	// DEFAULT TO 1!

	//if(!pNetGame->GetPlayerPool()->GetSlotState((BYTE)playerid))
		//return (int)ret;

	if (!amx_FindPublic(&m_amx, "OnPlayerRequestSpawn", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
int CGameModeAMX::OnPlayerEnterVehicle(cell playerid, cell vehicleid, cell ispassenger)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	//if(!pNetGame->GetPlayerPool()->GetSlotState((BYTE)playerid))
		//return (int)ret;

	if (!amx_FindPublic(&m_amx, "OnPlayerEnterVehicle", &idx))
	{
		amx_Push(&m_amx, ispassenger);
		amx_Push(&m_amx, vehicleid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerExitVehicle(playerid, vehicleid);
int CGameModeAMX::OnPlayerExitVehicle(cell playerid, cell vehicleid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;
	
	//if(!pNetGame->GetPlayerPool()->GetSlotState((BYTE)playerid))
		//return (int)ret;

	if (!amx_FindPublic(&m_amx, "OnPlayerExitVehicle", &idx))
	{
		amx_Push(&m_amx, vehicleid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerStateChange(playerid, newstate, oldstate);
int CGameModeAMX::OnPlayerStateChange(cell playerid, cell newstate, cell oldstate)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;
	
	//if(!pNetGame->GetPlayerPool()->GetSlotState((BYTE)playerid))
		//return (int)ret;

	if (!amx_FindPublic(&m_amx, "OnPlayerStateChange", &idx))
	{
		amx_Push(&m_amx, oldstate);
		amx_Push(&m_amx, newstate);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------
// forward OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);

int CGameModeAMX::OnPlayerInteriorChange(cell playerid, cell newid, cell oldid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;
	
	//if(!pNetGame->GetPlayerPool()->GetSlotState((BYTE)playerid))
		//return (int)ret;

	if (!amx_FindPublic(&m_amx, "OnPlayerInteriorChange", &idx))
	{
		amx_Push(&m_amx, oldid);
		amx_Push(&m_amx, newid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerEnterCheckpoint(playerid);
int CGameModeAMX::OnPlayerEnterCheckpoint(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;
	
	//if(!pNetGame->GetPlayerPool()->GetSlotState((BYTE)playerid))
		//return (int)ret;

	if (!amx_FindPublic(&m_amx, "OnPlayerEnterCheckpoint", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerLeaveCheckpoint(playerid);
int CGameModeAMX::OnPlayerLeaveCheckpoint(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerLeaveCheckpoint", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerEnterRaceCheckpoint(playerid);
int CGameModeAMX::OnPlayerEnterRaceCheckpoint(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerEnterRaceCheckpoint", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerLeaveRaceCheckpoint(playerid);
int CGameModeAMX::OnPlayerLeaveRaceCheckpoint(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerLeaveRaceCheckpoint", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
int CGameModeAMX::OnPlayerKeyStateChange(cell playerid, cell newkeys, cell oldkeys)
{
	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerKeyStateChange", &idx))
	{
		amx_Push(&m_amx, oldkeys);
		amx_Push(&m_amx, newkeys);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnRconCommand(cmd[]);
int CGameModeAMX::OnRconCommand(char* szCommand)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;
	int orig_strlen = strlen(szCommand);

	if (!amx_FindPublic(&m_amx, "OnRconCommand", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&m_amx, &amx_addr, &phys_addr, szCommand, 0, 0);
		amx_Exec(&m_amx, &ret, idx);
		amx_Release(&m_amx, amx_addr);
	}

	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnObjectMoved(objectid);
int CGameModeAMX::OnObjectMoved(cell objectid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnObjectMoved", &idx))
	{
		amx_Push(&m_amx, objectid);
		amx_Exec(&m_amx, &ret, idx);
	}

	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerObjectMoved(playerid, objectid);
int CGameModeAMX::OnPlayerObjectMoved(cell playerid, cell objectid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerObjectMoved", &idx))
	{
		amx_Push(&m_amx, objectid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}

	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerPickedUpPickup(playerid, pickupid);
int CGameModeAMX::OnPlayerPickedUpPickup(cell playerid, cell pickupid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerPickUpPickup", &idx))
	{
		amx_Push(&m_amx, pickupid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerExitedMenu(playerid);
int CGameModeAMX::OnPlayerExitedMenu(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerExitedMenu", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerSelectedMenuRow(playerid, row);
int CGameModeAMX::OnPlayerSelectedMenuRow(cell playerid, cell row)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerSelectedMenuRow", &idx))
	{
		amx_Push(&m_amx, row);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnVehicleRespray(playerid, vehicleid, color1, color2);
int CGameModeAMX::OnVehicleRespray(cell playerid, cell vehicleid, cell color1, cell color2)
{
	CHECK_INIT();
	int idx;
	cell ret = 1;

	if (!amx_FindPublic(&m_amx, "OnVehicleRespray", &idx))
	{
		amx_Push(&m_amx, color2);
		amx_Push(&m_amx, color1);
		amx_Push(&m_amx, vehicleid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnVehicleMod(playerid, vehicleid, componentid);
int CGameModeAMX::OnVehicleMod(cell playerid, cell vehicleid, cell componentid)
{
	CHECK_INIT();
	int idx;
	cell ret = 1;

	if (!amx_FindPublic(&m_amx, "OnVehicleMod", &idx))
	{
		amx_Push(&m_amx, componentid);
		amx_Push(&m_amx, vehicleid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

// forward OnEnterExitModShop(playerid, enterexit, interiorid);
int CGameModeAMX::OnEnterExitModShop(cell playerid, cell enterexit, cell interiorid)
{
	CHECK_INIT();
	int idx;
	cell ret = 1;

	if (!amx_FindPublic(&m_amx, "OnEnterExitModShop", &idx))
	{
		amx_Push(&m_amx, interiorid);
		amx_Push(&m_amx, enterexit);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

// forward OnVehiclePaintjob(playerid, vehicleid, paintjobid);
int CGameModeAMX::OnVehiclePaintjob(cell playerid, cell vehicleid, cell paintjobid)
{
	CHECK_INIT();
	int idx;
	cell ret = 1;

	if (!amx_FindPublic(&m_amx, "OnVehiclePaintjob", &idx))
	{
		amx_Push(&m_amx, paintjobid);
		amx_Push(&m_amx, vehicleid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------
// forward OnPlayerUpdate(playerid)

int CGameModeAMX::OnPlayerUpdate(cell playerid)
{
	CHECK_INIT();
	int idx;
	cell ret = 1;

	if(!amx_FindPublic(&m_amx, "OnPlayerUpdate", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

int CGameModeAMX::OnIncomingConnection(cell playerid, char* ip, cell port)
{
	CHECK_INIT();
	int idx = 0;
	cell ret = 1;
	if (!amx_FindPublic(&m_amx, "OnIncomingConnection", &idx))
	{
		cell amx_addr, * phys_addr;
		amx_Push(&m_amx, port);
		amx_PushString(&m_amx, &amx_addr, &phys_addr, ip, 0, 0);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
		amx_Release(&m_amx, amx_addr);
	}
	return (int)ret;
}

int CGameModeAMX::OnPlayerClickMap(cell playerid, float fX, float fY, float fZ)
{
	CHECK_INIT();

	int idx = 0;
	cell ret = 1;
	if (!amx_FindPublic(&m_amx, "OnPlayerClickMap", &idx))
	{
		amx_Push(&m_amx, amx_ftoc(fZ));
		amx_Push(&m_amx, amx_ftoc(fY));
		amx_Push(&m_amx, amx_ftoc(fX));
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

int CGameModeAMX::OnTrailerUpdate(cell playerid, cell vehicleid)
{
	CHECK_INIT();

	int idx = 0;
	cell ret = 1;
	if (!amx_FindPublic(&m_amx, "OnTrailerUpdate", &idx))
	{
		amx_Push(&m_amx, vehicleid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

int CGameModeAMX::OnRconLoginAttempt(char* szIP, char* szPassword, cell success)
{
	CHECK_INIT();
	int idx = 0;
	cell ret = 1;
	if (!amx_FindPublic(&m_amx, "OnRconLoginAttempt", &idx))
	{
		cell amx_addr1, amx_addr2, *phys_addr;
		amx_Push(&m_amx, success);
		amx_PushString(&m_amx, &amx_addr2, &phys_addr, szPassword, 0, 0);
		amx_PushString(&m_amx, &amx_addr1, &phys_addr, szIP, 0, 0);
		amx_Exec(&m_amx, &ret, idx);
		amx_Release(&m_amx, amx_addr1);
		amx_Release(&m_amx, amx_addr2);
	}
	return (int)ret;
}

void CGameModeAMX::OnPlayerBeginTyping(cell playerid)
{
	if (!m_bInitialised)
		return;

	int idx = 0;
	if (!amx_FindPublic(&m_amx, "OnPlayerBeginTyping", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, NULL, idx);
	}
}

void CGameModeAMX::OnPlayerEndTyping(cell playerid)
{
	if (!m_bInitialised)
		return;

	int idx = 0;
	if (!amx_FindPublic(&m_amx, "OnPlayerEndTyping", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, NULL, idx);
	}
}

int CGameModeAMX::OnPlayerStunt(cell playerid, cell vehicleid)
{
	CHECK_INIT();
	int idx = 0;
	if (!amx_FindPublic(&m_amx, "OnPlayerStunt", &idx))
	{
		amx_Push(&m_amx, vehicleid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, NULL, idx);
	}
	return 1;
}

void CGameModeAMX::OnClientCheckResponse(cell playerid, cell type, cell address, cell checksum)
{
	int idx = 0;

	if (!m_bInitialised)
		return;

	if (!amx_FindPublic(&m_amx, "OnClientCheckResponse", &idx))
	{
		amx_Push(&m_amx, checksum);
		amx_Push(&m_amx, address);
		amx_Push(&m_amx, type);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, NULL, idx);
	}
}

void CGameModeAMX::OnVehicleSirenStateChange(cell playerid, cell vehicleid, cell newstate)
{
	int idx = 0;

	if (!m_bInitialised)
		return;

	if (!amx_FindPublic(&m_amx, "OnVehicleSirenStateChange", &idx)) {
		amx_Push(&m_amx, newstate);
		amx_Push(&m_amx, vehicleid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, NULL, idx);
	}
}

void CGameModeAMX::OnVehicleDamageStatusUpdate(cell vehicleid, cell playerid)
{
	int idx = 0;

	if (!m_bInitialised)
		return;

	if (!amx_FindPublic(&m_amx, "OnVehicleDamageStatusUpdate", &idx)) {
		amx_Push(&m_amx, playerid);
		amx_Push(&m_amx, vehicleid);
		amx_Exec(&m_amx, NULL, idx);
	}
}
#pragma endregion
#pragma region CGameModeDLL
#ifdef WIN32


CGameModeDLL::CGameModeDLL()
{
	this->m_hDLL = NULL;
	this->m_bInitialised = false;
	this->m_bSleeping = false;
	this->m_fSleepTime = 0.0f;
}

CGameModeDLL::~CGameModeDLL()
{
}


bool CGameModeDLL::Load(char* pFileName)
{
#ifdef _DEBUG
	//Placed in a DEBUG block since this should never happen durring normal operation
	if (pFileName == nullptr) {
		throw "Null Reference Exception";
	}
#endif


	if (m_hDLL != NULL) {
		FreeLibrary((HMODULE)m_hDLL);
	}





	m_hDLL = (HANDLE)LoadLibraryEx(pFileName, NULL, NULL);//Using LoadLibraryEx instead of LoadLibrary for future proofing of the code
	if (m_hDLL == NULL) {//Obviously something went wrong while loading the DLL
		logprintf("There was an error loading the GameMode. GetLastError returned %d", GetLastError());


		switch (GetLastError()) {
		default:
#ifdef _DEBUG
			logprintf("Undocumented error code.");
#endif
			break;
		}
	}


	//Since this is a DLL there must be a check to se how compatible is the code to the SAMP server version
	//There could be mayor checks.
	//Since you are designing this from the ground up you could make a custom method of performing checks
	//But for now call the normal Plugin methods to determine what is needed






	pOnGameModeInit pOGI = (pOnGameModeInit)GetProcAddress((HMODULE)m_hDLL, "OnGameModeInit");
	if (pOGI != NULL) {
		pOGI();
	}

	return false;
}

void CGameModeDLL::Unload()
{
}

int CGameModeDLL::OnPlayerConnect(int playerid)
{
	return 0;
}

int CGameModeDLL::OnPlayerDisconnect(int playerid, int reason)
{
	return 0;
}

int CGameModeDLL::OnPlayerSpawn(int playerid)
{
	return 0;
}

int CGameModeDLL::OnPlayerDeath(int playerid, int killerid, int reason)
{
	return 0;
}

int CGameModeDLL::OnVehicleSpawn(int vehicleid)
{
	return 0;
}

int CGameModeDLL::OnVehicleDeath(int vehicleid, int killerid)
{
	return 0;
}

int CGameModeDLL::OnPlayerText(int playerid, unsigned char* szText)
{
	return 0;
}

int CGameModeDLL::OnPlayerCommandText(int playerid, unsigned char* szCommandText)
{
	return 0;
}

int CGameModeDLL::OnPlayerInfoChange(int playerid)
{
	return 0;
}

int CGameModeDLL::OnPlayerRequestClass(int playerid, int classid)
{
	return 0;
}

int CGameModeDLL::OnPlayerRequestSpawn(int playerid)
{
	return 0;
}

int CGameModeDLL::OnPlayerEnterVehicle(int playerid, int vehicleid, int ispassenger)
{
	return 0;
}

int CGameModeDLL::OnPlayerExitVehicle(int playerid, int vehicleid)
{
	return 0;
}

int CGameModeDLL::OnPlayerStateChange(int playerid, int newstate, int oldstate)
{
	return 0;
}

int CGameModeDLL::OnPlayerEnterCheckpoint(int playerid)
{
	return 0;
}

int CGameModeDLL::OnPlayerLeaveCheckpoint(int playerid)
{
	return 0;
}

int CGameModeDLL::OnPlayerEnterRaceCheckpoint(int playerid)
{
	return 0;
}

int CGameModeDLL::OnPlayerLeaveRaceCheckpoint(int playerid)
{
	return 0;
}

int CGameModeDLL::OnRconCommand(char* szCommand)
{
	return 0;
}

int CGameModeDLL::OnObjectMoved(int objectid)
{
	return 0;
}

int CGameModeDLL::OnPlayerObjectMoved(int playerid, int objectid)
{
	return 0;
}

int CGameModeDLL::OnPlayerPickedUpPickup(int playerid, int pickupid)
{
	return 0;
}

int CGameModeDLL::OnPlayerExitedMenu(int playerid)
{
	return 0;
}

int CGameModeDLL::OnPlayerSelectedMenuRow(int playerid, int row)
{
	return 0;
}

int CGameModeDLL::OnVehicleRespray(int playerid, int vehicleid, int color1, int color2)
{
	return 0;
}

int CGameModeDLL::OnVehicleMod(int playerid, int vehicleid, int componentid)
{
	return 0;
}

int CGameModeDLL::OnEnterExitModShop(int playerid, int enterexit, int interiorid)
{
	return 0;
}

int CGameModeDLL::OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid)
{
	return 0;
}

int CGameModeDLL::OnPlayerInteriorChange(int playerid, int newid, int oldid)
{
	return 0;
}

int CGameModeDLL::OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	return 0;
}

int CGameModeDLL::OnPlayerUpdate(int playerid)
{
	return 0;
}

int CGameModeDLL::OnIncomingConnection(int playerid, char* ip, int port)
{
	return 0;
}

int CGameModeDLL::OnPlayerClickMap(int playerid, float fX, float fY, float fZ)
{
	return 0;
}

int CGameModeDLL::OnTrailerUpdate(int playerid, int vehicleid)
{
	return 0;
}

int CGameModeDLL::OnRconLoginAttempt(char* szIP, char* szPassword, int success)
{
	return 0;
}

void CGameModeDLL::OnPlayerBeginTyping(int playerid)
{
}

void CGameModeDLL::OnPlayerEndTyping(int playerid)
{
}

int CGameModeDLL::OnPlayerStunt(int playerid, int vehicleid)
{
	return 0;
}

void CGameModeDLL::OnClientCheckResponse(int playerid, int type, int address, int checksum)
{
}

void CGameModeDLL::OnVehicleSirenStateChange(int playerid, int vehicleid, int newstate)
{
}

void CGameModeDLL::OnVehicleDamageStatusUpdate(int vehicleid, int playerid)
{
}

#endif
#pragma endregion