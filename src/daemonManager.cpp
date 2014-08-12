
#include "daemonManager.h"
#include "daemonDeployer.h"
#include "dataNodeDaemon.h"
#include "hadoopConfiguration.h"
#include "nameNodeDaemon.h"
#include "resourceManagerDaemon.h"

#include "nebu-app-framework/commandRunner.h"
#include "nebu-app-framework/daemonCollection.h"

#include "log4cxx/logger.h"

// Using declarations - standard library
using std::make_shared;
using std::shared_ptr;
using std::string;
// Using declarations - nebu-common
using nebu::common::VirtualMachine;
// Using declarations - nebu-app-framework
using nebu::app::framework::CommandRunner;
using nebu::app::framework::Daemon;
using nebu::app::framework::DaemonCollection;
using nebu::app::framework::DaemonType;

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("nebu.app.hadoop.DaemonManager"));

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{

			DaemonManager::DaemonManager(shared_ptr<DaemonCollection> daemonCollection,
					shared_ptr<DaemonDeployer> deployer) :
					framework::DaemonManager(), daemonCollection(daemonCollection),
					deployer(deployer), generatedConfiguration(false)
			{

			}

			void DaemonManager::prepareConfiguration()
			{
				string configDir = CONFIG_GET(CONFIG_HADOOP_CONFIGDIR);
				shared_ptr<NameNodeDaemon> nameNode = this->deployer->getNameNode();
				shared_ptr<ResourceManagerDaemon> resourceManager = this->deployer->getResourceManager();

				NEBU_RUNCOMMAND("scripts/generate-config.sh '" + configDir + "' '" +
						nameNode->getHostname() + "' '" + resourceManager->getHostname() + "'");

				generatedConfiguration = true;
			}

			void DaemonManager::refreshDaemons()
			{
				this->deployer->identifyDaemons();
				if (!this->generatedConfiguration && this->deployer->getNameNode() &&
						this->deployer->getResourceManager())
				{
					LOG4CXX_INFO(logger, "Creating configuration for NameNode '" <<
							this->deployer->getNameNode()->getHostname() <<
							"' and ResourceManager '" <<
							this->deployer->getResourceManager()->getHostname() << "'");
					this->prepareConfiguration();
				}

				if (this->deployer->getNameNode()) {
					this->deployer->getNameNode()->updateTopologyTable();
				}
			}

			void DaemonManager::deployDaemons()
			{
				this->deployer->deployDaemons();
			}

			DaemonType getTypeFromHostname(const string &hostname)
			{
				if (hostname.find(CONFIG_GET(CONFIG_HADOOP_DATANODE_HOSTPREFIX)) == 0) {
					return HadoopDaemonType::DATANODE;
				} else if (hostname.find(CONFIG_GET(CONFIG_HADOOP_NAMENODE_HOSTPREFIX)) == 0) {
					return HadoopDaemonType::NAMENODE;
				} else if (hostname.find(CONFIG_GET(CONFIG_HADOOP_RESOURCEMANAGER_HOSTPREFIX)) == 0) {
					return HadoopDaemonType::RESOURCEMANAGER;
				}

				return HadoopDaemonType::UNKNOWN;
			}

			void DaemonManager::newVMAdded(shared_ptr<VirtualMachine> vm)
			{
				DaemonType daemonType = getTypeFromHostname(vm->getHostname());
				if (daemonType == HadoopDaemonType::UNKNOWN)
					return;

				shared_ptr<Daemon> daemon;
				switch (daemonType) {
				case HadoopDaemonType::DATANODE:
					daemon = make_shared<DataNodeDaemon>(vm);
					LOG4CXX_INFO(logger, "Registering DataNode: " << daemon->getHostname());
					break;
				case HadoopDaemonType::NAMENODE:
					daemon = make_shared<NameNodeDaemon>(vm);
					LOG4CXX_INFO(logger, "Registering NameNode: " << daemon->getHostname());
					break;
				case HadoopDaemonType::RESOURCEMANAGER:
					daemon = make_shared<ResourceManagerDaemon>(vm);
					LOG4CXX_INFO(logger, "Registering ResourceManager: " << daemon->getHostname());
					break;
				default:
					LOG4CXX_ERROR(logger, "Attempt to register VM of unknown type");
					return;
				}

				this->daemonCollection->addDaemon(daemon);
			}
			void DaemonManager::existingVMChanged(shared_ptr<VirtualMachine> vm __attribute__((unused)),
					const framework::VMEvent event __attribute__((unused)))
			{
				// NOT USED
			}
			void DaemonManager::oldVMRemoved(const VirtualMachine &vm __attribute__((unused)))
			{
				// NOT USED
			}

		}
	}
}

