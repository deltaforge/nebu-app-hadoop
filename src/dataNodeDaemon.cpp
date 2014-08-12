
#include "dataNodeDaemon.h"
#include "hadoopConfiguration.h"
#include "nebu-app-framework/commandRunner.h"

#include <log4cxx/logger.h>

// Using declarations - standard library
using std::shared_ptr;
using std::string;

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("nebu.app.hadoop.DataNodeDaemon"));

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{

			bool DataNodeDaemon::launch()
			{
				LOG4CXX_TRACE(logger, "Launching data node '" << this->getHostname() << "'");

				int result = NEBU_RUNCOMMAND("scripts/launch-datanode.sh '" +
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
