#pragma once

#include "Engine.h"
#include "WResources.h"

namespace W
{
	class ThreadPool
	{
	public:
		static void Initiailize(int _iThreadCount);
		static void Shutdown();

		static void Enqueu(std::function<void()> _func);

		template <typename T>
		static void LoadingResource(const std::wstring& _strResourceName , const std::wstring& _strPath);

		static bool Joinable() { return m_bRunnig; }

	private:
		static std::vector<std::thread> m_vecWorker;
		static std::queue<std::function<void()>> m_queueTasks;

		static std::mutex m_mutex;
		static std::condition_variable m_CV;
		static std::atomic<bool> m_bRunnig;

	};
	template<typename T>
	inline void ThreadPool::LoadingResource(const std::wstring& _strResourceName, const std::wstring& _strPath)
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queueTasks.push([]()
				{
					//template에서 template함수 호출시 template 명시
					Resources::template Load<T>(_strResourceName, _strPath);
				});
		}

		m_CV.notify_all();	
	}
}
