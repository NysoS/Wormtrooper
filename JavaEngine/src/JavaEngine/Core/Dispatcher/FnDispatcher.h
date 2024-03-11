#pragma once

#include "DispatcherBase.h"
#include "jepch.h"
#include "JavaEngine/Core/Core.h"

namespace JavaEngine
{
	template <typename LhsBase, typename RhsBase, typename ReturnType = void>
	class FnDispatcher
	{
	public:
		using functor_type = std::function<ReturnType(LhsBase&, RhsBase&)>;

		template <typename LhsDerived, typename RhsDerived, typename InstanceType>
		void add(InstanceType* instance, ReturnType (InstanceType::*fn)(LhsBase&, RhsBase&))
		{
			m_dispatcherBase.template add<LhsDerived, RhsDerived>([instance, fn](LhsBase& lhs, RhsBase& rhs)
				{
					return (instance->*fn)(lhs, rhs);
				});
		}

		ReturnType operator()(LhsBase& lhs, RhsBase& rhs)
		{
			return m_dispatcherBase(lhs, rhs);
		}

	private:
		DispatcherBase<LhsBase, RhsBase, ReturnType, functor_type> m_dispatcherBase;
	};
}
