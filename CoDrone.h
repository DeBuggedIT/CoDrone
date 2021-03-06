/*
  CoDrone.h - CoDrone library
  Copyright (C) 2014 RoboLink.  All rights reserved.
  LastUpdate : 2016-04-20
*/

#ifndef CoDrone_h
#define CoDrone_h
#include "Arduino.h"
#include <avr/interrupt.h>

/***********************************************************************/


/***********************************************************************/
//////////////////////////typedef///////////////////////////////////////
/***********************************************************************/

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

/***********************************************************************/
////////////////////////Serial Select////////////////////////////////////
/***********************************************************************/
#if defined(UBRRH) || defined(UBRR0H)
#define FIND_HWSERIAL0
#endif

#if defined(UBRR1H)
#define FIND_HWSERIAL1
#endif

#if defined (FIND_HWSERIAL1)	//Serial Other Setting
#define DRONE_SERIAL 		Serial1		//drone serial
#define DEBUG_SERIAL    Serial		//debug serial1

#else	//Serial Smart Setting
#define DRONE_SERIAL 		Serial		//drone serial	
#define DEBUG_SERIAL    Serial1		//debug serial1

#endif

/***********************************************************************/
////////////////////////////HEADER///////////////////////////////////////
/***********************************************************************/
//START CODE
#define START1    	0x0A
#define START2   		0x55

/***********************************************************************/

#define MAX_PACKET_LENGTH 	100

/***********************************************************************/

#define	SEND_CHECK_TIME    		3

/***********************************************************************/

#define ROLL								CoDrone.roll
#define PITCH								CoDrone.pitch
#define YAW									CoDrone.yaw
#define THROTTLE						CoDrone.throttle

#define STATE								CoDrone.state
#define SEND_INTERVAL				CoDrone.SendInterval
#define ANALOG_OFFSET				CoDrone.analogOffset
#define BATTERY							CoDrone.battery
#define RSSI								CoDrone.rssi

#define AttitudeROLL				CoDrone.attitudeRoll
#define AttitudePITCH				CoDrone.attitudePitch
#define AttitudeYAW					CoDrone.attitudeYaw

/***********************************************************************/

#define DiscoverStop  			cType_LinkDiscoverStop
#define DiscoverStart  			cType_LinkDiscoverStart

#define PollingStop					cType_LinkRssiPollingStop
#define PollingStart				cType_LinkRssiPollingStart

#define	PAIRING							CoDrone.pairing

#define LinkModeMute 				LinkBroadcast_Mute
#define LinkModeActive			LinkBroadcast_Active
#define LinkModePassive 		LinkBroadcast_Passive

#define	NearbyDrone    			1
#define	ConnectedDrone  		2
#define AddressInputDrone 	3

//eeprom address
#define	EEP_AddressCheck   	10
#define	EEP_AddressFirst  	11
#define	EEP_AddressEnd  		15

/////////////////////////////////////////////////////////////////////////

#define FREE_PLAY					0
#define TEAM_RED					1
#define TEAM_BLUE					2
#define TEAM_GREEN				3
#define TEAM_YELLOW				4

#define MAX_ENERGY				8
/**********************	IR DATA****************************************/

#define FREE_MISSILE			0xaa01
#define RED_MISSILE				0xbb01
#define BLUE_MISSILE			0xcc01
#define GREEN_MISSILE			0xdd01
#define YELLOW_MISSILE		0xee01

/***********************************************************************/

#define Flight 						dMode_Flight
#define FlightNoGuard			dMode_FlightNoGuard,
#define FlightFPV					dMode_FlightFPV
#define Drive 				 		dMode_Drive
#define DriveFPV					dMode_DriveFPV

#define Absolute 					cSet_Absolute
#define Relative		 			cSet_Relative

#define TakeOff 					fEvent_TakeOff
#define FlipFront					fEvent_FlipFront
#define FlipRear					fEvent_FlipRear
#define FlipLeft					fEvent_flipLeft
#define FlipRight					fEvent_FlipRight
#define Stop							fEvent_Stop
#define Landing						fEvent_Landing
#define TurnOver					fEvent_TurnOver
#define Shot							fEvent_Shot
#define UnderAttack				fEvent_UnderAttack
#define Square						fEvent_Square
#define CircleLeft				fEvent_CircleLeft
#define CircleRight				fEvent_CircleRight
#define Rotate180					fEvent_Rotate180

