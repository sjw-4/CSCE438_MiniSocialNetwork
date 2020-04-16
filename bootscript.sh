#/bin/sh


if [ "$1" == "ts_server" ]
then
	./ts_server -p $2 -h $3 -r $4 	
fi

if [ "$1" == "ts_routing" ]
then
	./ts_routing $2
fi