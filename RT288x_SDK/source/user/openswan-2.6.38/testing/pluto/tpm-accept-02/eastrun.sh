echo "Adding group-2 policy"

ipsec whack --name west--east-psk-grp2 --delete
ipsec whack --name west--east-psk-grp3 --delete

ipsec whack --name west--east-psk-grp2 --encrypt --tunnel --pfs --dpdaction "hold" --psk --host "192.1.2.45" --nexthop "192.1.2.23" --updown "ipsec _updown" --id "192.1.2.45"  --sendcert "always" --to --host "192.1.2.23" --nexthop "192.1.2.45" --updown "ipsec _updown" --id "192.1.2.23"  --sendcert "always" --ipseclifetime "28800" --rekeymargin "540" --ikealg "3des-sha1-modp1024" --impair-die-oninfo --keyingtries "0"    

ipsec whack --name west--east-psk-grp2 --initiate

echo done
