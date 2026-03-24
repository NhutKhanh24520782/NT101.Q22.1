import random

def power_mod(base, exponent, modulus):
 
    if modulus == 1:
        return 0
    
    result = 1
    base = base % modulus
    
    while exponent > 0:
        if (exponent % 2) == 1:
            result = (result * base) % modulus
        exponent = exponent >> 1
        base = (base * base) % modulus
        
    return result

def is_prime_miller_rabin(n, k=40):
    if n == 2 or n == 3:
        return True
    if n <= 1 or n % 2 == 0:
        return False
    r = 0
    d = n - 1
    while d % 2 == 0:
        r += 1
        d //= 2

    for _ in range(k):
        a = random.randint(2, n - 2)
        x = power_mod(a, d, n)
        
        if x == 1 or x == n - 1:
            continue
            
        is_composite = True
        for _ in range(r - 1):
            x = power_mod(x, 2, n)
            if x == n - 1:
                is_composite = False
                break
                
        if is_composite:
            return False
            
    return True

def generate_random_prime(bits):
    while True:
        p = random.getrandbits(bits)
        p |= (1 << (bits - 1)) | 1 
        
        if is_prime_miller_rabin(p):
            return p

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

# PHẦN 1: YÊU CẦU VỀ SỐ NGUYÊN TỐ
print("--- YÊU CẦU 1: SỐ NGUYÊN TỐ ---")

# a) Tạo số nguyên tố ngẫu nhiên 8, 16, 64 bits
prime_8 = generate_random_prime(8)
prime_16 = generate_random_prime(16)
prime_64 = generate_random_prime(64)

print(f"Số nguyên tố 8 bits: {prime_8}")
print(f"Số nguyên tố 16 bits: {prime_16}")
print(f"Số nguyên tố 64 bits: {prime_64}")

# b) Xác định 10 số nguyên tố lớn nhất nhỏ hơn số Mersenne thứ 10
p_10 = 89
M_10 = (1 << p_10) - 1 # 2^89 - 1
print(f"\nSố nguyên tố Mersenne thứ 10 (M_89) = {M_10}")

print("10 số nguyên tố lớn nhất nhỏ hơn M_89:")
count = 0
num = M_10 - 2 # Bắt đầu từ số lẻ nhỏ hơn M_10
primes_list = []

while count < 10:
    if is_prime_miller_rabin(num):
        primes_list.append(num)
        count += 1
    num -= 2

for i, p in enumerate(primes_list):
    print(f"{i+1}. {p}")

# c) Kiểm tra một số nguyên tùy ý nhỏ hơn 2^89 - 1 có phải số nguyên tố không
test_num = random.randint(2, M_10 - 1)
is_prime = is_prime_miller_rabin(test_num)
print(f"\nKiểm tra số ngẫu nhiên < 2^89 - 1:\nSố: {test_num}\nLà số nguyên tố? {is_prime}")

# PHẦN 2: ƯỚC CHUNG LỚN NHẤT (GCD)
print("\n--- YÊU CẦU 2: ƯỚC CHUNG LỚN NHẤT (GCD) ---")

# Test với 2 số lớn (ví dụ 1024 bits)
num1 = random.getrandbits(1024)
num2 = random.getrandbits(1024)
print(f"Số A (1024 bits): {num1}")
print(f"Số B (1024 bits): {num2}")
print(f"GCD(A, B) = {gcd(num1, num2)}")

# PHẦN 3: TÍNH LŨY THỪA MODULO
print("\n--- YÊU CẦU 3: TÍNH LŨY THỪA MODULO ---")

# Test theo ví dụ của đề bài: 7^40 mod 19
base_test = 7
exp_test = 40
mod_test = 19
result = power_mod(base_test, exp_test, mod_test)
print(f"Ví dụ: {base_test}^{exp_test} mod {mod_test} = {result}")

# Test với số lớn hơn (RSA scale)
large_base = random.getrandbits(1024)
large_exp = random.getrandbits(1024)
large_mod = generate_random_prime(1024)
print(f"\nTính toán số lớn (1024 bits):")
print(f"Kết quả = {power_mod(large_base, large_exp, large_mod)}")