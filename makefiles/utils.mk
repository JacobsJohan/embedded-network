#
# This file contains macros and defines useful for other makefiles
#

ifndef INDOCKER
BRDOCK=@docker run --rm -it -e INDOCKER=1\
       -v=$(abspath $(BUILDDIR)):/v/build \
       -v=$(abspath $(BRCACHEDIR)):/root/.buildroot-ccache \
       -v=$(abspath $(BRDLDIR)):/buildroot/dl \
       -v=$(abspath $(CURRENTDIR)):/pwd \
       -w=/pwd $(BRIMG) /bin/bash -c

else
BRDOCK=/bin/bash -c
endif