#define RollIncrease			trim_RollIncrease
#define RollDecrease			trim_RollDecrease
#define PitchIncrease			trim_PitchIncrease
#define PitchDecrease			trim_PitchDecrease
#define YawIncrease				trim_YawIncrease
#define YawDecrease				trim_YawDecrease
#define ThrottleIncrease	trim_ThrottleIncrease
#define ThrottleDecrease	trim_ThrottleDecrease

/***********************************************************************/
/////////////////////////LINK MODULE/////////////////////////////////////
/***********************************************************************/
enum ModeLink
{
	linkMode_None = 0,	 	 	///< ????
	linkMode_Boot,	 	 	 		///< ???? 	 	
	linkMode_Ready,	 		 		///< ????(???? ??)
	linkMode_Connecting,	 	///< ???? ???? ??
	linkMode_Connected,	 	 	///< ???? ???? ????
	linkMode_Disconnecting,	///< ???? ???? ???? ??
	linkMode_ReadyToReset,	///< ???? ????(1?? ???? ???? ????)	
	linkMode_EndOfType
};

enum ModeLinkBroadcast
{
	LinkBroadcast_None = 0, ///< ????
	LinkBroadcast_Mute, 		///< LINK ???? ?????? ???? ???? . ???????? ?????? ????????
	LinkBroadcast_Active, 	///< ?????? ???? ???? . ???? ???? ?????? ????
	LinkBroadcast_Passive, 	///< ?????? ???? ???? . ???? ???? ?????? ???????? ????
	LinkBroadcast_EndOfType
};

enum EventLink
	{
		linkEvent_None = 0,									///< ????
		
		linkEvent_SystemReset,							///< ?????? ????
		
		linkEvent_Initialized,							///< ???? ?????? ????
		
		linkEvent_Scanning,									///< ???? ???? ????
		linkEvent_ScanStop,									///< ???? ???? ????

		linkEvent_FoundDroneService,				///< ???? ?????? ???? ????

		linkEvent_Connecting,								///< ???? ???? ????		
		linkEvent_Connected,								///< ???? ????

		linkEvent_ConnectionFaild,					///< ???? ????
		linkEvent_ConnectionFaildNoDevices,	///< ???? ???? - ?????? ????
		linkEvent_ConnectionFaildNotReady,	///< ???? ???? - ???? ?????? ????

		linkEvent_PairingStart,							///< ?????? ????
		linkEvent_PairingSuccess,						///< ?????? ????
		linkEvent_PairingFaild,							///< ?????? ????

		linkEvent_BondingSuccess,						///< Bonding ????

		linkEvent_LookupAttribute,					///< ???? ?????? ?? ???? ????(GATT Event ????)

		linkEvent_RssiPollingStart,					///< RSSI ???? ????
		linkEvent_RssiPollingStop,					///< RSSI ???? ????

		linkEvent_DiscoverService,										///< ?????? ????
		linkEvent_DiscoverCharacteristic,							///< ???? ????
		linkEvent_DiscoverCharacteristicDroneData,		///< ???? ????
		linkEvent_DiscoverCharacteristicDroneConfig,	///< ???? ????
		linkEvent_DiscoverCharacteristicUnknown,			///< ???? ????
		linkEvent_DiscoverCCCD,				///< CCCD ????

		linkEvent_ReadyToControl,			///< ???? ???? ????

		linkEvent_Disconnecting,			///< ???? ???? ???? ????
		linkEvent_Disconnected,				///< ???? ???? ???? ????

		linkEvent_GapLinkParamUpdate,	///< GAP_LINK_PARAM_UPDATE_EVENT

		linkEvent_RspReadError,				///< RSP ???? ????
		linkEvent_RspReadSuccess,			///< RSP ???? ????

		linkEvent_RspWriteError,			///< RSP ???? ????
		linkEvent_RspWriteSuccess,		///< RSP ???? ????

		linkEvent_SetNotify,					///< Notify ??????

		linkEvent_Write,							///< ?????? ???? ??????

		EndOfType
	};


