#include "UnkownBase.h"
#include "../Log/Log.h"

UnkownBase::UnkownBase(void)
    : cnt(1)
{
    TRACE_W("");
}


UnkownBase::~UnkownBase(void)
{
    TRACE_W("");
}

void UnkownBase::AddRef()
{
    ++cnt;
}

void UnkownBase::Release()
{
    TRACE_W("cnt=%d", cnt);
    if (--cnt == 0)
    {
        delete this;
    }
}

int UnkownBase::GetCount()
{
    return cnt;
}
