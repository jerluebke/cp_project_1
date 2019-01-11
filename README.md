# Nearest Neighbours using Quadtrees
1st project of the computational physics course (winter 18/19) at
Ruhr-University Bochum

---

_TODO_: implement 64-bit keys (currently only 16-bit keys are available)

---


## Usage
To run the test-cases, do:

    make test
    bin/test.out

To run the (naive) benchmarking, do:
    make timeit
    bin/timeit.out


## Presentation
The used algorithm is described in the latex-presentation.  
Compile the tex-files with lualatex _(you might need to adjust the output dir of
the minted package)_  

## Visualisation
Plotting can be done using the cython-interface. Compile with

    python setup.py build_ext --inplace

For an example of usage, see
[python/plot_quadtree.py](https://github.com/jerluebke/cp_project_1/blob/master/python/plot_quadtree.py)

Drawing of the trees is done with [Graphviz](https://graphviz.gitlab.io/); this
functionality is only included, when _not_ compiling under Windows (to change
this, adjust the makros in
[include/cvisualise.h](https://github.com/jerluebke/cp_project_1/blob/master/include/cvisualise.h)
and
[src/cvisualise.c](https://github.com/jerluebke/cp_project_1/blob/master/src/cvisualise.c))
