function solution(s) {

    let newString = s
    
    newString = newString.replace(/zero/g, 0)
    newString = newString.replace(/one/g, 1)
    newString = newString.replace(/two/g, 2)
    newString = newString.replace(/three/g, 3)
    newString = newString.replace(/four/g, 4)
    newString = newString.replace(/five/g, 5)
    newString = newString.replace(/six/g, 6)
    newString = newString.replace(/seven/g, 7)
    newString = newString.replace(/eight/g, 8)
    newString = newString.replace(/nine/g, 9)
    
    if (newString[0] === 0) {
        return "첫번 째 글자로는 0이 올 수 없습니다."
    }
    
    return Number(newString);
}