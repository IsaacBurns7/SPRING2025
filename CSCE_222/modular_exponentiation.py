def modular_exponentiation(base, exponent, mod):
    x = 1
    power = base % mod
    a = [int(bit) for bit in bin(exponent)[2:]] #[2:] to skip 0b \
    a.reverse()
    for i in range(0, len(a)):
        x_prev = x
        power_prev = power
        if(a[i] == 1):
            x *= power
            x %= mod
        power *= power
        power %= mod
        x_report = f"x = {x_prev} * {power_prev} mod {mod} = {x}" if a[i] % 2 == 1 else f"x = {x}"
        print(f"i = {i}, a{i} = {a[i]}, {x_report}, power = {power_prev}^2 mod {mod} = {power}. \\\\")
        #i = 0, a0 = 1, x = (11*1) mod 645 = 11, power = $11^2$ mod 645 = 121. \\

    return x

modular_exponentiation(11, 644, 645)


