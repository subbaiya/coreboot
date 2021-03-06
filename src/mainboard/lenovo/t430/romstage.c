/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017 Patrick Rudolph <siro@das-labor.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/io.h>
#include <device/pci_def.h>
#include <northbridge/intel/sandybridge/raminit_native.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <ec/lenovo/pmh7/pmh7.h>

void pch_enable_lpc(void)
{
	/* EC Decode Range Port60/64, Port62/66 */
	/* Enable TPM, EC, PS/2 Keyboard/Mouse */
	pci_write_config16(PCH_LPC_DEV, LPC_EN,
			   CNF2_LPC_EN | MC_LPC_EN | KBC_LPC_EN);

	pci_write_config32(PCH_LPC_DEV, LPC_GEN1_DEC,
			   (0x0c << 16) | EC_LENOVO_PMH7_BASE | 1);
}

void rcba_config(void)
{
	/* Disable unused devices (board specific, reserved only).
	 * FIXME: Test if reserved bits are read only. */
	RCBA32(FD) = PCH_DISABLE_ALWAYS | 0x10001fe0;
}

/* FIXME: used T530 values here */
const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 1,  0 },
	{ 1, 1,  1 },
	{ 1, 2,  3 },
	{ 1, 1, -1 },
	{ 1, 1,  2 },
	{ 1, 0, -1 },
	{ 0, 0, -1 },
	{ 1, 2, -1 },
	{ 1, 0, -1 },
	{ 1, 1,  5 },
	{ 1, 0, -1 },
	{ 1, 0, -1 },
	{ 1, 3, -1 },
	{ 1, 1, -1 },
};

void mainboard_early_init(int s3resume)
{
}

void mainboard_config_superio(void)
{
}

void mainboard_get_spd(spd_raw_data *spd, bool id_only)
{
	read_spd(&spd[0], 0x50, id_only);
	read_spd(&spd[2], 0x51, id_only);
}
