function solution(record) {
    let result = [];
    const resultObj = {};
    
    for (let i = 0; i < record.length; ++i) {
        const [statement, uid, nickname] = record[i].split(' ');
        
        if (statement === 'Leave') {
            result.push([uid, '님이 나갔습니다.']);
            
            continue;
        }
        
        if (statement === 'Enter') {
            result.push([uid, '님이 들어왔습니다.']);
        }
        resultObj[uid] = nickname;
    }
    
    return result.map(item => resultObj[item[0]] + item[1]);
}