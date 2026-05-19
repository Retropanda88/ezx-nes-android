
CC	=	gcc
CXX	=	g++

CFLAGS	=	-O2 -ffast-math -fstrict-aliasing -fomit-frame-pointer 
CXXFLAGS=	-O2 -ffast-math -fstrict-aliasing -fomit-frame-pointer -fno-exceptions 

INCPATH	=	-I$(ARM_DEV_DIR)/include -I$(QTDIR)/include -I$(QTDIR)/include/ezx
LINK	=	arm-linux-g++
LFLAGS	=	
LIBS	=	
MOC	=	moc

OBJS = .obj/nes_apu.o .obj/nes_apu_wrapper.o \
	.obj/nes6502.o .obj/nes_6502.o \
	.obj/libsnss.o \
	.obj/nes_ppu.o \
	.obj/nes_device_cclimber.o .obj/nes_device_gun.o .obj/nes_device_kbd.o .obj/nes_device_hypershot.o \
	.obj/nes_device_mic.o .obj/nes_device_paddle.o .obj/nes_device_mahjong.o \
	.obj/000.o .obj/001.o .obj/002.o .obj/003.o .obj/004.o .obj/005.o .obj/006.o \
	.obj/007.o .obj/008.o .obj/009.o .obj/010.o .obj/011.o .obj/013.o .obj/015.o \
	.obj/016.o .obj/017.o .obj/018.o .obj/019.o .obj/020.o .obj/021.o .obj/022.o \
	.obj/023.o .obj/024.o .obj/025.o .obj/026.o .obj/032.o .obj/033.o .obj/034.o \
	.obj/040.o .obj/041.o .obj/042.o .obj/043.o .obj/044.o .obj/045.o .obj/046.o \
	.obj/047.o .obj/048.o .obj/049.o .obj/050.o .obj/051.o .obj/052.o .obj/057.o \
	.obj/058.o .obj/060.o .obj/064.o .obj/065.o .obj/066.o .obj/067.o .obj/068.o \
	.obj/069.o .obj/070.o .obj/071.o .obj/072.o .obj/073.o .obj/075.o .obj/076.o \
	.obj/077.o .obj/078.o .obj/079.o .obj/080.o .obj/082.o .obj/083.o .obj/085.o \
	.obj/086.o .obj/087.o .obj/088.o .obj/089.o .obj/090.o .obj/091.o .obj/092.o \
	.obj/092.o .obj/093.o .obj/094.o .obj/095.o .obj/096.o .obj/097.o .obj/099.o \
	.obj/100.o .obj/101.o .obj/105.o .obj/112.o .obj/113.o .obj/117.o .obj/118.o \
	.obj/119.o .obj/122.o .obj/151.o .obj/160.o .obj/180.o .obj/181.o .obj/182.o \
	.obj/183.o .obj/185.o .obj/187.o .obj/188.o .obj/189.o .obj/225.o .obj/226.o \
	.obj/226.o .obj/227.o .obj/228.o .obj/229.o .obj/230.o .obj/231.o .obj/232.o \
	.obj/233.o .obj/234.o .obj/235.o .obj/236.o .obj/237.o .obj/240.o .obj/242.o \
	.obj/243.o .obj/245.o .obj/246.o .obj/248.o .obj/255.o .obj/getmapper.o \
	.obj/nes.o .obj/nes_mapper.o .obj/nes_pad.o .obj/nes_rom.o .obj/snss.o .obj/nnnesterj_cheat.o
	
#	 \ .obj/nsf.o .obj/163.o

all: $(OBJS)
	ar -cru nes.a $(OBJS)
	ranlib  nes.a

.obj/nes_apu.o: nes_apu.c nes_exsound.cpp nes_vrc6.cpp nes_vrc7.cpp nes_fds.cpp nes_mmc5.cpp nes_n106.cpp nes_fme7.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.obj/nes_apu_wrapper.o: nes_apu_wrapper.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


