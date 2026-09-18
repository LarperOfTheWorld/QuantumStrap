#ifndef BLACKLIST_H
#define BLACKLIST_H

// FastFlags known to cause kicks, physics breakage, or account flags.
// Stripped from user presets before launch by fastflags.c.
// To add a flag: open a PR with the flag name + a short reason.

typedef struct {
    const char* flag;
    const char* reason;
} BlacklistedFlag;

static const BlacklistedFlag BLACKLISTED_FLAGS[] = {
    { "FFlagDebugDisableTimeoutDisconnect",  "causes disconnect kicks" },
    { "DFFlagTaskSchedulerLimitTargetFps",   "breaks physics at high FPS" },
    { "FFlagDebugSimDefaultPrimalSolver",    "unstable solver, crashes" },
    { "DFIntConnectionMTUSize",              "network flagging risk" },
    { "FFlagDebugForceFSMCPULogging",        "censorship bypass risk" },
};

#define BLACKLIST_COUNT (sizeof(BLACKLISTED_FLAGS) / sizeof(BLACKLISTED_FLAGS[0]))

#endif
