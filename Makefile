#############################################################################
# Makefile for building: tr-sub
# Generated by qmake (2.01a) (Qt 4.6.2) on: Wed Nov 17 18:30:26 2010
# Project:  tr-sub.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile tr-sub.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I/mnt/ubuntu_home/sgh/prj/ixmaps/tr-sub/. -I. -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = MainWindow.cpp \
		SettingsDialog.cpp \
		BatchRunDialog.cpp \
		SingleRunDialog.cpp \
		main.cpp \
		TrHttp.cpp \
		HttpGet.cpp \
		traceroute.cpp \
		IPv4Privacy.cpp \
		ixmaps-wizard.cpp \
		TrWorkItem.cpp \
		ServerComm.cpp \
		TrStatus.cpp \
		TrDo.cpp \
		TrStatBrowser.cpp \
		PStatus.cpp moc_MainWindow.cpp \
		moc_TrHttp.cpp \
		moc_HttpGet.cpp \
		moc_SettingsDialog.cpp \
		moc_BatchRunDialog.cpp \
		moc_SingleRunDialog.cpp \
		moc_ixmaps-wizard.cpp \
		moc_ServerComm.cpp \
		moc_TrStatus.cpp \
		moc_TrDo.cpp \
		moc_PStatus.cpp
OBJECTS       = MainWindow.o \
		SettingsDialog.o \
		BatchRunDialog.o \
		SingleRunDialog.o \
		main.o \
		TrHttp.o \
		HttpGet.o \
		traceroute.o \
		IPv4Privacy.o \
		ixmaps-wizard.o \
		TrWorkItem.o \
		ServerComm.o \
		TrStatus.o \
		TrDo.o \
		TrStatBrowser.o \
		PStatus.o \
		moc_MainWindow.o \
		moc_TrHttp.o \
		moc_HttpGet.o \
		moc_SettingsDialog.o \
		moc_BatchRunDialog.o \
		moc_SingleRunDialog.o \
		moc_ixmaps-wizard.o \
		moc_ServerComm.o \
		moc_TrStatus.o \
		moc_TrDo.o \
		moc_PStatus.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		tr-sub.pro
QMAKE_TARGET  = tr-sub
DESTDIR       = 
TARGET        = tr-sub

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_about.h ui_mainwindow.h ui_settings.h ui_batchrun.h ui_singlerun.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: tr-sub.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtNetwork.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile tr-sub.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtNetwork.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile tr-sub.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/tr-sub1.0.0 || $(MKDIR) .tmp/tr-sub1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/tr-sub1.0.0/ && $(COPY_FILE) --parents MainWindow.h TrHttp.h HttpGet.h traceroute.h SettingsDialog.h BatchRunDialog.h SingleRunDialog.h IPv4Privacy.h ixmaps-wizard.h TrWorkItem.h ServerComm.h TrStatus.h TrDo.h TrStatBrowser.h PStatus.h .tmp/tr-sub1.0.0/ && $(COPY_FILE) --parents MainWindow.cpp SettingsDialog.cpp BatchRunDialog.cpp SingleRunDialog.cpp main.cpp TrHttp.cpp HttpGet.cpp traceroute.cpp IPv4Privacy.cpp ixmaps-wizard.cpp TrWorkItem.cpp ServerComm.cpp TrStatus.cpp TrDo.cpp TrStatBrowser.cpp PStatus.cpp .tmp/tr-sub1.0.0/ && $(COPY_FILE) --parents about.ui mainwindow.ui settings.ui batchrun.ui singlerun.ui .tmp/tr-sub1.0.0/ && (cd `dirname .tmp/tr-sub1.0.0` && $(TAR) tr-sub1.0.0.tar tr-sub1.0.0 && $(COMPRESS) tr-sub1.0.0.tar) && $(MOVE) `dirname .tmp/tr-sub1.0.0`/tr-sub1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/tr-sub1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_MainWindow.cpp moc_TrHttp.cpp moc_HttpGet.cpp moc_SettingsDialog.cpp moc_BatchRunDialog.cpp moc_SingleRunDialog.cpp moc_ixmaps-wizard.cpp moc_ServerComm.cpp moc_TrStatus.cpp moc_TrDo.cpp moc_PStatus.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_MainWindow.cpp moc_TrHttp.cpp moc_HttpGet.cpp moc_SettingsDialog.cpp moc_BatchRunDialog.cpp moc_SingleRunDialog.cpp moc_ixmaps-wizard.cpp moc_ServerComm.cpp moc_TrStatus.cpp moc_TrDo.cpp moc_PStatus.cpp
moc_MainWindow.cpp: ui_mainwindow.h \
		TrWorkItem.h \
		TrStatus.h \
		TrDo.h \
		ServerComm.h \
		PStatus.h \
		MainWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) MainWindow.h -o moc_MainWindow.cpp

