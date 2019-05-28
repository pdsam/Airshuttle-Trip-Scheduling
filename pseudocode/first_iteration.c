// Gi - graph representing the map
// Ri - sequence of reservations
// v - van to be used
// a - airport
PLAN_SINGLE_VAN_NOT_MIXING_PASSENGERS(Gi, Ri, v):

    CLEAR_SERVICES(v)

    for each r ∈ Ri do
        // Get path to destination and back to airport
        path_edges = GET_PATH_EDGES(Gi, a, dest(r))
        return_path = REVERSE_PATH(path_edges)
        path_edges = JOIN_PATHS(path_edges, return_path)

        // Create and add new service to the van
        // SERVICE(vacant, start_time, reservation, path)
        new_service = SERVICE(van_capacity(v) - num_people(r), LAST_SERVICE_END(v), r, path_edges)
        ADD_SERVICE(v, new_service)

        