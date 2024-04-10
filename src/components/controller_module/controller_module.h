#pragma once
#include "hidnswusb.h"
#include "hidxinput.h"
#include "hiddualshockusb.h"
#ifdef HAS_BT
#include <BleConnectionStatus.h>

#include <BleCompositeHID.h>
#include <XboxGamepadDevice.h>
#endif

#include <Arduino.h>

typedef enum
{
    Nintendo_Switch,
    Xbox_One,
    Dualshock,
} ControllerType;

typedef enum 
{
    BLE,
    USB
} ConnectionType;

#ifdef HAS_BT
inline BleCompositeHID g_compositeHID("Wireless Controller", "Microsoft", 100);
#endif

struct controller_interface
{
public:
    bool UsbConnected;
    ControllerType SelectedType;
    ConnectionType SelectedConnection;
#if CFG_TUD_HID
    HIDNSWUSB NSWUsb;
    HIDXInputUSB XInputUsb;
    HIDDualShockUSB DualShockUSB;
#endif
#ifdef HAS_BT
    XboxGamepadDevice* XboxBT;
#endif
};

inline uint16_t getXboxButtonValue(const char* buttonName) {
    if (strcmp(buttonName, "BUTTON_A") == 0) return XBOX_BUTTON_A;
    else if (strcmp(buttonName, "BUTTON_B") == 0) return XBOX_BUTTON_B;
    else if (strcmp(buttonName, "BUTTON_X") == 0) return XBOX_BUTTON_X;
    else if (strcmp(buttonName, "BUTTON_Y") == 0) return XBOX_BUTTON_Y;
    else if (strcmp(buttonName, "BUTTON_LBUMPER") == 0) return XBOX_BUTTON_LB;
    else if (strcmp(buttonName, "BUTTON_RBUMPER") == 0) return XBOX_BUTTON_RB;
    else if (strcmp(buttonName, "BUTTON_BACK") == 0) return XBOX_BUTTON_SELECT;
    else if (strcmp(buttonName, "BUTTON_START") == 0) return XBOX_BUTTON_START;
    else if (strcmp(buttonName, "BUTTON_HOME") == 0) return XBOX_BUTTON_HOME;
    else if (strcmp(buttonName, "BUTTON_LS") == 0) return XBOX_BUTTON_LS;
    else if (strcmp(buttonName, "BUTTON_RS") == 0) return XBOX_BUTTON_RS;
    else if (strcmp(buttonName, "DPAD_UP") == 0) return XBOX_BUTTON_DPAD_NORTH;
    else if (strcmp(buttonName, "DPAD_RIGHT") == 0) return XBOX_BUTTON_DPAD_EAST;
    else if (strcmp(buttonName, "DPAD_DOWN") == 0) return XBOX_BUTTON_DPAD_SOUTH;
    else if (strcmp(buttonName, "DPAD_LEFT") == 0) return XBOX_BUTTON_DPAD_WEST;
    else return 0; // Unknown button
}
