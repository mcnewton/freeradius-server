/*
 * rlm_debugpacket.c
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * Copyright 2012  Matthew Newton <mcn4@leicester.ac.uk>
 */

#include <freeradius-devel/radiusd.h>
#include <freeradius-devel/modules.h>


/*
 *	debugpacket_dump
 *
 *	Debug output as many value-pairs as we can get our mitts on.
 */
static int debugpacket_dump(void *instance, REQUEST *request)
{
	instance = instance;

	RDEBUG("---------------------------------------------------- PACKET DEBUG -----v-v-v-v-v");
	RDEBUG("Request:");
	debug_pair_list(request->packet->vps);

	RDEBUG("Reply:");
	debug_pair_list(request->reply->vps);

	if (request->proxy) {
		RDEBUG("Proxy:");
		debug_pair_list(request->proxy->vps);
	}

	if (request->proxy_reply) {
		RDEBUG("Proxy reply:");
		debug_pair_list(request->proxy_reply->vps);
	}

	RDEBUG("Control:");
	debug_pair_list(request->config_items);

	RDEBUG("-----------------------------------------------------------------------^-^-^-^-^");

	return RLM_MODULE_NOOP;
}


module_t rlm_debugpacket = {
	RLM_MODULE_INIT,
	"debugpacket",
	RLM_TYPE_THREAD_SAFE,		/* type */
	NULL,				/* instantiation */
	NULL,				/* detach */
	{
		debugpacket_dump,	/* authentication */
		debugpacket_dump,	/* authorization */
		debugpacket_dump,	/* preaccounting */
		debugpacket_dump,	/* accounting */
		debugpacket_dump,	/* checksimul */
		debugpacket_dump,	/* pre-proxy */
		debugpacket_dump,	/* post-proxy */
		debugpacket_dump	/* post-auth */
	},
};

