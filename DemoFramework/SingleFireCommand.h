#pragma once
#include "ICommand.h"
namespace Crawfis
{
	namespace Collections
	{
		class SingleFireCommand : public IGenericCommand
		{
		public:
			SingleFireCommand(IGenericCommand* command)
				: fired(false), theCommand(command)
			{
			}
			~SingleFireCommand()
			{
				delete theCommand;
			}
			virtual void Execute()
			{
				if (!fired)
				{
					theCommand->Execute();
					fired = true;
				}
			}
		private:
			bool fired;
			IGenericCommand* theCommand;
		};
	}
}

