# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

from waflib import Configure, Utils, Logs, Context
import os

VERSION = "0.1"
APPNAME = "signed-data1"



def options(opt):
    # gnu_dirs: Sets various standard variables such as INCLUDEDIR
    opt.load(['compiler_cxx', 'gnu_dirs'])

    opt.load(['default-compiler-flags', 'boost'],
              tooldir=['.waf-tools'])


def configure(conf):
    conf.load(['compiler_cxx', 'default-compiler-flags', 'boost', 'gnu_dirs'])

    conf.check_cfg(package='libndn-cxx', args=['--cflags', '--libs'],
                   uselib_store='NDN_CXX', mandatory=True)

    boost_libs = 'system iostreams random thread filesystem'

    conf.check_boost(lib=boost_libs)

    conf.write_config_header('config.h')

def build (bld):
    bld.recurse("src")

