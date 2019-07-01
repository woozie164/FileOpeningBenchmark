What's faster, reading from one large file, or many small files?

The answer to this question can be of interest when comparing the merits of storing program data/resources as plain files, or as some kind of bundle/archive format. 

This projects contains several benchmarks that compare performance of using one large file vs many small files.

----

RESULT:
It took 10x longer to read from 500 small files than 1 big file

Test system:
HDD: Caviar Green 2 TB 5400 RPM
