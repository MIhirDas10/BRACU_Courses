# ----- part 1 -----
import random
import math

neg_inf = float('-inf')
pos_inf = float('inf')
names = ["Magnus Carlsen", "Fabiano Caruana"]
carlsen_win = 0
caruana_win = 0
draw = 0

def strength(x):
    return math.log2(x+1)+x/10

def utility(max_strength, min_strength):
    max_num = strength(max_strength)
    min_num = strength(min_strength)
    i = random.randint(0, 1)
    random_factor = (-1)**i*random.randint(1, 10)/10
    return max_num - min_num + random_factor

def terminal(state):
    depth = state[5]
    return depth >= 5 

def evaluate(state):
    max_strength = state[3]
    min_strength = state[4]
    return utility(max_strength, min_strength)

def next_states(state):
    max_player, min_player, is_max_turn, max_strength, min_strength, depth = state

    child_states = []
    for i in range(2):
        new_state = (max_player, min_player, not is_max_turn, max_strength, min_strength, depth+1) # toggle
        child_states.append(new_state)
    return child_states

def max_value(s, alpha, beta):
    if terminal(s):
        return evaluate(s)
    v = neg_inf
    for c in next_states(s):
        v_prime = min_value(c, alpha, beta)
        if v_prime > v:
            v = v_prime
        if v >= beta:
            return v
        if v > alpha:
            alpha = v
    return v

def min_value(s, alpha, beta):
    if terminal(s):
        return evaluate(s)
    v = pos_inf
    for c in next_states(s):
        v_prime = max_value(c, alpha, beta)
        if v_prime < v:
            v = v_prime
        if v <= alpha:  
            return v
        if v < beta:
            beta = v
    return v

def minimax_decision(state):
    is_max_turn = state[2]
    if is_max_turn: return max_value(state, neg_inf, pos_inf)
    else: return min_value(state, neg_inf, pos_inf)

def game(first_player, carlsen_strength, caruana_strength):
    if first_player == 0:
        max_player = names[0]; min_player = names[1]
        max_strength = carlsen_strength; min_strength = caruana_strength
    else:
        max_player = names[1]; min_player = names[0]
        max_strength = caruana_strength; min_strength = carlsen_strength

    ini_state = (max_player, min_player, True, max_strength, min_strength, 0)
    res = minimax_decision(ini_state)

    if res > 0:
        winner = max_player; game_state = "Max"
    elif res < 0:
        winner = min_player; game_state = "Min"
    else:
        winner = "Draw"; game_state = ""
    return winner, game_state, res

def run_game(carlsen_win, caruana_win, draw):
    p1 = int(input("Enter starting player for game 1 (0 for Carlsen, 1 for Caruana): "))
    carlsen_base_strength = int(input("Enter base strength for Carlsen: "))
    caruana_base_strength = int(input("Enter base strength for Caruana: "))

    for i in range(1, 5):
        first_player = (p1 + i-1)%2
        # print(first_player)
        
        winner, game_state, utility_value = game(first_player, carlsen_base_strength, caruana_base_strength)
        if winner == "Draw":
            print(f"Game {i} Result: Draw (Utility value: {round(utility_value, 2)})")
            draw += 1
        else:
            print(f"Game {i} Winner: {winner} ({game_state}) (Utility value: {round(utility_value, 2)})")
            if winner == "Magnus Carlsen":
                carlsen_win += 1
            elif winner == "Fabiano Caruana":
                caruana_win += 1
              
    print("\nOverall Results:")
    print(f"Magnus Carlsen Wins: {carlsen_win}\nFabiano Caruana Wins: {caruana_win}\nDraws: {draw}")

    if carlsen_win > caruana_win:
        print("Overall Winner: Magnus Carlsen")
    elif caruana_win > carlsen_win:
        print("Overall Winner: Fabiano Caruana")
    else:
        print("Overall Result: Draw")
run_game(carlsen_win, caruana_win, draw)


# ----- part 2 ----- 
import random
import math

neg_inf = float('-inf')
pos_inf = float('inf')

def strength(x):
    return math.log2(x+1)+x/10

def utility(max_strength, min_strength):
    max_num = strength(max_strength)
    min_num = strength(min_strength)
    i = random.randint(0, 1)
    random_factor = (-1)**i*random.randint(1, 10)/10
    return max_num - min_num + random_factor

def terminal(state):
    depth = state[5]
    return depth >= 5 

def evaluate(state):
    max_strength = state[3]
    min_strength = state[4]
    return utility(max_strength, min_strength)
# 
# def next_states(state):
#     max_player, min_player, is_max_turn, max_strength, min_strength, depth = state

#     child_states = []
#     for i in range(2):
#         new_state = (max_player, min_player, not is_max_turn, max_strength, min_strength, depth+1) # toggle
#         child_states.append(new_state)
#     return child_states

# def max_value(s, alpha, beta):
#     if terminal(s):
#         return evaluate(s)
#     v = neg_inf
#     for c in next_states(s):
#         v_prime = min_value(c, alpha, beta)
#         if v_prime > v:
#             v = v_prime
#         if v >= beta:
#             return v
#         if v > alpha:
#             alpha = v
#     return v

# def min_value(s, alpha, beta):
#     if terminal(s):
#         return evaluate(s)
#     v = pos_inf
#     for c in next_states(s):
#         v_prime = max_value(c, alpha, beta)
#         if v_prime < v:
#             v = v_prime
#         if v <= alpha:  
#             return v
#         if v < beta:
#             beta = v
#     return v

# def minimax_decision(state):
#     max_turn = state[3]
#     if max_turn:
#         return max_value(state, neg_inf, pos_inf)
#     else:
#         return min_value(state, neg_inf, pos_inf)


def without_mind_control(player1, light_strength, l_strength):
    if player1 == 0:
        max_strength, min_strength = light_strength, l_strength
    else:
        max_strength, min_strength = l_strength, light_strength
    return utility(max_strength, min_strength)

def with_mind_control(player1, light_strength, l_strength):
    if player1 == 0:
        max_strength, min_strength = light_strength, l_strength
    else:
        max_strength, min_strength = l_strength, light_strength
    # assuming that max can mind controll so max would want his chances are more than min
    return utility(max_strength, min_strength/2)


def make_decision(max_player, normal, mind_control, after_cost):

    if normal > after_cost:
        return f"{max_player} should NOT use Mind Control as the position is already winning."
    elif normal < 0 and after_cost > 0:
        return f"{max_player} should use Mind Control."
    elif normal < 0 and after_cost < 0:
        return f"{max_player} should NOT use Mind Control as the position is losing either way."
    elif normal > 0 and after_cost < 0:
        return f"{max_player} should NOT use Mind Control as it backfires."
    else:
        return f"{max_player} should use Mind Control."
        
def run_game():
    player1 = int(input("Enter who goes first (0 for Light, 1 for L): "))
    c = float(input("Enter the cost of using Mind Control: "))
    light_strength = float(input("Enter base strength for Light: "))
    l_strength = float(input("Enter base strength for L: "))

    if player1 == 0: max_player = "Light"
    else: max_player = "L"
    normal = without_mind_control(player1, light_strength, l_strength)
    mind_control = with_mind_control(player1, light_strength, l_strength)
    after_cost = mind_control - c
    verdict = make_decision(max_player, normal, mind_control, after_cost)
    
    print(f"\nMinimax value without Mind Control: {round(normal, 2)}\nMinimax value with Mind Control: {round(mind_control, 2)}")
    print(f"Minimax value with Mind Control after incurring the cost: {round(after_cost, 2)}")
    print(verdict)
run_game()