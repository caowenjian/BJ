/*************************************************************************
    > File Name: auto_ptr.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Fri May 31 11:12:26 2019
 ************************************************************************/

#include<iostream>
using namespace std;
template <class T>
//#define funOne 
class CAutoPtr
{
    public:
    #ifdef funOne
        CAutoPtr(T* pPtr = 0)
        {
           m_pPtr = pPtr;
        }
        CAutoPtr(const CAutoPtr<T>& autoPtr) //加入const,为了解决临时对象或无名对象的问题，这些具有常性。如CAutoPtr<int> ap(CAutoPtr<int>(new int(2))) 
        {
            m_pPtr = autoPtr.m_pPtr;
            autoPtr.m_pPtr = NULL; //实现方法一：设置原来对象的指针为NULL，把指针权限交给新对象(旧对象不可再使用)，并保证了析构不会重复释放。
        }
        ~CAutoPtr()
        {
            if (m_pPtr)
            {
                delete m_pPtr;
                m_pPtr = NULL;
            }
        }
        CAutoPtr<T>& operator=(const CAutoPtr<T>& ap)
        {
            if (this != &ap)
            {
                if (m_pPtr)
                {
                    delete m_pPtr;
                }
                m_pPtr = ap.m_pPtr;
                ap.m_pPtr = NULL;
            }
            return *this;
        }
    #else
        CAutoPtr(T* pPtr = 0)
        {
            m_pPtr = pPtr;
            m_bOwner = true;
        }
        CAutoPtr(const CAutoPtr<T>& ap)
        {
            m_pPtr = ap.m_pPtr;
            m_bOwner = true;
            ap.m_bOwner = false;
        }
        CAutoPtr<T>& operator=(const CAutoPtr<T>& ap)
        {
            if (this != &ap)
            {
                if (m_pPtr)
                {
                    delete m_pPtr;
                }
                m_pPtr = ap.m_pPtr;
                ap.m_bOwner = false;
                m_bOwner = true;
            }
            return *this;
        }
        ~CAutoPtr()
        {
            if (m_bOwner)
            {
                delete m_pPtr;
                m_pPtr = NULL;
            }
        }
    #endif
        T& operator*()
        {
            return *m_pPtr;
        }
        T* operator->()
        {
            return m_pPtr;
        }
    private:
    mutable T* m_pPtr;
    #ifndef funOne
    mutable bool m_bOwner; //实现方法二：通过bool变量来使其旧对象（未释放新对象之前）能继续使用。
    #endif
};


int main()
{
    //CAutoPtr<int> ap(CAutoPtr<int>(new int(10)));
    CAutoPtr<int> ap(new int(1));
    CAutoPtr<int>ap1 = ap;
    cout << "ap1=" << *ap1 << " ap=" << *ap << endl;
    return 0;
}
