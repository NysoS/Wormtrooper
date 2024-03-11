#pragma once

#include <assert.h>

#include "jepch.h"
#include "JavaEngine/Core/Core.h"

namespace JavaEngine
{
	template <typename Lhs, typename Rhs = Lhs,
		typename ReturnType = void, typename Callable = std::function<ReturnType(Lhs&, Rhs&)>>
		class DispatcherBase
	{
	public:
		using key_type = std::pair<std::string, std::string>;

		using callback_type = Callable;
		using value_type = callback_type;
		using map_type = std::map<key_type, value_type>;

		template <typename LhsType, typename RhsType>
		void add(const callback_type& fn)
		{
			const key_type key(typeid(LhsType).name(), typeid(RhsType).name());
			if (m_map.contains(key))
			{
				return;
			}

			m_map.insert({ key, fn });
		}
		template <typename LhsType, typename RhsType, typename Instance>
		void add(const callback_type& fn)
		{
			const key_type key(typeid(LhsType).name(), typeid(RhsType).name());
			if (m_map.contains(key))
			{
				return;
			}

			m_map.insert({ key, fn });
		}

		ReturnType operator()(Lhs& lhs, Rhs& rhs)
		{
			auto it = std::find_if(m_map.begin(), m_map.end(), [&lhs, &rhs](const auto& element)
				{
					return (typeid(lhs).name() == element.first.first
						&& typeid(rhs).name() == element.first.second);
				});

			/*	assert(it == m_map.end(), "Dispatch function is not implemented");*/

			return it->second(lhs, rhs);
		}

	private:
		map_type m_map;
	};

}