moc_TrHttp.cpp: TrStatus.h \
		TrHttp.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) TrHttp.h -o moc_TrHttp.cpp

moc_HttpGet.cpp: HttpGet.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) HttpGet.h -o moc_HttpGet.cpp

moc_SettingsDialog.cpp: ui_settings.h \
		SettingsDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) SettingsDialog.h -o moc_SettingsDialog.cpp

moc_BatchRunDialog.cpp: ui_batchrun.h \
		BatchRunDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) BatchRunDialog.h -o moc_BatchRunDialog.cpp

moc_SingleRunDialog.cpp: ui_singlerun.h \
		SingleRunDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) SingleRunDialog.h -o moc_SingleRunDialog.cpp

moc_ixmaps-wizard.cpp: TrDo.h \
		TrWorkItem.h \
		TrStatus.h \
		ServerComm.h \
		PStatus.h \
		TrStatBrowser.h \
		ixmaps-wizard.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ixmaps-wizard.h -o moc_ixmaps-wizard.cpp

moc_ServerComm.cpp: TrStatus.h \
		ServerComm.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ServerComm.h -o moc_ServerComm.cpp

moc_TrStatus.cpp: TrStatus.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) TrStatus.h -o moc_TrStatus.cpp

moc_TrDo.cpp: TrWorkItem.h \
		TrStatus.h \
		ServerComm.h \
		PStatus.h \
		TrDo.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) TrDo.h -o moc_TrDo.cpp

moc_PStatus.cpp: PStatus.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) PStatus.h -o moc_PStatus.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_about.h ui_mainwindow.h ui_settings.h ui_batchrun.h ui_singlerun.h
compiler_uic_clean:
	-$(DEL_FILE) ui_about.h ui_mainwindow.h ui_settings.h ui_batchrun.h ui_singlerun.h
ui_about.h: about.ui
	/usr/bin/uic-qt4 about.ui -o ui_about.h

ui_mainwindow.h: mainwindow.ui
	/usr/bin/uic-qt4 mainwindow.ui -o ui_mainwindow.h

ui_settings.h: settings.ui
	/usr/bin/uic-qt4 settings.ui -o ui_settings.h

ui_batchrun.h: batchrun.ui
	/usr/bin/uic-qt4 batchrun.ui -o ui_batchrun.h

ui_singlerun.h: singlerun.ui
	/usr/bin/uic-qt4 singlerun.ui -o ui_singlerun.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

MainWindow.o: MainWindow.cpp MainWindow.h \
		ui_mainwindow.h \
		TrWorkItem.h \
		TrStatus.h \
		TrDo.h \
		ServerComm.h \
		PStatus.h \
		SettingsDialog.h \
		ui_settings.h \
		SingleRunDialog.h \
		ui_singlerun.h \
		BatchRunDialog.h \
		ui_batchrun.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MainWindow.o MainWindow.cpp

SettingsDialog.o: SettingsDialog.cpp SettingsDialog.h \
		ui_settings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SettingsDialog.o SettingsDialog.cpp

