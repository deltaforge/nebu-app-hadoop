#!/bin/sh

# Usage launch-namenode.sh output-dir namenode-FQDN

if [ $# -lt "2" ]; then
    echo "Invalid call to $0";
    exit 1;
fi

CONFIG=$1
NAMENODE=$2

ssh hadoop@$NAMENODE 'test -f .puppetcomplete'
if [ $? -ne "0" ]; then
	exit 2;
fi

scp -r $CONFIG/hadoop hadoop@$NAMENODE:

ssh -tt hadoop@$NAMENODE '. hadoop/etc/hadoop/sourceAll.sh && $HADOOP_PREFIX/bin/hdfs namenode -format'
if [ $? -ne "0" ]; then
	exit 3;
fi

ssh -tt hadoop@$NAMENODE '. hadoop/etc/hadoop/sourceAll.sh && $HADOOP_PREFIX/sbin/hadoop-daemon.sh start namenode'
if [ $? -ne "0" ]; then
	exit 4;
fi

