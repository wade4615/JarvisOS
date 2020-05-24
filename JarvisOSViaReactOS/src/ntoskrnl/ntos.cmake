
include_directories(
    ${JARVISOS_SOURCE_DIR}
    ${JARVISOS_SOURCE_DIR}/sdk/lib/drivers/arbiter
    ${JARVISOS_SOURCE_DIR}/sdk/lib/cmlib
    include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include/internal
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/drivers)

add_definitions(
    -D__NTOSKRNL__
    -D_NTOSKRNL_
    -D_NTSYSTEM_
    -D_IN_KERNEL_
    -DNTDDI_VERSION=0x05020400)

if(NOT DEFINED NEWCC)
    set(NEWCC FALSE)
endif()

if(NEWCC)
    add_definitions(-DNEWCC)
    list(APPEND SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/cachesub.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/copysup.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/fssup.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/lazyrite.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/logsup.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/mdlsup.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/pinsup.c)
else()
    list(APPEND SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cc/cacheman.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cc/copy.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cc/fs.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cc/lazywrite.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cc/mdl.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cc/pin.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cc/view.c)
endif()

list(APPEND SOURCE
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/include/ntoskrnl.h
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/section/io.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/section/data.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/section/fault.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/section/reqtools.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/section/sptab.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/cache/section/swapout.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmalloc.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmapi.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmboot.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmcheck.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmconfig.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmcontrl.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmdata.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmdelay.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmhook.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmhvlist.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cminit.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmkcbncb.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmlazy.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmmapvw.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmnotify.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmparse.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmquota.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmse.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmsecach.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmsysini.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmvalche.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/cmwraprs.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/ntapi.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/dbgk/dbgkobj.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/dbgk/dbgkutil.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/atom.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/callback.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/dbgctrl.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/efi.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/event.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/evtpair.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/exintrin.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/fmutex.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/handle.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/harderr.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/hdlsterm.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/init.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/interlocked.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/keyedevt.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/locale.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/lookas.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/mutant.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/profile.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/pushlock.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/resource.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/rundown.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/sem.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/shutdown.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/sysinfo.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/time.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/timer.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/uuid.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/win32k.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/work.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/xipdisp.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/zone.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/dbcsname.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/fastio.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/faulttol.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/filelock.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/filter.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/filtrctx.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/fsfilter.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/fsrtlpc.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/largemcb.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/mcb.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/name.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/notify.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/oplock.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/pnp.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/stackovf.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/tunnel.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fsrtl/unc.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fstub/disksup.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fstub/fstubex.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fstub/halstub.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/fstub/translate.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/inbv/inbv.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/inbv/inbvport.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/adapter.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/arcname.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/bootlog.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/controller.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/device.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/deviface.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/driver.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/error.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/file.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/iocomp.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/ioevent.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/iofunc.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/iomdl.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/iomgr.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/iorsrce.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/iotimer.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/iowork.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/irp.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/irq.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/ramdisk.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/rawfs.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/remlock.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/symlink.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/util.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/iomgr/volume.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/pnpmgr/arbs.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/pnpmgr/plugplay.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/pnpmgr/pnpdma.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/pnpmgr/pnpinit.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/pnpmgr/pnpmgr.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/pnpmgr/pnpnotify.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/pnpmgr/pnpreport.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/pnpmgr/pnpres.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/pnpmgr/pnproot.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/pnpmgr/pnputil.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/io/debug.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/apc.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/balmgr.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/bug.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/clock.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/config.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/devqueue.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/dpc.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/eventobj.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/except.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/freeze.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/gate.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/gmutex.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/ipi.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/krnlinit.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/mutex.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/procobj.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/profobj.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/queue.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/semphobj.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/spinlock.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/thrdobj.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/thrdschd.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/time.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/timerobj.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/wait.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/lpc/close.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/lpc/complete.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/lpc/connect.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/lpc/create.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/lpc/listen.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/lpc/port.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/lpc/reply.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/lpc/send.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/contmem.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/drvmgmt.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/dynamic.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/expool.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/hypermap.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/iosup.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/kdbg.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/largepag.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/mdlsup.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/mmdbg.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/mminit.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/mmsup.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/ncache.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/pagfault.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/pfnlist.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/pool.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/procsup.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/section.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/session.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/special.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/sysldr.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/syspte.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/vadnode.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/virtual.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/zeropage.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/balance.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/freelist.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/marea.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/mmfault.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/mminit.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/pagefile.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/region.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/rmap.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/section.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/shutdown.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/devicemap.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/obdir.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/obhandle.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/obinit.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/oblife.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/oblink.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/obname.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/obref.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/obsdcach.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/obsecure.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ob/obwait.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/po/events.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/po/guid.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/po/poshtdwn.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/po/povolume.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/po/power.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/apphelp.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/debug.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/job.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/kill.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/process.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/psmgr.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/psnotify.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/query.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/quota.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/security.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/state.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/thread.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/win32.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/rtl/libsupp.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/rtl/misc.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/se/access.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/se/accesschk.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/se/acl.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/se/audit.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/se/priv.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/se/sd.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/se/semgr.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/se/sid.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/se/srm.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/se/token.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/vf/driver.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/wmi/guidobj.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/wmi/smbios.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/wmi/wmi.c
    ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/wmi/wmidrv.c)

