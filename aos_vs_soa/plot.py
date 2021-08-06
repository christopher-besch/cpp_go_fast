import pandas as pd
import matplotlib.pyplot as plt
import glob, os
data = pd.read_csv("aos.csv")
plt.loglog(data["n"],data["time"],"o")
plt.title("aos")
plt.xlabel("n")
plt.ylabel("time")
plt.savefig("aos.png")
plt.show()
