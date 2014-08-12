
#ifndef NEBUAPPHADOOP_DATANODEDAEMON_H_
#define NEBUAPPHADOOP_DATANODEDAEMON_H_

#include "hadoopDaemon.h"
#include "nebu/virtualMachine.h"

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{

			class DataNodeDaemon : public framework::Daemon
			{
			public:
				DataNodeDaemon(std::shared_ptr<nebu::common::VirtualMachine> hostVM) : framework::Daemon(hostVM) { }
				virtual ~DataNodeDaemon() { }

				virtual bool launch();

				virtual framework::DaemonType getType() const
				{
					return HadoopDaemonType::DATANODE;
				}
			};

		}
	}
}

#endif
