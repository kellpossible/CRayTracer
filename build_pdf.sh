#!/bin/sh
python2 Source2Pdf.py --ext c h Makefile --exclude .*Dependencies.* .*nbproject.* .*[.]hg.* .*AssemblyInfo.* .*gtk-gui.* -o RayTracer.pdf --user-name "Luke Frisken" --project-name RayTracer
