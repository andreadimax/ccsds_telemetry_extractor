def rotr(string, n):
         return string[n:] + string[:n]



def bin_to_float(data):
    """Takes as input a binary data (expected in 32 bit) and return the float value following the IEEE754 standard"""

    s_filter = 0x80000000
    exp_filter = 0x7F800000
    mF = 0x7FFFFF

    s = (data & s_filter) >> (23+8)
    exp = bin((data & exp_filter) >> 23).replace("0b","")

    if len(exp) < 8:
        exp = exp.zfill(8)

    m = bin(mF & data).replace("0b","")

    if len(m) < 23:
        m = m.zfill(23)

    exp = int(exp[::-1],2)
    m = int(m[::-1],2)

    mant = "1."+str(m)

    _float = ((-1)**s)*((2**(exp-127)))*float(mant)

    return _float

a = 1061158912
print(bin_to_float(a))