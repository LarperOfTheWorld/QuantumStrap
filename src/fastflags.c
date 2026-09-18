#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fastflags.h"
#include "blacklist.h"

static int lineHasFlag(const char* line, const char* flag) {
    return strstr(line, flag) != NULL;
}

static int fileLen(FILE* f) {
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    return (int)sz;
}

int fastflags_sanitize(const char* presetPath) {
    FILE* f = fopen(presetPath, "rb");
    if (!f) {
        printf("[FastFlags] preset '%s' not found\n", presetPath);
        return -1;
    }

    int sz = fileLen(f);
    if (sz <= 0 || sz > 1024 * 1024) { fclose(f); return -1; }

    char* buf = (char*)malloc(sz + 1);
    if (!buf) { fclose(f); return -1; }
    if (fread(buf, 1, sz, f) != (size_t)sz) { free(buf); fclose(f); return -1; }
    buf[sz] = '\0';
    fclose(f);

    char* out = (char*)malloc(sz + 2);
    if (!out) { free(buf); return -1; }
    int outPos = 0, removed = 0;

    char* line = strtok(buf, "\n");
    int firstLine = 1;
    while (line) {
        int drop = 0;
        for (size_t b = 0; b < BLACKLIST_COUNT; b++) {
            if (lineHasFlag(line, BLACKLISTED_FLAGS[b].flag)) {
                drop = 1;
                removed++;
                printf("[FastFlags] removed blacklisted flag: %s (%s)\n",
                       BLACKLISTED_FLAGS[b].flag, BLACKLISTED_FLAGS[b].reason);
                break;
            }
        }
        if (!drop) {
            int l = (int)strlen(line);
            if (!firstLine && l > 0 && outPos > 0 && out[outPos - 1] != '\n')
                out[outPos++] = '\n';
            memcpy(out + outPos, line, l);
            outPos += l;
            firstLine = 0;
        }
        line = strtok(NULL, "\n");
    }
    out[outPos] = '\0';

    FILE* w = fopen(presetPath, "wb");
    if (!w) { free(buf); free(out); return -1; }
    fwrite(out, 1, outPos, w);
    fclose(w);

    free(buf);
    free(out);
    return removed;
}
