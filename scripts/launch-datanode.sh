#!/bin/sh

# Usage launch-datanode.sh output-dir datanode-FQDN

if [ $# -lt "2" ]; then
    echo "Invalid call to $0";
    exit 1;
fi

CONFIG=$1
DATANODE=$2

ssh hadoop@$DATANODE 'test -f .puppetcomplete'
if [ $? -ne "0" ]; then
	exit 2;
fi

scp -r $CONFIG/hadoop hadoop@$DATANODE:

ssh -tt hadoop@$DATANODE '. hadoop/etc/hadoop/sourceAll.sh && $HADOOP_PREFIX/sbin/hadoop-daemon.sh start datanode'
if [ $? -ne "0" ]; then
	exit 3;
fi

ssh -tt hadoop@$DATANODE '. hadoop/etc/hadoop/sourceAll.sh && $HADOOP_PREFIX/sbin/yarn-daemon.sh start nodemanager'
if [ $? -ne "0" ]; then
	exit 4;
fi

