// Gi - graph representing the map
// Ri - sequence of reservations (multiset)
// Vi - vans to be used (multiset)
// a - airport
// tm - time window to wait for passengers
// md - max distance to be considered when grouping passengers
PLAN_VANS_FLEET_MIXING_PASSENGERS(Gi, Ri, Vi, a):
    
    CLEAR_SERVICES(Vi)

    // must assign all reservations
    while not IS_EMPTY(Ri) do

        // get earliest reservation not already assigned    
        // reservations in a multiset organized by arrival time
        early_res = BEGIN(Ri)
        REMOVE_ELE(Ri, BEGIN(Ri))

        // get earliest van available
        // vans in a multiset organized by next available time
        early_van = BEGIN(Vi)
        REMOVE_ELE(Vi, BEGIN(Vi))

        // calculate time limit the van can wait for clients
        limit = arrival(early_res) + tm
        if limit < next_time_available(early_van) then
            limit = next_time_available(early_van)
        
        
        // vector of reservations for the new service
        service = ∅
        PUSH_BACK(service, early_res)

        // look for reservations arriving within the time window limit
        // that are close in distance to the earliest reservation
        // and group them togheter
        origin = position(FIND_VERTEX(Gi, dest(early_res)))
        occ_capacity = num_people(early_res)
        current_reservation = BEGIN(Ri)
        while (arrival(current_reservation) < limit) AND (current_reservation != END(Ri)) do

            node_pos = position(FIND_VERTEX(Gi, dest(current_reservation)))

            // found valid match within acceptable distance and which fits in the van
            if ((EUCLIDIAN_DISTANCE(origin, node_pos) < md) AND (occ_capacity + num_people(current_reservation) <= capacity(early_van))) then
                PUSH_BACK(service, current_reservation)
                occ_capacity += num_people(current_reservation)
                REMOVE_ELE(Ri, current_reservation)

                // cant fit more reservations
                if occ_capacity >= capacity(early_van) then
                    break
            else
                current_reservation = NEXT_ELE(Ri)

        // vector of vertices to traverse
        vertices = GET_VERTICES_FROM_SERVICE(service)

        // calculate best path through all the vertices
        // vector of edges
        path = CALCULATE_PATH(vertices)

        departure_time = TARDIEST_RESERVATION_TIME(service)

        // assign deliver time to each reservation
        total_time = 0
        for e ∈ path do
            total_time += weight(e)

            for r ∈ service do
                if assigned(r) then
                    continue

                if dest(r) == id(dest(e)) then
                    SET_DELIVER_TIME(r, departure_time + total_time)
                    assigned(r) = true

        // update next time available of used van
        next_time_available(early_van) = departure_time + total_time

        // add service to van and re-insert it in the multiset
        ADD_SERVICE(early_van, SERVICE(capacity(early_van) - occ_capacity, departure_time, service, path)
        INSERT(Vi, early_van)
            

