#/bin/sh


if [ "$1" == "ts_server" ]
then
	echo "Server is booting up..."
	./ts_server -p $2 -h $3 -r $4 	
fi

if [ "$1" == "ts_routing" ]
then
	echo "Router is booting up..."
	./ts_routing $2
fi