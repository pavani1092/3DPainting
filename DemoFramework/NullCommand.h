#pragma once

#include "ICommand.h"
namespace Crawfis
{
	namespace Collections
	{
		//
		// The Null (or no-op) command. Use the singleton
		// instance (Instance) as this is immutable.
		//
		class NullCommand : public IGenericCommand
		{
		public:
			static NullCommand Instance;
			NullCommand(NullCommand& command) { }
			void Execute() {}
		private:
			NullCommand() {}
		};
	}
}
