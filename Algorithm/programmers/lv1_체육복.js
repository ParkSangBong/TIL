function solution(n, lost, reserve) {
    
    let result = []
    let newReserve = []
    
    //질문하기에서 힌트를 보긴 했지만 내 로직에서 왜 정렬을 해야하지?? 이해가 안된다. 왜 정렬을 했더니 2개의 테스트 케이스가 통과 되었는가. 앞으로 해결해야할것
    //  TODO - 정렬을 했는데 내 로직에서 왜 되는지 확인할 것
    lost.sort((a,b) => a-b)
    reserve.sort((a,b) => a-b)

    for (let i=0; i<reserve.length; i++) {
        if (lost.includes(reserve[i])) {
            let lrIdx = lost.indexOf(reserve[i])
            lost.splice(lrIdx, 1)
        } else {
            newReserve.push(reserve[i])
        }
    }

    for (let i=0; i<lost.length; i++) {
        if (newReserve.includes(lost[i]-1)) {
            result.push(lost[i])
            let splIdx = newReserve.indexOf(lost[i]-1)
            newReserve.splice(splIdx,1)
        } else if (newReserve.includes(lost[i]+1)) {
            result.push(lost[i])
            let splIdx = newReserve.indexOf(lost[i]+1)
            newReserve.splice(splIdx,1)
        } else {
            continue
        }
    }

    return n-lost.length+result.length
}