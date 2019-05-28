// Gi - graph representing the map
// Ri - sequence of reservations (multiset organized by arrival time)
// Vi - vans to be used (multiset organized by next available time)
// a - airport
// tm - time window to wait for passengers
// md - max distance to be considered when grouping passengers
PLAN_SINGLE_VAN_MIXING_PASSENGERS(Gi, Ri, Vi, a, tm, md):
    
    // use first van available
    van = BEGIN(Vi)

    // must assign all reservations
    while not IS_EMPTY(Ri) do

        // get earliest reservation not already assigned    
        early_res = BEGIN(Ri)
        REMOVE_ELE(Ri, BEGIN(Ri))

        service = ∅
        PUSH_BACK(service, early_res)

        // group earliest client with next reservations
        num_slots = capacity(van) - num_people(early_res)
        aux = BEGIN(Ri)
        while num_slots > 0 AND aux != END(Ri) do
            inTimeWindow = arrival(aux) < arrival(early_res + tm)
            inRange = EUCLIDIAN_DISTANCE(dest(aux), dest(early_res)) < md
            canFit = num_slots >= num_people(aux)

            // no more reservations fit time window
            if not inTimeWindow then
                break

            // valid match
            if inRange AND canFit then
                PUSH_BACK(service, aux)
                num_slots -= num_people(aux)
                REMOVE_ELE(Ri, aux)
            
            // get next reservation
            aux = NEXT_ELE(Ri, aux)

        // calculate best path through all the destinations
        path = CALCULATE_PATH_FROM_SERVICE(Gi, a, service)

        // assign deliver time to each reservation
        departure_time = TARDIEST_RESERVATION_TIME(service)
        total_time = ASSIGN_TIME_OF_DELIVER_TO_RESERVATIONS(path, service, departure_time)

        // update next time available of used van
        next_time_available(early_van) = departure_time + total_time

        // add service to van
        ADD_SERVICE(early_van, SERVICE(num_slots, departure_time, service, path))

    // re-insert van in the multiset
    INSERT(Vi, early_van)

