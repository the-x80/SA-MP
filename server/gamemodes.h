/*

	SA:MP Multiplayer Modification
	Copyright 2004-2005 SA:MP Team

	file:
		gamemodes.h
	desc:
		GameMode script functions and management header file. 

	Version: $Id: gamemodes.h,v 1.12 2006/04/15 18:58:19 spookie Exp $
*/

#ifndef SAMPSRV_GAMEMODES_H
#define SAMPSRV_GAMEMODES_H

extern char szGameModeFileName[256];

//----------------------------------------------------------------------------------

class CGameMode
{
private:
	bool m_bInitialised;
	bool m_bSleeping;
	float m_fSleepTime;

	//CScriptTimers* m_pScriptTimers;
public:
	CGameMode();
	~CGameMode();

	char* GetFileName() { return &szGameModeFileName[0]; };
	//CScriptTimers* GetTimers() { return m_pScriptTimers; };
	void* GetGameModePointer() { return nullptr; };

	virtual bool Load(char* pFileName);
	virtual void Unload();
	virtual void Frame(float fElapsedTime);
	virtual bool IsInitialised() { return m_bInitialised; };

//----------------------------------------------------------------------------------

	virtual int CallPublic(char* szFuncName);

	virtual int OnPlayerConnect(cell playerid);
	virtual int OnPlayerDisconnect(cell playerid, cell reason);
	virtual int OnPlayerSpawn(cell playerid);
	virtual int OnPlayerDeath(cell playerid, cell killerid, cell reason);
	virtual int OnVehicleSpawn(cell vehicleid);
	virtual int OnVehicleDeath(cell vehicleid, cell killerid);
	virtual int OnPlayerText(cell playerid, unsigned char * szText);
	virtual int OnPlayerCommandText(cell playerid, unsigned char * szCommandText);
	virtual int OnPlayerInfoChange(cell playerid);
	virtual int OnPlayerRequestClass(cell playerid, cell classid);
	virtual int OnPlayerRequestSpawn(cell playerid);
	virtual int OnPlayerEnterVehicle(cell playerid, cell vehicleid, cell ispassenger);
	virtual int OnPlayerExitVehicle(cell playerid, cell vehicleid);
	virtual int OnPlayerStateChange(cell playerid, cell newstate, cell oldstate);
	virtual int OnPlayerEnterCheckpoint(cell playerid);
	virtual int OnPlayerLeaveCheckpoint(cell playerid);
	virtual int OnPlayerEnterRaceCheckpoint(cell playerid);
	virtual int OnPlayerLeaveRaceCheckpoint(cell playerid);
	virtual int OnRconCommand(char* szCommand);
	virtual int OnObjectMoved(cell objectid);
	virtual int OnPlayerObjectMoved(cell playerid, cell objectid);
	virtual int OnPlayerPickedUpPickup(cell playerid, cell pickupid);
	virtual int OnPlayerExitedMenu(cell playerid);
	virtual int OnPlayerSelectedMenuRow(cell playerid, cell row);
	virtual int OnVehicleRespray(cell playerid, cell vehicleid, cell color1, cell color2);
	virtual int OnVehicleMod(cell playerid, cell vehicleid, cell componentid);
	virtual int OnEnterExitModShop(cell playerid, cell enterexit, cell interiorid);
	virtual int OnVehiclePaintjob(cell playerid, cell vehicleid, cell paintjobid);
	virtual int OnPlayerInteriorChange(cell playerid, cell newid, cell oldid);
	virtual int OnPlayerKeyStateChange(cell playerid, cell newkeys, cell oldkeys);
	virtual int OnPlayerUpdate(cell playerid);
	virtual int OnIncomingConnection(cell playerid, char* ip, cell port);
	virtual int OnPlayerClickMap(cell playerid, float fX, float fY, float fZ);
	virtual int OnTrailerUpdate(cell playerid, cell vehicleid);
	virtual int OnRconLoginAttempt(char* szIP, char* szPassword, cell success);
	virtual void OnPlayerBeginTyping(cell playerid);
	virtual void OnPlayerEndTyping(cell playerid);
	virtual int OnPlayerStunt(cell playerid, cell vehicleid);
	virtual void OnClientCheckResponse(cell playerid, cell type, cell address, cell checksum);
	virtual void OnVehicleSirenStateChange(cell playerid, cell vehicleid, cell newstate);
	virtual void OnVehicleDamageStatusUpdate(cell vehicleid, cell playerid);

private:
	//Helper methods go here.

};

