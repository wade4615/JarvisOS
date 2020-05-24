#ifndef _NODETYPE_INCLUDED_
#define _NODETYPE_INCLUDED_


typedef USHORT NODE_TYPE_CODE;
typedef NODE_TYPE_CODE *PNODE_TYPE_CODE;
typedef CSHORT NODE_BYTE_SIZE;

#ifndef NodeType
#define NodeType(Ptr) (*((PNODE_TYPE_CODE)(Ptr)))
#endif

typedef struct _NODE_TYPE_CODE_AND_SIZE_NO_REFCOUNT
{
    NODE_TYPE_CODE NodeTypeCode;
    NODE_BYTE_SIZE NodeByteSize;
}  NODE_TYPE_CODE_AND_SIZE_NO_REFCOUNT;

typedef struct _NODE_TYPE_CODE_AND_SIZE
{
    NODE_TYPE_CODE_AND_SIZE_NO_REFCOUNT;
    volatile ULONG NodeReferenceCount;
} NODE_TYPE_CODE_AND_SIZE, *PNODE_TYPE_AND_SIZE;

#define ZeroAndInitializeNodeType(Node, Type, Size) \
{ \
        RtlZeroMemory(Node, Size); \
        ((NODE_TYPE_CODE_AND_SIZE *)(Node))->NodeTypeCode = Type; \
        ((NODE_TYPE_CODE_AND_SIZE *)(Node))->NodeByteSize = (CSHORT)Size; \
}

#define RDBSS_STORAGE_NTC(x) (0xec00 + (x))

typedef enum _RX_FILE_TYPE
{
    FileTypeNotYetKnown = 0,
    FileTypeDirectory = 2,
    FileTypeFile = 3
} RX_FILE_TYPE;

#define RDBSS_NTC_STORAGE_TYPE_UNKNOWN ((NODE_TYPE_CODE)0xec00)
#define RDBSS_NTC_STORAGE_TYPE_DIRECTORY ((NODE_TYPE_CODE)0xec02)
#define RDBSS_NTC_STORAGE_TYPE_FILE ((NODE_TYPE_CODE)0xec03)
#define RDBSS_NTC_OPENTARGETDIR_FCB ((NODE_TYPE_CODE)0xecff)
#define RDBSS_NTC_IPC_SHARE ((NODE_TYPE_CODE)0xecfe)
#define RDBSS_NTC_MAILSLOT ((NODE_TYPE_CODE)0xecfd)
#define RDBSS_NTC_SPOOLFILE ((NODE_TYPE_CODE)0xecfc)
#define RDBSS_NTC_SRVCALL ((NODE_TYPE_CODE)0xeb10)
#define RDBSS_NTC_NETROOT ((NODE_TYPE_CODE)0xeb11)
#define RDBSS_NTC_V_NETROOT ((NODE_TYPE_CODE)0xeb12)
#define RDBSS_NTC_VOLUME_FCB ((NODE_TYPE_CODE)0xeb1f)
#define RDBSS_NTC_SRVOPEN ((NODE_TYPE_CODE)0xeb1c)
#define RDBSS_NTC_INTERNAL_SRVOPEN ((NODE_TYPE_CODE)0xeb1d)
#define RDBSS_NTC_DEVICE_FCB ((NODE_TYPE_CODE)0xeb9a)
#define RDBSS_NTC_DATA_HEADER ((NODE_TYPE_CODE)0xeb00)
#define RDBSS_NTC_VCB ((NODE_TYPE_CODE)0xeb01)
#define RDBSS_NTC_FOBX ((NODE_TYPE_CODE)0xeb07)
#define RDBSS_NTC_RX_CONTEXT ((NODE_TYPE_CODE)0xeb08)
#define RDBSS_NTC_PREFIX_TABLE ((NODE_TYPE_CODE)0xeb0d)
#define RDBSS_NTC_PREFIX_ENTRY ((NODE_TYPE_CODE)0xeb0e)
#define RDBSS_NTC_FCB_TABLE ((NODE_TYPE_CODE)0xeb09)
#define RDBSS_NTC_FCB_TABLE_ENTRY ((NODE_TYPE_CODE)0xeb0a)
#define RDBSS_NTC_NONPAGED_FCB ((NODE_TYPE_CODE)0xebfd)
#define RDBSS_NTC_MINIRDR_DISPATCH ((NODE_TYPE_CODE)0xebff)

#define RDBSS_NTC_FCB RDBSS_NTC_STORAGE_TYPE_FILE

#define NodeTypeIsFcb(FCB) ((((NodeType(FCB) & 0xff00) == RDBSS_NTC_STORAGE_TYPE_UNKNOWN)) || ((NodeType(FCB) & 0xfff0) == 0xeb90))

#define RX_SCAVENGER_MASK (0x1000)

typedef enum _RDBSS_BUG_CHECK_CODES
{
     RDBSS_BUG_CHECK_FCBSTRUC = 0xfcb00000,
     RDBSS_BUG_CHECK_CACHESUP = 0xca550000,
     RDBSS_BUG_CHECK_CLEANUP = 0xc1ee0000,
     RDBSS_BUG_CHECK_CLOSE = 0xc10e0000,
     RDBSS_BUG_CHECK_NTEXCEPT = 0xbaad0000,
#ifdef __LCARSOS__
     RDBSS_BUG_CHECK_ASSERT = 0xa55a0000,
#endif
} RDBSS_BUG_CHECK_CODES;

#define RDBSS_FILE_SYSTEM RDR_FILE_SYSTEM

#define RxBugCheck(A, B, C) KeBugCheckEx(RDBSS_FILE_SYSTEM, BugCheckFileId | ((ULONG)(__LINE__)), A, B, C)

#endif
