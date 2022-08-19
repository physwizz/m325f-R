/*
 *
 * (C) COPYRIGHT ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can access it online at
 * http://www.gnu.org/licenses/gpl-2.0.html.
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 *//* SPDX-License-Identifier: GPL-2.0 */

/*
 * (C) COPYRIGHT 2019 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 */

#ifndef _KBASE_CS_EXPERIMENTAL_H_
#define _KBASE_CS_EXPERIMENTAL_H_

#include <linux/kernel.h>

#if MALI_CS_EXPERIMENTAL

/**
 * mali_kbase_has_cs_experimental() - Has the driver been built with
 *   CS_EXPERIMENTAL=y
 *
 * It is preferable to guard cs_experimental code with this rather than #ifdef
 * all through the code.
 *
 * Return: true if built with CS_EXPERIMENTAL false otherwise
 */
static inline bool mali_kbase_has_cs_experimental(void)
{
	return true;
}
#else
static inline bool mali_kbase_has_cs_experimental(void)
{
	return false;
}
#endif

/**
 * mali_kbase_print_cs_experimental() - Print a string if built with
 *   CS_EXPERIMENTAL=y
 */
static inline void mali_kbase_print_cs_experimental(void)
{
	if (mali_kbase_has_cs_experimental())
		pr_info("mali_kbase: EXPERIMENTAL (MALI_CS_EXPERIMENTAL) flag enabled");
}

#endif /* _KBASE_CS_EXPERIMENTAL_H_ */

