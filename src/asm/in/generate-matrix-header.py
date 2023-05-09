with open("matmul_huge.ily", 'a') as f:
    for i in range(0, 100):
        line = f"""li r0 {i}\nli r1 {700 + i}\nsw r0 r1 0\n"""
        f.write(line)
    for i in range(0, 100):
        line = f"""li r0 {i}\nli r1 {800 + i}\nsw r0 r1 0\n"""
        f.write(line)
