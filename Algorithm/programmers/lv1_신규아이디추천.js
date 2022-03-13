function solution(new_id) {
    
    let newString = new_id.toLowerCase()
    console.log("6line : ", newString)
    
    newString = newString.replace(/[^\w\.\-]/g, '')
    console.log(newString)
    
    newString = newString.replace(/\.+/g, '.')
    console.log(newString)
    
    newString = newString.replace(/^\.|\.$/g, '')
    console.log(newString)
    
    if (newString.length === 0) {
        newString += 'a'
    }
    console.log(newString)
    
    if (newString.length > 15) {
        newString = newString.substring(0, 15)
        if (newString[14] === '.') {
            newString = newString.slice(0, -1)
        }
    }
    console.log(newString)
    
    while (newString.length < 3) {
        newString += newString[newString.length - 1]
    }
    
    console.log(newString)
    
    return newString;
}
