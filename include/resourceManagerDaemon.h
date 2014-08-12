
#ifndef NEBUAPPHADOOP_RESOURCEMANAGERDAEMON_H_
#define NEBUAPPHADOOP_RESOURCEMANAGERDAEMON_H_

#include "hadoopDaemon.h"
#include "nebu/virtualMachine.h"

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{

			class ResourceManagerDaemon : public framework::Daemon
			{
			public:
				ResourceManagerDaemon(std::shared_ptr<nebu::common::VirtualMachine> hostVM) :
					framework::Daemon(hostVM) { }
				virtual ~ResourceManagerDaemon() { }

				virtual bool launch();

				virtual framework::DaemonType getType() const
				{
					return HadoopDaemonType::RESOURCEMANAGER;
				}
			};

		}
	}
}

#endif