class CGameModeAMX : public CGameMode{
private:
	AMX m_amx;
	bool m_bInitialised;
	bool m_bSleeping;
	float m_fSleepTime;

	//CScriptTimers* m_pScriptTimers;
public:
	CGameModeAMX();
	~CGameModeAMX();

	char* GetFileName() { return &szGameModeFileName[0]; };
	//CScriptTimers* GetTimers() { return m_pScriptTimers; };
	AMX* GetGameModePointer() { return &m_amx; };

	bool Load(char* pFileName) override;
	void Unload() override;
	void Frame(float fElapsedTime) override;
	bool IsInitialised()  override { return m_bInitialised; };

	//----------------------------------------------------------------------------------

	int CallPublic(char* szFuncName) override;

	int OnPlayerConnect(cell playerid) override;
	int OnPlayerDisconnect(cell playerid, cell reason) override;
	int OnPlayerSpawn(cell playerid) override;
	int OnPlayerDeath(cell playerid, cell killerid, cell reason) override;
	int OnVehicleSpawn(cell vehicleid) override;
	int OnVehicleDeath(cell vehicleid, cell killerid) override;
	int OnPlayerText(cell playerid, unsigned char* szText) override;
	int OnPlayerCommandText(cell playerid, unsigned char* szCommandText) override;
	int OnPlayerInfoChange(cell playerid) override;
	int OnPlayerRequestClass(cell playerid, cell classid) override;
	int OnPlayerRequestSpawn(cell playerid) override;
	int OnPlayerEnterVehicle(cell playerid, cell vehicleid, cell ispassenger) override;
	int OnPlayerExitVehicle(cell playerid, cell vehicleid) override;
	int OnPlayerStateChange(cell playerid, cell newstate, cell oldstate) override;
	int OnPlayerEnterCheckpoint(cell playerid) override;
	int OnPlayerLeaveCheckpoint(cell playerid) override;
	int OnPlayerEnterRaceCheckpoint(cell playerid) override;
	int OnPlayerLeaveRaceCheckpoint(cell playerid) override;
	int OnRconCommand(char* szCommand) override;
	int OnObjectMoved(cell objectid) override;
	int OnPlayerObjectMoved(cell playerid, cell objectid) override;
	int OnPlayerPickedUpPickup(cell playerid, cell pickupid) override;
	int OnPlayerExitedMenu(cell playerid) override;
	int OnPlayerSelectedMenuRow(cell playerid, cell row) override;
	int OnVehicleRespray(cell playerid, cell vehicleid, cell color1, cell color2) override;
	int OnVehicleMod(cell playerid, cell vehicleid, cell componentid) override;
	int OnEnterExitModShop(cell playerid, cell enterexit, cell interiorid) override;
	int OnVehiclePaintjob(cell playerid, cell vehicleid, cell paintjobid) override;
	int OnPlayerInteriorChange(cell playerid, cell newid, cell oldid) override;
	int OnPlayerKeyStateChange(cell playerid, cell newkeys, cell oldkeys) override;
	int OnPlayerUpdate(cell playerid) override;
	int OnIncomingConnection(cell playerid, char* ip, cell port) override;
	int OnPlayerClickMap(cell playerid, float fX, float fY, float fZ) override;
	int OnTrailerUpdate(cell playerid, cell vehicleid) override;
	int OnRconLoginAttempt(char* szIP, char* szPassword, cell success) override;
	void OnPlayerBeginTyping(cell playerid) override;
	void OnPlayerEndTyping(cell playerid) override;
	int OnPlayerStunt(cell playerid, cell vehicleid) override;
	void OnClientCheckResponse(cell playerid, cell type, cell address, cell checksum) override;
	void OnVehicleSirenStateChange(cell playerid, cell vehicleid, cell newstate) override;
	void OnVehicleDamageStatusUpdate(cell vehicleid, cell playerid) override;
};
#ifdef WIN32
class CGameModeDLL : public CGameMode{
private:
	HANDLE m_hDLL;

