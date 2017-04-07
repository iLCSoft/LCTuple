# LCTuple
[![Build Status](https://travis-ci.org/iLCSoft/LCTuple.svg?branch=master)](https://travis-ci.org/iLCSoft/LCTuple)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/12360/badge.svg)](https://scan.coverity.com/projects/ilcsoft-lctuple)

Marlin package that creates a ROOT TTree with a column wise ntuple from LCIO collections.

LCTuple is distributed under the [GPLv3 License](http://www.gnu.org/licenses/gpl-3.0.en.html)

[![License](https://www.gnu.org/graphics/gplv3-127x51.png)](https://www.gnu.org/licenses/gpl-3.0.en.html)

## Build LCTuple
```
./path/to/ilcsoft/installation/v01-XX/init_ilcsoft.sh
mkdir build
cd build
cmake -C $ILCSOFT/ILCSoft.cmake ..
make install 
cd ..
```

## Running LCTuple
```
export MARLIN_DLL=$PWD/lib/libLCTuple.so
cd example
Marlin --global.LCIOInputFiles=./DST01-06_ppr004_6f_bbqqqq_500_ILD_00_0.001.slcio --global.MaxRecordNumber=1000 lctuple.xml
// make plots with TTree:Draw(), e.g.
root -l 
.x /example_plots.C("./lctuple.root")
// see also other examples	

// hit maps from sim hits r-z and r-phi
draw_simhits.C
//draw vertices of secondary MCParticles
draw_mcp_vtx.C
//draw tue and reconstructed z-vertex position
draw_vtx_z.C
//draw true and reconstructed total energy
draw_etot.C
```


## License and Copyright
Copyright (C), LCTuple Authors

LCTuple is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License long with this program.  If not, see <http://www.gnu.org/licenses/>.
