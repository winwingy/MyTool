#pragma once
class UnkownBase
{
public:
    UnkownBase(void);
    virtual ~UnkownBase(void);
    void AddRef();
    void Release();
    int GetCount();

private:
    int cnt;
};

