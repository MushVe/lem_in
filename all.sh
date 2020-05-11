#!/bin/bash

for i in jj/maps/*
do
	echo $i
	./lem-in < $i
done