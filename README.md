# CSCE438_MiniSocialNetwork
Assignment to build a mini social network interfaced with terminal

To run with the script:
  1) run the routing server: bash bootscript.sh ts_routing -p <port no>
  2) run one or more servers: bash bootscript.sh ts_server -p <port no> -h <routing server IP> -r <routing server port no>
To run without the script:
  1) run the routing server:  ./ts_routing -p <port no>
  2) run one or more servers: ./ts_server -p <port no> -h <routing server IP> -r <routing server port no>
  3) run one or more clients: ./ts_client -u <username> -h <routing server IP> -p <routing server port no>
