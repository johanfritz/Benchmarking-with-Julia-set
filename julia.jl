using Plots
function converge(a, b)
    creal=-0.4
    cimag=0.6
    lim=200
    for k in 0:lim
        atemp=a*a-b*b+creal
        b=2*a*b+cimag
        a=atemp
        if a*a+b*b >2.25
            return k
        end
    end
    return lim
end
t0=time()
prec=10000
rea=LinRange(-2, 2, prec)
ima=LinRange(-2, 2, prec)
C=[converge(r, i) for r in rea, i in ima]
t1=time()
elements=size(C)[1]*size(C)[2]
println("elements: ", elements)
println("total time (s): ", t1-t0)
println("time per element (ns): ", 1e9*(t1-t0)/(prec*prec))
heatmap(C)