/***********************************************************************/
//////////////////////////////DRONE/////////////////////////////////////
/***********************************************************************/
enum DataType
{
	dType_None = 0, 					///< ????
	
	// ?????? ????
	dType_Ping, 							///< ???? ????(reserve)
	dType_Ack, 								///< ?????? ?????? ???? ????
	dType_Error, 							///< ????(reserve, ???? ???????? ?????? ????)
	dType_Request, 						///< ?????? ?????? ?????? ????
	dType_DeviceName, 				///< ?????? ???? ????
	
	// ????, ????
	dType_Control = 0x10, 		///< ????
	dType_Command, 						///< ????
	dType_Command2, 					///< ???? ????(2???? ?????? ?????? ????)
	DType_Command3, 					///< ???? ????(3???? ?????? ?????? ????)
	
	// LED
	dType_LedMode = 0x20, 		///< LED ???? ????
	dType_LedMode2, 					///< LED ???? 2?? ????
	dType_LedModeCommand, 		///< LED ????, ??????
	dType_LedModeCommandIr, 	///< LED ????, ??????, IR ?????? ????
	dType_LedModeColor, 			///< LED ???? 3?? ???? ????
	dType_LedModeColor2, 			///< LED ???? 3?? ???? ???? 2??
	dType_LedEvent, 					///< LED ??????
	dType_LedEvent2, 					///< LED ?????? 2??,
	dType_LedEventCommand, 		///< LED ??????, ??????
	dType_LedEventCommandIr,	///< LED ??????, ??????, IR ?????? ????
	dType_LedEventColor, 			///< LED ?????? 3?? ???? ????
	dType_LedEventColor2, 		///< LED ?????? 3?? ???? ???? 2??
	
	// ????
	dType_Address = 0x30, 		///< IEEE address
	dType_State, 							///< ?????? ????(???? ????, ????????, ????????)
	dType_Attitude, 					///< ?????? ????(Vector)
	dType_GyroBias,						///< ?????? ???????? ??(Vector)
	dType_TrimAll, 						///< ???? ???? (????+????)?
	dType_TrimFlight,					///< ???? ????
	dType_TrimDrive, 					///< ???? ????
			
	// ?????? ??????	
	dType_IrMessage = 0x40, 			///< IR ?????? ??????
		
	// ????
	dType_ImuRawAndAngle = 0x50, 	///< IMU Raw + Angle
	dType_Pressure, 							///< ???? ???? ??????
	dType_ImageFlow, 							///< ImageFlow
	dType_Button, 								///< ???? ????
	dType_Batery, 								///< ??????
	dType_Motor, 									///< ???? ???? ?? ???? ???? ?? ????
	dType_Temperature, 						///< ????
	
	// ???? ????
	dType_LinkState = 0xE0,				///< ???? ?????? ????
	dType_LinkEvent,							///< ???? ?????? ??????
	dType_LinkEventAddress,				///< ???? ?????? ?????? + ????
	dType_LinkRssi,								///< ?????? ?????? ?????? RSSI??
	dType_LinkDiscoveredDevice,		///< ?????? ????
	dType_LinkPasscode,          	///< ?????? ???? ?????? ???? ????
	dType_StringMessage = 0xD0, 	///< ?????? ??????
	dType_EndOfType
};

/***********************************************************************/
enum CommandType
{
	cType_None = 0, 								///< ?????? ????
	
	// ????	
	cType_ModeDrone = 0x10, 				///< ???? ???? ???? ????
	
	// ????
	cType_Coordinate = 0x20, 				///< ???? ???? ????
	cType_Trim, 										///< ???? ????
	cType_FlightEvent, 							///< ???? ?????? ????
	cType_DriveEvent, 							///< ???? ?????? ????
	cType_Stop, 										///< ????
	cType_ResetHeading = 0x50, 			///< ?????? ????(???????? ???? ?? ?? ???? heading?? 0???? ????)
	cType_ClearGyroBiasAndTrim, 		///< ?????? ?????????? ???? ???? ??????
	
	// ????
	cType_PairingActivate = 0x80, 	///< ?????? ??????
	cType_PairingDeactivate, 				///< ?????? ????????
	cType_TerminateConnection, 			///< ???? ????
	
