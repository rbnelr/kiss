#import faulthandler
#faulthandler.enable()

#def frame(inp):
#
#	draw_circle((0,0))

import kiss

kiss.open_window(caption="Title")

while True:

	inp = kiss.get_input()

	if inp.close:
		break
	
	#frame(inp)

	kiss.swap_buffers()

kiss.close_window()

pass