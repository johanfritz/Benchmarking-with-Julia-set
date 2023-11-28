import numpy as np
import matplotlib.pyplot as plt
import time
t0=time.perf_counter_ns()
x = np.linspace(-2, 2, 1000)
y = np.linspace(-2, 2, 1000)
elements:int=len(x)*len(y)
X, Y=np.meshgrid(x, y)
Z=X+1j*Y

def julia(z):
    c:complex=-0.4+0.6j
    lim:int=200
    for k in range(lim):
        z=(z**2)+c
        if np.abs(z)>1.5:
            return k
    return lim

Julia=np.vectorize(julia)
J=Julia(Z)
t1=time.perf_counter_ns()
print(f"total time (s): {(t1-t0)*1e-9:.4f}")
print(f"time per element (ns): {(t1-t0)/elements}")
plt.imshow(J)
plt.show()