	// ????
	cType_Request = 0x90, 					///< ?????? ?????? ?????? ????
	
	// ???? ????
	cType_LinkModeBroadcast = 0xE0, ///< LINK ?????? ???? ????
	cType_LinkSystemReset, 					///< ?????? ??????
	cType_LinkDiscoverStart, 				///< ???? ???? ????
	cType_LinkDiscoverStop, 				///< ???? ???? ????
	cType_LinkConnect, 							///< ????
	cType_LinkDisconnect, 					///< ???? ????
	cType_LinkRssiPollingStart, 		///< RSSI ???? ????
	cType_LinkRssiPollingStop, 			///< RSSI ???? ????

	cType_EndOfType
};

/***********************************************************************/
enum ModeDrone
{
	dMode_None = 0, 			///< ????
	dMode_Flight = 0x10, 	///< ???? ????(???? ????)
	dMode_FlightNoGuard, 	///< ???? ????(???? ????)
	dMode_FlightFPV, 			///< ???? ????(FPV)
	dMode_Drive = 0x20, 	///< ???? ????
	dMode_DriveFPV, 			///< ???? ????(FPV)
	dMode_Test = 0x30, 		///< ?????? ????
	dMode_EndOfType
};

/***********************************************************************/
enum ModeVehicle
{
	vMode_None = 0,
	vMode_Boot, 					///< ????
	vMode_Wait, 					///< ???? ???? ????
	vMode_Ready, 					///< ???? ????
	vMode_Running, 				///< ???? ???? ????
	vMode_Update, 				///< ?????? ????????
	vMode_UpdateComplete,	///< ?????? ???????? ????
	vMode_Error, 					///< ????
	vMode_EndOfType
};

/***********************************************************************/
enum ModeFlight
{
	fMode_None = 0,
	fMode_Ready, 					///< ???? ????
	fMode_TakeOff, 				///< ???? (Flight?? ????????)
	fMode_Flight, 				///< ????
	fMode_Flip, 					///< ????
	fMode_Stop, 					///< ???? ????
	fMode_Landing, 				///< ????
	fMode_Reverse, 				///< ??????
	fMode_Accident, 			///< ???? (Ready?? ????????)
	fMode_Error, 					///< ????
	fMode_EndOfType
};

/***********************************************************************/
enum ModeDrive
{
	dvMode_None = 0,
	dvMode_Ready, 				///< ????
	dvMode_Start, 				///< ????
	dvMode_Drive, 				///< ????
	dvMode_Stop, 					///< ???? ????
	dvMode_Accident, 			///< ???? (Ready?? ????????)
	dvMode_Error, 				///< ????
	dvMode_EndOfType
};

/***********************************************************************/
enum SensorOrientation
{
	senOri_None = 0,
	senOri_Normal, 				///< ????
	senOri_ReverseStart, 	///< ???????? ????
	senOri_Reverse, 			///< ??????
	senOri_EndOfType
};

/***********************************************************************/
enum Coordinate
{
	cSet_None = 0, 				///< ????
	cSet_Absolute, 				///< ???? ??????
	cSet_Relative, 				///< ???? ??????
	cSet_EndOfType
};

/***********************************************************************/

enum Trim
{
	trim_None = 0, 					///< ????
	trim_RollIncrease, 			///< Roll ????
	trim_RollDecrease, 			///< Roll ????
	trim_PitchIncrease, 		///< Pitch ????
	trim_PitchDecrease, 		///< Pitch ????
	trim_YawIncrease, 			///< Yaw ????
	trim_YawDecrease, 			///< Yaw ????
	trim_ThrottleIncrease, 	///< Throttle ????
	trim_ThrottleDecrease, 	///< Throttle ????
	trim_EndOfType
};

/***********************************************************************/

enum FlightEvent
{
	fEvent_None = 0, 			///< ????
	fEvent_TakeOff, 			///< ????
	fEvent_FlipFront, 		///< ????
	fEvent_FlipRear, 			///< ????
	fEvent_flipLeft, 			///< ????
	fEvent_FlipRight, 		///< ????
	fEvent_Stop, 					///< ????
	fEvent_Landing, 			///< ????
	fEvent_TurnOver, 			///< ??????
	fEvent_Shot, 					///< ???????? ?? ?? ??????
	fEvent_UnderAttack, 	///< ???????? ???? ?? ??????
	fEvent_Square, 				///< ?????? ????
	fEvent_CircleLeft, 		///< ???????? ????
	fEvent_CircleRight, 	///< ?????????? ????
	fEvent_Rotate180,			///< 180?? ????
	fEvent_EndOfType
};

