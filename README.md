Nebu Hadoop Extension
===

The Nebu Hadoop Extension (nebu-hadoop) is an application that uses the Nebu system to provide virtualization-awareness to Hadoop (requires Hadoop version >= 2.4.0). It must be deployed on a machine that has SSH access to the machines that will run Hadoop. Nebu-hadoop polls the Nebu core system for virtual machines. Whenever new machines are deployed through Nebu, the Hadoop extension will deploy Hadoop on those machines and add them to the cluster.

Deploying the Nebu Hadoop Extension
---

To deploy the Nebu Hadoop Extension, you need to have a running instance of the [Nebu core system](https://github.com/deltaforge/nebu-core). For this guide, we will assume this instance is running at nebu-master:1234 (can be anywhere as long as the host is accessible and the port is open). Before starting the Hadoop extension, you will need to create an application in the Nebu system (using the /app POST request). We will assume this application's id is "my-hadoop-application". The Nebu Hadoop Extension must have SSH access to the machines that will be launched by Nebu (i.e. it should be placed in the same VLAN), and it is recommended to run the Nebu Hadoop Extension on a small, separate machine. You can start the application using:

	nebu-hadoop --app my-hadoop-application --nebu nebu-master:1234

Note that nebu-hadoop does not currently daemonize, so it is recommended to run it using e.g. screen.

To add nodes to the Hadoop extension using the default configuration, create and deploy three VM templates in Nebu:

| Daemon type | Hostname prefix | Amount |
| --- | --- | --- |
| Namenode | hadoop-name- | 1 |
| Resource Manager | hadoop-res- | 1 |
| Datanode | hadoop-data- | N |

Requirements for Virtual Machine template
---

The virtual machines for the different daemons can all use the same base template (a VM to clone). The requirements for this template are:

 * The virtual machine must have Hadoop version 2.4.0 or higher (can be deployed through e.g. puppet).
 * The virtual machine must have a user called "hadoop" with full access to the Hadoop directory.
 * The hadoop user must be accessible through passwordless SSH from the account and machine running the Nebu Hadoop Extension.
 * The home directory of the hadoop user should contain:
   * A directory called "hadoop" linking to $HADOOP\_HOME.
   * An (empty) file called ".puppetcomplete" to signal that Hadoop is available (a hack used during development to detect when puppet had completed, will be changed in the future".
 * The directory /data/hadoop owned by the hadoop user.
 * Due to limitations in Hadoop, it is not possible to have iptables active on the virtual machines.

The specific directory structure, names, etc. can be changed by editing the bash files in the scripts/ directory of this repository, and by editing the Hadoop configuration files in hadoop/etc/hadoop/.

Notes
---

 * Nebu-hadoop can not (yet) detect the number of cores and memory available for Hadoop on each worker. These should be constant values across the deployment (i.e. heterogeneous clusters are not yet supported) and can be set in hadoop/etc/hadoop/yarn-site.xml.

Dependencies
---

Runtime dependencies:

 * [libnebu-app-framework](https://github.com/deltaforge/nebu-app-framework-cpp), version 0.1.
 
Compile dependencies:

 * automake, version 2.61
 * g++, version 4.4.7
 * Development packages of the runtime dependencies.
 
Compiling
---

To compile libnebu-app-framework, execute the following commands:

	./bootstrap
    ./configure
    make
    make install

License
---

The Nebu Hadoop Extension is distributed under the LGPL version 3 license. See the provided LICENSE file for more information.
