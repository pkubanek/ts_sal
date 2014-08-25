##############################################################################
# pgmview - displays an image from the rover and allows the user to pick
#             a point to track using the on-board visual servoing software
#
# INPUTS:
#    title - title of the imageview window
#
# OUTPUTS:
#    none
#
# RETURNS:
#    none
##############################################################################
proc pgmview {file} {
    global imageFold imageAck imageResend;
    global picture;
    ##########################################################################
    # Bring up window
    toplevel .image;

    ##########################################################################
    # Set window manager options
    wm title .image $file;
    wm geometry .image +0+0;

    ##########################################################################
    # image display
    ##########################################################################
    frame .image.p;

    set picture [image create photo ];

    canvas .image.p.c -height 240 -width 256  \
	    -xscrollcommand ".image.p.bot.x set" \
	    -yscrollcommand ".image.p.y set";
    .image.p.c create image 0 0 -image $picture -anchor nw;
    #.image.p.c create line 0 0 50 50;
    pack .image.p

    # scrollbars
    frame .image.p.bot;
    scrollbar .image.p.bot.x -orient horiz \
	    -command {.image.p.c xview};
    frame .image.p.bot.fill -height 19 -width 19;
    pack append .image.p.bot \
	    .image.p.bot.x {left fillx expand} \
	    .image.p.bot.fill right;

    scrollbar .image.p.y -orient vert \
	    -command {.image.p.c yview};
    nddsImage $picture imgHeader imgPacket -newimage {
	puts $this(date);
	set iwidth [image width $picture];
	set iheight [image height $picture];
 	.image.p.c configure -scrollregion [list 0 0 $iwidth $iheight];
 	.image.p.c configure -width $iwidth;
 	.image.p.c configure -height $iheight;
    } -complete {
	puts "Finished grabbing image\n";
     } $imageFold $imageResend $imageAck;
    pack append .image.p \
	    .image.p.bot {bottom fillx} \
	    .image.p.y {right filly} \
	    .image.p.c {left expand}
}

set imageFold "";
set imageAck "imgResendSeq";
set imageResend "-resends";
set Ndds_tcl_debug_level    1;	 # turns on the verbose mode of nddswish
set picture "";
nddsConnect;
load libimagetcl.so

set Ndds_tcl_debug_level    2;	 # turns on the verbose mode of nddswish
pgmview test.pgm;		# bring up the live image window
bind all <Control-q> {exit};	# map Ctrl-q to quit