enum DriveEvent
{
	dEvent_None = 0,
	dEvent_Ready, 				///< ????
	dEvent_Start, 				///< ????
	dEvent_Drive, 				///< ????
	dEvent_Stop, 					///< ???? ????
	dEvent_Accident, 			///< ???? (Ready?? ????????)
	dEvent_Error, 				///< ????
	dEvent_EndOfType
};

/***********************************************************************/
enum Request
{		
	// ????
	Req_Address = 0x30, 				///< IEEE address
	Req_State, 									///< ?????? ????(???? ????, ????????, ????????)
	Req_Attitude, 							///< ?????? ????(Vector)
	Req_GyroBias, 							///< ?????? ???????? ??(Vector)
	Req_TrimAll, 								///< ???? ????
	Req_TrimFlight, 						///< ???? ????
	Req_TrimDrive, 							///< ???? ????
		
	// ????
	Req_ImuRawAndAngle = 0x50, 	///< IMU Raw + Angle
	Req_Pressure, 							///< ???? ???? ??????
	Req_ImageFlow, 							///< ImageFlow
	Req_Button, 								///< ???? ????
	Req_Batery, 								///< ??????
	Req_Motor, 									///< ???? ???? ?? ???? ???? ?? ????
	Req_Temperature, 						///< ????
	Req_EndOfType
};

/***********************************************************************/
enum ModeLight
{
  Light_None,
  WaitingForConnect, 					///< ???? ???? ????
  Connected,
  
  EyeNone = 0x10,
  EyeHold, 										///< ?????? ?????? ???? ??
  EyeMix, 										///< ?????????? LED ?? ????
  EyeFlicker, 								///< ??????
  EyeFlickerDouble, 					///< ??????(?? ?? ???????? ?????? ???????? ????)
  EyeDimming, 								///< ???? ???????? ?????? ??????
  
  ArmNone = 0x40,
  ArmHold, 										///< ?????? ?????? ???? ??
  ArmMix, 										///< ?????????? LED ?? ????
  ArmFlicker, 								///< ??????
  ArmFlickerDouble, 					///< ??????(?? ?? ???????? ?????? ???????? ????)
  ArmDimming, 								///< ???? ???????? ?????? ??????
  ArmFlow, 										///< ?????? ???? ????
  ArmFlowReverse, 						///< ?????? ?????? ????
  EndOfLedMode
};

/***********************************************************************/
enum Colors
{
	AliceBlue, AntiqueWhite, Aqua,
	Aquamarine, Azure, Beige,
	Bisque, Black, BlanchedAlmond,
	Blue, BlueViolet, Brown,
	BurlyWood, CadetBlue, Chartreuse,
	Chocolate, Coral, CornflowerBlue,
	Cornsilk, Crimson, Cyan,
	DarkBlue, DarkCyan, DarkGoldenRod,
	DarkGray, DarkGreen, DarkKhaki,
	DarkMagenta, DarkOliveGreen, DarkOrange,
	DarkOrchid, DarkRed, DarkSalmon,
	DarkSeaGreen, DarkSlateBlue, DarkSlateGray,
	DarkTurquoise, DarkViolet, DeepPink,
	DeepSkyBlue, DimGray, DodgerBlue,
	FireBrick, FloralWhite, ForestGreen,
	Fuchsia, Gainsboro, GhostWhite,
	Gold, GoldenRod, Gray,
	Green, GreenYellow, HoneyDew,
	HotPink, IndianRed, Indigo,
	Ivory, Khaki, Lavender,
	LavenderBlush, LawnGreen, LemonChiffon,
	LightBlue, LightCoral, LightCyan,
	LightGoldenRodYellow, LightGray, LightGreen,
	LightPink, LightSalmon, LightSeaGreen,
	LightSkyBlue, LightSlateGray, LightSteelBlue,
	LightYellow, Lime, LimeGreen,
	Linen, Magenta, Maroon,
	MediumAquaMarine, MediumBlue, MediumOrchid,
	MediumPurple, MediumSeaGreen, MediumSlateBlue,
	MediumSpringGreen, MediumTurquoise, MediumVioletRed,
	MidnightBlue, MintCream, MistyRose,
	Moccasin, NavajoWhite, Navy,
	OldLace, Olive, OliveDrab,
	Orange, OrangeRed, Orchid,
	PaleGoldenRod, PaleGreen, PaleTurquoise,
	PaleVioletRed, PapayaWhip, PeachPuff,
	Peru, Pink, Plum,
	PowderBlue, Purple, RebeccaPurple,
	Red, RosyBrown, RoyalBlue,
	SaddleBrown, Salmon, SandyBrown,
	SeaGreen, SeaShell, Sienna,
	Silver, SkyBlue, SlateBlue,
	SlateGray, Snow, SpringGreen,
	SteelBlue, Tan, Teal,
	Thistle, Tomato, Turquoise,
	Violet, Wheat, White,
	WhiteSmoke, Yellow, YellowGreen,
	EndOfColor
};

