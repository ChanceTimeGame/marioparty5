#ifndef M568_ARCHIVE_H
#define M568_ARCHIVE_H

#include "REL/mgcpp/game.h"

namespace m568 {


class IArchive {
public:
    virtual void* GetData(const char* name) = 0; /* 0x08 */
};

class CArchive : public IArchive {
public:
    /* the file header, copied as a struct (Init 24C: five words, four bytes, two words) */
    struct Header {
        u32 totalSize;  /* 0x00 compared (unsigned) with the running offset */
        u32 dataSize;   /* 0x04 data block length */
        u32 relocNum;   /* 0x08 u32 entries */
        u32 publicNum;  /* 0x0C {dataOfs, nameOfs} entries */
        u32 num4;       /* 0x10 8-byte entries, never read after Init */
        u8 b[4];        /* 0x14 copied bytewise (host: not swapped) */
        struct Pair {
            u32 a, b;
        } unk18;        /* 0x18 never read; a nested 8-byte struct (Init copies it as one lwz/lwz/stw/stw block) */
    };
    struct PubEntry {
        u32 dataOfs; /* 0x0 into the data block */
        u32 nameOfs; /* 0x4 into the string table */
    };

    CArchive(int dataNum);                 /* fn_1_0 */
    ~CArchive();                           /* fn_1_A8 non-virtual; does not free m_file (overlay heap) */
    /* fn_1_100 (unreferenced; inlined into Init): adds m_data to every relocated u32, once */
    void Relocate();
    int GetPublicNum();                    /* fn_1_1A8 (unreferenced; auto-inlined into the later bodies) */
    void* GetPublicData(int idx);
    int Init(void* raw, int unused);       /* fn_1_24C always 0 */
    const char* GetPublicName(int idx);    /* fn_1_428 (unreferenced) */
    void* FindPublic(const char* name);    /* fn_1_460 (unreferenced; inlined into GetData) */
    virtual void* GetData(const char* name); /* fn_1_534 slot 0x08 */

    Header m_header;     /* 0x04 */
    u8* m_data;          /* 0x24 */
    u32* m_reloc;        /* 0x28 */
    PubEntry* m_public;  /* 0x2C */
    void* m_table4;      /* 0x30 */
    char* m_strings;     /* 0x34 only if the running offset < totalSize */
    u8 m_unk38[8];       /* 0x38 never touched (inside the zero-filled range) */
    int m_valid;         /* 0x40 = 1 by Init */
    void* m_raw;         /* 0x44 Init's argument */
    void* m_file;        /* 0x48 HuDataSelHeapReadNum */
    u8 m_relocated;      /* 0x4C */
};

} // namespace m568

#endif
