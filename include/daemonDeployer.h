
#ifndef NEBUAPPHADOOP_DAEMONDEPLOYER_H_
#define NEBUAPPHADOOP_DAEMONDEPLOYER_H_

#include "nebu-app-framework/daemonCollection.h"
#include "nebu-app-framework/topologyManager.h"
#include "nebu/virtualMachine.h"

#include <map>
#include <memory>
#include <set>
#include <vector>

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{

			class NameNodeDaemon;
			class ResourceManagerDaemon;

			class DaemonDeployer
			{
			public:
				DaemonDeployer(std::shared_ptr<framework::DaemonCollection> daemonCollection,
						std::shared_ptr<framework::TopologyManager> topologyManager);
				virtual ~DaemonDeployer() { };

				virtual void identifyDaemons();
				virtual void deployDaemons();

				virtual std::shared_ptr<NameNodeDaemon> getNameNode()
				{
					return this->activeNameNode;
				}
				virtual std::shared_ptr<ResourceManagerDaemon> getResourceManager()
				{
					return this->activeResourceManager;
				}

			private:
				std::shared_ptr<framework::DaemonCollection> daemonCollection;
				std::shared_ptr<framework::TopologyManager> topologyManager;

				std::shared_ptr<NameNodeDaemon> activeNameNode;
				std::shared_ptr<ResourceManagerDaemon> activeResourceManager;

				void deployNameNode();
				void deployResourceManager();
				void deployDataNodes();

				bool pickRequiredNodes();
				bool requiredNodesActive();
				std::shared_ptr<NameNodeDaemon> pickNameNode();
				std::shared_ptr<ResourceManagerDaemon> pickResourceManager();
			};

		}
	}
}

#endif
