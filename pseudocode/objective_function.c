// Vi - list of vans with services assigned
OBJECTIVE_FUNCTION(Vi):
    total = 0
    for each v ∈ Vi do
        for each s ∈ services(v) do
            for each r ∈ reservations(s) do
                total += (deliver(r) - arrival(r))
    return total