# TPCC
#### Enumeration of tensor product chain complexes

## Overview

This little library enumerates the objects in a tensor product chain complex, that is for instance, the k-dimensional facets in an n-dimensional Cartesian mesh.

Design goals are
- regular numbering schemes which are purely algorithmic and do not need data.
- enable as much compile time computation as possible, thus reducing runtime overhead.
- header-only library without configuration step which can be used easily by other projects

### Example for a TPCC

Here is an example for a tensor product chain complex in three dimension. The objects are shrunk for better visibility, in reality they are touching.

#### 3D facets (bricks)
![3D facets, bricks](/doc/img/3d-small.png?raw=true)

#### 2D facets (rectangles)
![2D facets, rectangles](/doc/img/2d-small.png?raw=true)

#### 1D facets (lines)
![1D facets, lines](/doc/img/1d-small.png?raw=true)

#### 0D facets (points)
No further picture for those. These are just the vertices of the 3D bricks.