.obj/nes6502.o: nes6502.c
	$(CC) $(CFLAGS) -c $< -o $@

.obj/nes_6502.o: nes_6502.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


.obj/libsnss.o: libsnss.c
	$(CC) $(CFLAGS) -c $< -o $@
	
.obj/nes_ppu.o: nes_ppu.cpp nes_ppu.h render_bg.cpp render_tile.cpp render_spr.cpp render_spr_tile.cpp do_scanline.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


.obj/nes_device_cclimber.o: nes_device_cclimber.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/nes_device_gun.o: nes_device_gun.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/nes_device_kbd.o: nes_device_kbd.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/nes_device_hypershot.o: nes_device_hypershot.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/nes_device_mic.o: nes_device_mic.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/nes_device_paddle.o: nes_device_paddle.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/nes_device_mahjong.o: nes_device_mahjong.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

	
.obj/000.o: 000.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/001.o: 001.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/002.o: 002.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/003.o: 003.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/004.o: 004.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/005.o: 005.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/006.o: 006.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/007.o: 007.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/008.o: 008.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/009.o: 009.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/010.o: 010.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/011.o: 011.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/013.o: 013.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/015.o: 015.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/016.o: 016.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.obj/017.o: 017.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/018.o: 018.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/019.o: 019.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/020.o: 020.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/021.o: 021.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/022.o: 022.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/023.o: 023.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/024.o: 024.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/025.o: 025.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/026.o: 026.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/032.o: 032.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/033.o: 033.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/034.o: 034.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/040.o: 040.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/041.o: 041.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/042.o: 042.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/043.o: 043.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/044.o: 044.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/045.o: 045.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/046.o: 046.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/047.o: 047.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/048.o: 048.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/049.o: 049.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/050.o: 050.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/051.o: 051.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/052.o: 052.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/057.o: 057.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/058.o: 058.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/060.o: 060.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/064.o: 064.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/065.o: 065.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/066.o: 066.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/067.o: 067.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/068.o: 068.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/069.o: 069.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/070.o: 070.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/071.o: 071.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/072.o: 072.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/073.o: 073.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/075.o: 075.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/076.o: 076.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/077.o: 077.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/078.o: 078.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/079.o: 079.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/080.o: 080.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/082.o: 082.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/083.o: 083.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/085.o: 085.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/086.o: 086.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/087.o: 087.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/088.o: 088.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/089.o: 089.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/090.o: 090.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/091.o: 091.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/092.o: 092.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/093.o: 093.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/094.o: 094.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/095.o: 095.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/096.o: 096.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/097.o: 097.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/099.o: 099.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/100.o: 100.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/101.o: 101.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/102.o: 102.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/105.o: 105.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/112.o: 112.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/113.o: 113.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/117.o: 117.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/118.o: 118.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/119.o: 119.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/122.o: 122.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/151.o: 151.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/160.o: 160.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/180.o: 180.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/181.o: 181.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/182.o: 182.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/183.o: 183.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/185.o: 185.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/187.o: 187.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/188.o: 188.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/189.o: 189.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/225.o: 225.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/226.o: 226.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/227.o: 227.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/228.o: 228.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/229.o: 229.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/230.o: 230.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/231.o: 231.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/232.o: 232.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/233.o: 233.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/234.o: 234.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/235.o: 235.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/236.o: 236.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/237.o: 237.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/240.o: 240.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/242.o: 242.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/243.o: 243.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/245.o: 245.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/246.o: 246.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/248.o: 248.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/255.o: 255.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/nsf.o: nsf.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/getmapper.o: getmapper.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/nes.o: nes.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/nes_mapper.o: nes_mapper.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/nes_pad.o: nes_pad.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/nes_rom.o: nes_rom.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/snss.o: snss.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.obj/nnnesterj_cheat.o: nnnesterj_cheat.c
	$(CC) $(CLAGS) -c $< -o $@


.obj/163.o: 163.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f .obj/*.o
	rm -f nes.a
