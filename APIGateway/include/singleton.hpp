#pragma once

#include <atomic>
#include <functional>
#include <mutex>

template<class T>
class Singleton
{
public:
    Singleton() = delete;
    Singleton(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton &operator=(Singleton &&) = delete;
    
    ~Singleton() = delete;

    template<class... Args>
    static T *GetInstance(Args&&... args);
    
private:
    static std::atomic<T*> s_ptr;
    static void CleanUp();
};

template<class T>
std::atomic<T*> Singleton<T>::s_ptr;

template<class T>
template<class... Args>
T* Singleton<T>::GetInstance(Args&&... args)
{
    static std::mutex s_mutex;

    T *tmp = s_ptr.load(std::memory_order_acquire);

    if(!tmp)
    {
        std::lock_guard<std::mutex> lock(s_mutex);
        tmp = s_ptr.load(std::memory_order_relaxed);

        if(!tmp)
        {
            tmp = new T(std::forward<Args>(args)...);
            s_ptr.store(tmp, std::memory_order_release);
            atexit(CleanUp);
        }
    }
    return tmp;
}

template<class T>
void Singleton<T>::CleanUp()
{
    delete s_ptr.load();
}
