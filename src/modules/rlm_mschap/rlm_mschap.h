/* Copyright 2006-2014 The FreeRADIUS server project */

#ifndef _RLM_MSCHAP_H
#define _RLM_MSCHAP_H

RCSIDH(rlm_mschap_h, "$Id$")

typedef struct rlm_mschap_t {
	int use_mppe;
	int require_encryption;
        int require_strong;
        int with_ntdomain_hack;	/* this should be in another module */
	char *passwd_file;
	const char *xlat_name;
	char *ntlm_auth;
	int ntlm_auth_timeout;
	const char *auth_type;
	int allow_retry;
	char *retry_msg;
	int use_winbind;
	char *ntlm_username;
	char *ntlm_domain;
#ifdef __APPLE__
	int  open_directory;
#endif  
} rlm_mschap_t;

#endif
