/*
 * how pluto keeps its secrets
 * Copyright (C) 2005 Michael Richardson <mcr@xelerance.com>
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
 * RCSID $Id: //WIFI_SOC/MP/SDK_4_3_0_0/RT288x_SDK/source/user/openswan-2.4.9/programs/pluto/secrets.h#1 $
 */

#ifndef _SECRETS_H_
#define _SECRETS_H_

extern void load_preshared_secrets(int whackfd);
extern void free_preshared_secrets(void);

extern const chunk_t *get_preshared_secret(const struct connection *c);


#endif /* _SECRETS_H_ */

