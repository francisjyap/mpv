/*
 * The sample format system used lin libaf is based on bitmasks.
 * The format definition only refers to the storage format,
 * not the resolution.
 *
 * This file is part of mpv.
 *
 * mpv is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * mpv is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with mpv.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MPLAYER_AF_FORMAT_H
#define MPLAYER_AF_FORMAT_H

#include <stdbool.h>

#include "misc/bstr.h"

enum af_format {
    AF_FORMAT_UNKNOWN = 0,

    AF_FORMAT_U8,
    AF_FORMAT_S16,
    AF_FORMAT_S24,
    AF_FORMAT_S32,
    AF_FORMAT_FLOAT,
    AF_FORMAT_DOUBLE,

    // Planar variants
    AF_FORMAT_U8P,
    AF_FORMAT_S16P,
    AF_FORMAT_S32P,
    AF_FORMAT_FLOATP,
    AF_FORMAT_DOUBLEP,

    // All of these use IEC61937 framing, and otherwise pretend to be like PCM.
    AF_FORMAT_S_AAC,
    AF_FORMAT_S_AC3,
    AF_FORMAT_S_DTS,
    AF_FORMAT_S_DTSHD,
    AF_FORMAT_S_EAC3,
    AF_FORMAT_S_MP3,
    AF_FORMAT_S_TRUEHD,

    AF_FORMAT_COUNT
};

#define AF_FORMAT_IS_IEC61937(f) af_fmt_is_spdif(f)
#define AF_FORMAT_IS_SPECIAL(f) af_fmt_is_spdif(f)
#define AF_FORMAT_IS_FLOAT(f) af_fmt_is_float(f)
#define AF_FORMAT_IS_PLANAR(f) af_fmt_is_planar(f)

struct af_fmt_entry {
    const char *name;
    int format;
};

extern const struct af_fmt_entry af_fmtstr_table[];

int af_str2fmt_short(bstr str);
const char *af_fmt_to_str(int format);

int af_fmt2bps(int format);
int af_fmt2bits(int format);
int af_fmt_change_bits(int format, int bits);

bool af_fmt_unsigned(int format);
bool af_fmt_is_float(int format);
bool af_fmt_is_int(int format);
bool af_fmt_is_planar(int format);
bool af_fmt_is_spdif(int format);

int af_fmt_to_planar(int format);
int af_fmt_from_planar(int format);

// Amount of bytes that contain audio of the given duration, aligned to frames.
int af_fmt_seconds_to_bytes(int format, float seconds, int channels, int samplerate);

bool af_fmt_is_valid(int format);

void af_fill_silence(void *dst, size_t bytes, int format);

int af_format_conversion_score(int dst_format, int src_format);

int af_format_sample_alignment(int format);

#endif /* MPLAYER_AF_FORMAT_H */
