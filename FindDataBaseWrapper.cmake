# - Find DataBaseWrapper
# Find the DataBaseWrapper includes and library
# This module defines
#  DBWRAPPER_INCLUDE_DIR, where to find DataBase.h, and other headers.
#  DBWRAPPER_LIBRARIES, the libraries needed to use DataBaseWrapper.
#  DBWRAPPER_FOUND, If false, do not try to use DataBaseWrapper.
#
# Copyright (c) 2006, Jaroslaw Staniek, <js@iidea.pl>
#
# Adpated from FindSQLite3.cmake by Jonas M. Gastal, <jokerwww@gmail.com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if(DBWRAPPER_INCLUDE_DIR AND DBWRAPPER_LIBRARIES)
   set(DBWRAPPER_FOUND TRUE)

else(DBWRAPPER_INCLUDE_DIR AND DBWRAPPER_LIBRARIES)
  find_package( SQLITE3 REQUIRED )
  find_package( MySQL REQUIRED )

  find_path(DBWRAPPER_INCLUDE_DIR DataBase.h
      /usr/include/DataBaseWrapper
      /usr/local/include/DataBaseWrapper
      $ENV{ProgramFiles}/DataBaseWrapper/include
      $ENV{SystemDrive}/DataBaseWrapper/include
      $ENV{ProgramFiles}/DataBaseWrapper
      $ENV{SystemDrive}/DataBaseWrapper
      )
  set( DBWRAPPER_INCLUDE_DIR ${DBWRAPPER_INCLUDE_DIR} ${SQLITE3_INCLUDE_DIR} ${MYSQL_INCLUDE_DIR} )

  find_library(DBWRAPPER_LIBRARIES NAMES DataBaseWrapper
      PATHS
      /usr/lib
      /usr/local/lib
      $ENV{ProgramFiles}/DataBaseWrapper/lib
      $ENV{SystemDrive}/DataBaseWrapper/lib
      $ENV{ProgramFiles}/DataBaseWrapper
      $ENV{SystemDrive}/DataBaseWrapper
      )

  if(DBWRAPPER_INCLUDE_DIR AND DBWRAPPER_LIBRARIES)
    set(DBWRAPPER_FOUND TRUE)
    message(STATUS "Found SQLite3: ${DBWRAPPER_INCLUDE_DIR}, ${DBWRAPPER_LIBRARIES}")
  else(DBWRAPPER_INCLUDE_DIR AND DBWRAPPER_LIBRARIES)
    set(DBWRAPPER_FOUND FALSE)
    message(STATUS "DataBaseWrapper not found.")
  endif(DBWRAPPER_INCLUDE_DIR AND DBWRAPPER_LIBRARIES)

  mark_as_advanced(DBWRAPPER_INCLUDE_DIR DBWRAPPER_LIBRARIES)

endif(DBWRAPPER_INCLUDE_DIR AND DBWRAPPER_LIBRARIES)
