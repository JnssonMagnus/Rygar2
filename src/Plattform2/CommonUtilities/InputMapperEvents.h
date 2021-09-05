#pragma once
namespace Input
{
	enum class eInputState
	{
		ePressed,
		eDown,
		eUp
	};

	enum class eInputEvent
	{
		eDash,
		eUseHook,
		eUseItem,
		eFire,
		eFireGun1,
		eFireGun2,
		eTeleport,
		eReject, 
		eRestart,
		eScreenshot,
		eJump,
		eMoveRight,
		eMoveLeft,
		eDodge,
		eDown,
		ePickUp,
		eAimX,
		eAimY,
		eExit,
		eCaptureMouse,
		eCycleWeapons,
	};

	enum eInputAction
	{
		eKeyESCAPE        =  0x01,
		eKey1             =  0x02,
		eKey2             =  0x03,
		eKey3             =  0x04,
		eKey4             =  0x05,
		eKey5             =  0x06,
		eKey6             =  0x07,
		eKey7             =  0x08,
		eKey8             =  0x09,
		eKey9             =  0x0A,
		eKey0             =  0x0B,
		eKeyMINUS         =  0x0C,    /* - on main keyboard */
		eKeyEQUALS        =  0x0D,
		eKeyBACK          =  0x0E,    /* backspace */
		eKeyTAB           =  0x0F,
		eKeyQ             =  0x10,
		eKeyW             =  0x11,
		eKeyE             =  0x12,
		eKeyR             =  0x13,
		eKeyT             =  0x14,
		eKeyY             =  0x15,
		eKeyU             =  0x16,
		eKeyI             =  0x17,
		eKeyO             =  0x18,
		eKeyP             =  0x19,
		eKeyLBRACKET      =  0x1A,
		eKeyRBRACKET      =  0x1B,
		eKeyRETURN        =  0x1C,    /* Enter on main keyboard */
		eKeyLCONTROL      =  0x1D,
		eKeyA             =  0x1E,
		eKeyS             =  0x1F,
		eKeyD             =  0x20,
		eKeyF             =  0x21,
		eKeyG             =  0x22,
		eKeyH             =  0x23,
		eKeyJ             =  0x24,
		eKeyK             =  0x25,
		eKeyL             =  0x26,
		eKeySEMICOLON     =  0x27,
		eKeyAPOSTROPHE    =  0x28,
		eKeyGRAVE         =  0x29,    /* accent grave */
		eKeyLSHIFT        =  0x2A,
		eKeyBACKSLASH     =  0x2B,
		eKeyZ             =  0x2C,
		eKeyX             =  0x2D,
		eKeyC             =  0x2E,
		eKeyV             =  0x2F,
		eKeyB             =  0x30,
		eKeyN             =  0x31,
		eKeyM             =  0x32,
		eKeyCOMMA         =  0x33,
		eKeyPERIOD        =  0x34,    /* . on main keyboard */
		eKeySLASH         =  0x35,    /* / on main keyboard */
		eKeyRSHIFT        =  0x36,
		eKeyMULTIPLY      =  0x37,    /* * on numeric keypad */
		eKeyLMENU         =  0x38,    /* left Alt */
		eKeySPACE         =  0x39,
		eKeyCAPITAL       =  0x3A,
		eKeyF1            =  0x3B,
		eKeyF2            =  0x3C,
		eKeyF3            =  0x3D,
		eKeyF4            =  0x3E,
		eKeyF5            =  0x3F,
		eKeyF6            =  0x40,
		eKeyF7            =  0x41,
		eKeyF8            =  0x42,
		eKeyF9            =  0x43,
		eKeyF10           =  0x44,
		eKeyNUMLOCK       =  0x45,
		eKeySCROLL        =  0x46,    /* Scroll Lock */
		eKeyNUMPAD7       =  0x47,
		eKeyNUMPAD8       =  0x48,
		eKeyNUMPAD9       =  0x49,
		eKeySUBTRACT      =  0x4A,    /* - on numeric keypad */
		eKeyNUMPAD4       =  0x4B,
		eKeyNUMPAD5       =  0x4C,
		eKeyNUMPAD6       =  0x4D,
		eKeyADD           =  0x4E,    /* + on numeric keypad */
		eKeyNUMPAD1       =  0x4F,
		eKeyNUMPAD2       =  0x50,
		eKeyNUMPAD3       =  0x51,
		eKeyNUMPAD0       =  0x52,
		eKeyDECIMAL       =  0x53,    /* . on numeric keypad */
		eKeyOEM_102       =  0x56,    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
		eKeyF11           =  0x57,
		eKeyF12           =  0x58,
		eKeyF13           =  0x64,    /*                     (NEC PC98) */
		eKeyF14           =  0x65,    /*                     (NEC PC98) */
		eKeyF15           =  0x66,    /*                     (NEC PC98) */
		eKeyKANA          =  0x70,    /* (Japanese keyboard)            */
		eKeyABNT_C1       =  0x73,    /* /? on Brazilian keyboard */
		eKeyCONVERT       =  0x79,    /* (Japanese keyboard)            */
		eKeyNOCONVERT     =  0x7B,    /* (Japanese keyboard)            */
		eKeyYEN           =  0x7D,    /* (Japanese keyboard)            */
		eKeyABNT_C2       =  0x7E,    /* Numpad . on Brazilian keyboard */
		eKeyNUMPADEQUALS  =  0x8D,    /* = on numeric keypad (NEC PC98) */
		eKeyPREVTRACK     =  0x90,    /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
		eKeyAT            =  0x91,    /*                     (NEC PC98) */
		eKeyCOLON         =  0x92,    /*                     (NEC PC98) */
		eKeyUNDERLINE     =  0x93,    /*                     (NEC PC98) */
		eKeyKANJI         =  0x94,    /* (Japanese keyboard)            */
		eKeySTOP          =  0x95,    /*                     (NEC PC98) */
		eKeyAX            =  0x96,    /*                     (Japan AX) */
		eKeyUNLABELED     =  0x97,    /*                        (J3100) */
		eKeyNEXTTRACK     =  0x99,    /* Next Track */
		eKeyNUMPADENTER   =  0x9C,    /* Enter on numeric keypad */
		eKeyRCONTROL      =  0x9D,
		eKeyMUTE          =  0xA0,    /* Mute */
		eKeyCALCULATOR    =  0xA1,    /* Calculator */
		eKeyPLAYPAUSE     =  0xA2,    /* Play / Pause */
		eKeyMEDIASTOP     =  0xA4,    /* Media Stop */
		eKeyVOLUMEDOWN    =  0xAE,    /* Volume - */
		eKeyVOLUMEUP      =  0xB0,    /* Volume + */
		eKeyWEBHOME       =  0xB2,    /* Web home */
		eKeyNUMPADCOMMA   =  0xB3,    /* , on numeric keypad (NEC PC98) */
		eKeyDIVIDE        =  0xB5,    /* / on numeric keypad */
		eKeySYSRQ         =  0xB7,
		eKeyRMENU         =  0xB8,    /* right Alt */
		eKeyPAUSE         =  0xC5,    /* Pause */
		eKeyHOME          =  0xC7,    /* Home on arrow keypad */
		eKeyUP            =  0xC8,    /* UpArrow on arrow keypad */
		eKeyPRIOR         =  0xC9,    /* PgUp on arrow keypad */
		eKeyLEFT          =  0xCB,    /* LeftArrow on arrow keypad */
		eKeyRIGHT         =  0xCD,    /* RightArrow on arrow keypad */
		eKeyEND           =  0xCF,    /* End on arrow keypad */
		eKeyDOWN          =  0xD0,    /* DownArrow on arrow keypad */
		eKeyNEXT          =  0xD1,    /* PgDn on arrow keypad */
		eKeyINSERT        =  0xD2,    /* Insert on arrow keypad */
		eKeyDELETE        =  0xD3,    /* Delete on arrow keypad */
		eKeyLWIN          =  0xDB,    /* Left Windows key */
		eKeyRWIN          =  0xDC,    /* Right Windows key */
		eKeyAPPS          =  0xDD,    /* AppMenu key */
		eLastKeyCode,
		eMouse_LeftButtonDown,
		eMouse_RightButtonDown,
		eMouse_LeftButtonPressed,
		eMouse_RightButtonPressed,
		eMouse_MovedX,
		eMouse_MovedY,
		eMouse_Scroll,
		eOVR_R_IndexTriggerDown,
		eOVR_L_IndexTriggerDown,
		eControllerStart,
		eControllerSelect,
		eControllerCross,
		eControllerSquare,
		eControllerTriangle,
		eControllerCircle,
		eControllerRTrigger1,
		eControllerRTrigger2,
		eControllerLTrigger1,
		eControllerLTrigger2,
		eControllerDPad,
		eControllerLThumbStick,
		eControllerRThumbStick
	};
}