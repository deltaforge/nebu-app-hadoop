
#ifndef NEBUAPPHADOOP_HADOOPAPPLICATION_H_
#define NEBUAPPHADOOP_HADOOPAPPLICATION_H_

#include "nebu-app-framework/applicationHooks.h"
#include "nebu-app-framework/topologyWriter.h"

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{

			class DaemonManager;

			class HadoopApplication : public framework::ApplicationHooks
			{
			public:
				HadoopApplication() : framework::ApplicationHooks() { }
				virtual ~HadoopApplication() { }

				virtual void registerConfigurationOptions();
				virtual void initialise(std::string command, std::vector<std::string> &arguments);

				virtual void postRefreshTopology();

				virtual std::shared_ptr<framework::DaemonManager> getDaemonManager();

			protected:
				std::shared_ptr<DaemonManager> daemonManager;
				std::shared_ptr<framework::TopologyWriter> topologyWriter;
			};

		}
	}
}

#endif
