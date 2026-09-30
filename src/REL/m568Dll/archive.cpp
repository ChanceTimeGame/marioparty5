#include "REL/m568Dll/archive.h"
#include "REL/mgcpp/assert.h"
#include "REL/mgcpp/new.h"
#ifdef __MWERKS__
extern "C" { /* libc/string.h has no extern "C" guard: retail calls the C strcmp */
#include <string.h>
}
#endif

namespace m568 {

/* the zero fill of +0x04..+0x47 in the ctor and Init: the value is a `const T&` bound to the literal 0, which CW
 * materialises as a 4-byte .data temporary per call site (data_0 / data_34); `lwz; extsb; stb` */
template <class T>
inline void ArcFill(char* b, char* e, const T& v)
{
    while (b != e) {
        *b++ = (char)v;
    }
}

CArchive::CArchive(int dataNum)
{
    ArcFill((char*)&m_header, (char*)&m_file, 0); /* +0x04..+0x47 on GC; by member on the host (8-byte vptr) */
    m_file = HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL); /* 2 */
    m_relocated = 0;
    Init(m_file, 0);
}

CArchive::~CArchive() {}

void CArchive::Relocate()
{
    if (m_data && m_reloc && !m_relocated) {
        u32 first = *(u32*)(m_data + m_reloc[0]);
        if (first < (u32)m_data) {
            for (u32 i = 0; i < m_header.relocNum; i++) {
                u32* p = (u32*)(m_data + m_reloc[i]);
                *p += (u32)m_data;
            }
            m_relocated = 1;
        }
    }
}

int CArchive::GetPublicNum()
{
    return m_header.publicNum;
}

/* line padding: the assert below is retail's archive.cpp:92 */





















void* CArchive::GetPublicData(int idx)
{
    assert(idx >=0 && idx <= GetPublicNum());
    return m_data + m_public[idx].dataOfs;
}

int CArchive::Init(void* raw, int unused)
{
    ArcFill((char*)&m_header, (char*)&m_file, 0); /* +0x04..+0x47 on GC; by member on the host (8-byte vptr) */
    m_valid = 1;
    m_header = *(Header*)raw;
    u32 ofs = 0;
    ofs += sizeof(Header);
    if (m_header.dataSize) {
        m_data = (u8*)raw + ofs;
        ofs += m_header.dataSize;
    }
    if (m_header.relocNum) {
        m_reloc = (u32*)((u8*)raw + ofs);
        ofs += m_header.relocNum * 4;
    }
    if (m_header.publicNum) {
        m_public = (PubEntry*)((u8*)raw + ofs);
        ofs += m_header.publicNum * 8;
    }
    if (m_header.num4) {
        m_table4 = (u8*)raw + ofs;
        ofs += m_header.num4 * 8;
    }
    if (ofs < m_header.totalSize) {
        m_strings = (char*)raw + ofs;
    }
    m_raw = raw;
    Relocate();
    return 0;
}

const char* CArchive::GetPublicName(int idx)
{
    if (idx < 0 || m_header.publicNum <= (u32)idx) {
        return 0;
    }
    return m_strings + m_public[idx].nameOfs;
}

void* CArchive::FindPublic(const char* name)
{
    PubEntry* pub = m_public;
    char* strings = m_strings;
    int n = m_header.publicNum;
    for (int i = 0; i < n; i++) {
        if (strcmp(strings + pub[i].nameOfs, name) == 0) {
            return GetPublicData(i);
        }
    }
    return 0;
}

void* CArchive::GetData(const char* name)
{
    return FindPublic(name);
}

} // namespace m568
