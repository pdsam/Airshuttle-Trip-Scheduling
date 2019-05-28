// Gi - graph
// s - start vertex
DFS_CONNECTIVITY(Gi, s):
    for each v ∈ vertex_set(Gi) do
        visited(v) = false
    DFS_VISIT(s)

// Gi - graph
// v - current vertex
DFS_VISIT(Gi, v):
    visited(v) = true
    for each e ∈ adj(v) do
        if not visited(dest(e)) then
            DFS_VISIT(dest(e))
