#!/bin/sh

# Usage launch-resourcemanager.sh output-dir resourcemanager-FQDN

if [ $# -lt "2" ]; then
    echo "Invalid call to $0";
    exit 1;
fi

CONFIG=$1
RESOURCEMANAGER=$2

ssh hadoop@$RESOURCEMANAGER 'test -f .puppetcomplete'
if [ $? -ne "0" ]; then
	exit 2;
fi

scp -r $CONFIG/hadoop hadoop@$RESOURCEMANAGER:

ssh -tt hadoop@$RESOURCEMANAGER '. hadoop/etc/hadoop/sourceAll.sh && $HADOOP_PREFIX/sbin/yarn-daemon.sh start resourcemanager'
if [ $? -ne "0" ]; then
	exit 3;
fi