list(APPEND ASM_SOURCE ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/zw.S)

if(ARCH STREQUAL "i386")
    list(APPEND ASM_SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/i386/fastinterlck_asm.S
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/i386/ioport.S
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/ctxswitch.S
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/trap.s
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/usercall_asm.S
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/rtl/i386/stack.S)
    list(APPEND SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/i386/cmhardwr.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/abios.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/cpu.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/context.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/exp.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/irqobj.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/kiinit.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/ldt.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/mtrr.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/patpge.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/thrdini.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/traphdlr.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/usercall.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/i386/v86vdm.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/i386/page.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/i386/init.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/i386/psctx.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/i386/psldt.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/vdm/vdmmain.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/vdm/vdmexec.c)
elseif(ARCH STREQUAL "amd64")
    list(APPEND ASM_SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/boot.S
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/ctxswitch.S
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/trap.S)
    list(APPEND SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/i386/cmhardwr.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/context.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/cpu.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/except.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/interrupt.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/irql.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/kiinit.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/krnlinit.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/spinlock.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/stubs.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/amd64/thrdini.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/amd64/init.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/amd64/page.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/amd64/psctx.c)
elseif(ARCH STREQUAL "arm")
    list(APPEND ASM_SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ex/arm/ioport.s
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/boot.s
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/ctxswtch.s
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/stubs_asm.s
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/trap.s)
    list(APPEND SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/arm/cmhardwr.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/arm/kdbg.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/cpu.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/exp.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/interrupt.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/kiinit.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/thrdini.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/trapc.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/arm/usercall.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/arm/page.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/ARM3/arm/init.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ps/arm/psctx.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/rtl/arm/rtlexcpt.c)
elseif(ARCH STREQUAL "powerpc")
    list(APPEND ASM_SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/powerpc/main_asm.S
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/powerpc/ctxhelp.S)
    list(APPEND SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/config/powerpc/cmhardwr.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/powerpc/cpu.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/powerpc/exp.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/powerpc/kiinit.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/powerpc/ppc_irq.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/powerpc/stubs.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/powerpc/systimer.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/powerpc/thrdini.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/ke/powerpc/ctxswitch.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/powerpc/pfault.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/mm/powerpc/page.c)
endif()

if(NOT _WINKD_)
    if(ARCH STREQUAL "i386")
        list(APPEND SOURCE
            ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/i386/kdbg.c
            ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/wrappers/gdbstub.c)
        if(KDBG)
            list(APPEND ASM_SOURCE ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/i386/kdb_help.S)
            list(APPEND SOURCE ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/i386/i386-dis.c)
        endif()
    elseif(ARCH STREQUAL "amd64")
        list(APPEND SOURCE
            ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/i386/kdbg.c  # Use the x86 file
            ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/amd64/kd.c)
        if(KDBG)
            list(APPEND ASM_SOURCE ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/amd64/kdb_help.S)
            list(APPEND SOURCE
                ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/amd64/i386-dis.c
                ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/amd64/kdb.c)
        endif()
    elseif(ARCH STREQUAL "arm")
        list(APPEND SOURCE ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/arm/kdbg.c)
    elseif(ARCH STREQUAL "powerpc")
        list(APPEND SOURCE ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/wrappers/gdbstub_powerpc.c)
    endif()

    if(KDBG)
        list(APPEND SOURCE
            ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/kdb.c
            ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/kdb_cli.c
            ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/kdb_expr.c
            ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/kdb_keyboard.c
            ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/kdb_serial.c
            ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kdbg/kdb_symbols.c)
    endif()

    list(APPEND SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/wrappers/bochs.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/wrappers/kdbg.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/kdinit.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/kdio.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd/kdmain.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/kdapi.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/kddata.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/kdprint.c)

else() # _WINKD_

    list(APPEND SOURCE
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/kdapi.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/kdbreak.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/kddata.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/kdinit.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/kdlock.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/kdprint.c
        ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/kdtrap.c)

    if(ARCH STREQUAL "i386")
        list(APPEND SOURCE ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/i386/kdx86.c)
    elseif(ARCH STREQUAL "amd64")
        list(APPEND SOURCE ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/amd64/kdx64.c)
    elseif(ARCH STREQUAL "arm")
        list(APPEND SOURCE ${JARVISOS_SOURCE_DIR}/src/ntoskrnl/kd64/arm/kdarm.c)
    endif()

endif()
