import numpy as np
import matplotlib.pyplot as plt
import time
t0=time.perf_counter_ns()
def converge(a, b):
    lim=200
    creal=-0.4
    cimag=0.6
    for k in range(lim):
        (a, b)=(a*a-b*b+creal, 2*a*b+cimag)
        if a*a+b*b > 2.25:
            return k
    return lim
prec=4000
a=np.linspace(-2, 2, prec)
A=np.ones((prec, prec))*a
b=np.linspace(-2, 2, prec)
B=np.ones((prec, prec))*np.reshape(b, (prec, 1))*-1
Converge=np.vectorize(converge)
Z=Converge(A, B)
t1=time.perf_counter_ns()
print(f"Total time (s): {(t1-t0)*1e-9:0.4f}")
print(f"Time per element (ns): {(t1-t0)/(prec**2)}")
print(f"Elements: {prec**2}")
#plt.imshow(Z)
#plt.show()