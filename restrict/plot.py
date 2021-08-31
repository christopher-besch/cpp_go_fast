import pandas as pd
import matplotlib.pylab as plt

data = pd.read_csv("restrict.csv",delimiter=",")

plt.loglog(data["n"],data["res"],label="restrict")
plt.loglog(data["n"],data["no_res"],label="no_restrict")

plt.legend()
plt.xlabel("n")
plt.ylabel("time")
plt.tight_layout()
plt.show()


