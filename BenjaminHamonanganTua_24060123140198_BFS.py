# Representasi graf dalam bentuk adjacency list
graph = {
    'S': ['A', 'B', 'C'],
    'A': ['D', 'E'],
    'B': ['G'],  # G adalah tujuan
    'C': ['F'],
    'D': ['H'],
    'E': [],
    'F': [],
    'G': [],  # Goal
    'H': []
}

# Implementasi Depth-Limited Search (DLS)
def dls(graph, node, goal, depth_limit, depth=0):
    print("  " * depth + f"Exploring: {node} (Depth: {depth})")

    if node == goal:  # Jika menemukan tujuan
        print("  " * depth + f"Goal {goal} ditemukan!")
        return True

    if depth >= depth_limit:  # Jika sudah mencapai batas kedalaman
        print("  " * depth + f"Depth limit reached at {node}")
        return False

    for neighbor in graph[node]:  # Telusuri semua tetangga
        if dls(graph, neighbor, goal, depth_limit, depth + 1):
            return True  # Berhenti jika goal ditemukan
    
    return False  # Jika tidak ditemukan dalam batas kedalaman

# Jalankan DLS dengan batas kedalaman tertentu
depth_limit = 2  # Ganti sesuai kebutuhan
print(f"Menjalankan DLS dengan depth limit {depth_limit}:")
found = dls(graph, 'S', 'G', depth_limit)

if not found:
    print("\nGoal tidak ditemukan dalam batas kedalaman.")