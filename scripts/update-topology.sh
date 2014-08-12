#!/bin/sh

# Usage update-topology.sh topology-file namenode-FQDN

if [ $# -lt "2" ]; then
    echo "Invalid call to $0";
    exit 1;
fi

TOPOLOGYFILE=$1
NAMENODE=$2

ssh hadoop@$NAMENODE 'test -f .puppetcomplete'
if [ $? -ne "0" ]; then
    exit 2;
fi

OUTTOPOLOGYFILE=$(mktemp)
exec< $TOPOLOGYFILE
while read line; do
       split=( $line )
       ipaddr=$( dig +short ${split[0]} )
       if [ "$ipaddr" ]; then
               echo "$ipaddr ${split[1]}" >> $OUTTOPOLOGYFILE
       fi
done

scp $OUTTOPOLOGYFILE hadoop@$NAMENODE:hadoop/etc/hadoop/topology.table
rm $OUTTOPOLOGYFILE 