/***********************************************************************/

class CoDroneClass
{
public:

	CoDroneClass(void);

/////////////////////////////////////////////////////////////////////////

	void begin(long baud);
	
	void Receive(void);
	
	void Control();
	void Control(int interval);

	void Send_Command(int sendCommand, int sendOption);	
	void Send_Processing(byte _data[], byte _length, byte _crc[]);
	
/////////////////////////////////////////////////////////////////////////

	void LinkReset();
	void Send_LinkState();
	void Send_LinkModeBroadcast(byte mode);
	
/////////////////////////////////////////////////////////////////////////
	
	void AutoConnect(byte mode);
  void AutoConnect(byte mode, byte address[]);	
	void Send_ConnectAddressInputDrone(byte address[]);
	void Send_ConnectConnectedDrone();
	void Send_ConnectNearbyDrone();	
	void Send_Connect(byte index);
	void Send_Disconnect();		
	void Send_Discover(byte action);
	void Send_Check(byte _data[], byte _length, byte _crc[]);

/////////////////////////////////////////////////////////////////////////

	void Send_Ping();
	void Send_ResetHeading();			
	void Send_RSSI_Polling(byte action);	
	void Send_DroneMode(byte event);
	void Send_Coordinate(byte mode);	
	void Send_ClearGyroBiasAndTrim();		
	void DroneModeChange(byte event);			
	void FlightEvent(byte event);
	void DriveEvent(byte event);
	
/////////////////////////////////////////////////////////////////////////

	void BattleShooting();
	void BattleReceive();
	void BattleBegin(byte teamSelect);	
	void BattleDamageProcess();	
	
/////////////////////////////////////////////////////////////////////////
		
	void Request_DroneState();	
	void Request_DroneAttitude();
	void Request_DroneGyroBias();	
	
	void Request_TrimAll();
	void Request_TrimFlight();
	void Request_TrimDrive();	
	
	void Request_ImuRawAndAngle();
	void Request_Pressure();
	void Request_ImageFlow();
	void Request_Button();	
	void Request_Battery();	
	void Request_Motor();	
	void Request_Temperature();
	
/////////////////////////////////////////////////////////////////////////

	void Set_Trim(byte event);
	void Set_TrimReset();
	void Set_TrimAll(int _roll, int _pitch, int _yaw, int _throttle, int _wheel);
	void Set_TrimFlight(int _roll, int _pitch, int _yaw, int _throttle);
	void Set_TrimDrive(int _wheel);

/////////////////////////////////////////////////////////////////////////

	void LedColor(byte sendMode, byte sendColor, byte sendInterval);
	void LedColor(byte sendMode, byte r, byte g, byte b, byte sendInterval);
	void LedColor(byte sendMode, byte sendColor[], byte sendInterval);
	
	void LedEvent(byte sendMode, byte sendColor, byte sendInterval, byte sendRepeat);
	void LedEvent(byte sendMode, byte sendColor[], byte sendInterval, byte sendRepeat);
	void LedEvent(byte sendMode, byte r, byte g, byte b, byte sendInterval, byte sendRepeat);
	
/////////////////////////////////////////////////////////////////////////
			
