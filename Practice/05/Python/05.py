g=9.8
xt=int
print('x0 = ')
x0=int(input())
print('v0 = ')
v0=int(input())
print('t = ')
t=int(input())
xt=x0 + v0*t - g*t*t/2
print('x(t) =', xt)
input()