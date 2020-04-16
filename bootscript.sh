#/bin/sh

make
if ["$1" = "ts_server"]
then
	ts_server
fi