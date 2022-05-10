function solution(numbers, hand) {

    const coordinateArr = [[3,1], [0,0], [0,1], [0,2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2]]
    let leftPosition = [3,0]
    let rightPosition = [3,2]
    let resultStr = ""

    for (let i=0; i<numbers.length; i++) {
        
        if (numbers[i] === 1 || numbers[i] === 4 || numbers[i] === 7) {
            
            leftPosition = coordinateArr[numbers[i]]
            resultStr += "L"
            
        } else if (numbers[i] === 3 || numbers[i] === 6 || numbers[i] === 9) {
            
            rightPosition = coordinateArr[numbers[i]]
            resultStr += "R"
            
        } else if (numbers[i] === 2 || numbers[i] === 5 || numbers[i] === 8 || numbers[i] === 0) {
            
            let leftDist = Math.abs(coordinateArr[numbers[i]][0] - leftPosition[0]) + Math.abs(coordinateArr[numbers[i]][1] - leftPosition[1])
            let rightDist = Math.abs(coordinateArr[numbers[i]][0] - rightPosition[0]) + Math.abs(coordinateArr[numbers[i]][1] - rightPosition[1])

            if (leftDist<rightDist) {

                leftPosition = coordinateArr[numbers[i]]
                resultStr += "L"

            } else if (leftDist>rightDist) {

                rightPosition = coordinateArr[numbers[i]]
                resultStr += "R"

            } else if (leftDist === rightDist) {

                if (hand === "left") {
                    leftPosition = coordinateArr[numbers[i]]
                    resultStr += "L"
                } else if (hand === "right") {
                    rightPosition = coordinateArr[numbers[i]]
                    resultStr += "R"
                }

            }
            
        } 
        
    }
    
    return resultStr
    
}