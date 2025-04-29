# <--- PART 1 --->
import random
# Step 1
def chromosome_generator(size):
    chromosomes = {}
    # Step 2
    for i in range(size):
        chromo = {
            "stop_loss": random.randint(1, 99),
            "take_profit": random.randint(1, 99),
            "trade_size": random.randint(1, 99),
        }
        chromosomes[f"p{i+1}"] = chromo
    return chromosomes

# chromosomes = chromosome_generator(4)  # Generate 4 chromosomes
# for u,v in chromosomes.items():
#   print("chromosomes:",v)
# print("full view:",chromosomes)

# string representation
def chromosome_to_string(chromo):
    return f"{chromo['stop_loss']:02}{chromo['take_profit']:02}{chromo['trade_size']:02}" # to fill 2 digit

# chromosome_strings = {}
# for key, value in chromosomes.items():
#     string_representation = chromosome_to_string(value)
#     chromosome_strings[key] = string_representation

# for u,v in chromosome_strings.items():
    # print(u)
    # print("string:",v)


# Step 3
hpm = [-1.2, 3.4, -0.8, 2.1, -2.5, 1.7, -0.3, 5.8, -1.1, 3.5]
def calculate_fitness(chromosome_strings, initial_capital=1000):
    fitness_scores = {}
    for key, x in chromosome_strings.items():
        stop_loss = int(x[:2])/100
        take_profit = int(x[2:4])/100
        trade_size = int(x[4:6])/100
        capital = initial_capital

        for i in hpm:
            trade_amount = capital * trade_size
            if i < -stop_loss:
                loss = trade_amount * stop_loss
                capital -= loss
            elif i > take_profit:
                profit = trade_amount * take_profit
                capital += profit
            else:
                profit_loss = trade_amount * (i/100)
                capital += profit_loss

        fitness_scores[key] = round(capital - initial_capital, 2)
    return fitness_scores

# fitness_scores = calculate_fitness(chromosome_strings, initial_capital)
# print("\nfitness_scores:",fitness_scores)


# Step 4
def get_fitness(item):
    return item[1]  # Extract the fitness score

def chromosome_chooser(fitness_scores):
    sorted_chromosomes = list(fitness_scores.items())  # Convert dictionary to list of tuples
    sorted_chromosomes.sort(key=get_fitness, reverse=True)  # Sort using user-defined function
    return sorted_chromosomes[0][0], sorted_chromosomes[1][0]  # Return top 2 keys
    # returns p1/p2/p3/p4 -> best two
# it returns the best two chromosomes

# k1, k2 = chromosome_chooser(fitness_scores)
# print()
# print("Mihir",chromosome_strings)
# print(f"picked: {k1} ->",chromosome_strings[k1])
# print(f"picked: {k2} ->",chromosome_strings[k2])
# print()
# print(chromosome_chooser(calculate_fitness(chromosome_strings, initial_capital)))


# Step 5
def crossover(p1, p2, chromosome_strings):
    p1 = chromosome_strings[p1] # key
    p2 = chromosome_strings[p2] # key
    # print("parent1:", p1)
    # print("parent2:", p2)
    split_point = random.randint(1,len(p1)-1) # 1 to 5
    # print(f"split point: {split_point}\n")
    child1 = p1[:split_point] + p2[split_point:]
    child2 = p2[:split_point] + p1[split_point:]
    return child1, child2
# p1, p2 = chromosome_chooser(fitness_scores)
# print(f"this is the crossover {crossover(p1, p2, chromosome_strings)}")  # Pass the chosen chromosomes



