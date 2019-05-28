// Gi - graph representing the map
// Ri - sequence of reservations
// a - airport
PRE_PROCESS_DATA(Gi, Ri, a):
    DFS_CONNECTIVITY(Gi, a)
    REMOVE_UNVISITED_VERTICES(Gi)

    for each r ∈ Ri do
        if FIND_VERTEX(Gi, dest(r)) == NULL then
            REMOVE_RESERVATION(Ri, r)
    
    DIJKSTRA_SHORTEST_PATH(Gi)

