# Top-level output directory
OUTDIR = build

# Test executable output directory
OUTTEST = $(OUTDIR)\test

# Output library name
OUTLIB = gaym.lib

# Include directory
INCDIR = include

# Source file directory
SRCDIR = src

# Test file directory
TESTDIR = test

# C++ compiler
CC = cl

# Compiler options
CCOPTS = /EHsc /I$(INCDIR) /c /nologo

# Test compiler options
CCTESTOPTS = /EHsc /I$(INCDIR) /nologo

# Linker
LINK = link

# Linker options
LINKOPTS = /nologo

# Static library builder
LIB = lib

# Library builder options
LIBOPTS = /nologo

logger.obj: {$(SRCDIR)}logger.cpp
	$(CC) $** $(CCOPTS) /Fo$(OUTDIR)\$@

logger_test.exe: {$(TESTDIR)}logger_test.cpp logger.obj
	$(CC) $(TESTDIR)\logger_test.cpp $(CCOPTS) /Fo$(OUTDIR)\logger_test.obj
	$(LINK) $(LINKOPTS) $(OUTDIR)\logger_test.obj $(OUTDIR)\logger.obj /OUT:$(OUTTEST)\$@
