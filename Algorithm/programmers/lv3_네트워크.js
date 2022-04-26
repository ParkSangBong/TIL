function solution(n, computers) {
    
    let visited = []
    let result = 0
    
    for (let i=0; i<n; i++) {
        visited.push(false)
    }
    
    function dfs(index) {
        visited[index] = true
        
        for (let i=0; i<n; i++) {
            if (index === i) {
                continue
            } else if (computers[index][i] === 1 && visited[i] === false) {
                dfs(i)
            }
        }
        
    }
    
    for (let i=0; i<n; i++) {
        if (!visited[i]) {
            dfs(i)
            result++
        }
    }
    
    return result;
}