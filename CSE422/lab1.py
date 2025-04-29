import heapq
# Arad
# Bucharest
graph_info = {}
with open("input.txt", "r") as input_file:
    for line in input_file:
        parts = line.split()
        city, heuristic_value = parts[0], int(parts[1])
        # print(city)
        # print(heuristic_value)
        # print(parts)

        connections = {}
        for i in range(2, len(parts), 2):
            # print(parts[i])
            child = parts[i]
            distance = int(parts[i+1])
            connections[child] = distance
        # print(connections)
        graph_info[city] = {'heuristic': heuristic_value, 'connections': connections} # 2 key-value pairs
    # print(graph_info) # gives the entire graph view

heuristic = {}
for city, info in graph_info.items(): 
    # print(city)
    # print(info)
    heuristic[city] = info['heuristic']  # picks the city and heuristic value in the heuristic dict
# print(heuristic)

graph = {}
for city, info in graph_info.items():
    graph[city] = info['connections'] # picks the city and the connections from info in graph dict
# print(graph)

def a_star(start, goal):
    pq = [(heuristic[start], start, [start], 0)]
    print(pq)
    visited = {}

    while pq:
        # f(n) = g(n) + h(n)
        # f(n) = actual path cost + heuristic value
        fn, curr_node, path, gn = heapq.heappop(pq) # pops on the basis of fn
        # print(curr_node)

        if curr_node == goal:
            return path, gn

        if curr_node in visited:
          continue

        visited[curr_node] = gn

        for child, cost in graph[curr_node].items():
            # print(curr_node)
            # print(cost)
            new_gn = gn + cost
            new_fn = new_gn + heuristic[child]
            new_path = path + [child]

            heapq.heappush(pq, (new_fn, child, new_path, new_gn))

    return None, None
# ----------------------------------------------------------------
# start_city = input("Start city: ")
# goal_city = input("Goal city: ")
start_city = "Arad"
goal_city = "Bucharest"
path, total_dist = a_star(start_city, goal_city)

if path:
    print("Path:", " -> ".join(path))
    print("Total distance:", total_dist, "km")
else:
    print("NO PATH FOUND")