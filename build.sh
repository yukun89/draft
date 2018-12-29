#!/bin/bash
set -exu
g++ -c asp.cpp
g++ -c sp.cpp
g++  sp.o asp.o