# Step 6
def mutation(child_list, mutation_rate=0.05):
    # print("child list:",child_list) # after crossover -> two child in a tuple
    mutated_children = []
    for i in range(len(child_list)):
        r_val = random.random()
        child = child_list[i]
        # print("random value:",r_val)
        # print(f"BEFORE: child {i+1}: {child}")
        if r_val < mutation_rate:
            # print("True")
            mutate_index = random.randint(0, 5) # randomly generates a index where mutation will occur
            new_value = f"{random.randint(0, 9)}" # what the value will be if it occurs
            child = child[:mutate_index] + new_value + child[mutate_index + 1:]
            # print(f"Mutation in child {i+1}: Index {mutate_index} -> {new_value}")
        # else:
        #     print("False")

        mutated_children.append(child)
        # print(f"AFTER: child {i+1}: {child}\n")
        
    return mutated_children

# children = crossover(p1, p2, chromosome_strings)
# mutated_chromosomes = mutation(children)
# print("Mutated Chromosomes:",mutated_chromosomes)


# Step 7
def genetic_algorithm(generations, population_size, initial_capital, hpm, mutation_rate=0.05):
    chromosomes = chromosome_generator(population_size)
    chromosome_strings = {}
    for k, v in chromosomes.items():
        string_representation = chromosome_to_string(v)
        chromosome_strings[k] = string_representation


    for i in range(generations):
        fitness_scores = calculate_fitness(chromosome_strings, initial_capital)
        parent1, parent2 = chromosome_chooser(fitness_scores) # best two chromosomes -> p1/p2/p3/p4
    
        children = crossover(parent1, parent2, chromosome_strings)
        mutated_children = mutation(children, mutation_rate)
        chromosome_strings[parent1], chromosome_strings[parent2] = mutated_children  # Replace parents with mutated ones

    final_fitness = calculate_fitness(chromosome_strings, initial_capital)
    # print("final fitness",final_fitness)

    best_chromo_name = max(final_fitness, key=final_fitness.get) # based on fitness value
    best_chromo_value = chromosome_strings[best_chromo_name]
    # print("name",best_chromo_name)
    # print("value",best_chromo_value)

    best_chromo = {
        "stop_loss": int(best_chromo_value[:2]),
        "take_profit": int(best_chromo_value[2:4]),
        "trade_size": int(best_chromo_value[4:6]),
    }
    return best_chromo_name, best_chromo, final_fitness[best_chromo_name]

best_chromo_name, best_chromo, final_profit = genetic_algorithm(10, 4, 1000, hpm)
print(f"Best_strategy: {best_chromo}")
print(f"Final_profit: {final_profit}")




# <--- PART 2 --->
import random
def chromosome_generator(size):
    chromosomes = {}
    for i in range(size):
        chromo = {
            "stop_loss": random.randint(1, 99),
            "take_profit": random.randint(1, 99),
            "trade_size": random.randint(1, 99),
        }
        chromosomes[f"p{i+1}"] = chromo
    return chromosomes
chromosomes = chromosome_generator(4)
def chromosome_to_string(chromo):
    return f"{chromo['stop_loss']:02}{chromo['take_profit']:02}{chromo['trade_size']:02}"

chromosome_strings = {}

for key, value in chromosomes.items():
    string_representation = chromosome_to_string(value)
    chromosome_strings[key] = string_representation
def chromosome_chooser(chromosome_strings):
    return random.sample(list(chromosome_strings.values()), 2)

def dual_crossover(p_list):
    p1, p2 = p_list[0], p_list[1]
    # print(f"Parent 1: {p1}, Parent 2: {p2}")
    split = sorted(random.sample(range(1, len(p1)), 2))
    # print(split)
    split_point1 = min(split)
    split_point2 = max(split)
    # print(f"Split point 1: {split_point1}, Split point 2: {split_point2}")
    child1 = p1[:split_point1] + p2[split_point1:split_point2] + p1[split_point2:]
    child2 = p2[:split_point1] + p1[split_point1:split_point2] + p2[split_point2:]

    return child1, child2

selected_parents = chromosome_chooser(chromosome_strings)
offspring1, offspring2 = dual_crossover(selected_parents)

print(f"Two offsprings are {offspring1} & {offspring2}")
