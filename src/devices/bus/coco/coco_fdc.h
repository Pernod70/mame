// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/*********************************************************************

	coco_fdc.h

	CoCo/Dragon Floppy Disk Controller

*********************************************************************/

#ifndef MAME_DEVICES_BUS_COCO_FDC_H
#define MAME_DEVICES_BUS_COCO_FDC_H

#include "emu.h"
#include "cococart.h"
#include "imagedev/floppy.h"


/***************************************************************************
	TYPE DEFINITIONS
***************************************************************************/

// ======================> coco_family_fdc_device_base

class coco_family_fdc_device_base :
	public device_t,
	public device_cococart_interface
{
public:
	// construction/destruction
	coco_family_fdc_device_base(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
		: device_t(mconfig, type, name, tag, owner, clock, shortname, source)
		, device_cococart_interface(mconfig, *this)
	{
		m_owner = dynamic_cast<cococart_slot_device *>(owner);
	};

	DECLARE_WRITE_LINE_MEMBER(fdc_intrq_w) { m_intrq = state; update_lines(); }
	DECLARE_WRITE_LINE_MEMBER(fdc_drq_w) { m_drq = state; update_lines(); }

	DECLARE_FLOPPY_FORMATS(floppy_formats);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// FDC overrides 
	virtual void update_lines() = 0;
	virtual UINT8* get_cart_base() override;

	// wrapper for setting the cart line
	void cart_set_line(cococart_slot_device::line which, cococart_slot_device::line_value value)
	{
		m_owner->cart_set_line(which, value);
	}
	void cart_set_line(cococart_slot_device::line which, bool value)
	{
		cart_set_line(which, value ? cococart_slot_device::line_value::ASSERT : cococart_slot_device::line_value::CLEAR);
	}

	// accessors
	UINT8 dskreg() const { return m_dskreg; }
	bool intrq() const { return m_intrq; }
	bool drq() const { return m_drq; }
	void set_dskreg(UINT8 data) { m_dskreg = data; }

private:
	// internal state
	cococart_slot_device *m_owner;

	// registers
	UINT8 m_dskreg;
	bool m_intrq;
	bool m_drq;
};

// device type definitions - CoCo FDC
extern const device_type COCO_FDC;
extern const device_type COCO_FDC_V11;
extern const device_type COCO3_HDB1;
extern const device_type CP400_FDC;

// device type definitions - Dragon FDC
extern const device_type DRAGON_FDC;
extern const device_type SDTANDY_FDC;

#endif // MAME_DEVICES_BUS_COCO_FDC_H
