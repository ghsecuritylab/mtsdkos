/* header auto-generated by pidl */

#include "librpc/ndr/libndr.h"
#include "autoconf/librpc/gen_ndr/msgsvc.h"

#ifndef _HEADER_NDR_msgsvc
#define _HEADER_NDR_msgsvc

#define NDR_MSGSVC_UUID "17fdd703-1827-4e34-79d4-24a55c53bb37"
#define NDR_MSGSVC_VERSION 1.0
#define NDR_MSGSVC_NAME "msgsvc"
#define NDR_MSGSVC_HELPSTRING "Messaging Service"
extern const struct ndr_interface_table ndr_table_msgsvc;
#define NDR_NETRMESSAGENAMEADD (0x00)

#define NDR_NETRMESSAGENAMEENUM (0x01)

#define NDR_NETRMESSAGENAMEGETINFO (0x02)

#define NDR_NETRMESSAGENAMEDEL (0x03)

#define NDR_MSGSVC_CALL_COUNT (4)
void ndr_print_NetrMessageNameAdd(struct ndr_print *ndr, const char *name, int flags, const struct NetrMessageNameAdd *r);
void ndr_print_NetrMessageNameEnum(struct ndr_print *ndr, const char *name, int flags, const struct NetrMessageNameEnum *r);
void ndr_print_NetrMessageNameGetInfo(struct ndr_print *ndr, const char *name, int flags, const struct NetrMessageNameGetInfo *r);
void ndr_print_NetrMessageNameDel(struct ndr_print *ndr, const char *name, int flags, const struct NetrMessageNameDel *r);
#endif /* _HEADER_NDR_msgsvc */
#ifndef _HEADER_NDR_msgsvcsend
#define _HEADER_NDR_msgsvcsend

#define NDR_MSGSVCSEND_UUID "5a7b91f8-ff00-11d0-a9b2-00c04fb6e6fc"
#define NDR_MSGSVCSEND_VERSION 1.0
#define NDR_MSGSVCSEND_NAME "msgsvcsend"
#define NDR_MSGSVCSEND_HELPSTRING NULL
extern const struct ndr_interface_table ndr_table_msgsvcsend;
#define NDR_NETRSENDMESSAGE (0x00)

#define NDR_MSGSVCSEND_CALL_COUNT (1)
void ndr_print_NetrSendMessage(struct ndr_print *ndr, const char *name, int flags, const struct NetrSendMessage *r);
#endif /* _HEADER_NDR_msgsvcsend */