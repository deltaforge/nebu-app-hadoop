
#include "nebu-app-framework/daemonCollection.h"
#include "daemonDeployer.h"
#include "hadoopConfiguration.h"
#include "hadoopDaemon.h"
#include "nameNodeDaemon.h"
#include "resourceManagerDaemon.h"

#include "nebu-app-framework/topologyManager.h"
#include "nebu/topology/physicalRack.h"

#include <log4cxx/logger.h>

// Using declarations - standard library
using std::set;
using std::shared_ptr;
using std::static_pointer_cast;
// Using declarations - nebu-common
using nebu::common::PhysicalRack;
using nebu::common::VirtualMachine;
// Using declarations - nebu-app-framework
using nebu::app::framework::Daemon;
using nebu::app::framework::DaemonCollection;
using nebu::app::framework::DaemonType;
using nebu::app::framework::TopologyManager;

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{

			DaemonDeployer::DaemonDeployer(shared_ptr<DaemonCollection> daemonCollection,
								shared_ptr<TopologyManager> topologyManager) :
					daemonCollection(daemonCollection), topologyManager(topologyManager),
					activeNameNode(), activeResourceManager()
			{

			}

			void DaemonDeployer::identifyDaemons()
			{
				if (!this->requiredNodesActive()) {
					this->activeNameNode = this->pickNameNode();
					this->activeResourceManager = this->pickResourceManager();
				}
			}

			void DaemonDeployer::deployDaemons()
			{
				if (!this->requiredNodesActive()) {
					return;
				}

				this->deployNameNode();
				this->deployResourceManager();
				this->deployDataNodes();
			}

			void DaemonDeployer::deployNameNode()
			{
				if (!this->activeNameNode->hasLaunched()) {
					if (this->activeNameNode->updateTopologyTable()) {
						this->activeNameNode->launch();
					}
				}
			}

			void DaemonDeployer::deployResourceManager()
			{
				if (!this->activeResourceManager->hasLaunched()) {
					this->activeResourceManager->launch();
				}
			}

			void DaemonDeployer::deployDataNodes()
			{
				if (this->activeNameNode->hasLaunched() && this->activeResourceManager->hasLaunched()) {
					set<shared_ptr<Daemon>> dataNodes = this->daemonCollection->getDaemonsForType(HadoopDaemonType::DATANODE);
					for (set<shared_ptr<Daemon>>::iterator dataNode = dataNodes.begin();
							dataNode != dataNodes.end();
							dataNode++)
					{
						if (!(*dataNode)->hasLaunched()) {
							(*dataNode)->launch();
						}
					}
				}
			}

			bool DaemonDeployer::requiredNodesActive()
			{
				return ((this->activeNameNode) && (this->activeResourceManager));
			}

			shared_ptr<NameNodeDaemon> DaemonDeployer::pickNameNode()
			{
				set<shared_ptr<Daemon>> nameNodes = this->daemonCollection->getDaemonsForType(HadoopDaemonType::NAMENODE);
				if (nameNodes.size() >= 1) {
					return static_pointer_cast<NameNodeDaemon>(*nameNodes.begin());
				} else {
					return shared_ptr<NameNodeDaemon>();
				}
			}

			shared_ptr<ResourceManagerDaemon> DaemonDeployer::pickResourceManager()
			{
				set<shared_ptr<Daemon>> resourceManagers = this->daemonCollection->getDaemonsForType(HadoopDaemonType::RESOURCEMANAGER);
				if (resourceManagers.size() >= 1) {
					return static_pointer_cast<ResourceManagerDaemon>(*resourceManagers.begin());
				} else {
					return shared_ptr<ResourceManagerDaemon>();
				}
			}

		}
	}
}