BatchRunDialog.o: BatchRunDialog.cpp BatchRunDialog.h \
		ui_batchrun.h \
		SettingsDialog.h \
		ui_settings.h \
		MainWindow.h \
		ui_mainwindow.h \
		TrWorkItem.h \
		TrStatus.h \
		TrDo.h \
		ServerComm.h \
		PStatus.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o BatchRunDialog.o BatchRunDialog.cpp

SingleRunDialog.o: SingleRunDialog.cpp SingleRunDialog.h \
		ui_singlerun.h \
		SettingsDialog.h \
		ui_settings.h \
		MainWindow.h \
		ui_mainwindow.h \
		TrWorkItem.h \
		TrStatus.h \
		TrDo.h \
		ServerComm.h \
		PStatus.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SingleRunDialog.o SingleRunDialog.cpp

main.o: main.cpp MainWindow.h \
		ui_mainwindow.h \
		TrWorkItem.h \
		TrStatus.h \
		TrDo.h \
		ServerComm.h \
		PStatus.h \
		ixmaps-wizard.h \
		TrStatBrowser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

TrHttp.o: TrHttp.cpp TrHttp.h \
		TrStatus.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TrHttp.o TrHttp.cpp

HttpGet.o: HttpGet.cpp HttpGet.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o HttpGet.o HttpGet.cpp

traceroute.o: traceroute.cpp traceroute.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o traceroute.o traceroute.cpp

IPv4Privacy.o: IPv4Privacy.cpp IPv4Privacy.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o IPv4Privacy.o IPv4Privacy.cpp

ixmaps-wizard.o: ixmaps-wizard.cpp ixmaps-wizard.h \
		TrDo.h \
		TrWorkItem.h \
		TrStatus.h \
		ServerComm.h \
		PStatus.h \
		TrStatBrowser.h \
		SettingsDialog.h \
		ui_settings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ixmaps-wizard.o ixmaps-wizard.cpp

TrWorkItem.o: TrWorkItem.cpp TrWorkItem.h \
		TrStatus.h \
		SettingsDialog.h \
		ui_settings.h \
		traceroute.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TrWorkItem.o TrWorkItem.cpp

ServerComm.o: ServerComm.cpp ServerComm.h \
		TrStatus.h \
		HttpGet.h \
		TrHttp.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ServerComm.o ServerComm.cpp

TrStatus.o: TrStatus.cpp TrStatus.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TrStatus.o TrStatus.cpp

TrDo.o: TrDo.cpp TrDo.h \
		TrWorkItem.h \
		TrStatus.h \
		ServerComm.h \
		PStatus.h \
		IPv4Privacy.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TrDo.o TrDo.cpp

TrStatBrowser.o: TrStatBrowser.cpp TrStatBrowser.h \
		TrStatus.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TrStatBrowser.o TrStatBrowser.cpp

PStatus.o: PStatus.cpp PStatus.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o PStatus.o PStatus.cpp

moc_MainWindow.o: moc_MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MainWindow.o moc_MainWindow.cpp

moc_TrHttp.o: moc_TrHttp.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_TrHttp.o moc_TrHttp.cpp

moc_HttpGet.o: moc_HttpGet.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_HttpGet.o moc_HttpGet.cpp

moc_SettingsDialog.o: moc_SettingsDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_SettingsDialog.o moc_SettingsDialog.cpp

moc_BatchRunDialog.o: moc_BatchRunDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_BatchRunDialog.o moc_BatchRunDialog.cpp

moc_SingleRunDialog.o: moc_SingleRunDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_SingleRunDialog.o moc_SingleRunDialog.cpp

moc_ixmaps-wizard.o: moc_ixmaps-wizard.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ixmaps-wizard.o moc_ixmaps-wizard.cpp

moc_ServerComm.o: moc_ServerComm.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ServerComm.o moc_ServerComm.cpp

moc_TrStatus.o: moc_TrStatus.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_TrStatus.o moc_TrStatus.cpp

moc_TrDo.o: moc_TrDo.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_TrDo.o moc_TrDo.cpp

moc_PStatus.o: moc_PStatus.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_PStatus.o moc_PStatus.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

