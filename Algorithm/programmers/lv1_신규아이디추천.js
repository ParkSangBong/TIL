function solution(new_id) {
    
    let resultStr = new_id.toLowerCase()
    resultStr = resultStr.replace(/[^\w\-\.]/g, '')
    resultStr = resultStr.replace(/\.+/g, '.')
    resultStr = resultStr.replace(/^\.|\.$/g,'')
    
    if (resultStr.length === 0) {
        resultStr = "a"
    } 

    if (resultStr.length > 15) {
        resultStr = resultStr.slice(0, 15)
        if (resultStr[resultStr.length - 1] === '.') {
            resultStr = resultStr.slice(0, -1)
        }
    }
    
    while (resultStr.length < 3) {
        resultStr = resultStr + resultStr[resultStr.length - 1]
    }

    return resultStr
    
}