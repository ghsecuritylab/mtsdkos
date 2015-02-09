#
# $Id: //WIFI_SOC/MP/SDK_4_3_0_0/RT288x_SDK/source/user/openswan-2.6.22/testing/baseconfigs/net.road.sh#1 $
#
if [ -n "$UML_northpublic_CTL" ]
then
    net_eth0="eth0=daemon,10:00:00:ab:cd:02,unix,$UML_northpublic_CTL,$UML_northpublic_DATA";
else
    net_eth0="eth0=mcast,10:00:00:96:96:A1,239.192.3.2,31205"
fi

net="$net_eth0"

