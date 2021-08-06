bdir = "build"
csvdir = "csvs"

build_all: aos_vs_soa

aos_vs_soa: aos_vs_soa/aos.c
	gcc aos_vs_soa/aos.c -std=gnu99 -O3 -ffast-math -o ${bdir}/aos
	gcc aos_vs_soa/aos.c -std=gnu99 -O3 -ffast-math -S -o ${bdir}/aos.asm

aos_vs_soa_plot: aos_vs_soa
	cd ./${bdir} ; ./aos
	cd ./${bdir} ; python ./../aos_vs_soa/plot.py


plot_all: aos_vs_soa_plot