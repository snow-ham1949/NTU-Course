def DAG_minimum_augmentation_strong_connectivity(graph, indeg, outdeg):
    n = len(graph)
    if n <= 1:
        return []

    found = [0] * n

    def dfs(node):
        if found[node]:
            return
        found[node] = 1
        if outdeg[node] == 0:
            # unmatched sink found
            return node
        for nei in graph[node]:
            ret = dfs(nei)
            if ret is not None:
                # unmatched sink found
                return ret

    matched_sources = []
    matched_sinks = []

    never_matched_sources = []
    never_matched_sinks = []

    for node in range(n):
        if indeg[node] == 0:
            matching_sink = dfs(node)
            if matching_sink is not None:
                matched_sources.append(node)
                matched_sinks.append(matching_sink)
            else:
                never_matched_sources.append(node)

    for node in range(n):
        if outdeg[node] == 0 and not found[node]:
            never_matched_sinks.append(node)

    sources = matched_sources + never_matched_sources
    sinks = matched_sinks + never_matched_sinks

    P = len(matched_sources)
    N = len(sources)
    M = len(sinks)
    K = min(N, M)

    ret = [(0, P - 1)]
    ret += ((i, i - 1) for i in range(1, P))
    ret += ((i, i) for i in range(P, K))
    ret += ((0, i) for i in range(K, N))
    ret += ((i, 0) for i in range(K, M))
    return [(sinks[i], sources[j]) for i, j in ret]