	bool m_bInitialised;
	bool m_bSleeping;
	float m_fSleepTime;
public:
	CGameModeDLL();
	~CGameModeDLL();



	bool Load(char* pFileName) override;
	void Unload() override;
	bool IsInitialized() { return m_bInitialised; }


	int OnPlayerConnect(int playerid) override;
	int OnPlayerDisconnect(int playerid, int reason) override;
	int OnPlayerSpawn(int playerid) override;
	int OnPlayerDeath(int playerid, int killerid, int reason) override;
	int OnVehicleSpawn(int vehicleid) override;
	int OnVehicleDeath(int vehicleid, int killerid) override;
	int OnPlayerText(int playerid, unsigned char* szText) override;
	int OnPlayerCommandText(int playerid, unsigned char* szCommandText) override;
	int OnPlayerInfoChange(int playerid) override;
	int OnPlayerRequestClass(int playerid, int classid) override;
	int OnPlayerRequestSpawn(int playerid) override;
	int OnPlayerEnterVehicle(int playerid, int vehicleid, int ispassenger) override;
	int OnPlayerExitVehicle(int playerid, int vehicleid) override;
	int OnPlayerStateChange(int playerid, int newstate, int oldstate) override;
	int OnPlayerEnterCheckpoint(int playerid) override;
	int OnPlayerLeaveCheckpoint(int playerid) override;
	int OnPlayerEnterRaceCheckpoint(int playerid) override;
	int OnPlayerLeaveRaceCheckpoint(int playerid) override;
	int OnRconCommand(char* szCommand) override;
	int OnObjectMoved(int objectid) override;
	int OnPlayerObjectMoved(int playerid, int objectid) override;
	int OnPlayerPickedUpPickup(int playerid, int pickupid) override;
	int OnPlayerExitedMenu(int playerid) override;
	int OnPlayerSelectedMenuRow(int playerid, int row) override;
	int OnVehicleRespray(int playerid, int vehicleid, int color1, int color2) override;
	int OnVehicleMod(int playerid, int vehicleid, int componentid) override;
	int OnEnterExitModShop(int playerid, int enterexit, int interiorid) override;
	int OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid) override;
	int OnPlayerInteriorChange(int playerid, int newid, int oldid) override;
	int OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys) override;
	int OnPlayerUpdate(int playerid) override;
	int OnIncomingConnection(int playerid, char* ip, int port) override;
	int OnPlayerClickMap(int playerid, float fX, float fY, float fZ) override;
	int OnTrailerUpdate(int playerid, int vehicleid) override;
	int OnRconLoginAttempt(char* szIP, char* szPassword, int success) override;
	void OnPlayerBeginTyping(int playerid) override;
	void OnPlayerEndTyping(int playerid) override;
	int OnPlayerStunt(int playerid, int vehicleid) override;
	void OnClientCheckResponse(int playerid, int type, int address, int checksum) override;
	void OnVehicleSirenStateChange(int playerid, int vehicleid, int newstate) override;
	void OnVehicleDamageStatusUpdate(int vehicleid, int playerid) override;
};
#endif
//----------------------------------------------------------------------------------

#endif

