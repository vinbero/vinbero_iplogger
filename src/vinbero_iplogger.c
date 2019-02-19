#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <gaio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vinbero_com/vinbero_com_Error.h>
#include <vinbero_com/vinbero_com_Status.h>
#include <vinbero_com/vinbero_com_Call.h>
#include <vinbero_com/vinbero_com_Config.h>
#include <vinbero_com/vinbero_com_Module.h>
#include <vinbero_com/vinbero_com_ClModule.h>
#include <vinbero_com/vinbero_com_Log.h>
#include <vinbero/vinbero_iface_MODULE.h>
#include <vinbero/vinbero_iface_TLOCAL.h>
#include <vinbero/vinbero_iface_CLOCAL.h>
#include <vinbero/vinbero_iface_CLSERVICE.h>
#include <libgenc/genc_Nstr_cat.h>
#include <libgenc/genc_Tree.h>
#include <libgenc/genc_Uint_toNstr.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "config.h"

VINBERO_COM_MODULE_META_NAME("vinbero_iplogger")
VINBERO_COM_MODULE_META_LICENSE("MPL-2.0")
VINBERO_COM_MODULE_META_VERSION(
    VINBERO_IPLOGGER_VERSION_MAJOR,
    VINBERO_IPLOGGER_VERSION_MINOR,
    VINBERO_IPLOGGER_VERSION_PATCH
)

VINBERO_COM_MODULE_META_IN_IFACES("TLOCAL,CLOCAL,CLSERVICE")
VINBERO_COM_MODULE_META_OUT_IFACES("")
VINBERO_COM_MODULE_META_CHILD_COUNT(0, 0)

VINBERO_IFACE_MODULE_FUNCS;
VINBERO_IFACE_TLOCAL_FUNCS;
VINBERO_IFACE_CLOCAL_FUNCS;
VINBERO_IFACE_CLSERVICE_FUNCS;

struct vinbero_iplogger_ClModule {
    struct gaio_Io* clientIo;
};

int vinbero_iface_MODULE_init(struct vinbero_com_Module* module) {
    VINBERO_COM_LOG_TRACE2();
    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_MODULE_rInit(struct vinbero_com_Module* module) {
    VINBERO_COM_LOG_TRACE2();
    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_TLOCAL_init(struct vinbero_com_TlModule* tlModule) {
    VINBERO_COM_LOG_TRACE2();
    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_TLOCAL_rInit(struct vinbero_com_TlModule* tlModule) {
    VINBERO_COM_LOG_TRACE2();
    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_CLOCAL_init(struct vinbero_com_ClModule* clModule) {
    VINBERO_COM_LOG_TRACE2();
    clModule->localClModule.pointer = malloc(1 * sizeof(struct vinbero_iplogger_ClModule));
    struct vinbero_iplogger_ClModule* localClModule = clModule->localClModule.pointer;
    localClModule->clientIo = clModule->arg;
    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_CLOCAL_rInit(struct vinbero_com_ClModule* clModule) {
    VINBERO_COM_LOG_TRACE2();
    return VINBERO_COM_STATUS_SUCCESS;
}


int vinbero_iface_CLSERVICE_call(struct vinbero_com_ClModule* clModule) {
    VINBERO_COM_LOG_TRACE2();
    struct vinbero_iplogger_ClModule* localClModule = clModule->localClModule.pointer;

    struct sockaddr_in addr;
    socklen_t addrSize = sizeof(struct sockaddr_in);
    getpeername(localClModule->clientIo->object.integer, (struct sockaddr *)&addr, &addrSize);
    char ipaddr[20];
    strcpy(ipaddr, inet_ntoa(addr.sin_addr));
    VINBERO_COM_LOG_INFO("SOCKET %d IP: %s", localClModule->clientIo->object.integer, ipaddr);

    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_CLOCAL_destroy(struct vinbero_com_ClModule* clModule) {
    VINBERO_COM_LOG_TRACE2();
    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_CLOCAL_rDestroy(struct vinbero_com_ClModule* clModule) {
    VINBERO_COM_LOG_TRACE2();
    struct vinbero_iplogger_ClModule* localClModule = clModule->localClModule.pointer;
    free(localClModule);
    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_TLOCAL_destroy(struct vinbero_com_TlModule* tlModule) {
    VINBERO_COM_LOG_TRACE2();
    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_TLOCAL_rDestroy(struct vinbero_com_TlModule* tlModule) {
    VINBERO_COM_LOG_TRACE2();
    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_MODULE_destroy(struct vinbero_com_Module* module) {
    VINBERO_COM_LOG_TRACE2();
    return VINBERO_COM_STATUS_SUCCESS;
}

int vinbero_iface_MODULE_rDestroy(struct vinbero_com_Module* module) {
    VINBERO_COM_LOG_TRACE2();
    return VINBERO_COM_STATUS_SUCCESS;
}
