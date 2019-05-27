// Gi - graph representing the map
// Ri - sequence of reservations (multiset organized by arrival time)
// Vi - vans to be used (multiset organized by next available time)
// a - airport
// tm - time window to wait for passengers
// md - max distance to be considered when grouping passengers
PLAN_VANS_FLEET_MIXING_PASSENGERS(Gi, Ri, Vi, a):
    
    CLEAR_SERVICES(Vi)

    // must assign all reservations
    while not IS_EMPTY(Ri) do

        // get earliest reservation not already assigned    
        early_res = BEGIN(Ri)
        REMOVE_ELE(Ri, BEGIN(Ri))

        // get earliest van available
        early_van = BEGIN(Vi)
        REMOVE_ELE(Vi, BEGIN(Vi))

        // group earliest client with next reservations
        occ_capacity = 0
        service = MIX_CLIENTS_WITH_EARLIEST(Gi, Ri, early_res, early_van, tm, md, &occ_capacity)

        // calculate best path through all the destinations
        path = CALCULATE_PATH_FROM_SERVICE(Gi, service)

        // assign deliver time to each reservation
        departure_time = TARDIEST_RESERVATION_TIME(service)
        total_time = ASSIGN_TIME_OF_ARRIVAL_TO_RESERVATIONS(path, service, departure_time)

        // update next time available of used van
        next_time_available(early_van) = departure_time + total_time

        // add service to van
        ADD_SERVICE(early_van, SERVICE(capacity(early_van) - occ_capacity, departure_time, service, path)

        // re-insert van in the multiset
        INSERT(Vi, early_van)

// Gi - graph representing the map
// Ri - sequence of reservations (multiset)
// res - first reservation that entered the van
// van - van to be used
// md - max distance to be considered when grouping passengers
// occ - variable passed by reference to return unmber of occupied seats in the van
MIX_CLIENTS_WITH_EARLIEST(Gi, Ri, res, van, tm, md, occ):

    // calculate time limit the van can wait for clients
    limit = arrival(res) + tm
    if limit < next_time_available(van) then
        limit = next_time_available(van)
    
    
    // vector of reservations for the new service
    service = ∅
    PUSH_BACK(service, res)

    // look for reservations arriving within the time window limit
    // that are close in distance to the earliest reservation
    // and group them togheter
    origin = position(FIND_VERTEX(Gi, dest(res)))
    occ_capacity = num_people(res)
    current_reservation = BEGIN(Ri)
    while (arrival(current_reservation) < limit) AND (current_reservation != END(Ri)) do

        node_pos = position(FIND_VERTEX(Gi, dest(current_reservation)))

        // found valid match within acceptable distance and which fits in the van
        if ((EUCLIDIAN_DISTANCE(origin, node_pos) < md) AND (occ_capacity + num_people(current_reservation) <= capacity(van))) then
            PUSH_BACK(service, current_reservation)
            occ_capacity += num_people(current_reservation)
            REMOVE_ELE(Ri, current_reservation)

            // cant fit more reservations
            if occ_capacity >= capacity(van) then
                break
        else
            current_reservation = NEXT_ELE(Ri)
    
    return service



// Gi - graph
// service - list of reservations to attend
CALCULATE_PATH_FROM_SERVICE(Gi, service):

    // vector of vertices to traverse
    vertices = GET_VERTICES_FROM_SERVICE(Gi, service)

    // calculate best path through all the vertices
    // vector of edges
    path = CALCULATE_PATH(vertices)

    return path



// path - list of edges that will be traversed
// service - list of reservations to attend
// departure_time - time at which the van leaves
ASSIGN_TIME_OF_ARRIVAL_TO_RESERVATIONS(path, service, departure_time):

    total_time = 0
    for e ∈ path do
        total_time += weight(e)

        for r ∈ service do
            if assigned(r) then
                continue

            if dest(r) == id(dest(e)) then
                SET_DELIVER_TIME(r, departure_time + total_time)
                assigned(r) = true
    return total_time


// Gi - graph
// a - airport vertex
// vertices - list of vertices to calculate path
CALCULATE_PATH(Gi, a, vertices):
    
    path = ∅
    
    vertices_copy = vertices

    // from airport trip
    closest = GET_CLOSEST_VERTEX(a, vertices_copy)
    ERASE(vertices_copy, closest)

    // path calculated with dijkstra in pre-processing
    from_aiport = GET_PATH_EDGES(Gi, a, closest)
    APPEND(path, from_aiport)

    // nearest neighbour approach using A*
    current_source = closest
    while not IS_EMPTY(vertices_copy) do
        closest_to_source = GET_CLOSEST_VERTEX(current_source, vertices_copy)
        ERASE(vertices_copy, closest_to_source)

        ASTAR(Gi, current_source, closest_to_source)
        temp_path = GET_A_STAR_PATH(Gi, current_source, closest_to_source)
        APPEND(path, temp_path)

        current_source = closest_to_source

    // return to airport trip
    ASTAR(Gi, current_source, airport)
    temp_path = GET_A_STAR_PATH(Gi, current_source, airport)
    APPEND(path, temp_path)

    return path


