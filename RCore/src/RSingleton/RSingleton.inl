#pragma once

namespace RCore
{
	template<typename T>
	class RSingleton
	{
		static T* s_instance;

	public:
		static T* getInstance()
		{
			if (!s_instance)
				s_instance = new T();

			return s_instance;
		}

		static void destroyInstance()
		{
			if (s_instance)
			{
				delete s_instance;
				s_instance = nullptr;
			}
		}
	};
}