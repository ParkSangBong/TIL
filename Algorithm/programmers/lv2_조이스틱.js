function solution(name) {
    
    let resultCount = 0
    let resultArr = []
    
    for (let i=0; i<name.length; i++) {
        console.log("ALP: ", name[i], name.charCodeAt(i))
        if (name.charCodeAt(i) - 65 < 14) {
            resultCount += name.charCodeAt(i) - 65
            resultArr.push(name.charCodeAt(i) - 65)
        } else if (name.charCodeAt(i) - 65 >= 14) {
            resultCount += 91 - name.charCodeAt(i)
            resultArr.push(91 - name.charCodeAt(i))
        }
        // TODO - 좌우로 움직이는 로직을 구현해야함.
        resultCount += 1
    }
    
    console.log("rA:", resultArr)
    
    return resultCount-1
    
}