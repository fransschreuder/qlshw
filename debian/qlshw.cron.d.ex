#
# Regular cron jobs for the qlshw package
#
0 4	* * *	root	[ -x /usr/bin/qlshw_maintenance ] && /usr/bin/qlshw_maintenance
