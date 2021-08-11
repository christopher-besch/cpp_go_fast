import pandas as pd
import matplotlib.pyplot as plt
import glob, os
aos_data = pd.read_csv("aos.csv")
soa_data = pd.read_csv("soa.csv")
plt.loglog(aos_data["n"],aos_data["time"],"o",markersize=1,label="aos")
plt.loglog(soa_data["n"],soa_data["time"],"o",markersize=1,label="soa")
plt.title("aos vs soa")
plt.legend()
plt.xlabel("n")
plt.ylabel("time")
plt.savefig("aos_vs_soa.png")
plt.show()
