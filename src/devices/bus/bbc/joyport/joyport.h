// license:BSD-3-Clause
// copyright-holders:Nigel Barnes
/**********************************************************************

    BBC Master Compact Joystick/Mouse port

**********************************************************************

    A 9 way 'D' type plug (PL8) is provided for connection to
    external devices. It is compatible with existing 'ATARI' type joysticks
    whose digital outputs are converted by the operating system into suitable
    ADVAL's to emulate BBC analogue joystick operation.

  Pinout: 9 way D-type plug

    +-----------+
    | 1 2 3 4 5 |
     \ 6 7 8 9 /
      +-------+

      1 PB3    6 PB0
      2 PB2    7 +5v
      3 PB1    8 0v
      4 PB4    9 CB2 (LPTSTB if connected)
      5 CB1

**********************************************************************/

#pragma once

#ifndef __COMPACT_JOYPORT__
#define __COMPACT_JOYPORT__

#include "emu.h"


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_COMPACT_JOYPORT_ADD( _tag, _slot_intf, _def_slot) \
	MCFG_DEVICE_ADD(_tag, BBC_JOYPORT_SLOT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> bbc_joyport_slot_device

class device_bbc_joyport_interface;

class bbc_joyport_slot_device : public device_t, public device_slot_interface
{
public:
	// construction/destruction
	bbc_joyport_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~bbc_joyport_slot_device() {}

	UINT8 cb_r();
	UINT8 pb_r();

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	device_bbc_joyport_interface *m_device;
};


// ======================> device_bbc_joyport_interface

class device_bbc_joyport_interface : public device_slot_card_interface
{
public:
	// construction/destruction
	device_bbc_joyport_interface(const machine_config &mconfig, device_t &device);
	virtual ~device_bbc_joyport_interface();

	virtual UINT8 cb_r() { return 0xff; }
	virtual UINT8 pb_r() { return 0x1f; }

protected:
	bbc_joyport_slot_device *m_slot;
};


// device type definition
extern const device_type BBC_JOYPORT_SLOT;

SLOT_INTERFACE_EXTERN( bbc_joyport_devices );


#endif /* __COMPACT_JOYPORT__ */
