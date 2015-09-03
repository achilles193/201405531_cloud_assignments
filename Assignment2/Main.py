
from mininet.net import Mininet
from mininet.node import Controller
from mininet.cli import CLI
from mininet.log import setLogLevel, info
import time
import os
from mininet.link import TCLink
from mininet.node import RemoteController
import sys
def emptyNet():
    args=(sys.argv)
    hosts_per_switch=int(args[1])
    no_of_switches=int(args[2])
    no_of_hosts=hosts_per_switch*no_of_switches
    net_even='10.0.0.'
    net_odd='11.1.0.'
    net=Mininet(autoStaticArp=True,link=TCLink)
    net.addController(controller=RemoteController)
    hosts=[]
    switch=[]
    path=[]
    cur=1
    for i in range(no_of_hosts):
        if cur==1:
            hosts.append(net.addHost('h'+str(i+1),ip=net_even+str(i+1)))
            cur=0
        else:
            hosts.append(net.addHost('h'+str(i+1),ip=net_odd+str(i+1)))
            cur=1
    for i in range(no_of_switches):
        switch.append(net.addSwitch('s'+str(i+1)))  
    ctr=0
    for i in range(no_of_switches):
        for j in range(hosts_per_switch):
            path.append(net.addLink(hosts[ctr],switch[i]))
            ctr+=1
    bwl=1
    for i in range(len(path)):
        if bwl==1:
            path[i].intf1.config(bw=1)
            bwl=0
        else:
            path[i].intf1.config(bw=2)
            bwl=1
    for i in range(no_of_switches-1):
        path.append(net.addLink(switch[i],switch[i+1]))
    
    net.start()
    CLI(net)
    net.stop()
if __name__=='__main__':
    setLogLevel('info')
    emptyNet()

