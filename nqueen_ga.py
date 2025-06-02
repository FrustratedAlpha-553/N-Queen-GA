import random
import matplotlib.pyplot as plt 

N = 40
POP_SIZE = 10000
GENERATIONS = 10000
MU_RATE = 0.2


def initial_population(n):
    chrom = list(range(n))
    random.shuffle(chrom)
    return chrom + [-1] 

def fitness(chrom, n):
    conflict = 0
    for i in range(n):
        for j in range(i + 1, n):
            if abs(i - j) == abs(chrom[i] - chrom[j]):
                conflict += 1
    chrom[-1] = conflict
    return chrom


def mutation(chrom, m_r, n):
    if random.random() < m_r:
        i, j = random.sample(range(n), 2)
        chrom[i], chrom[j] = chrom[j], chrom[i]

def select_parent(pop_list):
    best = random.randint(0, POP_SIZE - 1)
    for _ in range(N * 2):
        rand = random.randint(0, POP_SIZE - 1)

        
        if not isinstance(pop_list[rand], list) or not isinstance(pop_list[best], list):
            print(f"[ERROR] Non-list individual at rand={rand} or best={best}")
            continue
        if len(pop_list[rand]) != N + 1 or len(pop_list[best]) != N + 1:
            print(f"[ERROR] Invalid chromosome length at rand={rand} or best={best}")
            continue
        if not isinstance(pop_list[rand][-1], int) or not isinstance(pop_list[best][-1], int):
            print(f"[ERROR] Invalid fitness value at rand={rand} or best={best}")
            continue

        if pop_list[rand][-1] < pop_list[best][-1]:
            best = rand
    return best

def valid_mapping_val(mapping, val):
    seen = set()
    while val in mapping and mapping[val] != -1:
        if val in seen:
            break  
        seen.add(val)
        val = mapping[val]
    return val


def PMX(p1, p2):
    start, end = sorted([random.randint(0, N - 1), random.randint(0, N - 1)])
    child = [-1] * N
    mapping = {}

    for i in range(start, end + 1):
        child[i] = p1[i]
        mapping[p2[i]] = p1[i]

    for i in range(N):
        if start <= i <= end:
            continue
        val = p2[i]
        val = valid_mapping_val(mapping, val)
        if val not in child:
            child[i] = val
        else:
            for alt in range(N):
                if alt not in child:
                    child[i] = alt
                    break


    if len(child) != N or len(set(child)) != N:
        print(f"[ERROR] Invalid PMX child: {child}")
    return child + [-1]

def show(pop_list, n):
    if not pop_list:
        print("Population list is empty!")
        return

    best_solution = pop_list[0][:n]

    plt.figure(figsize=(5 , 5))
    colors = ['blue', 'white']

    for row in range(n):
        for col in range(n):
            color = colors[(row + col) % 2]
            plt.fill_between([col, col + 1], row, row + 1, color=color)

    for row, col in enumerate(best_solution):
        if 0 <= col < n:
            plt.text(col + 0.5, row + 0.5, 'X', ha='center', va='center', fontsize=24, color='red')
        else:
            print("Invalid Point Error ")

    plt.xlim(0, n)
    plt.ylim(0, n)
    plt.xticks([])
    plt.yticks([])
    plt.gca().invert_yaxis()
    plt.title(f'{n}-Queens Solution')
    plt.show()




if __name__ == "__main__":
    random.seed()

    pop_list = [fitness(initial_population(N), N) for _ in range(POP_SIZE)]
    new_pop_list = [fitness(initial_population(N), N) for _ in range(POP_SIZE)]

    for gen in range(1, GENERATIONS + 1):
        found = False
        for idx, individual in enumerate(pop_list):
            if not isinstance(individual, list) or len(individual) != N + 1:
                print(f"[ERROR] Invalid individual at index {idx}: {individual}")

        for i in range(POP_SIZE):
            p1 = select_parent(pop_list)
            p2 = select_parent(pop_list)

            child = PMX(pop_list[p1], pop_list[p2])

            if not isinstance(child, list) or len(child) != N + 1:
                print(f"[ERROR] Malformed child at generation {gen}, index {i}: {child}")
                continue

            mutation(child, MU_RATE, N)
            new_pop_list[i] = fitness(child, N)

            if new_pop_list[i][-1] == 0:
                print(f"Solution found in generation {gen} ")
                print("chromosome :", new_pop_list[i][:-1])
                show(new_pop_list,N)
                found = True
                break

        if found:
            break
        else:
            pop_list = [chrom[:N] + [chrom[-1]] for chrom in new_pop_list]

        if gen % 100 == 0:
            print(f"{gen} still searching ...")
