// QuantumStrap — open-source Roblox bootstrapper
// MIT licensed. See README.md.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "launcher.h"
#include "fastflags.h"
#include "inject.h"

#define QS_VERSION "2.1.3"

static void printUsage(void) {
    printf("QuantumStrap v%s (open-source build)\n\n", QS_VERSION);
    printf("Usage:\n");
    printf("  QuantumStrap                Launch Roblox (default profile)\n");
    printf("  QuantumStrap --multi N      Launch N instances (--multi 3)\n");
    printf("  QuantumStrap --preset FILE   Use a FastFlag preset JSON\n");
    printf("  QuantumStrap --dry          Sanitize preset only, don't launch\n");
}

int main(int argc, char** argv) {
    int instances = 1;
    const char* presetPath = NULL;
    int dryRun = 0;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--multi") && i + 1 < argc) {
            instances = atoi(argv[++i]);
            if (instances < 1) instances = 1;
            if (instances > 16) instances = 16;
        } else if (!strcmp(argv[i], "--preset") && i + 1 < argc) {
            presetPath = argv[++i];
        } else if (!strcmp(argv[i], "--dry")) {
            dryRun = 1;
        } else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
            printUsage();
            return 0;
        }
    }

    printf("QuantumStrap v%s\n", QS_VERSION);
    printf("https://github.com/YOUR_USERNAME/QuantumStrap\n\n");

    // 1. Sanitize FastFlag preset against the blacklist
    if (presetPath) {
        int removed = fastflags_sanitize(presetPath);
        printf("[FastFlags] preset sanitized, %d blacklisted flag(s) removed\n", removed);
    }

    if (dryRun) {
        printf("[Dry run] not launching.\n");
        return 0;
    }

    // 2. Launch Roblox client (multi-instance)
    for (int i = 0; i < instances; i++) {
        int ok = launcher_start();
        if (ok == 0)
            printf("[Launch] instance %d started\n", i + 1);
        else {
            printf("[Launch] failed to start instance %d (is Roblox installed?)\n", i + 1);
            return 1;
        }
    }

    // 3. Start Quantum Inject hotkey listener (F6)
    inject_start_listener();

    printf("[OK] %d instance(s) running. Press F6 in-game for Quantum Inject.\n", instances);
    return 0;
}

