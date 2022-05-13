function solution(answers) {
    
    let answerOfFirst = [1,2,3,4,5]
    let answerOfSecond = [2,1,2,3,2,4,2,5]
    let answerOfThird = [3,3,1,1,2,2,4,4,5,5]
    
    let countArr = []
    let count = 0
    
    let resultArr = []
    
    for (let i=0; i<answers.length; i++) {
        if (answerOfFirst[i%answerOfFirst.length] === answers[i]) {
            count += 1
        }
    }

    countArr.push(count)
    count = 0
    
    for (let i=0; i<answers.length; i++) {
        if (answerOfSecond[i%answerOfSecond.length] === answers[i]) {
            count += 1
        }
    }

    countArr.push(count)
    count = 0
    
    for (let i=0; i<answers.length; i++) {
        if (answerOfThird[i%answerOfThird.length] === answers[i]) {
            count += 1
        }
    }

    countArr.push(count)
    count = 0
    
    let maxCount = countArr.reduce((acc, cur) => {
        return acc > cur ? acc : cur
    })
    
    for (let i=0; i<3; i++) {
        if (countArr[i] === maxCount) {
            resultArr.push(i+1)
        }
    }
    
    return resultArr
    
}