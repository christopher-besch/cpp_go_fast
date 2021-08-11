bdir = "build"
csvdir = "csvs"

build_all: aos_vs_soa

aos_vs_soa: aos_vs_soa/aos.c aos_vs_soa/soa.c
	gcc aos_vs_soa/aos.c -std=gnu99 -O3 -ffast-math -o ${bdir}/aos
	gcc aos_vs_soa/aos.c -std=gnu99 -O3 -ffast-math -S -o ${bdir}/aos.asm
	gcc aos_vs_soa/soa.c -std=gnu99 -O3 -ffast-math -o ${bdir}/soa
	gcc aos_vs_soa/soa.c -std=gnu99 -O3 -ffast-math -S -o ${bdir}/soa.asm

aos_vs_soa_plot: aos_vs_soa
	cd ./${bdir} ; ./aos
	cd ./${bdir} ; ./soa
	cd ./${bdir} ; python ./../aos_vs_soa/plot.py


plot_all: aos_vs_soa_plot