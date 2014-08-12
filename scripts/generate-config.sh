#!/bin/sh

# Usage: generate-config output-dir namenode-FQDN resourcemanager-FQDN

if [ $# -lt "3" ]; then
    echo "Invalid call to $0";
    exit 1;
fi

CONFIGDIR=$1
NAMENODE=$2
RESOURCEMANAGER=$3

mkdir -p $CONFIGDIR
cp -R hadoop $CONFIGDIR/

sed -i "s/\\\$NAMENODE\\\$/$NAMENODE/" $CONFIGDIR/hadoop/etc/hadoop/core-site.xml
sed -i "s/\\\$RESOURCEMANAGER\\\$/$RESOURCEMANAGER/" $CONFIGDIR/hadoop/etc/hadoop/yarn-site.xml
