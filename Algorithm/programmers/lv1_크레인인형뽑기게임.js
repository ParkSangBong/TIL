function solution(board, moves) {

  let result = []
  let answer = 0
    
  for (let i=0; i<moves.length; i++) {
    for (let j=0; j<board.length; j++) {
      if (board[j][moves[i]-1] !== 0) {
        if (result.length !== 0 && result[result.length - 1] === board[j][moves[i]-1]) {
          result.pop()
          answer += 2
          board[j][moves[i]-1] = 0
          break
        } else {
          result.push(board[j][moves[i]-1])
          board[j][moves[i]-1] = 0
          break
        }
      }
    }
  }
    
  return answer
    
}