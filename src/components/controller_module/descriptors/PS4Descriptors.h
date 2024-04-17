#ifndef PS4_DESCRIPTORS_H
#define PS4_DESCRIPTORS_H

#define PS4_REPORT_USB_DESCRIPTOR_SIZE 483
#define PS4_REPORT_BT_DESCRIPTOR_SIZE 442

#include <stdint.h>
#include <Arduino.h>

const uint8_t ps4_report_USB_descriptor[PS4_REPORT_USB_DESCRIPTOR_SIZE] PROGMEM = {
    0x05, 0x01,                    // Usage Page (Generic Desktop),
    0x09, 0x05,                    // Usage (Game Pad),
    0xA1, 0x01,                    // Collection (Application),
    0x85, 0x01,                    //   Report ID (1),
    0x09, 0x30,                    //   Usage (X),
    0x09, 0x31,                    //   Usage (Y),
    0x09, 0x32,                    //   Usage (Z),
    0x09, 0x35,                    //   Usage (Rz),
    0x15, 0x00,                    //   Logical Minimum (0),
    0x26, 0xFF, 0x00,              //   Logical Maximum (255),
    0x75, 0x08,                    //   Report Size (8),
    0x95, 0x04,                    //   Report Count (4),
    0x81, 0x02,                    //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position),
    0x09, 0x39,                    //   Usage (Hat switch),
    0x15, 0x00,                    //   Logical Minimum (0),
    0x25, 0x07,                    //   Logical Maximum (7),
    0x35, 0x00,                    //   Physical Minimum (0),
    0x46, 0x3B, 0x01,              //   Physical Maximum (315),
    0x65, 0x14,                    //   Unit (System: English Rotation, Length: Centimeter),
    0x75, 0x04,                    //   Report Size (4),
    0x95, 0x01,                    //   Report Count (1),
    0x81, 0x42,                    //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State),
    0x65, 0x00,                    //   Unit (None),
    0x05, 0x09,                    //   Usage Page (Button),
    0x19, 0x01,                    //   Usage Minimum (0x01),
    0x29, 0x0E,                    //   Usage Maximum (0x0E),
    0x15, 0x00,                    //   Logical Minimum (0),
    0x25, 0x01,                    //   Logical Maximum (1),
    0x75, 0x01,                    //   Report Size (1),
    0x95, 0x0E,                    //   Report Count (14),
    0x81, 0x02,                    //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position),
    0x06, 0x00, 0xFF,              //   Usage Page (Vendor Defined 0xFF00),
    0x09, 0x20,                    //   Usage (0x20),
    0x75, 0x06,                    //   Report Size (6),
    0x95, 0x01,                    //   Report Count (1),
    0x15, 0x00,                    //   Logical Minimum (0),
    0x25, 0x7F,                    //   Logical Maximum (127),
    0x81, 0x02,                    //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position),
    0x05, 0x01,                    //   Usage Page (Generic Desktop),
    0x09, 0x33,                    //   Usage (Rx),
    0x09, 0x34,                    //   Usage (Ry),
    0x15, 0x00,                    //   Logical Minimum (0),
    0x26, 0xFF, 0x00,              //   Logical Maximum (255),
    0x75, 0x08,                    //   Report Size (8),
    0x95, 0x02,                    //   Report Count (2),
    0x81, 0x02,                    //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position),
    0x06, 0x00, 0xFF,              //   Usage Page (Vendor Defined 0xFF00),
    0x09, 0x21,                    //   Usage (0x21),
    0x95, 0x36,                    //   Report Count (54),
    0x81, 0x02,                    //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position),
    0x85, 0x05,                    //   Report ID (5),
    0x09, 0x22,                    //   Usage (0x22),
    0x95, 0x1F,                    //   Report Count (31),
    0x91, 0x02,                    //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x04,                    //   Report ID (4),
    0x09, 0x23,                    //   Usage (0x23),
    0x95, 0x24,                    //   Report Count (36),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x02,                    //   Report ID (2),
    0x09, 0x24,                    //   Usage (0x24),
    0x95, 0x24,                    //   Report Count (36),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x08,                    //   Report ID (8),
    0x09, 0x25,                    //   Usage (0x25),
    0x95, 0x03,                    //   Report Count (3),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x10,                    //   Report ID (16),
    0x09, 0x26,                    //   Usage (0x26),
    0x95, 0x04,                    //   Report Count (4),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x11,                    //   Report ID (17),
    0x09, 0x27,                    //   Usage (0x27),
    0x95, 0x02,                    //   Report Count (2),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x12,                    //   Report ID (18),
    0x06, 0x02, 0xFF,              //   Usage Page (Vendor Defined 0xFF02),
    0x09, 0x21,                    //   Usage (0x21),
    0x95, 0x0F,                    //   Report Count (15),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x13,                    //   Report ID (19),
    0x09, 0x22,                    //   Usage (0x22),
    0x95, 0x16,                    //   Report Count (22),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x14,                    //   Report ID (20),
    0x06, 0x05, 0xFF,              //   Usage Page (Vendor Defined 0xFF05),
    0x09, 0x20,                    //   Usage (0x20),
    0x95, 0x10,                    //   Report Count (16),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x15,                    //   Report ID (21),
    0x09, 0x21,                    //   Usage (0x21),
    0x95, 0x2C,                    //   Report Count (44),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x06, 0x80, 0xFF,              //   Usage Page (Vendor Defined 0xFF80),
    0x85, 0x80,                    //   Report ID (128),
    0x09, 0x20,                    //   Usage (0x20),
    0x95, 0x06,                    //   Report Count (6),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x81,                    //   Report ID (129),
    0x09, 0x21,                    //   Usage (0x21),
    0x95, 0x06,                    //   Report Count (6),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x82,                    //   Report ID (130),
    0x09, 0x22,                    //   Usage (0x22),
    0x95, 0x05,                    //   Report Count (5),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x83,                    //   Report ID (131),
    0x09, 0x23,                    //   Usage (0x23),
    0x95, 0x01,                    //   Report Count (1),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x84,                    //   Report ID (132),
    0x09, 0x24,                    //   Usage (0x24),
    0x95, 0x04,                    //   Report Count (4),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x85,                    //   Report ID (133),
    0x09, 0x25,                    //   Usage (0x25),
    0x95, 0x06,                    //   Report Count (6),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x86,                    //   Report ID (134),
    0x09, 0x26,                    //   Usage (0x26),
    0x95, 0x06,                    //   Report Count (6),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x87,                    //   Report ID (135),
    0x09, 0x27,                    //   Usage (0x27),
    0x95, 0x23,                    //   Report Count (35),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x88,                    //   Report ID (136),
    0x09, 0x28,                    //   Usage (0x28),
    0x95, 0x22,                    //   Report Count (34),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x89,                    //   Report ID (137),
    0x09, 0x29,                    //   Usage (0x29),
    0x95, 0x02,                    //   Report Count (2),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x90,                    //   Report ID (144),
    0x09, 0x30,                    //   Usage (0x30),
    0x95, 0x05,                    //   Report Count (5),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x91,                    //   Report ID (145),
    0x09, 0x31,                    //   Usage (0x31),
    0x95, 0x03,                    //   Report Count (3),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x92,                    //   Report ID (146),
    0x09, 0x32,                    //   Usage (0x32),
    0x95, 0x03,                    //   Report Count (3),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0x93,                    //   Report ID (147),
    0x09, 0x33,                    //   Usage (0x33),
    0x95, 0x0C,                    //   Report Count (12),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xA0,                    //   Report ID (160),
    0x09, 0x40,                    //   Usage (0x40),
    0x95, 0x06,                    //   Report Count (6),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xA1,                    //   Report ID (161),
    0x09, 0x41,                    //   Usage (0x41),
    0x95, 0x01,                    //   Report Count (1),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xA2,                    //   Report ID (162),
    0x09, 0x42,                    //   Usage (0x42),
    0x95, 0x01,                    //   Report Count (1),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xA3,                    //   Report ID (163),
    0x09, 0x43,                    //   Usage (0x43),
    0x95, 0x30,                    //   Report Count (48),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xA4,                    //   Report ID (164),
    0x09, 0x44,                    //   Usage (0x44),
    0x95, 0x0D,                    //   Report Count (13),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xA5,                    //   Report ID (165),
    0x09, 0x45,                    //   Usage (0x45),
    0x95, 0x15,                    //   Report Count (21),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xA6,                    //   Report ID (166),
    0x09, 0x46,                    //   Usage (0x46),
    0x95, 0x15,                    //   Report Count (21),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xF0,                    //   Report ID (240),
    0x09, 0x47,                    //   Usage (0x47),
    0x95, 0x3F,                    //   Report Count (63),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xF1,                    //   Report ID (241),
    0x09, 0x48,                    //   Usage (0x48),
    0x95, 0x3F,                    //   Report Count (63),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xF2,                    //   Report ID (242),
    0x09, 0x49,                    //   Usage (0x49),
    0x95, 0x0F,                    //   Report Count (15),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xA7,                    //   Report ID (167),
    0x09, 0x4A,                    //   Usage (0x4A),
    0x95, 0x01,                    //   Report Count (1),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xA8,                    //   Report ID (168),
    0x09, 0x4B,                    //   Usage (0x4B),
    0x95, 0x01,                    //   Report Count (1),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xA9,                    //   Report ID (169),
    0x09, 0x4C,                    //   Usage (0x4C),
    0x95, 0x08,                    //   Report Count (8),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xAA,                    //   Report ID (170),
    0x09, 0x4E,                    //   Usage (0x4E),
    0x95, 0x01,                    //   Report Count (1),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xAB,                    //   Report ID (171),
    0x09, 0x4F,                    //   Usage (0x4F),
    0x95, 0x39,                    //   Report Count (57),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xAC,                    //   Report ID (172),
    0x09, 0x50,                    //   Usage (0x50),
    0x95, 0x39,                    //   Report Count (57),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xAD,                    //   Report ID (173),
    0x09, 0x51,                    //   Usage (0x51),
    0x95, 0x0B,                    //   Report Count (11),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xAE,                    //   Report ID (174),
    0x09, 0x52,                    //   Usage (0x52),
    0x95, 0x01,                    //   Report Count (1),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xAF,                    //   Report ID (175),
    0x09, 0x53,                    //   Usage (0x53),
    0x95, 0x02,                    //   Report Count (2),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xB0,                    //   Report ID (176),
    0x09, 0x54,                    //   Usage (0x54),
    0x95, 0x3F,                    //   Report Count (63),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xB1,                    //   Report ID (177),
    0x09, 0x55,                    //   Usage (0x55),
    0x95, 0x02,                    //   Report Count (2),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0x85, 0xB2,                    //   Report ID (178),
    0x09, 0x56,                    //   Usage (0x56),
    0x95, 0x02,                    //   Report Count (2),
    0xB1, 0x02,                    //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non Volatile),
    0xC0                           // End Collection
};


