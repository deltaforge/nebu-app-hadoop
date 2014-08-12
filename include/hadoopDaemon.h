
#ifndef NEBUAPPHADOOP_HADOOPDAEMON_H_
#define NEBUAPPHADOOP_HADOOPDAEMON_H_

#include "nebu-app-framework/daemon.h"

namespace nebu
{
	namespace app
	{
		namespace hadoop
		{
			namespace HadoopDaemonType {
				enum {
					UNKNOWN,
					NAMENODE,
					DATANODE,
					RESOURCEMANAGER
				};
			}
		}
	}
}

#endif
