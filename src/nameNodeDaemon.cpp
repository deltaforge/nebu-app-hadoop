
#include "hadoopConfiguration.h"
#include "nameNodeDaemon.h"

#include "nebu-app-framework/commandRunner.h"

#include <log4cxx/logger.h>

// Using declarations - standard library
using std::shared_ptr;
using std::string;

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("nebu.app.hadoop.NameNodeDaemon"));

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{

			bool NameNodeDaemon::updateTopologyTable()
			{
				LOG4CXX_TRACE(logger, "Updating topology table on name node '" << this->getHostname() << "'");

				int result = NEBU_RUNCOMMAND("scripts/update-topology.sh '" +
						CONFIG_GET(CONFIG_HADOOP_TOPOLOGYFILE) + "' '" +
						this->getHostname() + "'");

				LOG4CXX_TRACE(logger, "Topology update finished with result: " << result);

				return result == 0;
			}

			bool NameNodeDaemon::launch()
			{
				LOG4CXX_TRACE(logger, "Launching name node '" << this->getHostname() << "'");

				int result = NEBU_RUNCOMMAND("scripts/launch-namenode.sh '" +
						CONFIG_GET(CONFIG_HADOOP_CONFIGDIR) +
						"' '" + this->getHostname() + "'");

				if (result == 0) {
					this->launched = true;
					LOG4CXX_DEBUG(logger, "Launch Successfull: " << this->getHostname());
				}
				return this->hasLaunched();
			}

		}
	}
}

