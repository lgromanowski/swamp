#ifndef SWAMP_SINGLETON_H
#define SWAMP_SINGLETON_H

#include <mutex>
#include <cstdlib>

namespace swamp {

template <
	class T
>
struct Singleton {
	typedef T singleton_type_t;

	Singleton(Singleton&) = delete;
	Singleton& operator=(Singleton&) = delete;

	static singleton_type_t* getInstance() {
		if (m_instance == nullptr) {
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_instance == nullptr) {
				m_instance = new singleton_type_t;
				atexit(destroy);
			}
		}

		return m_instance;
	}

	protected:
		Singleton(){}
		virtual ~Singleton(){}

		static void destroy() {
			delete m_instance;
		}

		static singleton_type_t* m_instance;
		static std::mutex m_mutex;
};

template <class T>
typename Singleton<T>::singleton_type_t* Singleton<T>::m_instance = nullptr;

template <class T>
std::mutex Singleton<T>::m_mutex;

} /* namespace swamp */

#endif /* SWAMP_SINGLETON_H */
