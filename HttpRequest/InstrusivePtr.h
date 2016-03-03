#pragma once
#include "../Log/Log.h"


//自己写的一个简单的智能指针

template <typename T>
class InstrusivePtr
{
public:
    explicit InstrusivePtr(T* p)
    {
        TRACE_W("%s  __LINE__=%d\n", __FUNCTION__, __LINE__);
        if (p == NULL)
        {
            InstrusivePtr();
        }
        else
        {
            ptr_ = p;
            cnt_ = new long(1);            
        }
    }

    explicit InstrusivePtr()
    {
        TRACE_W("%s  __LINE__=%d\n", __FUNCTION__, __LINE__);
        ptr_ = NULL;
        cnt_ = NULL;
    }

    InstrusivePtr(const InstrusivePtr& istPtr)
    {
        ptr_ = istPtr.ptr_;
        cnt_ = istPtr.cnt_;
        AddCount();
    }

    T* get()
    {
        return ptr_;
    }

    T& operator * ()
    {
        return *ptr_;
    }

    T* operator -> ()
    {
        return ptr_;
    }

    InstrusivePtr& operator = (const InstrusivePtr& istPtr)
    {
        if (ptr_ == istPtr->ptr_)
        {
            ++cnt_;
            return *this;
        }
        ReleaseCount();
        ptr_ = istPtr->ptr_;
        cnt_ = istPtr->cnt_;
        AddCount();
    }

    bool operator == (const InstrusivePtr& istPtr)
    {
        return ptr_ == istPtr->ptr_;
    }

    InstrusivePtr* GetThis()
    {
        return this;
    }

    int useCount()
    {
        if (cnt_)
        {
            return *cnt_;
        }
        return 0;
    }

    void AddCount()
    {
        if (cnt_)
        {
            InterlockedIncrement(cnt_);        
        }        
    }

    void ReleaseCount()
    {
        if (cnt_)
        {
            int cnt = InterlockedDecrement(cnt_);       
            if (cnt == 0)
            {
                TRACE_W("");
                delete ptr_;
                delete cnt_;
            }
        }
    }
    ~InstrusivePtr(void)
    {
        TRACE_W("useCount=%d", useCount());
        ReleaseCount();
    }
private:

    InstrusivePtr& operator = (T* p)
    {        
        return *this;
    }
    T* ptr_;
    long* cnt_;
};

