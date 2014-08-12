
AM_CPPFLAGS = -pthread -I\$(top_srcdir)/include -std=c++0x -Wall -Wextra $(LOG4CXX_CFLAGS)
LDFLAGS += -pthread
if TESTS_ENABLED
AM_CPPFLAGS += --coverage -O0 -g -fno-default-inline -fno-inline
LDFLAGS += --coverage
else
AM_CPPFLAGS += -O2
endif

src_SOURCES = \
	daemonDeployer.cpp \
	daemonManager.cpp \
	dataNodeDaemon.cpp \
	hadoopApplication.cpp \
	nameNodeDaemon.cpp \
	resourceManagerDaemon.cpp

bin_PROGRAMS = $(top_builddir)/hadoop-nebu

__top_builddir__hadoop_nebu_SOURCES = $(src_SOURCES)
__top_builddir__hadoop_nebu_LDFLAGS = $(LDFLAGS)
__top_builddir__hadoop_nebu_LDADD = $(NEBU_APP_FRAMEWORK_LIBS) $(LOG4CXX_LIBS) $(TINYXML2_LIBS) -lrestclient-cpp