const uint8_t ps4_report_BT_descriptor[PS4_REPORT_BT_DESCRIPTOR_SIZE] PROGMEM = {
    0x05, 0x01, 0x09, 0x05, 0xA1, 0x01, 0x85, 0x01, 0x09, 0x30, 0x09, 0x31, 0x09, 0x32, 0x09, 0x35,
    0x15, 0x00, 0x26, 0xFF, 0x00, 0x75, 0x08, 0x95, 0x04, 0x81, 0x02, 0x09, 0x39, 0x15, 0x00, 0x25,
    0x07, 0x75, 0x04, 0x95, 0x01, 0x81, 0x42, 0x05, 0x09, 0x19, 0x01, 0x29, 0x0E, 0x15, 0x00, 0x25,
    0x01, 0x75, 0x01, 0x95, 0x0E, 0x81, 0x02, 0x75, 0x06, 0x95, 0x01, 0x81, 0x01, 0x05, 0x01, 0x09,
    0x33, 0x09, 0x34, 0x15, 0x00, 0x26, 0xFF, 0x00, 0x75, 0x08, 0x95, 0x02, 0x81, 0x02, 0x06, 0x04,
    0xFF, 0x85, 0x02, 0x09, 0x24, 0x95, 0x24, 0xB1, 0x02, 0x85, 0xA3, 0x09, 0x25, 0x95, 0x30, 0xB1,
    0x02, 0x85, 0x05, 0x09, 0x26, 0x95, 0x28, 0xB1, 0x02, 0x85, 0x06, 0x09, 0x27, 0x95, 0x34, 0xB1,
    0x02, 0x85, 0x07, 0x09, 0x28, 0x95, 0x30, 0xB1, 0x02, 0x85, 0x08, 0x09, 0x29, 0x95, 0x2F, 0xB1,
    0x02, 0x85, 0x09, 0x09, 0x2A, 0x95, 0x13, 0xB1, 0x02, 0x06, 0x03, 0xFF, 0x85, 0x03, 0x09, 0x21,
    0x95, 0x26, 0xB1, 0x02, 0x85, 0x04, 0x09, 0x22, 0x95, 0x2E, 0xB1, 0x02, 0x85, 0xF0, 0x09, 0x47,
    0x95, 0x3F, 0xB1, 0x02, 0x85, 0xF1, 0x09, 0x48, 0x95, 0x3F, 0xB1, 0x02, 0x85, 0xF2, 0x09, 0x49,
    0x95, 0x0F, 0xB1, 0x02, 0x06, 0x00, 0xFF, 0x85, 0x11, 0x09, 0x20, 0x15, 0x00, 0x26, 0xFF, 0x00,
    0x75, 0x08, 0x95, 0x4D, 0x81, 0x02, 0x09, 0x21, 0x91, 0x02, 0x85, 0x12, 0x09, 0x22, 0x95, 0x8D,
    0x81, 0x02, 0x09, 0x23, 0x91, 0x02, 0x85, 0x13, 0x09, 0x24, 0x95, 0xCD, 0x81, 0x02, 0x09, 0x25,
    0x91, 0x02, 0x85, 0x14, 0x09, 0x26, 0x96, 0x0D, 0x01, 0x81, 0x02, 0x09, 0x27, 0x91, 0x02, 0x85,
    0x15, 0x09, 0x28, 0x96, 0x4D, 0x01, 0x81, 0x02, 0x09, 0x29, 0x91, 0x02, 0x85, 0x16, 0x09, 0x2A,
    0x96, 0x8D, 0x01, 0x81, 0x02, 0x09, 0x2B, 0x91, 0x02, 0x85, 0x17, 0x09, 0x2C, 0x96, 0xCD, 0x01,
    0x81, 0x02, 0x09, 0x2D, 0x91, 0x02, 0x85, 0x18, 0x09, 0x2E, 0x96, 0x0D, 0x02, 0x81, 0x02, 0x09,
    0x2F, 0x91, 0x02, 0x85, 0x19, 0x09, 0x30, 0x96, 0x22, 0x02, 0x81, 0x02, 0x09, 0x31, 0x91, 0x02,
    0x06, 0x80, 0xFF, 0x85, 0x82, 0x09, 0x22, 0x95, 0x3F, 0xB1, 0x02, 0x85, 0x83, 0x09, 0x23, 0xB1,
    0x02, 0x85, 0x84, 0x09, 0x24, 0xB1, 0x02, 0x85, 0x90, 0x09, 0x30, 0xB1, 0x02, 0x85, 0x91, 0x09,
    0x31, 0xB1, 0x02, 0x85, 0x92, 0x09, 0x32, 0xB1, 0x02, 0x85, 0x93, 0x09, 0x33, 0xB1, 0x02, 0x85,
    0x94, 0x09, 0x34, 0xB1, 0x02, 0x85, 0xA0, 0x09, 0x40, 0xB1, 0x02, 0x85, 0xA4, 0x09, 0x44, 0xB1,
    0x02, 0x85, 0xA7, 0x09, 0x45, 0xB1, 0x02, 0x85, 0xA8, 0x09, 0x45, 0xB1, 0x02, 0x85, 0xA9, 0x09,
    0x45, 0xB1, 0x02, 0x85, 0xAA, 0x09, 0x45, 0xB1, 0x02, 0x85, 0xAB, 0x09, 0x45, 0xB1, 0x02, 0x85,
    0xAC, 0x09, 0x45, 0xB1, 0x02, 0x85, 0xAD, 0x09, 0x45, 0xB1, 0x02, 0x85, 0xB3, 0x09, 0x45, 0xB1,
    0x02, 0x85, 0xB4, 0x09, 0x46, 0xB1, 0x02, 0x85, 0xB5, 0x09, 0x47, 0xB1, 0x02, 0x85, 0xD0, 0x09,
    0x40, 0xB1, 0x02, 0x85, 0xD4, 0x09, 0x44, 0xB1, 0x02, 0xC0
};


#endif