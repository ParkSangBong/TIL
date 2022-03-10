function solution(participant, completion) {
    
    participant.sort()
    completion.sort()
    
    for (let i=0; i<participant.length; i++) {
        
        if (participant[i] !== completion[i]) {
            return participant[i]
        } else {
            continue
        }
        
    }
    
    var answer = '의도한데로 작동하지 않았거나 찾지 못했습니다.';
    return answer;
}