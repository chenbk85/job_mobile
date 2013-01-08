
cfg = {
    # max room user
	"MaxUser":2,
    # ignore this configuration
	"Category":[
		"category=0:max_user=4000:low_rank=0:high_rank=2",
		"category=1:max_user=4000:low_rank=1:high_rank=3",
		"category=2:max_user=4000:low_rank=3:high_rank=5",
		"category=3:max_user=4000:low_rank=4:high_rank=6",
		"category=4:max_user=4000:low_rank=5:high_rank=8",
#		"category=5:money=50000:limitmoney=500000:Enter=0:person=100"
	],
    # game server list configure
	"GameList": {
        # format : category_id:[(game_server_ip, game_server_port, room_number_begin, room_number_end)]
		0:[("127.0.0.1", 15630, 0, 1000)],
		1:[("127.0.0.1", 15630, 1000, 2000)]
	},
	# presend server ip/port configure
	"Presence": ("127.0.0.1", 15610),
}
	


