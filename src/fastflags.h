#ifndef FASTFLAGS_H
#define FASTFLAGS_H

// Loads a FastFlag preset file, removes known-bad flags (see blacklist.h),
// and rewrites the file in place. Returns number of flags removed.

int fastflags_sanitize(const char* presetPath);

#endif
