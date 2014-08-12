
#ifndef NEBUAPPHADOOP_NAMENODEDAEMON_H_
#define NEBUAPPHADOOP_NAMENODEDAEMON_H_

#include "hadoopDaemon.h"
#include "nebu/virtualMachine.h"

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{

			class NameNodeDaemon : public framework::Daemon
			{
			public:
				NameNodeDaemon(std::shared_ptr<nebu::common::VirtualMachine> hostVM) : Daemon(hostVM) { }
				virtual ~NameNodeDaemon() { }

				virtual bool updateTopologyTable();
				virtual bool launch();

				virtual framework::DaemonType getType() const
				{
					return HadoopDaemonType::NAMENODE;
				}
			};

		}
	}
}

#endif
