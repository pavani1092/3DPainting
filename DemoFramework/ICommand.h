#pragma once

namespace Crawfis
{
	namespace Collections
	{
		template <class T>
		class ICommand
		{
		public:
			virtual void Execute(T) = 0;
		};

		// Non-templated class
		class IGenericCommand
		{
		public:
			virtual void Execute() = 0;
		};
	}
}