#!/bin/bash

for soubor in "$@" ; do
	cat "$soubor" | tr -d '\r' > $soubor.lin
done
