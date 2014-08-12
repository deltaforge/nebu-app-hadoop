
#include "daemonDeployer.h"
#include "daemonManager.h"
#include "hadoopApplication.h"
#include "hadoopConfiguration.h"

#include "nebu-app-framework/topologyManager.h"
#include "nebu-app-framework/topologyWriter.h"
#include "nebu-app-framework/vmManager.h"

// Using declarations - standard library
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::vector;
// Using declarations - nebu-app-framework
using nebu::app::framework::Configuration;
using nebu::app::framework::DaemonCollection;
using nebu::app::framework::TopologyWriter;

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{

			void HadoopApplication::registerConfigurationOptions()
			{
				Configuration::addCommandLineOption("--datanode-prefix", CONFIG_HADOOP_DATANODE_HOSTPREFIX);
				Configuration::addCommandLineOption("--namenode-prefix", CONFIG_HADOOP_NAMENODE_HOSTPREFIX);
				Configuration::addCommandLineOption("--resource-prefix", CONFIG_HADOOP_RESOURCEMANAGER_HOSTPREFIX);
				Configuration::addCommandLineOption("--configdir", CONFIG_HADOOP_CONFIGDIR);
				Configuration::addCommandLineOption("--topologyfile", CONFIG_HADOOP_TOPOLOGYFILE);

				Configuration::addDefaultValue(CONFIG_HADOOP_DATANODE_HOSTPREFIX, "hadoop-data-");
				Configuration::addDefaultValue(CONFIG_HADOOP_NAMENODE_HOSTPREFIX, "hadoop-name-");
				Configuration::addDefaultValue(CONFIG_HADOOP_RESOURCEMANAGER_HOSTPREFIX, "hadoop-res-");
				Configuration::addDefaultValue(CONFIG_HADOOP_CONFIGDIR, "/tmp/nebu-hadoop-config");
				Configuration::addDefaultValue(CONFIG_HADOOP_TOPOLOGYFILE, "/tmp/nebu-hadoop-topology");
			}

			void HadoopApplication::initialise(string command __attribute__((unused)),
					vector<string> &arguments __attribute__((unused)))
			{
				this->topologyWriter = make_shared<TopologyWriter>();
				this->topologyWriter->setFilename(CONFIG_GET(CONFIG_HADOOP_TOPOLOGYFILE));
			}

			void HadoopApplication::postRefreshTopology()
			{
				this->topologyWriter->write(this->getTopologyManager()->getRoot(),
						this->getVMManager()->getVMs());
			}

			shared_ptr<framework::DaemonManager> HadoopApplication::getDaemonManager()
			{
				if (!this->daemonManager) {
					shared_ptr<DaemonDeployer> daemonDeployer = make_shared<DaemonDeployer>(this->getDaemonCollection(),
							this->getTopologyManager());
					this->daemonManager = make_shared<DaemonManager>(this->getDaemonCollection(), daemonDeployer);
				}
				return this->daemonManager;
			}

		}
	}
}

namespace nebu
{
	namespace app
	{
		namespace framework
		{

			shared_ptr<ApplicationHooks> initApplication()
			{
				return make_shared<nebu::app::hadoop::HadoopApplication>();
			}

		}
	}
}
