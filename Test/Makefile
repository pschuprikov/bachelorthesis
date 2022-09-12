all: checkmakefiles
	cd src && $(MAKE)

run-2pc: all
	cd src && opp_run -m -u Qtenv -n ../simulations:.:../../traffic-engineering/simulations:../../traffic-engineering/src:../../inet4/src -l ./Test -l ../../traffic-engineering/src/trafficengineering -l ../../inet4/src/INET 2PC.ini

run-nbac: all
	cd src && opp_run -m -u Qtenv -n ../simulations:.:../../traffic-engineering/simulations:../../traffic-engineering/src:../../inet4/src -l ./Test -l ../../traffic-engineering/src/trafficengineering -l ../../inet4/src/INET NBAC.ini

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile

makefiles:
	cd src && opp_makemake -f --deep

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '======================================================================='; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '======================================================================='; \
	echo; \
	exit 1; \
	fi