	void LinkStateCheck();
	void ReceiveEventCheck();
	int LowBatteryCheck(byte value);
	void DisplayRSSI();
	
/////////////////////////////////////////////////////////////////////////

	void LED_PORTC(int value);
	void LED_DDRC(int value);
	void LED_Move_Radar(byte display);
	void LED_Start();
	void LED_Move_Slide();
	void LED_Connect();
	void LED_Standard();
	void LED_Blink(int time, int count);
	
/////////////////////////////////////////////////////////////////////////

	unsigned short CRC16_Make(unsigned char *buf, int len); //CRC16-CCITT Format
	boolean CRC16_Check(unsigned char data[], int len, unsigned char crc[]);
	
/////////////////////////////////////////////////////////////////////////

	void PrintDroneAddress();	
	void DisplayAddress(byte count);
	
	void ReadSensor(void);
	void PrintSensor(void);
	
/////////////////////////////////////////////////////////////////////////
	
	void ButtonPreesHoldWait(int button);
	void ButtonPreesHoldWait(int button1, int button2);	
	
	int AnalogScaleChange(int analogValue);			

/////////////////////////////////////////////////////////////////////////

	boolean TimeCheck(word interval); 						//milliseconds
	boolean TimeOutSendCheck(word interval); //milliseconds		
	boolean TimeCheckBuzz(word interval); 				//microseconds
	
/////////////////////////////////////////////////////////////////////////

	void Buzz(long frequency, int tempo);
	void BeepWarning(int count);

/////////////////////////////////////////////////////////////////////////

	byte cmdBuff[MAX_PACKET_LENGTH];
	byte dataBuff[MAX_PACKET_LENGTH];
	byte crcBuff[2];
	
	byte checkHeader;
	int cmdIndex;
	int receiveDtype;
	int receiveLength;
	int receiveEventState;
	int receiveLinkState;
	int receiveLikMode;
	int receiveComplete;
	int receiveCRC;
			
/////////////////////////////////////////////////////////////////////////

	byte displayMode;	//smar inventor : default 1
	byte debugMode;		//smar inventor : default 0
	
	byte discoverFlag;
	byte connectFlag;
			
	boolean pairing;
	
	int SendInterval; //millis seconds		
	int analogOffset;
	byte displayLED;

	byte timeOutRetry;
	
	byte sendCheckFlag;
	
	byte receiveAttitudeSuccess;
	
	int energy;
	
	byte team;
	unsigned long weapon;
	
/////////////////////////////////////////////////////////////////////////
	
	byte devCount;
	byte devFind[3];
	
	int devRSSI0;
	int devRSSI1;
	int devRSSI2;
		
	byte devName0[20];
	byte devName1[20];
	byte devName2[20];
		
	byte devAddress0[6];
	byte devAddress1[6];
	byte devAddress2[6];
	
	byte devAddressBuf[6];
	byte devAddressConnected[6];
	
/////////////////////////////////////////////////////////////////////////
	
	int roll;
	int pitch;
	int yaw;
	int throttle;
		
	int attitudeRoll;
	int attitudePitch;
	int attitudeYaw;
	
/////////////////////////////////////////////////////////////////////////
	
	int linkState;
	int rssi;
	byte battery;
		
	byte irMassageDirection;
  unsigned long	irMassageReceive;
	
	byte droneState[7];	
	byte droneIrMassage[5];	
	
	byte droneAttitude[6];
	byte droneGyroBias[6];
	byte droneTrimAll[10];		
	byte droneTrimFlight[8];
	byte droneTrimDrive[2];
	byte droneImuRawAndAngle[9];
	byte dronePressure[16];	
	byte droneImageFlow[8];
	byte droneButton[1];
	byte droneBattery[16];
	byte droneMotor[4];
	byte droneTemperature[8];

/////////////////////////////////////////////////////////////////////////

		long PreviousMillis;
		
/////////////////////////////////////////////////////////////////////////
private:
	long PreviousBuzz;		

	long timeOutSendPreviousMillis;
};

extern CoDroneClass CoDrone;

#endif 