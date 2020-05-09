#!/bin/sh


for i in {1..1}
do
    i=`printf %03d $i`
    echo ${i}
	mkdir -p abc${i}
	cp -r  a.cpp abc${i}/a.cpp
	cp -r  b.cpp abc${i}/b.cpp
	cp -r  c.cpp abc${i}/c.cpp
	cp -r  d.cpp abc${i}/d.cpp
done
