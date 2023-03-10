TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        heap_4.c \
        main.c \
        port/os_win.c \
        shell.c \
        sqlite-bench/bench_main.c \
        sqlite-bench/benchmark.c \
        sqlite-bench/histogram.c \
        sqlite-bench/random.c \
        sqlite-bench/raw.c \
        sqlite-bench/util.c \
        sqlite3.c \
        sqlite3_demo.c

HEADERS += \
    config.h \
    heap_4.h \
    sqlite-bench/bench.h \
    sqlite3.h \
    sqlite3ext.h

INCLUDEPATH += \
    . \
    port \
    sqlite-bench\
