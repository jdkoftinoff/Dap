PROJECT=jdksdap
PROJECT_NAME=jdksdap
PROJECT_VERSION=20140914
PROJECT_EMAIL=jeffk@jdkoftinoff.com
PROJECT_LICENSE=BSD
PROJECT_MAINTAINER=jeffk@jdkoftinoff.com
PROJECT_COPYRIGHT=Copyright 2014
PROJECT_DESCRIPTION=jdksdap
PROJECT_WEBSITE=http://github.com/jdkoftinoff/jdksdap
PROJECT_IDENTIFIER=com.jdkoftinoff.jdksdap
TOP_LIB_DIRS+=.
CONFIG_TOOLS+=
PKGCONFIG_PACKAGES+=

CXXFLAGS+=-std=c++11 -stdlib=libc++

