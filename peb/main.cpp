#include <windows.h>
#include <winnt.h>
#include <iostream>
#include "myStruct.h"


int main(){
    PTEB teb = NtCurrentTeb();
    if (!teb) {
        std::cout << "[+] NtCurrentTeb failed :)\n" << std::endl;
    }
    printf("[+] TEB : 0x%x\n", teb);

    PPEB peb = teb->ProcessEnvironmentBlock;

    printf("[+] PEB : 0x%x\n", peb);
    printf("[+] ImageBaseAddress: 0x%x\n", peb->ImageBaseAddress);
    
    PPEB_LDR_DATA ldr = peb->Ldr;
    
    printf("[+] ldr length: 0x%x\n", ldr->Length);

    PLIST_ENTRY memoryOrderModuleList = &ldr->InMemoryOrderModuleList;

    PLDR_DATA_TABLE_ENTRY module1 = CONTAINING_RECORD((memoryOrderModuleList->Flink)-8, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

    //PLDR_DATA_TABLE_ENTRY module1 = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(memoryOrderModuleList->Flink);

    printf("[+] list: 0x%x\n", memoryOrderModuleList);

    printf("[+] table1: 0x%x\n", module1);
    printf("[+] EntryPoint: 0x%x\n", module1->EntryPoint);
    printf("[+] BaseDLL Name: %s\n", module1->BaseDllName.Buffer);
    printf("[+] FullDLL Name: %s\n", module1->FullDllName.Buffer);
    printf("[+] Size of Image: 0x%x\n", module1->SizeOfImage);

    return 0;
}


/*
0:005> dt ntdll!_eprocess
   +0x000 Pcb              : _KPROCESS
   +0x438 ProcessLock      : _EX_PUSH_LOCK
   +0x440 UniqueProcessId  : Ptr64 Void
   +0x448 ActiveProcessLinks : _LIST_ENTRY
   +0x458 RundownProtect   : _EX_RUNDOWN_REF
   +0x460 Flags2           : Uint4B
   +0x460 JobNotReallyActive : Pos 0, 1 Bit
   +0x460 AccountingFolded : Pos 1, 1 Bit
   +0x460 NewProcessReported : Pos 2, 1 Bit
   +0x460 ExitProcessReported : Pos 3, 1 Bit
   +0x460 ReportCommitChanges : Pos 4, 1 Bit
   +0x460 LastReportMemory : Pos 5, 1 Bit
   +0x460 ForceWakeCharge  : Pos 6, 1 Bit
   +0x460 CrossSessionCreate : Pos 7, 1 Bit
   +0x460 NeedsHandleRundown : Pos 8, 1 Bit
   +0x460 RefTraceEnabled  : Pos 9, 1 Bit
   +0x460 PicoCreated      : Pos 10, 1 Bit
   +0x460 EmptyJobEvaluated : Pos 11, 1 Bit
   +0x460 DefaultPagePriority : Pos 12, 3 Bits
   +0x460 PrimaryTokenFrozen : Pos 15, 1 Bit
   +0x460 ProcessVerifierTarget : Pos 16, 1 Bit
   +0x460 RestrictSetThreadContext : Pos 17, 1 Bit
   +0x460 AffinityPermanent : Pos 18, 1 Bit
   +0x460 AffinityUpdateEnable : Pos 19, 1 Bit
   +0x460 PropagateNode    : Pos 20, 1 Bit
   +0x460 ExplicitAffinity : Pos 21, 1 Bit
   +0x460 ProcessExecutionState : Pos 22, 2 Bits
   +0x460 EnableReadVmLogging : Pos 24, 1 Bit
   +0x460 EnableWriteVmLogging : Pos 25, 1 Bit
   +0x460 FatalAccessTerminationRequested : Pos 26, 1 Bit
   +0x460 DisableSystemAllowedCpuSet : Pos 27, 1 Bit
   +0x460 ProcessStateChangeRequest : Pos 28, 2 Bits
   +0x460 ProcessStateChangeInProgress : Pos 30, 1 Bit
   +0x460 InPrivate        : Pos 31, 1 Bit
   +0x464 Flags            : Uint4B
   +0x464 CreateReported   : Pos 0, 1 Bit
   +0x464 NoDebugInherit   : Pos 1, 1 Bit
   +0x464 ProcessExiting   : Pos 2, 1 Bit
   +0x464 ProcessDelete    : Pos 3, 1 Bit
   +0x464 ManageExecutableMemoryWrites : Pos 4, 1 Bit
   +0x464 VmDeleted        : Pos 5, 1 Bit
   +0x464 OutswapEnabled   : Pos 6, 1 Bit
   +0x464 Outswapped       : Pos 7, 1 Bit
   +0x464 FailFastOnCommitFail : Pos 8, 1 Bit
   +0x464 Wow64VaSpace4Gb  : Pos 9, 1 Bit
   +0x464 AddressSpaceInitialized : Pos 10, 2 Bits
   +0x464 SetTimerResolution : Pos 12, 1 Bit
   +0x464 BreakOnTermination : Pos 13, 1 Bit
   +0x464 DeprioritizeViews : Pos 14, 1 Bit
   +0x464 WriteWatch       : Pos 15, 1 Bit
   +0x464 ProcessInSession : Pos 16, 1 Bit
   +0x464 OverrideAddressSpace : Pos 17, 1 Bit
   +0x464 HasAddressSpace  : Pos 18, 1 Bit
   +0x464 LaunchPrefetched : Pos 19, 1 Bit
   +0x464 Background       : Pos 20, 1 Bit
   +0x464 VmTopDown        : Pos 21, 1 Bit
   +0x464 ImageNotifyDone  : Pos 22, 1 Bit
   +0x464 PdeUpdateNeeded  : Pos 23, 1 Bit
   +0x464 VdmAllowed       : Pos 24, 1 Bit
   +0x464 ProcessRundown   : Pos 25, 1 Bit
   +0x464 ProcessInserted  : Pos 26, 1 Bit
   +0x464 DefaultIoPriority : Pos 27, 3 Bits
   +0x464 ProcessSelfDelete : Pos 30, 1 Bit
   +0x464 SetTimerResolutionLink : Pos 31, 1 Bit
   +0x468 CreateTime       : _LARGE_INTEGER
   +0x470 ProcessQuotaUsage : [2] Uint8B
   +0x480 ProcessQuotaPeak : [2] Uint8B
   +0x490 PeakVirtualSize  : Uint8B
   +0x498 VirtualSize      : Uint8B
   +0x4a0 SessionProcessLinks : _LIST_ENTRY
   +0x4b0 ExceptionPortData : Ptr64 Void
   +0x4b0 ExceptionPortValue : Uint8B
   +0x4b0 ExceptionPortState : Pos 0, 3 Bits
   +0x4b8 Token            : _EX_FAST_REF
   +0x4c0 MmReserved       : Uint8B
   +0x4c8 AddressCreationLock : _EX_PUSH_LOCK
   +0x4d0 PageTableCommitmentLock : _EX_PUSH_LOCK
   +0x4d8 RotateInProgress : Ptr64 _ETHREAD
   +0x4e0 ForkInProgress   : Ptr64 _ETHREAD
   +0x4e8 CommitChargeJob  : Ptr64 _EJOB
   +0x4f0 CloneRoot        : _RTL_AVL_TREE
   +0x4f8 NumberOfPrivatePages : Uint8B
   +0x500 NumberOfLockedPages : Uint8B
   +0x508 Win32Process     : Ptr64 Void
   +0x510 Job              : Ptr64 _EJOB
   +0x518 SectionObject    : Ptr64 Void
   +0x520 SectionBaseAddress : Ptr64 Void
   +0x528 Cookie           : Uint4B
   +0x530 WorkingSetWatch  : Ptr64 _PAGEFAULT_HISTORY
   +0x538 Win32WindowStation : Ptr64 Void
   +0x540 InheritedFromUniqueProcessId : Ptr64 Void
   +0x548 OwnerProcessId   : Uint8B
   +0x550 Peb              : Ptr64 _PEB
   +0x558 Session          : Ptr64 _MM_SESSION_SPACE
   +0x560 Spare1           : Ptr64 Void
   +0x568 QuotaBlock       : Ptr64 _EPROCESS_QUOTA_BLOCK
   +0x570 ObjectTable      : Ptr64 _HANDLE_TABLE
   +0x578 DebugPort        : Ptr64 Void
   +0x580 WoW64Process     : Ptr64 _EWOW64PROCESS
   +0x588 DeviceMap        : Ptr64 Void
   +0x590 EtwDataSource    : Ptr64 Void
   +0x598 PageDirectoryPte : Uint8B
   +0x5a0 ImageFilePointer : Ptr64 _FILE_OBJECT
   +0x5a8 ImageFileName    : [15] UChar
   +0x5b7 PriorityClass    : UChar
   +0x5b8 SecurityPort     : Ptr64 Void
   +0x5c0 SeAuditProcessCreationInfo : _SE_AUDIT_PROCESS_CREATION_INFO
   +0x5c8 JobLinks         : _LIST_ENTRY
   +0x5d8 HighestUserAddress : Ptr64 Void
   +0x5e0 ThreadListHead   : _LIST_ENTRY
   +0x5f0 ActiveThreads    : Uint4B
   +0x5f4 ImagePathHash    : Uint4B
   +0x5f8 DefaultHardErrorProcessing : Uint4B
   +0x5fc LastThreadExitStatus : Int4B
   +0x600 PrefetchTrace    : _EX_FAST_REF
   +0x608 LockedPagesList  : Ptr64 Void
   +0x610 ReadOperationCount : _LARGE_INTEGER
   +0x618 WriteOperationCount : _LARGE_INTEGER
   +0x620 OtherOperationCount : _LARGE_INTEGER
   +0x628 ReadTransferCount : _LARGE_INTEGER
   +0x630 WriteTransferCount : _LARGE_INTEGER
   +0x638 OtherTransferCount : _LARGE_INTEGER
   +0x640 CommitChargeLimit : Uint8B
   +0x648 CommitCharge     : Uint8B
   +0x650 CommitChargePeak : Uint8B
   +0x680 Vm               : _MMSUPPORT_FULL
   +0x7c0 MmProcessLinks   : _LIST_ENTRY
   +0x7d0 ModifiedPageCount : Uint4B
   +0x7d4 ExitStatus       : Int4B
   +0x7d8 VadRoot          : _RTL_AVL_TREE
   +0x7e0 VadHint          : Ptr64 Void
   +0x7e8 VadCount         : Uint8B
   +0x7f0 VadPhysicalPages : Uint8B
   +0x7f8 VadPhysicalPagesLimit : Uint8B
   +0x800 AlpcContext      : _ALPC_PROCESS_CONTEXT
   +0x820 TimerResolutionLink : _LIST_ENTRY
   +0x830 TimerResolutionStackRecord : Ptr64 _PO_DIAG_STACK_RECORD
   +0x838 RequestedTimerResolution : Uint4B
   +0x83c SmallestTimerResolution : Uint4B
   +0x840 ExitTime         : _LARGE_INTEGER
   +0x848 InvertedFunctionTable : Ptr64 _INVERTED_FUNCTION_TABLE
   +0x850 InvertedFunctionTableLock : _EX_PUSH_LOCK
   +0x858 ActiveThreadsHighWatermark : Uint4B
   +0x85c LargePrivateVadCount : Uint4B
   +0x860 ThreadListLock   : _EX_PUSH_LOCK
   +0x868 WnfContext       : Ptr64 Void
   +0x870 ServerSilo       : Ptr64 _EJOB
   +0x878 SignatureLevel   : UChar
   +0x879 SectionSignatureLevel : UChar
   +0x87a Protection       : _PS_PROTECTION
   +0x87b HangCount        : Pos 0, 3 Bits
   +0x87b GhostCount       : Pos 3, 3 Bits
   +0x87b PrefilterException : Pos 6, 1 Bit
   +0x87c Flags3           : Uint4B
   +0x87c Minimal          : Pos 0, 1 Bit
   +0x87c ReplacingPageRoot : Pos 1, 1 Bit
   +0x87c Crashed          : Pos 2, 1 Bit
   +0x87c JobVadsAreTracked : Pos 3, 1 Bit
   +0x87c VadTrackingDisabled : Pos 4, 1 Bit
   +0x87c AuxiliaryProcess : Pos 5, 1 Bit
   +0x87c SubsystemProcess : Pos 6, 1 Bit
   +0x87c IndirectCpuSets  : Pos 7, 1 Bit
   +0x87c RelinquishedCommit : Pos 8, 1 Bit
   +0x87c HighGraphicsPriority : Pos 9, 1 Bit
   +0x87c CommitFailLogged : Pos 10, 1 Bit
   +0x87c ReserveFailLogged : Pos 11, 1 Bit
   +0x87c SystemProcess    : Pos 12, 1 Bit
   +0x87c HideImageBaseAddresses : Pos 13, 1 Bit
   +0x87c AddressPolicyFrozen : Pos 14, 1 Bit
   +0x87c ProcessFirstResume : Pos 15, 1 Bit
   +0x87c ForegroundExternal : Pos 16, 1 Bit
   +0x87c ForegroundSystem : Pos 17, 1 Bit
   +0x87c HighMemoryPriority : Pos 18, 1 Bit
   +0x87c EnableProcessSuspendResumeLogging : Pos 19, 1 Bit
   +0x87c EnableThreadSuspendResumeLogging : Pos 20, 1 Bit
   +0x87c SecurityDomainChanged : Pos 21, 1 Bit
   +0x87c SecurityFreezeComplete : Pos 22, 1 Bit
   +0x87c VmProcessorHost  : Pos 23, 1 Bit
   +0x87c VmProcessorHostTransition : Pos 24, 1 Bit
   +0x87c AltSyscall       : Pos 25, 1 Bit
   +0x87c TimerResolutionIgnore : Pos 26, 1 Bit
   +0x87c DisallowUserTerminate : Pos 27, 1 Bit
   +0x880 DeviceAsid       : Int4B
   +0x888 SvmData          : Ptr64 Void
   +0x890 SvmProcessLock   : _EX_PUSH_LOCK
   +0x898 SvmLock          : Uint8B
   +0x8a0 SvmProcessDeviceListHead : _LIST_ENTRY
   +0x8b0 LastFreezeInterruptTime : Uint8B
   +0x8b8 DiskCounters     : Ptr64 _PROCESS_DISK_COUNTERS
   +0x8c0 PicoContext      : Ptr64 Void
   +0x8c8 EnclaveTable     : Ptr64 Void
   +0x8d0 EnclaveNumber    : Uint8B
   +0x8d8 EnclaveLock      : _EX_PUSH_LOCK
   +0x8e0 HighPriorityFaultsAllowed : Uint4B
   +0x8e8 EnergyContext    : Ptr64 _PO_PROCESS_ENERGY_CONTEXT
   +0x8f0 VmContext        : Ptr64 Void
   +0x8f8 SequenceNumber   : Uint8B
   +0x900 CreateInterruptTime : Uint8B
   +0x908 CreateUnbiasedInterruptTime : Uint8B
   +0x910 TotalUnbiasedFrozenTime : Uint8B
   +0x918 LastAppStateUpdateTime : Uint8B
   +0x920 LastAppStateUptime : Pos 0, 61 Bits
   +0x920 LastAppState     : Pos 61, 3 Bits
   +0x928 SharedCommitCharge : Uint8B
   +0x930 SharedCommitLock : _EX_PUSH_LOCK
   +0x938 SharedCommitLinks : _LIST_ENTRY
   +0x948 AllowedCpuSets   : Uint8B
   +0x950 DefaultCpuSets   : Uint8B
   +0x948 AllowedCpuSetsIndirect : Ptr64 Uint8B
   +0x950 DefaultCpuSetsIndirect : Ptr64 Uint8B
   +0x958 DiskIoAttribution : Ptr64 Void
   +0x960 DxgProcess       : Ptr64 Void
   +0x968 Win32KFilterSet  : Uint4B
   +0x970 ProcessTimerDelay : _PS_INTERLOCKED_TIMER_DELAY_VALUES
   +0x978 KTimerSets       : Uint4B
   +0x97c KTimer2Sets      : Uint4B
   +0x980 ThreadTimerSets  : Uint4B
   +0x988 VirtualTimerListLock : Uint8B
   +0x990 VirtualTimerListHead : _LIST_ENTRY
   +0x9a0 WakeChannel      : _WNF_STATE_NAME
   +0x9a0 WakeInfo         : _PS_PROCESS_WAKE_INFORMATION
   +0x9d0 MitigationFlags  : Uint4B
   +0x9d0 MitigationFlagsValues : <anonymous-tag>
   +0x9d4 MitigationFlags2 : Uint4B
   +0x9d4 MitigationFlags2Values : <anonymous-tag>
   +0x9d8 PartitionObject  : Ptr64 Void
   +0x9e0 SecurityDomain   : Uint8B
   +0x9e8 ParentSecurityDomain : Uint8B
   +0x9f0 CoverageSamplerContext : Ptr64 Void
   +0x9f8 MmHotPatchContext : Ptr64 Void
   +0xa00 DynamicEHContinuationTargetsTree : _RTL_AVL_TREE
   +0xa08 DynamicEHContinuationTargetsLock : _EX_PUSH_LOCK
   +0xa10 DynamicEnforcedCetCompatibleRanges : _PS_DYNAMIC_ENFORCED_ADDRESS_RANGES
   +0xa20 DisabledComponentFlags : Uint4B
   +0xa28 PathRedirectionHashes : Ptr64 Uint4B


0:005> dt ntdll!_teb
   +0x000 NtTib            : _NT_TIB
   +0x038 EnvironmentPointer : Ptr64 Void
   +0x040 ClientId         : _CLIENT_ID
   +0x050 ActiveRpcHandle  : Ptr64 Void
   +0x058 ThreadLocalStoragePointer : Ptr64 Void
   +0x060 ProcessEnvironmentBlock : Ptr64 _PEB
   +0x068 LastErrorValue   : Uint4B
   +0x06c CountOfOwnedCriticalSections : Uint4B
   +0x070 CsrClientThread  : Ptr64 Void
   +0x078 Win32ThreadInfo  : Ptr64 Void
   +0x080 User32Reserved   : [26] Uint4B
   +0x0e8 UserReserved     : [5] Uint4B
   +0x100 WOW32Reserved    : Ptr64 Void
   +0x108 CurrentLocale    : Uint4B
   +0x10c FpSoftwareStatusRegister : Uint4B
   +0x110 ReservedForDebuggerInstrumentation : [16] Ptr64 Void
   +0x190 SystemReserved1  : [30] Ptr64 Void
   +0x280 PlaceholderCompatibilityMode : Char
   +0x281 PlaceholderHydrationAlwaysExplicit : UChar
   +0x282 PlaceholderReserved : [10] Char
   +0x28c ProxiedProcessId : Uint4B
   +0x290 _ActivationStack : _ACTIVATION_CONTEXT_STACK
   +0x2b8 WorkingOnBehalfTicket : [8] UChar
   +0x2c0 ExceptionCode    : Int4B
   +0x2c4 Padding0         : [4] UChar
   +0x2c8 ActivationContextStackPointer : Ptr64 _ACTIVATION_CONTEXT_STACK
   +0x2d0 InstrumentationCallbackSp : Uint8B
   +0x2d8 InstrumentationCallbackPreviousPc : Uint8B
   +0x2e0 InstrumentationCallbackPreviousSp : Uint8B
   +0x2e8 TxFsContext      : Uint4B
   +0x2ec InstrumentationCallbackDisabled : UChar
   +0x2ed UnalignedLoadStoreExceptions : UChar
   +0x2ee Padding1         : [2] UChar
   +0x2f0 GdiTebBatch      : _GDI_TEB_BATCH
   +0x7d8 RealClientId     : _CLIENT_ID
   +0x7e8 GdiCachedProcessHandle : Ptr64 Void
   +0x7f0 GdiClientPID     : Uint4B
   +0x7f4 GdiClientTID     : Uint4B
   +0x7f8 GdiThreadLocalInfo : Ptr64 Void
   +0x800 Win32ClientInfo  : [62] Uint8B
   +0x9f0 glDispatchTable  : [233] Ptr64 Void
   +0x1138 glReserved1      : [29] Uint8B
   +0x1220 glReserved2      : Ptr64 Void
   +0x1228 glSectionInfo    : Ptr64 Void
   +0x1230 glSection        : Ptr64 Void
   +0x1238 glTable          : Ptr64 Void
   +0x1240 glCurrentRC      : Ptr64 Void
   +0x1248 glContext        : Ptr64 Void
   +0x1250 LastStatusValue  : Uint4B
   +0x1254 Padding2         : [4] UChar
   +0x1258 StaticUnicodeString : _UNICODE_STRING
   +0x1268 StaticUnicodeBuffer : [261] Wchar
   +0x1472 Padding3         : [6] UChar
   +0x1478 DeallocationStack : Ptr64 Void
   +0x1480 TlsSlots         : [64] Ptr64 Void
   +0x1680 TlsLinks         : _LIST_ENTRY
   +0x1690 Vdm              : Ptr64 Void
   +0x1698 ReservedForNtRpc : Ptr64 Void
   +0x16a0 DbgSsReserved    : [2] Ptr64 Void
   +0x16b0 HardErrorMode    : Uint4B
   +0x16b4 Padding4         : [4] UChar
   +0x16b8 Instrumentation  : [11] Ptr64 Void
   +0x1710 ActivityId       : _GUID
   +0x1720 SubProcessTag    : Ptr64 Void
   +0x1728 PerflibData      : Ptr64 Void
   +0x1730 EtwTraceData     : Ptr64 Void
   +0x1738 WinSockData      : Ptr64 Void
   +0x1740 GdiBatchCount    : Uint4B
   +0x1744 CurrentIdealProcessor : _PROCESSOR_NUMBER
   +0x1744 IdealProcessorValue : Uint4B
   +0x1744 ReservedPad0     : UChar
   +0x1745 ReservedPad1     : UChar
   +0x1746 ReservedPad2     : UChar
   +0x1747 IdealProcessor   : UChar
   +0x1748 GuaranteedStackBytes : Uint4B
   +0x174c Padding5         : [4] UChar
   +0x1750 ReservedForPerf  : Ptr64 Void
   +0x1758 ReservedForOle   : Ptr64 Void
   +0x1760 WaitingOnLoaderLock : Uint4B
   +0x1764 Padding6         : [4] UChar
   +0x1768 SavedPriorityState : Ptr64 Void
   +0x1770 ReservedForCodeCoverage : Uint8B
   +0x1778 ThreadPoolData   : Ptr64 Void
   +0x1780 TlsExpansionSlots : Ptr64 Ptr64 Void
   +0x1788 DeallocationBStore : Ptr64 Void
   +0x1790 BStoreLimit      : Ptr64 Void
   +0x1798 MuiGeneration    : Uint4B
   +0x179c IsImpersonating  : Uint4B
   +0x17a0 NlsCache         : Ptr64 Void
   +0x17a8 pShimData        : Ptr64 Void
   +0x17b0 HeapData         : Uint4B
   +0x17b4 Padding7         : [4] UChar
   +0x17b8 CurrentTransactionHandle : Ptr64 Void
   +0x17c0 ActiveFrame      : Ptr64 _TEB_ACTIVE_FRAME
   +0x17c8 FlsData          : Ptr64 Void
   +0x17d0 PreferredLanguages : Ptr64 Void
   +0x17d8 UserPrefLanguages : Ptr64 Void
   +0x17e0 MergedPrefLanguages : Ptr64 Void
   +0x17e8 MuiImpersonation : Uint4B
   +0x17ec CrossTebFlags    : Uint2B
   +0x17ec SpareCrossTebBits : Pos 0, 16 Bits
   +0x17ee SameTebFlags     : Uint2B
   +0x17ee SafeThunkCall    : Pos 0, 1 Bit
   +0x17ee InDebugPrint     : Pos 1, 1 Bit
   +0x17ee HasFiberData     : Pos 2, 1 Bit
   +0x17ee SkipThreadAttach : Pos 3, 1 Bit
   +0x17ee WerInShipAssertCode : Pos 4, 1 Bit
   +0x17ee RanProcessInit   : Pos 5, 1 Bit
   +0x17ee ClonedThread     : Pos 6, 1 Bit
   +0x17ee SuppressDebugMsg : Pos 7, 1 Bit
   +0x17ee DisableUserStackWalk : Pos 8, 1 Bit
   +0x17ee RtlExceptionAttached : Pos 9, 1 Bit
   +0x17ee InitialThread    : Pos 10, 1 Bit
   +0x17ee SessionAware     : Pos 11, 1 Bit
   +0x17ee LoadOwner        : Pos 12, 1 Bit
   +0x17ee LoaderWorker     : Pos 13, 1 Bit
   +0x17ee SkipLoaderInit   : Pos 14, 1 Bit
   +0x17ee SpareSameTebBits : Pos 15, 1 Bit
   +0x17f0 TxnScopeEnterCallback : Ptr64 Void
   +0x17f8 TxnScopeExitCallback : Ptr64 Void
   +0x1800 TxnScopeContext  : Ptr64 Void
   +0x1808 LockCount        : Uint4B
   +0x180c WowTebOffset     : Int4B
   +0x1810 ResourceRetValue : Ptr64 Void
   +0x1818 ReservedForWdf   : Ptr64 Void
   +0x1820 ReservedForCrt   : Uint8B
   +0x1828 EffectiveContainerId : _GUID


0:005> dt ntdll!_peb
   +0x000 InheritedAddressSpace : UChar
   +0x001 ReadImageFileExecOptions : UChar
   +0x002 BeingDebugged    : UChar
   +0x003 BitField         : UChar
   +0x003 ImageUsesLargePages : Pos 0, 1 Bit
   +0x003 IsProtectedProcess : Pos 1, 1 Bit
   +0x003 IsImageDynamicallyRelocated : Pos 2, 1 Bit
   +0x003 SkipPatchingUser32Forwarders : Pos 3, 1 Bit
   +0x003 IsPackagedProcess : Pos 4, 1 Bit
   +0x003 IsAppContainer   : Pos 5, 1 Bit
   +0x003 IsProtectedProcessLight : Pos 6, 1 Bit
   +0x003 IsLongPathAwareProcess : Pos 7, 1 Bit
   +0x004 Padding0         : [4] UChar
   +0x008 Mutant           : Ptr64 Void
   +0x010 ImageBaseAddress : Ptr64 Void
   +0x018 Ldr              : Ptr64 _PEB_LDR_DATA
   +0x020 ProcessParameters : Ptr64 _RTL_USER_PROCESS_PARAMETERS
   +0x028 SubSystemData    : Ptr64 Void
   +0x030 ProcessHeap      : Ptr64 Void
   +0x038 FastPebLock      : Ptr64 _RTL_CRITICAL_SECTION
   +0x040 AtlThunkSListPtr : Ptr64 _SLIST_HEADER
   +0x048 IFEOKey          : Ptr64 Void
   +0x050 CrossProcessFlags : Uint4B
   +0x050 ProcessInJob     : Pos 0, 1 Bit
   +0x050 ProcessInitializing : Pos 1, 1 Bit
   +0x050 ProcessUsingVEH  : Pos 2, 1 Bit
   +0x050 ProcessUsingVCH  : Pos 3, 1 Bit
   +0x050 ProcessUsingFTH  : Pos 4, 1 Bit
   +0x050 ProcessPreviouslyThrottled : Pos 5, 1 Bit
   +0x050 ProcessCurrentlyThrottled : Pos 6, 1 Bit
   +0x050 ProcessImagesHotPatched : Pos 7, 1 Bit
   +0x050 ReservedBits0    : Pos 8, 24 Bits
   +0x054 Padding1         : [4] UChar
   +0x058 KernelCallbackTable : Ptr64 Void
   +0x058 UserSharedInfoPtr : Ptr64 Void
   +0x060 SystemReserved   : Uint4B
   +0x064 AtlThunkSListPtr32 : Uint4B
   +0x068 ApiSetMap        : Ptr64 Void
   +0x070 TlsExpansionCounter : Uint4B
   +0x074 Padding2         : [4] UChar
   +0x078 TlsBitmap        : Ptr64 Void
   +0x080 TlsBitmapBits    : [2] Uint4B
   +0x088 ReadOnlySharedMemoryBase : Ptr64 Void
   +0x090 SharedData       : Ptr64 Void
   +0x098 ReadOnlyStaticServerData : Ptr64 Ptr64 Void
   +0x0a0 AnsiCodePageData : Ptr64 Void
   +0x0a8 OemCodePageData  : Ptr64 Void
   +0x0b0 UnicodeCaseTableData : Ptr64 Void
   +0x0b8 NumberOfProcessors : Uint4B
   +0x0bc NtGlobalFlag     : Uint4B
   +0x0c0 CriticalSectionTimeout : _LARGE_INTEGER
   +0x0c8 HeapSegmentReserve : Uint8B
   +0x0d0 HeapSegmentCommit : Uint8B
   +0x0d8 HeapDeCommitTotalFreeThreshold : Uint8B
   +0x0e0 HeapDeCommitFreeBlockThreshold : Uint8B
   +0x0e8 NumberOfHeaps    : Uint4B
   +0x0ec MaximumNumberOfHeaps : Uint4B
   +0x0f0 ProcessHeaps     : Ptr64 Ptr64 Void
   +0x0f8 GdiSharedHandleTable : Ptr64 Void
   +0x100 ProcessStarterHelper : Ptr64 Void
   +0x108 GdiDCAttributeList : Uint4B
   +0x10c Padding3         : [4] UChar
   +0x110 LoaderLock       : Ptr64 _RTL_CRITICAL_SECTION
   +0x118 OSMajorVersion   : Uint4B
   +0x11c OSMinorVersion   : Uint4B
   +0x120 OSBuildNumber    : Uint2B
   +0x122 OSCSDVersion     : Uint2B
   +0x124 OSPlatformId     : Uint4B
   +0x128 ImageSubsystem   : Uint4B
   +0x12c ImageSubsystemMajorVersion : Uint4B
   +0x130 ImageSubsystemMinorVersion : Uint4B
   +0x134 Padding4         : [4] UChar
   +0x138 ActiveProcessAffinityMask : Uint8B
   +0x140 GdiHandleBuffer  : [60] Uint4B
   +0x230 PostProcessInitRoutine : Ptr64     void 
   +0x238 TlsExpansionBitmap : Ptr64 Void
   +0x240 TlsExpansionBitmapBits : [32] Uint4B
   +0x2c0 SessionId        : Uint4B
   +0x2c4 Padding5         : [4] UChar
   +0x2c8 AppCompatFlags   : _ULARGE_INTEGER
   +0x2d0 AppCompatFlagsUser : _ULARGE_INTEGER
   +0x2d8 pShimData        : Ptr64 Void
   +0x2e0 AppCompatInfo    : Ptr64 Void
   +0x2e8 CSDVersion       : _UNICODE_STRING
   +0x2f8 ActivationContextData : Ptr64 _ACTIVATION_CONTEXT_DATA
   +0x300 ProcessAssemblyStorageMap : Ptr64 _ASSEMBLY_STORAGE_MAP
   +0x308 SystemDefaultActivationContextData : Ptr64 _ACTIVATION_CONTEXT_DATA
   +0x310 SystemAssemblyStorageMap : Ptr64 _ASSEMBLY_STORAGE_MAP
   +0x318 MinimumStackCommit : Uint8B
   +0x320 SparePointers    : [4] Ptr64 Void
   +0x340 SpareUlongs      : [5] Uint4B
   +0x358 WerRegistrationData : Ptr64 Void
   +0x360 WerShipAssertPtr : Ptr64 Void
   +0x368 pUnused          : Ptr64 Void
   +0x370 pImageHeaderHash : Ptr64 Void
   +0x378 TracingFlags     : Uint4B
   +0x378 HeapTracingEnabled : Pos 0, 1 Bit
   +0x378 CritSecTracingEnabled : Pos 1, 1 Bit
   +0x378 LibLoaderTracingEnabled : Pos 2, 1 Bit
   +0x378 SpareTracingBits : Pos 3, 29 Bits
   +0x37c Padding6         : [4] UChar
   +0x380 CsrServerReadOnlySharedMemoryBase : Uint8B
   +0x388 TppWorkerpListLock : Uint8B
   +0x390 TppWorkerpList   : _LIST_ENTRY
   +0x3a0 WaitOnAddressHashTable : [128] Ptr64 Void
   +0x7a0 TelemetryCoverageHeader : Ptr64 Void
   +0x7a8 CloudFileFlags   : Uint4B
   +0x7ac CloudFileDiagFlags : Uint4B
   +0x7b0 PlaceholderCompatibilityMode : Char
   +0x7b1 PlaceholderCompatibilityModeReserved : [7] Char
   +0x7b8 LeapSecondData   : Ptr64 _LEAP_SECOND_DATA
   +0x7c0 LeapSecondFlags  : Uint4B
   +0x7c0 SixtySecondEnabled : Pos 0, 1 Bit
   +0x7c0 Reserved         : Pos 1, 31 Bits
   +0x7c4 NtGlobalFlag2    : Uint4B
*/
