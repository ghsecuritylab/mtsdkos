/* FreeS/WAN comparisons functions (cmp.h)
 * Copyright (C) 2001-2002 Mathieu Lafon - Arkoon Network Security
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * RCSID $Id: //WIFI_SOC/MP/SDK_4_3_0_0/RT288x_SDK/source/user/openswan-2.6.22/include/ipsecconf/cmp.h#1 $
 */

#ifndef _STARTER_CMP_H_
#define _STARTER_CMP_H_

int starter_cmp_conn (struct starter_conn *c1, struct starter_conn *c2);
int starter_cmp_klips (struct starter_config *c1, struct starter_config *c2);
int starter_cmp_pluto (struct starter_config *c1, struct starter_config *c2);

#endif
