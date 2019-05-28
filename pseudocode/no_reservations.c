// Gi - graph
// Vi - list of vans with services assigned
// a - airport
// client - new client with no reservation to integrate
// waiting_time - time the client is willing to wait for a van
INTEGRATE_CLIENT_NO_RESERVATION(Gi, Vi, a, client, waiting_time):

    // list of pairs in the format <service, next_service>
    // required to later acquire next_service more efficiently
    close = ∅

    // find services which may be a possible match
    for each v ∈ Vi do
        for each s ∈ services(v) do

            // time diff from arrival of new client to start of service
            time_diff = start(s) - arrival(client)

            // is at correct time and has vacant spots
            if 0 <= time_diff <= waiting_time AND vacant(s) >= num_people(client) then
                next = NEXT_SERVICE(services(v), s)

                // if there is no service after this one, can always integrate
                if next == NULL then
                    NEW_DEST_INTEGRATION(Gi, a, client, s)
                    return

                ENLIST(close, PAIR(s, next)) 

    // find services which already go through same destination
    for each pair ∈ close do
        s = first(pair)
        for each r ∈ reservations(s) do
            if dest(r) == dest(client) then
                SAME_DEST_INTEGRATION(client, s)
                return

    // find services which are not affected by adding client
    for each pair ∈ close do
        s = first(pair)
        next = second(pair) 
        path_vertices = GET_SERVICE_DESTINATIONS(Gi, s)
        INSERT(path_vertices, FIND_VERTEX(Gi, dest(client)))

        path_edges = CALCULATE_PATH(Gi, a, path_vertices)
        total = TRAVEL_TIME(path_edges)

        if start(service) + total <= start(next) then
            NEW_DEST_INTEGRATION(Gi, a, client, s)
            return


// Gi - graph
// a - airport
// c - client to integrate
// s - service in which to integrate client
NEW_DEST_INTEGRATION(Gi, a, c, s):

    // determine set of vertices the service must go through
    vertices = GET_SERVICE_DESTINATIONS(Gi, s)
    INSERT(vertices, FIND_VERTEX(Gi, dest(c)))

    // recalculate path, now going through new destination
    path_edges = CALCULATE_PATH(Gi, a, vertices)
    total = TRAVEL_TIME(path_edges)

    // update service info
    PUSH_BACK(reservations(s), c)
    path(s) = path_edges
    end(s) = start(s) + total
    vacant(s) -= num_people(c)
    

// c - client to integrate
// s - service in which to integrate client 
SAME_DEST_INTEGRATION(c, s):
    
    // find reservation with same destination and add client after it
    for each r ∈ reservations(s) do
        if dest(r) == dest(c) then
            INSERT_AFTER(reservations(s), c, r)
            break
        
    vacant(s) -= num_people(c)
         