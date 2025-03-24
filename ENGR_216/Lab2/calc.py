n_normal = 0
n_subtracted = 0
n_explicit = 0

for i in range(1, 201):
    n_subtracted += i ** 3
for i in range(1, 99):
    n_subtracted -= i ** 3
for i in range(99, 201):
    n_normal += i ** 3

n1 = 200
n2 = 98
n_explicit += ((n1 ** 2) * (n1+1) ** 2) / 4
n_explicit -= ((n2 ** 2) * (n2+1) ** 2) / 4

print("CALCULATE normal:", n_normal)
print("CALCULATE DERIVED:", n_subtracted)
print("calculate explicit", n_explicit)
