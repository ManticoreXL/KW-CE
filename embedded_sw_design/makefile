########## Path for uCOS-II core source files #################################
UCOS_SRC=C:\SOFTWARE\PROJECT\SOURCE

########## Path for uCOS-II WIN32 port source files ###########################
UCOS_PORT_SRC=C:\SOFTWARE\uCOS-II\Ports\80x86\WIN32\VC\src

########## Path for uCOS-II WIN32 example source files ########################
UCOS_PORT_EX=.\

UCOS_APP_SRC=.\APP

########## Name of Example source file ########################################
MAIN=main.c

all:
	cl /MD /I$(UCOS_APP_SRC) /I$(UCOS_SRC) /I$(UCOS_PORT_SRC) /I$(UCOS_PORT_EX) $(MAIN) $(UCOS_APP_SRC)\task.c $(UCOS_SRC)\ucos_ii.c $(UCOS_PORT_SRC)\pc.c $(UCOS_PORT_SRC)\os_cpu_c.c  winmm.lib user32.lib

clean:
	@if exist *.obj del *.obj
	@if exist *.bak del *.bak
	@if exist *.pdb del *.pdb
	@if exist *.ilk del *.ilk
	@if exist *.log del *.log	
	